var net = require('net')
var mysql = require('mysql')
var redis = require('redis')

// 配置数据库
var conn = mysql.createConnection({
    host: 'localhost',
    user: '',
    password: '',
    database: '',
    port: 3306
});
// 连接数据库
conn.connect();

// 连接Redis
var redisClient = redis.createClient({
    host: 'localhost',
    port: 6379
});

net.createServer(function(socket) {
    socket.on('data', function(data) {
        conn.query('SELECT * FROM status',function(err,rows,fields){
    			if (rows[rows.length-1].status == 1) {
    				socket.write("1");
    				// time = new Date().toLocaleString();
    				conn.query('INSERT INTO status SET ?',{"status":"0"},function(error,result,fields){
    					if (error) throw error;
    				})
    			}else{
    				socket.write("0");
    			}
    		})
        // tem hum indoor feng
        var text = JSON.parse(data.toString());
        console.log(text)
        var arr = {}
        arr.tem = text.temperature;
        arr.hum = text.humidity;
        arr.feng = text.Fengshan;
        arr.indoor = text.Yellow_Led;
        conn.query('INSERT INTO pet SET ?', arr, function(error, result, fields) {
            if (error) throw error;
        })
        console.log(arr)
        redisClient.set("tem", arr.tem, function(err, reply) {
            console.log("set tem error:" + err);
        })
        redisClient.expire('tem', 5000); //10秒后到期

        redisClient.set("hum", arr.hum, function(err, reply) {
            console.log("set hum error:" + err);
        })
        redisClient.expire('hum', 5000); //10秒后到期

        redisClient.set("indoor", arr.indoor, function(err, reply) {
            console.log("set indoor error:" + err);
        })
        redisClient.expire('indoor', 5000); //10秒后到期

        redisClient.set("feng", arr.feng, function(err, reply) {
            console.log("set feng error:" + err);
        })
        redisClient.expire('', 5000); //10秒后到期
    })
    socket.on('end', function(data) {
        console.log('end');
    })
    socket.write('ready to receive your msg')
}).listen(4001);
