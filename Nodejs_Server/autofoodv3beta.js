var mysql = require('mysql');
var schedule = require('node-schedule');

var conn = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'root',
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
            theSelect(tem)
        }
    })
})

function theSelect(x) {
    switch (x) {
        case 1:
            flag = 1
            console.info('job ' + ' running at ' + new Date().toLocaleString());
            j = schedule.scheduleJob('12 * * * * * ', function() {
                console.log(1)

            });
            break;
        case 2:
            flag = 2
            console.info('job ' + ' running at ' + new Date().toLocaleString());
            j = schedule.scheduleJob('34 * * * * * ', function() {
                console.log(2)

            });
            break;
        case 3:
            flag = 3
            console.info('job ' + ' running at ' + new Date().toLocaleString());
            j = schedule.scheduleJob('56 * * * * * ', function() {
                console.log(3)

            });
            break;
        default:
            console.log("error");
            break;
    }
}