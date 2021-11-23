app.controller("realdataCtrl", function($scope, $log, $http) {
    // $scope.checkLogin()
    var socket = io('http://119.28.84.27:5000')
    socket.on('indoor', function(data) {
        console.log("indoor:" + data)

        if (data == 0) {
            $(".doorimg").removeClass("imgactive")
            $("#outimg").addClass("imgactive")
        } else {
            $(".doorimg").removeClass("imgactive")
            $("#inimg").addClass("imgactive")
        }
    })
    socket.on('feng', function(data) {
        console.log("feng:" + data)

        if (data == 1) {
            $(".fengimg").removeClass("imgactive")
            $("#fengoff").addClass("imgactive")
        } else {
            $(".fengimg").removeClass("imgactive")
            $("#fengon").addClass("imgactive")
        }
    })
})