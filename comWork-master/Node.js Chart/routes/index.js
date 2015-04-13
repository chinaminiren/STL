
/*
 * GET home page.
 */
var url = require('url');
var querystring = require("querystring");

var config = require('../config.json');

var mysql = require('mysql'); //mysql
var superagent = require('superagent');  //http 

var moment = require('moment');//js 时间处理函数

var connection = mysql.createConnection({
    host     : config.connection.host,
    user     : config.connection.user,
    password : config.connection.password,
    database : config.connection.database
});

connection.connect(function (err) {
    if (err) {
        console.log(err.code); // 'ECONNREFUSED'
        console.log(err.fatal); // true
    }
});

//connection.end(); //TODO 需要研究一下

exports.loginPage = function (req, res) //--登录页面
{
    res.render('Login', { title: 'Express', year: new Date().getFullYear() });
}

exports.indexPage = function (req, res) {
    res.render('index', { title: 'Express', year: new Date().getFullYear() });
};

exports.OnlineDataPage = function (req, res) {
    //实时数据 分区  分游戏 还是统一
    res.render('OnlineData', { year: new Date().getFullYear(),title: '实时在线', chartTile: '实时在线', chartSubTile:'', yText:'在线数(单位 个人)',seriesName: '实时曲线' });
};

exports.HistoryDataPage = function (req, res) {
    
    //历史数据 分游戏 还是统一

    res.render('HistoryData', { array: config.GameZone,year: new Date().getFullYear(), title: '历史在线查询', chartTile: '历史在线', chartSubTile: '', yText: '在线数(单位 个人)',seriesName:'历史曲线'});
};

function GetCurTableName() {
    var dt = new Date();
    
    var month = dt.getMonth() + 1;   //parseInt(dt.getMonth().toString()) + 1;
    var monthstr = month < 10 ? '0' + month.toString() :month.toString();
    var tablename = 'GAMEZONEONLINE_' + dt.getFullYear().toString() + monthstr;

    return tablename;
}

exports.RealTimeData = function (req, res) {

    var objectUrl = url.parse(req.url);
    var objectQuery = querystring.parse(objectUrl.query);
    
    //获取当前表中的数据
    var dt = new Date();

    var id = objectQuery['id'];
    if (id == undefined) {
        id = 0;
    }
    var sql = 'SELECT * FROM ' + GetCurTableName() + ' where GameID = ' + id + '  order by DT desc limit 1';

    connection.query(sql, function (err, rows, fields) {
        if (!err) {
            if (rows.length == 1) {
                var time = dt.getTime() - (dt.getTimezoneOffset() * 60 * 1000);
                var array = {
                    dt: time,  //需要转换为UTC 时间
                    num:rows[0].NUM
                };
                res.json(array);
            }
            else {
                res.end('[]\n');
            }
            console.log('access db success ');
        }
        else {
            console.log('Error while performing Query.');
            res.end('[]\n');
        }
    });
    
};

exports.GetHistoryData = function (req, res) {

    var objectUrl = url.parse(req.url);
    var objectQuery = querystring.parse(objectUrl.query);
    var id = objectQuery['id'];
    if (id == undefined) {
        id = 0;
    }
    
    var daynum = objectQuery['day']; //--获取几天的历史数据?
    if (daynum == undefined) {
        daynum = 7;//默认是七天
    }
    
    //var dt = new Date();
    //console.log(dt);
    //var day = dt.getDay() - daynum; //获取最近 天数
    //dt.setDate(day);
    
    //跨月情况 //TODO
    //跨年情况 //TODO
    var now = moment();
    now.add(-daynum, 'day')
    var sqldt = now.format("YYYY-MM-DD");//
    var dt = new Date();
    var sql = 'SELECT * FROM ' + GetCurTableName() + ' where GameID = ' + id + ' and  DT > ' + sqldt + '  order by DT asc';
    
    var array = [];

    connection.query(sql, function (err, rows, fields) {
        if (!err) {
            if (rows.length > 0) {
                
                for (var i = 0; i < rows.length; i++) {
                    var time = rows[i].DT - (dt.getTimezoneOffset() * 60 * 1000);
                    array.push([time, rows[i].NUM]);                  
                }
                res.json(array);
            }
            else {
                res.json(array);
            }
        }
        else {
            console.log('Error while performing Query.');
            res.json(array);
        }
    });
};

var crypto = require('crypto');
//加密
function encrypt(str, secret) {
    var cipher = crypto.createCipher('aes192', secret);
    var enc = cipher.update(str, 'utf8', 'hex');
    enc += cipher.final('hex');
    return enc;
}

function gen_session(user, res) {
    var auth_token = encrypt(user.username + '\t' + user.password, 'session_secret');
    res.cookie('auth_cookie_name', auth_token, { path: '/', maxAge: 20 * 60 * 60 * 1000 }); //cookie 有效期30天
}

exports.logoutAction = function (req, res) {
    req.session.destroy();
    loginPage(req, res);
}



exports.loginAction = function (req, res) {
  
    var user = {
        'username': req.body.username,
        'password': req.body.password
    };
    
    if (user.username == "abc" && user.password == "123") {
        gen_session(user, res); //保存加密账号信息到cookie
        
        req.session.regenerate(function () {//写session。存入username
            req.session.user = user;
            res.end('0');
        });
    }
    else {
        res.end('-1');
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