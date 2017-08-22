var http = require('http'),
	io   = require('socket.io')
var server = http.createServer(function(req,res){
	res.writeHead(200, {'Content-Type':'text/html'});
	res.end('<h1>Hello socket lover!</h1>')	
})

server.listen(8080);
var socket = io.listen(server)
socket.on('connection',function(client){
	client.on('message',function(event){
		console.log('Received message from client!', event);
	});
	client.on('disconnect',function(){
		console.log('server has disconnected')
	})
})