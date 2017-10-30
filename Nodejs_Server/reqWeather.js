var express = require("express")
var request = require("request")

var app = express()

//设置所有路由无限制访问，不需要跨域
app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    res.header("Access-Control-Allow-Methods", "*");
    next();
})

//天气获取
app.get("/getWeather", function(req, res) {

    //短信模板请求参数设置
    var options = {
        url: "http://api.avatardata.cn/Weather/Query?key=4d3644ed982a49339a65b1c5e5943e58&cityname=%E6%BB%81%E5%B7%9E",
        method: 'GET',
        headers: {
            "content-type": "application/json",
        },
        json: true
    }
    request(options, function(error, response, body) {
        if (error) throw new Error(error);
        if (body.resultCode === 200) {
            console.log("send success")
        } else {
            console.log("send fail")
        }
        res.send(body);
    })
})

//端口：3000
var server = app.listen(5438, function() {
    console.log("127.0.0.1:5438");
})