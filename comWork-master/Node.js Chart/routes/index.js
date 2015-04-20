
/*
 * GET home page.
 */
var url = require('url');
var querystring = require("querystring");
var async = require('async');

var config = require('../config.json');//配置

var mysql = require('mysql'); //mysql
var superagent = require('superagent');  //http 

var moment = require('moment');//js 时间处理函数

var crypto = require('crypto');

var nodeExcel = require('excel-export');

//加密
function encrypt(str, secret) {
    var cipher = crypto.createCipher('aes192', secret);
    var enc = cipher.update(str, 'utf8', 'hex');
    enc += cipher.final('hex');
    return enc;
}

var pool = mysql.createPool({
    connectionLimit : 1,
    host     : config.connection.host,
    user     : config.connection.user,
    password : config.connection.password,
    database : config.connection.database
});

function getRandomString(size) {
    size = size || 6;
    var code_string = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    var max_num = code_string.length + 1;
    var new_pass = '';
    while (size > 0) {
        new_pass += code_string.charAt(Math.floor(Math.random() * max_num));
        size--;
    }
    return new_pass;
};

function loginning(req, res)
{
    var loginEncryptKey = getRandomString(128);
    res.cookie('loginEncryptKey', loginEncryptKey, { path: '/', maxAge: 5 * 60 * 1000 });
    req.session.loginEncryptKey = loginEncryptKey; //sessions 保存20 分钟 //前端 保存 5分钟
    res.render('Login', { title: '系统登录', year: new Date().getFullYear() });
}

exports.loginPage = function (req, res) //--登录页面
{
     loginning(req, res);
}

exports.indexPage = function (req, res) {
    console.log(req.session.user.name);
    res.render('index', { title: '主页', year: new Date().getFullYear(),loginName: req.session.user.username});
};

exports.OnlineDataPage = function (req, res) {
    //实时数据 分区  分游戏 还是统一
    res.render('OnlineData', { gamearray: config.GameZone,year: new Date().getFullYear(),title: '实时在线', chartTile: '实时在线', chartSubTile:'', yText:'在线数(单位 个人)',seriesName: '实时曲线' , loginName: req.session.user.username});
};

exports.HistoryDataPage = function (req, res) {
    
    //历史数据 分游戏 还是统一
    var itemArray = [];
    for (var key in config.GameZone) {
        if (config.GameZone[key].GameID != 0) {
            itemArray.push(config.GameZone[key]);
        }
    }

    res.render('HistoryData', { gamearray: itemArray,year: new Date().getFullYear(), title: '历史在线查询', chartTile: '历史在线', chartSubTile: '', yText: '在线数(单位 个人)',seriesName:'历史曲线', loginName: req.session.user.username});
};

function GetCurTableName() {
    var dt = new Date();
    
    var month = dt.getMonth() + 1;   //parseInt(dt.getMonth().toString()) + 1;
    var monthstr = month < 10 ? '0' + month.toString() :month.toString();
    var tablename = 'GAMEZONEONLINE_' + dt.getFullYear().toString() + monthstr;

    return tablename;
}
function GetSpecificTableName(year, month)
{
    var monthstr = month < 10 ? '0' + month.toString() : month.toString();
    var tablename = 'GAMEZONEONLINE_' + year.toString() + monthstr;
  
    return tablename;
}

function GetFormatDate(date){
    var now = moment(date);
    var sqldt = now.format("YYYY-MM-DD");//
    return sqldt;
}

function GetSqlArray(beginDate, endDate, gameID) { //--设计只能查询 30 天内 的数据 //需要验证间隔天数
       
    var beginYear = beginDate.getFullYear();
    var endYear = endDate.getFullYear();

    var beginMonth = beginDate.getMonth() + 1;
    var endMonth = endDate.getMonth() + 1;
    
    var sqlArray = [];//要执行的sql 语句
    
    var beginTime = beginDate.getTime() / 1000;
    var endTime = endDate.getTime() / 1000;

    if (beginYear == endYear && beginMonth == endMonth) {
        //查询当月数据
        var item = {};
        var sql = 'SELECT * FROM ' + GetSpecificTableName(beginYear, beginMonth) + ' where GAMEID = ' + gameID 
            + ' and  TIMESTAMP >=' + beginTime + '  and TIMESTAMP <=' +endTime+' order by TIMESTAMP asc';
        var table = 'select TABLE_NAME from INFORMATION_SCHEMA.TABLES where TABLE_SCHEMA=\''+config.connection.database+ '\' and TABLE_NAME=\''+GetSpecificTableName(beginYear, beginMonth)+'\'';
        
        //用于判断表是否存在
        item.table = table;
        item.sql = sql;
        sqlArray.push(item);
    }
    else {
        var sqla = 'SELECT * FROM ' + GetSpecificTableName(beginYear, beginMonth) + ' where GAMEID = ' + gameID 
            + ' and  TIMESTAMP >=' + beginTime + '  order by TIMESTAMP asc';
        var tablea = 'select TABLE_NAME from INFORMATION_SCHEMA.TABLES where TABLE_SCHEMA=\'' + config.connection.database + '\' and TABLE_NAME=\'' + GetSpecificTableName(beginYear, beginMonth) + '\'';
        
        var itema = {};
        itema.table = tablea;
        itema.sql = sqla;
        sqlArray.push(itema);
        
        var sqlb = 'SELECT * FROM ' + GetSpecificTableName(endYear, endMonth) + ' where GAMEID = ' + gameID 
            + ' and  TIMESTAMP <=' + endTime + '  order by TIMESTAMP asc';
        var tableb = 'select TABLE_NAME from INFORMATION_SCHEMA.TABLES where TABLE_SCHEMA=\'' + config.connection.database + '\' and TABLE_NAME=\'' + GetSpecificTableName(endYear, endMonth) + '\'';
        
        var itemb = {};
        itemb.table = tableb;
        itemb.sql = sqlb;
        sqlArray.push(itemb);
    }
    
    return sqlArray;
}

function GetData(id, beginDate, endDate, dataCallback,dealCallback) {

    var taskArray = GetSqlArray(beginDate, endDate, id);
    
    //----- define task
    
    var getConnection = function (callback) {
        pool.getConnection(function (err, connection) {
            if (!err) {
                callback(null, connection);
            }
            else {
                callback('数据库连接获取失败', connection);
            }
        });
    };
    
    //---- end one of task
    
    //-- begin task
    async.map(taskArray, function (task, callback) {
        
        async.waterfall(
            [
                getConnection, 

                function (connection, callback) {
                    connection.query(task.table, function (err, rows, fields) { //查询表是否正在
                        if (!err && rows.length > 0) {
                            callback(null, connection);
                        }
                        else {
                            callback('当前查询表不存在', connection); //async.waterfall
                        }
                    });
                }, 

                function (connection, callback) {
                    connection.query(task.sql, function (err, rows, fields) {
                        if (!err) {
                            for (var i = 0; i < rows.length; i++) {
                                dealCallback(rows[i]);//                             
                            }
                        }
                        callback(err, connection); //async.waterfall
                    });
                }
            ], 
            function (err, connection) {
                connection.release(); //发生错误 以及结束都要回调这个....
                if (err) {
                    console.log(err); //因为 async map结果互相不影响
                }
                callback(null, null); // end async map
            }
        );
    }, 
    function (err, results) {
        if (err) {
            console.log(err);
        }
        dataCallback();//获取数据完毕 回调函数
    });
}

exports.GetHistoryData = function (req, res) {

    var result = {
        result : -1, //失败
        data: [],
        showTips:''
    };

    var objectUrl = url.parse(req.url);
    var objectQuery = querystring.parse(objectUrl.query);
    var id = objectQuery['id'];
    if (id == undefined) {
        res.json(result);
        return;
    }
    
    var beginDateTime = objectQuery['beginDateTime']; //--获取几天的历史数据?
    var endDateTime = objectQuery['endDateTime']; //--获取几天的历史数据?
    //检查间隔时间 //TODO    
    
    if ((!beginDateTime) || (!endDateTime)) {
        res.json(result);
        return;
    }

    var beginDate = new Date();
    beginDate.setTime(beginDateTime);

    var endDate = new Date();
    endDate.setTime(endDateTime);

    var taskArray = GetSqlArray(beginDate, endDate, id);

    var dt = new Date();
    
    var dealCallback = function (row) {
                
        var time = row.TIMESTAMP * 1000 - (dt.getTimezoneOffset() * 60 * 1000);
        result.data.push([time, row.ONLINENUM]);
    };
    
    var maxArray = function (array) {
        var max = array[0][1];
        var m = 0;
        var len = array.length;
        for (var i = 1; i < len; i++) {
            if (array[i][1] > max) {
                max = array[i][1];
                m = i;
            }
        }
       return array[m];
    };
    
    var minArray = function (array) {
        var min = array[0][1];
        var m = 0;

        var len = array.length;
        for (var i = 1; i < len; i++) {
            if (array[i][1] < min) {
                min = array[i][1];
                m = i;
            }
        }
        return array[m];
    };

    var dataCallback = function () {
        result.result = 0;
        if (result.data.length > 0) {
            var dt = new Date();
            var max = maxArray(result.data)[1];
            var maxTime = maxArray(result.data)[0] + (dt.getTimezoneOffset() * 60 * 1000);

            var min = minArray(result.data)[1];
            var minTime = minArray(result.data)[0] + (dt.getTimezoneOffset() * 60 * 1000);

            var showTips = '最大：'+moment(maxTime).format("MM/DD hh:mm:ss")  +' : ' + max + ' 最小：' + moment(minTime).format("MM/DD hh:mm:ss") + ' ： ' + min ;
            result.showTips = showTips;
        }

        res.json(result);
    };
    
    GetData(id, beginDate, endDate, dataCallback, dealCallback);

};

exports.RealTimeData = function (req, res) {
    
    var jsonResult = {
        result: -1
    };

    var objectUrl = url.parse(req.url);
    var objectQuery = querystring.parse(objectUrl.query);
    
    //获取当前表中的数据
    var dt = new Date();

    var id = objectQuery['id'];
    if (id == undefined) {
        id = 0;
        res.json(result);
        return;
    }
    
    var table = 'select TABLE_NAME from INFORMATION_SCHEMA.TABLES where TABLE_SCHEMA=\'' + config.connection.database + '\' and TABLE_NAME=\'' + GetCurTableName() + '\'';
    var sql = '';
    if (id > 0) {
       sql = 'SELECT * FROM ' + GetCurTableName() + ' where GAMEID = ' + id + '  order by TIMESTAMP desc limit 1';
    }
    else if(id == 0) {
        sql = 'SELECT tt.GAMEID,tt.TIMESTAMP,tt.ONLINENUM from ' + GetCurTableName() + ' as tt inner join(SELECT GAMEID, MAX(TIMESTAMP)as TIMESTAMP FROM  ' + GetCurTableName() + ''
               + ' GROUP BY GAMEID) maxt ' 
               + ' on(maxt.GAMEID = tt.GAMEID and maxt.TIMESTAMP = tt.TIMESTAMP) ';
    }
    if (sql == '') {
        res.json(result);
        return; //直接返回
    }
    
    var lastCallback = function (err, connection) {
        if (err) {
            console.log('获取实时数据失败：' + err);
        }
        connection.release(); //发生错误 以及结束都要回调这个....
        res.json(jsonResult);
    };
    
    var getConnection = function (callback) {
        pool.getConnection(function (err, connection) {
            if (!err) {
                callback(null, connection);
            }
            else {
                callback('数据库连接获取失败', connection);
            }
        });
    };
    
    var testDbTable = function (connection, callback) {
        connection.query(table, function (err, rows, fields) { //查询表是否正在
            if (!err && rows.length > 0) {
                callback(null, connection);
            }
            else {
                callback('当前查询表不存在', connection);
            }
        });
    };
    
    var getDbData = function (connection, callback) {
        
        connection.query(sql,function (err, rows, fields) {
            if (!err && rows.length > 0) {                                                
                var time = dt.getTime() - (dt.getTimezoneOffset() * 60 * 1000);
                if (id > 0) {
                    //判断数据是否合法 小于当前时间
                    jsonResult.result = 0;
                    jsonResult.dt = time;
                    jsonResult.num = rows[0].ONLINENUM;
                }
                else {
                    //整理最大值
                    var totalNum = 0;
                    for (var i = 0; i < rows.length; i++) {
                        totalNum = totalNum + rows[i].ONLINENUM;
                    } //end for items
                    jsonResult.result = 0;
                    jsonResult.dt = time;
                    jsonResult.num = totalNum;
                }
                
                callback(null, connection); 
            }
            else {
                callback(err, connection); 
            }
        });
    };

    async.waterfall([getConnection, testDbTable, getDbData], lastCallback);
};

function gen_session(user, res) {
    var auth_token = encrypt(user.username + '\t' + user.password, 'session_secret');
    res.cookie('auth_cookie_name', auth_token, { path: '/', maxAge: 20 * 60 * 60 * 1000 }); //cookie 有效期30天
}

exports.logoutAction = function (req, res) {
    
    req.session.regenerate(function () {//写session。存入username

        var loginEncryptKey = getRandomString(128);
        res.cookie('loginEncryptKey', loginEncryptKey, { path: '/', maxAge: 5 * 60 * 1000 });
        req.session.loginEncryptKey = loginEncryptKey; //sessions 保存20 分钟 //前端 保存 5分钟

        res.render('Login', { title: '登录', year: new Date().getFullYear() });
    });
}


function loginFail(req, res){
    var loginEncryptKey = getRandomString(128);
    req.session.loginEncryptKey = loginEncryptKey; //sessions 保存20 分钟 //前端 保存 5分钟
    res.cookie('loginEncryptKey', loginEncryptKey, { path: '/', maxAge: 5 * 60 * 1000 });
    res.end('-1');
}

exports.loginAction = function (req, res) {
  
    var user = {
        'username': req.body.username,
        'password': req.body.password
    };
    var loginEncryptKey = req.session.loginEncryptKey;
    if (loginEncryptKey) {
        if (user.username == "abc" && user.password == "123") {
            gen_session(user, res); //保存加密账号信息到cookie
            
            req.session.regenerate(function () {//写session。存入username
                req.session.user = user;
                res.end('0');
            });
        }
        else {
            loginFail(req, res);
        }
    }
    else {
        loginFail(req, res);
    }
   
    /*
    superagent.get(config.LoginUrlApi) 
   .query({ username: user.username })
   .query({ password: user.password })
   .end(function (error, loginres) {
        if (error) {
            res.end('-1'); //登录失败
        }
        else if (loginres.text == '0') {
            gen_session(user, res); //保存加密账号信息到cookie
            
            req.session.regenerate(function () {//写session。存入username
                // Store the user's primary key
                // in the session store to be retrieved,
                // or in this case the entire user object
                req.session.user = user;
                res.end('0');
            });
        }
        else {
            res.end('-1'); //登录失败
        }
       
    });
     */
};

//--修改密码
exports.ChangePasswd = function (req, res) {

    var password = req.body.newpasswd;  //--新密码
    var password = req.body.oldpasswd; //--旧密码
    
    if (password != req.session.user.password) {
        res.end('-1'); //修改失败
    }
    else {
        superagent.get(config.ChangePasswd)
        .query({ password: password })//-- 支持者 url get方式 不加密...我没有没有办法
        .end(function (error, results) {
            if (error) {
                res.end('-1'); //登录失败
            }
            else if (results.text == '0') {
                req.session.user.password = password;
                res.end('0');
            }
            else {
                res.end('-1'); //修改失败
            }
       
        });
    }   
}

exports.DownExcelData = function (req, res) {
    
    var objectUrl = url.parse(req.url);
    var objectQuery = querystring.parse(objectUrl.query);
    
    //获取当前表中的数据
    var dt = new Date();
    
    var beginDateTime = objectQuery['beginDate'];
    var endDateTime = objectQuery['endDate'];
    var id = objectQuery['gameID'];
    
    if (!beginDateTime || !endDateTime || !id) {
        res.json('传参数错误');
        return;
    }
    
    var beginDate = new Date();
    beginDate.setTime(beginDateTime);
    
    var endDate = new Date();
    endDate.setTime(endDateTime);
    
    //--begin define config
    var conf = {};
    conf.stylesXmlFile = "styles.xml";
    conf.cols = [{
            caption: '区域',
            type: 'string'
        }, {
            caption: '时间',
            type: 'string'
        }, {
            caption: '在线人数',
            type: 'number'
        }];
    //--end xlsx config 
    
    conf.rows = [];

    var gameName = "";
    for (var i = 0; i < config.GameZone.length; i++) {
        if (config.GameZone[i].GameID == id) {
            gameName = config.GameZone[i].GameName;
            break;
        }
    }

    var dealCallback = function (row) {

        var time = row.TIMESTAMP * 1000;// - (dt.getTimezoneOffset() * 60 * 1000);
        var cdate = new Date();
        cdate.setTime(time);
        var now = moment(cdate);
        var dtStr = now.format("YYYY-MM-DD hh:mm:ss");//

        conf.rows.push([gameName, dtStr, row.ONLINENUM]); 
    };
   

    var dataCallback = function () {
        
        //sort
        conf.rows.sort(function (a, b) {
            var dta = (new Date(a[1])).getTime();
            var dtb = (new Date(b[1])).getTime();
            return dta > dtb?-1:1;
        });
               
        var result = nodeExcel.execute(conf);
        res.setHeader('Content-Type', 'application/vnd.openxmlformats');
        res.setHeader("Content-Disposition", "attachment; filename=" + "OnlineData.xlsx");
        res.end(result, 'binary');
    };

    GetData(id, beginDate, endDate, dataCallback, dealCallback);
}