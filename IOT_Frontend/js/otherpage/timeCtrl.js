app.controller("timeCtrl", function($scope, $log, $http) {
    var rooturl = "http://119.28.84.27:3000"
    // $scope.checkLogin()
        // var rooturl = "http://localhost:3000"
    if (localStorage.getItem("zzes") == "klren") {
        $scope.showthis = true
    } else {
        $scope.showthis = false
    }
    // 访问喂食接口
    $scope.givefood = function() {
        if ($scope.showthis) {
            var givefoodurl = rooturl + "/buttonclick1"
            $http({
                method: "get",
                url: givefoodurl,
                headers: {
                    "content-type": "application/json"
                }
            }).then(function(req) {

            })
        } else {
            new Notification("错误！", {
                body: "您未被治电授权进行此操作！"
            })
        }
    }

    //喂食定时接口
    $scope.time2feed = function() {
        if ($scope.showthis) {
            var time2feedurl = rooturl + "/foodTime"
            var databody = '{"hour":' + $scope.foodhour + ',"minute":' + $scope.foodminute + ',"second":' + $scope.foodsecond + '}';
            $log.log(databody)
            $http({
                method: "post",
                url: time2feedurl,
                headers: {
                    "content-type": "application/json"
                },
                data: databody
            }).then(function(req) {

            })
        } else {
            new Notification("错误！", {
                body: "您未被治电授权进行此操作！"
            })
        }
    }

    //消息定时接口
    $scope.time2msg = function() {
        if ($scope.showthis) {
            var time2msgurl = rooturl + "/msgtime"
            var databody = '{"hour":' + $scope.hour + ',"minute":' + $scope.minute + ',"second":' + $scope.second + '}';
            $log.log(databody)
            $http({
                method: "post",
                url: time2msgurl,
                headers: {
                    "content-type": "application/json"
                },
                data: databody
            }).then(function(req) {

            })
        } else {
            new Notification("错误！", {
                body: "您未被治电授权进行此操作！"
            })
        }
    }

})