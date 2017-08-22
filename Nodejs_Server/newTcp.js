var net = require('net')
// var mysql = require('mysql')
var redis = require('redis')

// 配置数据库
// var conn = mysql.createConnection({
// 	host:'localhost',
// 	user:'root',
// 	password:'root',
// 	database:'nodemysql',
// 	port:3306
// });
// 连接数据库
// conn.connect();

// 连接Redis
var redisClient = redis.createClient({
	host:'localhost',
	port:6379
});

net.createServer(function(socket){
	socket.on('data', function(data){
		console.log('got: ', data.toString());
		// tem hum indoor feng 
		var text = JSON.parse(data.toString());
		console.log(text.tem)

		
		redisClient.set("tem", text.tem, function(err, reply){
			console.log("set tem error:" + err);
		})
		redisClient.expire('tem', 50);//10秒后到期

		redisClient.set("hum", text.hum, function(err, reply){
			console.log("set hum error:" + err);
		})
		redisClient.expire('hum', 50);//10秒后到期

		redisClient.set("indoor", text.indoor, function(err, reply){
			console.log("set indoor error:" + err);
		})
		redisClient.expire('indoor', 50);//10秒后到期

		redisClient.set("feng", text.feng, function(err, reply){
			console.log("set feng error:" + err);
		})
		redisClient.expire('', 50);//10秒后到期
	})
	socket.on('end', function(data){
		console.log('end');
	})
	socket.write('ready to receive your msg')
}).listen(4001);