 var mysql = require('mysql') //mysql模块
 var schedule = require('node-schedule');
 // 数据库配置
 var conn = mysql.createConnection({
     host: '119.29.201.31',
     user: 'root',
     password: '123456',
     database: 'nodemysql',
     port: 3306
 });
 //连接数据库
 conn.connect();
 // 初始化全局变量
 var hour, minute, second;

 conn.query("SELECT * FROM autofood ORDER BY  id DESC LIMIT 1", function(err, rows, fields) {
     // console.log(rows[0])
     hour = rows[0].hour
     minute = rows[0].minute
     second = rows[0].second
     scheduleRecurrenceRule(rows[0])
 })

 //定时轮询数据库设置的时间
 var defaulttime = new schedule.RecurrenceRule();
 defaulttime.second = 0;
 schedule.scheduleJob(defaulttime, function() {
     conn.query("SELECT * FROM autofood ORDER BY  id DESC LIMIT 1", function(err, rows, fields) {
         // console.log(rows[0])
         if (hour !== rows[0].hour || minute !== rows[0].minute || second !== rows[0].second) {
             j.cancel()
             hour = rows[0].hour
             minute = rows[0].minute
             second = rows[0].second
             scheduleRecurrenceRule(rows[0])
         } else {
             //do not do sth
             console.log("no change , go on")
         }
     })
 })

 // 定时发送配置
 var j

 function scheduleRecurrenceRule(time) {
     var rule = new schedule.RecurrenceRule();
     rule.hour = time.hour;
     rule.minute = time.minute;
     rule.second = time.second;
     console.log(rule)
     j = schedule.scheduleJob(rule, function() {
         console.log('scheduleRecurrenceRule:' + new Date());
         getData();
     })
 }


 //存入开启命令
 function getData() {
     conn.query('INSERT INTO status SET ?', { "status": 1 }, function(err, rows, fields) {
         if (error) throw error;
     })
 }