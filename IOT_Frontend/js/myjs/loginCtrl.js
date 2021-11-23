loginApp.controller("loginCtrl", function($scope, $http, $log) {
    $scope.logindiv = true;
    $scope.registerdiv =false;
    $scope.login = function() {
        var databody = '{"username":"' + $scope.username + '","password":"' + $scope.password + '"}'
        $http({
            method: "post",
            url: "http://localhost:3456/login",
            headers: {
                "content-type": "application/json"
            },
            data: databody
        }).then(function(req) {
            $log.log(req.data)
            if (req.data.resultCode === 200) {

            }
        })
    }
    $scope.register = function(){
        var databody = '{"username":"' + $scope.regusername + '","password":"' + $scope.regpassword + '"}'
        $http({
            method: "post",
            url: "http://localhost:3456/register",
            headers: {
                "content-type": "application/json"
            },
            data: databody
        }).then(function(req) {
            $log.log(req.data)
            if (req.data.resultCode === 200) {

            }
        })
    }
    // $scope.getAuthCode = function() {
    //     var databody = '{"phone":' + $scope.phone + '}'
    //     $http({
    //         method: "post",
    //         url: 'http://119.29.201.31:3250/sendAuthMsg',
    //         headers: {
    //             "content-type": "application/json"
    //         },
    //         data: databody
    //     }).then(function(req) {
    //         $log.log(req.data)

    //         /**
    //          * 
    //          *  "messageId": "22ea8ff32e444971bf34062f5962bf3e",
    //          *  "resultCode": 200,
    //          *  "resultMsg": "response success"
    //          */
    //         if (req.data.resultCode === 200) {
    //             $scope.megId = req.data.messageId
    //             $("#authCodeBtn").attr('disabled', "true");
    //             $("#authCodeBtn").css("background", "#d4d4d4")
    //             setInterval(function() {
    //                 $("#authCodeBtn").removeAttr("disabled");
    //                 $("#authCodeBtn").css("background", "#C1272D")
    //             }, 100000)
    //         }

    //     })
    // }
    // $scope.login = function() {
    //     var databody = '{"id":"' + $scope.megId + '","phone":' + $scope.phone + ',"code":"' + $scope.authcode + '"}'
    //     $http({
    //         method: "post",
    //         url: "http://119.29.201.31:3250/authCode",
    //         headers: {
    //             "content-type": "application/json"
    //         },
    //         data: databody
    //     }).then(function(req) {
    //         $log.log(req.data)
    //         if (req.data.resultCode === 200) {
    //             window.location.href = 'index.html#!/home';
    //             localStorage.setItem("access", $scope.phone)
    //             localStorage.setItem("zzes", "klren")
    //         }
    //     })
    // }
})