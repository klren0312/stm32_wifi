var app = require('http').createServer()
var io = require('socket.io')(app)
var redis = require('redis')
var redisClient = redis.createClient({
    host: 'localhost',
    port: 6379
})

app.listen(5000)


redisClient.on('ready', function() {
    io.on('connection', function(socket) {
        setInterval(function(){
			redisClient.get("hum", function(err, reply) {
                console.log("get tem error:" + err)
                console.log("get the humdata: " + reply)
                socket.emit('news', { reply })
            })
        }, 10000)
    })

})