var pg = require('pg');

//数据库配置
// var config = {
// 	user:'postgres',
// 	database:'nodejspg',
// 	password:'root',
//   host:'localhost',
// 	port:'5432',
// }
var conString = "tcp://postgres:root@localhost/nodejspg";
//创建连接池
var client =  new pg.Client(conString);
var tem = 33;
selectSQLString = 'insert into pet(tem) values ('+tem+') ';

//客户端连接
client.connect(function(error, results){
  if (error) {
    console.log('clientConnectionReady Error:'+error.message);
    client.end();
    return;
  }
  console.log('connection success...\n');
  client.query(selectSQLString,function(error,results){
    // console.log(results.rows[0].username);
    console.log(error);
  })
});
// 查询


