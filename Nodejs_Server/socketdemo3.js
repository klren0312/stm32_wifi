var app = require('http').createServer()
var io = require('socket.io')(app)
var net = require('net')

app.listen(5000)


net.createServer(function(so){
	so.on('data',function(data){
		console.log('got:',data.toString());
		var text = JSON.parse(data.toString());
		var tem = parseInt(text.tem)
		console.log(tem)
		io.on('connection', function(socket){ 
			console.log()	 
			socket.emit('news', { hello:'tem' });
			socket.on('my other event', function (data) {
				console.log(data);
   			})
		})
	})
	so.on('end',function(data){
		console.log('end');
	});
	so.write('Ready to receive your message!')
	 
}).listen(4001);


	
		