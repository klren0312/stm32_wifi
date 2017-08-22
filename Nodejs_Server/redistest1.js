var redis = require('redis');
var redisClient = redis.createClient({host:'localhost',port:6379});

redisClient.on('ready', function () {
	console.log("Redis is ready");
	// 存入键值对
	redisClient.set("language", "nodejs",function(err,reply){
		console.log("error: "+err);
		console.log("存入反馈："+reply);
	})
	// 根据键读取值
	redisClient.get("language",function(err,reply){
		console.log("error: "+err);
		console.log("读取反馈："+reply);
	});
	// 存取json
	redisClient.hmset("tools", "webserver", "expressjs", "database", "mongoDB", "devops", "jenkins", function(err,reply){
		console.log("error: "+ err);
		console.log("存入json反馈："+reply);
	})
	// 读取json
	redisClient.hgetall("tools", function(err,reply){
		console.log("error: "+err);
		console.log("读取json反馈：")
		console.log(reply);
	})
	// 存储 List对象
	redisClient.rpush(["languages","angularjs","nodejs","go"],function(err,reply){
		console.log("error: "+err);
		console.log("存入List反馈："+reply);
	})
	// 读取Set 对象
	redisClient.sadd(["devopstools","jenkins","codeship","jenkins"],function(err,reply){
		console.log("error："+err);
		console.log("存入Set反馈："+reply);//输出2，是因为Set中的值不唯一
	})
	// 判断键是否存在
	redisClient.exists('language', function(err,reply){
		if(!err){
			if(reply === 1){
				console.log("key exists");
			} else{
				console.log("don't exists");
			}
		}
	})
	// 删除键
	redisClient.del('language', function(err,reply){
		if(!err){
			if (reply === 1) {
				console.log("key is deleted");
			}else{
				console.log("don't exists")
			}
		}
	})
	// 设置键值的到期时间
	redisClient.expire('tools', 30);//30秒后到期
});

redisClient.on('error', function(){
	console.log('error in redis')
})