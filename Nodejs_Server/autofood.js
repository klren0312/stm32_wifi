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

conn.query('select * from autofood',function(err,rows,fields){
	var i = rows.length;
	var tem = rows[i-1].type;
	console.log(tem);
	switch(tem){
		case 1:
			console.log("type1");
			var j =schedule.scheduleJob('12 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			break;
		case 2:
			console.log("type2");
			var j =schedule.scheduleJob('9 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			var k =schedule.scheduleJob('15 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			break;
		case 3:
			console.log("type3");
			var j =schedule.scheduleJob('8 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			var k =schedule.scheduleJob('12 * * * *',function(){
				var post = {status:1};
				conn.query('INSERT INTO status SET ?', post ,function(error,result,fields){
					if(error) throw error;
				});
			});
			var l =schedule.scheduleJob('18 * * * *',function(){
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
})