var mysql = require('mysql');
var schedule = require('node-schedule');

var conn = mysql.createConnection({
	host:'localhost',
	user:'root',
	password:'root',
	database:'nodemysql',
	port:3306
});

conn.connect();

function change(x){
	switch(x){
		case 1:
			console.log("type1");
			var j =schedule.scheduleJob('feed','12 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			break;
		case 2:
			console.log("type2");
			var j =schedule.scheduleJob('feed','9 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			var k =schedule.scheduleJob('feed','15 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			break;
		case 3:
			console.log("type3");
			var j =schedule.scheduleJob('feed','8 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			var k =schedule.scheduleJob('feed','12 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			var l =schedule.scheduleJob('feed','18 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			break;
		default:
			console.log("error");
			break;
	}
}

function check(x){
	conn.query('select * from autofood', function(err,rows,fields){
				let len = rows.length;
				let tem = rows[len-1].type;
				if (tem !== x) {
					if (schedule.scheduledJobs['feed']) {
						var result = schedule.cancelJob('feed');
						console.log("关闭当前定时: ")
						console.log(result)
					}
					big()
				}else{
					console.log("same")
				}
			})
}
 

function big(){
	conn.query('select * from autofood',function(err,rows,fields){
		var i = rows.length;
		var tem = rows[i-1].type;
		console.log(tem);
		change(tem)
		console.log(schedule.scheduledJobs)
		setInterval(function(){
			check(tem)
		},3000)
	})
}

big();
