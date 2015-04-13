
/**
 * Module dependencies.
 */

var express = require('express');
// 首先引入 express-session 这个模块
var session = require('express-session');
var favicon = require('serve-favicon');
var logger = require('morgan');
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var cookieParser = require('cookie-parser')

var routes = require('./routes');
var http = require('http');
var path = require('path');
var url = require("url");

var config = require('./config.json');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.set('view options', { compileDebug: true });
app.set('view options', { pretty: true });
//app.use(express.favicon());
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());


app.use(session({
    secret: config.secret, // 建议使用 128 个字符的随机字符串
    cookie: { maxAge: 20 * 60* 1000 },
    resave: false,
    saveUninitialized: true, 
}));
//app.use(express.methodOverride());
//app.use(require('stylus').middleware(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, 'public')));


// development only
if ('development' == app.get('env')) {
    app.use(errorHandler());
}

//每次登陆 都会有session 信息 --TODO 应该优化掉 登录成功才有session
app.get('/LoginPage', routes.loginPage); //登录页面
app.post('/loginAction', routes.loginAction); //用户密码登录
app.get('/logoutAction', routes.logoutAction); //用户注销

app.use(require('./control/site').auth_user); // 添加这个中间件，用来解析cookie

app.get('/IndexPage', routes.indexPage); //主页

app.get('/HistoryDataPage', routes.HistoryDataPage);
app.get('/OnlineDataPage', routes.OnlineDataPage);

app.get('/RealTimeData', routes.RealTimeData);
app.get('/GetHistoryData', routes.GetHistoryData);

http.createServer(app).listen(config.port, function () {
    console.log('Express server listening on port ' + config.port);
});
