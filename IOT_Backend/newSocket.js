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
        function getData(){
            redisClient.get("hum", function(err, reply) {
              console.log("get hum :" + reply)
              socket.emit('hum', reply)
            })
            redisClient.get("tem",function(err, reply){
              console.log("get tem :"+reply)
              socket.emit('tem', reply)
            })
            redisClient.get("indoor",function(err, reply){
              console.log("get indoor :"+reply)
              socket.emit('indoor', reply)
            })
            redisClient.get("feng",function(err, reply){
              console.log("get feng :"+reply)
              socket.emit('feng', reply)
            })
        }
        setInterval(function(){
          getData()
        }, 10000)
    })

})
