app.controller("historydataCtrl", function($scope, $http, $log) {
    var rooturl = "http://119.28.84.27:3000"
    // $scope.checkLogin()
    var map = new AMap.Map('mapcontainer', {
        resizeEnable: true,
        zoom: 30,
        center: [118.310948, 32.274839]
    });
    marker = new AMap.Marker({
        icon: "http://webapi.amap.com/theme/v1.3/markers/n/mark_b.png",
        position: [118.310948, 32.274839]
    });
    marker.setMap(map);

    //请求所有数据
    var alldataUrl = rooturl + "/alldata"
    $http({
        method: "get",
        url: alldataUrl,
        headers: {
            "content-type": "application/json"
        }
    }).then(function(req) {
        $scope.alldatas = req.data
            // 设置分页相关数据
        $scope.setPage($scope.alldatas)
    })

    //请求数据的平均值
    var avgdataUrl = rooturl + "/avgdata"
    $http({
        method: "get",
        url: avgdataUrl,
        headers: {
            "content-type": "application/json"
        }
    }).then(function(req) {
        $log.log(req)
        $scope.temavg = req.data.temavg
        $scope.humavg = req.data.humavg
    })

    //请求喂食次数
    var eattimesUrl = rooturl + "/eattimes"
    $http({
        method: "get",
        url: eattimesUrl,
        headers: {
            "content-type": "application/json"
        }
    }).then(function(req) {
        $scope.eattimes = req.data.eattimes
    })

    //更新离屋数据
    $http({
        method: "get",
        url: rooturl + "/update"
    }).then(function(req) {

    })

    //离屋分析
    $http({
        method: "get",
        url: rooturl + "/getIndoorAnalysis",
        headers: {
            "content-type": "application/json"
        }
    }).then(function(req) {
        $log.log(req.data[0])
        $scope.data = req.data[0]

        // $scope.d08 = req.data[0].d08
        // $scope.d912 = req.data[0].d912
        // $scope.d1318 = req.data[0].d1318
        // $scope.d1923 = req.data[0].d1923
    })


})