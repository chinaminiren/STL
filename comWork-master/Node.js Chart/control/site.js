
var crypto = require('crypto');
//加密
function encrypt(str, secret) {
    var cipher = crypto.createCipher('aes192', secret);
    var enc = cipher.update(str, 'utf8', 'hex');
    enc += cipher.final('hex');
    return enc;
}
//解密
function decrypt(str, secret) {
    var decipher = crypto.createDecipher('aes192', secret);
    var dec = decipher.update(str, 'hex', 'utf8');
    dec += decipher.final('utf8');
    return dec;
}
/*session无效验证*/
function noSession(req, res) {
    if (!req.session || !req.session.user) {
        res.redirect('LoginPage'); //--登录页面
        return;
    }
}

exports.auth_user = function (req, res, next) {
    if (!req.session.user) {
        noSession(req,res);//若没有session，直接跳过此中间件
    } else {
        var cookie = req.cookies['auth_cookie_name'];//读cookie，通过配置文件中标识符读cookie //config.auth_cookie_name
        if (!cookie) {
            noSession(req, res);//
        }
        else {
            //验证用户 信息
            var auth_token = decrypt(cookie, 'session_secret');//解密操作 //config.session_secret
            var auth = auth_token.split('\t');
            var user = auth[0], passwd = auth[1];//解密后拿到username与password
            var data = {
                name: user,
                password: passwd,
            }
            //session 中密码 或者 验证账号服务器
            if (data.name == req.session.user.username && data.password == req.session.user.password) {
                return next();//进行下一步
            }
            else {
                noSession(req, res);
            }
        }
    }
};

//用户登录参考:https://gist.github.com/guanbo/3747843