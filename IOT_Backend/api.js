var express = require('express');
var mysql = require('mysql');
var bodyParser = require("body-parser");
var json2csv = require('json2csv')
app = express();
app.use('/static', express.static('public'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
//数据库配置
var conn = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '123456',
    database: 'nodemysql',
    port: 3306
});
//连接数据库
conn.connect();

//设置所有路由无限制访问，不需要跨域
app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    res.header("Access-Control-Allow-Methods", "*");
    next();
})

//获取统计后的离家数据
app.get('/getIndoorAnalysis', function(req, res) {
    conn.query("SELECT *  FROM analysis", function(error, result, fields) {
        if (error) throw error;
        res.send(result)
    });
})

//统计离家频率接口
//!怕不怕！
app.get('/update', function(req, res) {
    conn.query("SELECT SUM(indoor) as d08 FROM pet WHERE DATE_FORMAT(time,'%T')>='0' and DATE_FORMAT(time,'%T')<='8' ", function(error, result, fields) {
        if (error) throw error;
        var post = {}
        post.d08 = result[0].d08
        conn.query('UPDATE analysis SET ? WHERE type = "indoor"', post, function(error, result, field) {
            if (error) throw error;
        })
    });
    conn.query("SELECT SUM(indoor) as d912 FROM pet WHERE DATE_FORMAT(time,'%T')>='9' and DATE_FORMAT(time,'%T')<='12' ", function(error, result, fields) {
        if (error) throw error;
        var post = {}
        post.d912 = result[0].d912
        conn.query('UPDATE analysis SET ? WHERE type = "indoor"', post, function(error, result, field) {
            if (error) throw error;
        })
    });
    conn.query("SELECT SUM(indoor) as d1318 FROM pet WHERE DATE_FORMAT(time,'%T')>='13' and DATE_FORMAT(time,'%T')<='18' ", function(error, result, fields) {
        if (error) throw error;
        var post = {}
        post.d1318 = result[0].d1318
        conn.query('UPDATE analysis SET ? WHERE type = "indoor"', post, function(error, result, field) {
            if (error) throw error;
        })
    });
    conn.query("SELECT SUM(indoor) as d1923 FROM pet WHERE DATE_FORMAT(time,'%T')>='19' and DATE_FORMAT(time,'%T')<='23' ", function(error, result, fields) {
        if (error) throw error;
        var post = {}
        post.d1923 = result[0].d1923
        conn.query('UPDATE analysis SET ? WHERE type = "indoor"', post, function(error, result, field) {
            if (error) throw error;
        })
    });
    res.send('{"result":"ok"}')
})

//获取统计后的离家数据
app.get('/getIndoorAnalysis', function(req, res) {
    conn.query("SELECT *  FROM analysis", function(error, result, fields) {
        if (error) throw error;
        res.send(result)
    });
})

// 定时喂食接口
app.post('/foodTime', function(req, res) {
    // console.log(req.body)
    console.log("小时：" + req.body.hour + ",分钟：" + req.body.minute + "，秒：" + req.body.second)
    var time = {}
    time.hour = req.body.hour
    time.minute = req.body.minute
    time.second = req.body.second
    conn.query('INSERT INTO autofood SET ?', time, function(error, result, fields) {
        if (error) throw error;
    });
    res.send('{"statusCode":200}')
})

// 定时通知接口
app.post('/msgtime', function(req, res) {
    // console.log(req.body)
    console.log("小时：" + req.body.hour + ",分钟：" + req.body.minute + "，秒：" + req.body.second)
    var time = {}
    time.hour = req.body.hour
    time.minute = req.body.minute
    time.second = req.body.second
    conn.query('INSERT INTO thetime SET ?', time, function(error, result, fields) {
        if (error) throw error;
    });
    res.send('{"statusCode":200}')
})

//喂食统计接口
app.get('/eattimes', function(req, res) {
    conn.query('SELECT SUM(status) as sum FROM status', function(error, result, field) {
        res.send('{"eattimes":' + result[0].sum + '}')
    })
})

//所有数据接口
app.get('/alldata', function(req, res) {
    conn.query("SELECT * FROM pet ORDER BY id DESC LIMIT 200", function(err, rows, fields) {
        res.send(rows)
    })
})

//导出所有数据为csv
app.get('/exportAllData', function(req, res) {
    conn.query("SELECT * FROM pet ORDER BY id DESC LIMIT 200", function(err, rows, fields) {
        var fields = ['tem', 'hum', 'indoor', 'feng', 'time']
            // 设置 header 使浏览器下载文件
        res.setHeader('Content-Description', 'File Transfer');
        res.setHeader('Content-Type', 'application/csv; charset=utf-8');
        res.setHeader('Content-Disposition', 'attachment; filename=data.csv');
        res.setHeader('Expires', '0');
        res.setHeader('Cache-Control', 'must-revalidate');
        json2csv({
            data: rows,
            fields: fields,
        }, function(err, csv) {
            if (err) {
                console.log(err)
            }
            // 为了让 Windows 能识别 utf-8，加上了 dom
            res.send('\uFEFF' + csv)
        })
    })
})

//温度平均值
app.get('/avgdata', function(req, res) {
    conn.query("SELECT AVG(tem) as temavg, AVG(hum) as humavg FROM pet ORDER BY id DESC LIMIT 200", function(err, rows, fields) {
        res.send('{"temavg":' + rows[0].temavg + ',"humavg":' + rows[0].humavg + '}')
    })
})

//定时接口
// app.post('/times', function(req, res) {
//     console.log(req.body.times)
//     if (req.body.times == 1 || req.body.times == 2 || req.body.times == 3) {
//         var post = {}
//         post.type = req.body.times
//         conn.query('INSERT INTO autofood SET ?', post, function(error, result, fields) {
//             if (error) throw error;
//         });
//         res.send("ok");
//     } else {
//         res.send('{"retResult":"error"}')
//     }
// })

//温度
app.get('/tem', function(req, res) {
    var tem = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var i = rows.length;
        var j = i - 5;
        var c = 0;
        while (j < i) {
            tem[c] = rows[j].tem;
            c++;
            j++;
        }

        res.send(JSON.stringify(tem));
    })
})

//湿度
app.get('/hum', function(req, res) {
    var hum = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var i = rows.length;
        var j = i - 5;
        var c = 0;
        while (j < i) {
            hum[c] = rows[j].hum;
            c++;
            j++;
        }
        res.send(JSON.stringify(hum));
    })
})

//宠物室内室外
app.get('/indoor', function(req, res) {
    var indoor = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var i = rows.length;
        var j = i - 5;
        var c = 0;
        while (j < i) {
            indoor[c] = rows[j].indoor;
            c++;
            j++;
        }
        res.send(JSON.stringify(indoor));
    })

})

//宠物门
app.get('/door', function(req, res) {
    var door = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var i = rows.length;
        var j = i - 5;
        var c = 0;
        while (j < i) {
            door[c] = rows[j].door;
            c++;
            j++;
        }
        res.send(JSON.stringify(door));
    })
})

//宠物屋风扇
app.get('/feng', function(req, res) {
    var feng = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var i = rows.length;
        var j = i - 5;
        var c = 0;
        while (j < i) {
            feng[c] = rows[j].feng;
            c++;
            j++;
        }
        res.send(JSON.stringify(feng));
    })

})

//时间推送
app.get('/time', function(req, res) {
    var time = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var i = rows.length;
        var j = i - 5;
        var c = 0;
        while (j < i) {
            var timeorigin = rows[j].time;
            time[c] = new Date(timeorigin).toLocaleTimeString();
            c++;
            j++;
        }

        res.send(JSON.stringify(time));
    })
})

//手表推送
app.get('/watch', function(req, res) {
    var tem = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var indoor;
        if (rows[rows.length - 1].indoor == 1) {
            indoor = "在";
        } else {
            indoor = "不";
        }

        var tem = "{ \"temhum\" :" + "\"" + rows[rows.length - 1].tem + " " + indoor +
            " " + rows[rows.length - 1].hum + "\"" + "}";
        res.send(tem);
    })
})

//new 手表推送
app.get('/newwatch', function(req, res) {
    var data = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        var indoor = "";
        if (rows[rows.length - 1].indoor == 1) {
            indoor = "在"
        } else {
            indoor = "不在"
        }

        data = "{ \"tem\":" + rows[rows.length - 1].tem + ",\"hum\":" + rows[rows.length - 1].hum + ",\"indoor\":" + "\"" + indoor + "\" }"
        res.send(data);
    })
})

//按钮api
app.get('/buttonclick1', function(req, res) {
    //增加
    var post = { status: 1 };
    conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
        if (error) throw error;
    });
    res.send("1");

    res.end(); // 如果不执行end(), 那么前端网页则会一直等待response
})
app.get('/buttonclick0', function(req, res) {
    //增加
    var post = { status: 0 };
    conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
        if (error) throw error;
    });
    res.send("0");

    res.end(); // 如果不执行end(), 那么前端网页则会一直等待response
})


//树莓派HomeKit接口
app.get('/homekit', function(req, res) {
    var data = [];
    conn.query('SELECT * FROM pet', function(err, rows, fields) {
        data = "{ \"temperature\":" + rows[rows.length - 1].tem + ",\"humidity\":" + rows[rows.length - 1].hum +"}"
        res.send(data);
    })
})


//端口：3000
var server = app.listen(3000, function() {
    console.log("127.0.0.1:3000");
})