var mysql = require('mysql');
var schedule = require('node-schedule');

var conn = mysql.createConnection({
    host: '119.29.201.31',
    user: 'root',
    password: '123456',
    database: 'nodemysql',
    port: 3306
});

conn.connect();
var flag, j, k, l

conn.query('select * from autofood', function(err, rows, fields) {
    var i = rows.length;
    var tem = rows[i - 1].type;
    console.log(tem);
    theSelect(tem)
})

var c = schedule.scheduleJob('40 * * * * *', function() {
    conn.query('select * from autofood', function(err, rows, fields) {
        var i = rows.length;
        var tem = rows[i - 1].type;
        console.log("flag:" + flag);
        if (tem !== flag) {
            // theCancel(flag)
            j.cancel()

            // k.cancel()
            // l.cancel()
            theSelect(tem)
        }
    })
})

function theSelect(x) {
    switch (x) {
        case 1:
            flag = 1
            console.log("type1");
            j = schedule.scheduleJob('12 * * * ', function() {
                var post = { status: 1 };
                conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
                    if (error) throw error;
                });
            });
            break;
        case 2:
            flag = 2
            console.log("type2");
            j = schedule.scheduleJob('9 * * * ', function() {
                var post = { status: 1 };
                conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
                    if (error) throw error;
                });
            });
            k = schedule.scheduleJob('15 * * * ', function() {
                var post = { status: 1 };
                conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
                    if (error) throw error;
                });
            });
            break;
        case 3:
            flag = 3
            console.log("type3");
            j = schedule.scheduleJob('8 * * * ', function() {
                var post = { status: 1 };
                conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
                    if (error) throw error;
                });
            });
            k = schedule.scheduleJob('12 * * *', function() {
                var post = { status: 1 };
                conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
                    if (error) throw error;
                });
            });
            l = schedule.scheduleJob('18 * * * ', function() {
                var post = { status: 1 };
                conn.query('INSERT INTO status SET ?', post, function(error, result, fields) {
                    if (error) throw error;
                });
            });
            break;
        default:
            console.log("error");
            break;
    }
}