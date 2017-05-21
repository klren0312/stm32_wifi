var pg = require('pg');
var net = require('net');

var conString = "tcp://postgres:root@localhost/nodejspg";
var client = new pg.Client(conString);

// client.connect();
net.createServer(function(socket){
	socket.on('data',function(data){
		var text = JSON.parse(data.toString());
		console.log(text);
		var arr = [];

		arr[0] = text.tem.toString();
		arr[1] = text.hum.toString();
		arr[2] = text.indoor.toString();
		arr[3] = text.door.toString();
		arr[4] = text.feng.toString();
		// arr[5] = new Date().toLocaleString();
		console.log(arr);
		var sql = "INSERT INTO pet(tem,hum,indoor,door,feng) VALUES ("+arr[0]+","+arr[1]+","+arr[2]+","+arr[3]+","+arr[4]+")";
		//客户端连接
		client.connect(function(error, results){
		  if (error) {
		    console.log('clientConnectionReady Error:'+error.message);
		    client.end();
		    return;
		  }
		  client.query(sql,function(error,results){
		    // console.log(results.rows[0].username);
		    if (error) {
		    	console.log(error);	
		    }
		  })
		});

	});
	socket.on('end',function(data){
		console.log('end');
	});

}).listen(4001);
