app.controller("indexCtrl", function($state, $scope, $http, $log) {
    //申请通知权限
    Notification.requestPermission()

    /**
     * 判断是否登陆
     */
    // $scope.checkLogin = function() {
    //     if (localStorage.getItem("access")) {
    //         console.log("welcome")
    //     } else {
    //         alert("请登录！0.0")
    //         window.location.href = 'login.html'
    //     }
    // }

    /**
     * 分页函数
     * 传入数据数组
     */
    $scope.setPage = function(databody) {
        $scope.pageSize = 6;
        $scope.pages = Math.ceil(databody.length / $scope.pageSize); //分页数
        $scope.newPages = $scope.pages > $scope.pageSize ? $scope.pageSize : $scope.pages;
        $scope.pageList = [];
        $scope.selPage = 1;
        // 设置表格数据源
        $scope.setData = function() {
            // 通过当前页数筛选出表格当前显示数据
            $scope.items = databody.slice(($scope.pageSize * ($scope.selPage - 1)), ($scope.selPage * $scope.pageSize))
        }
        $scope.items = databody.slice(0, $scope.pageSize);
        // 分页数组
        for (var i = 0; i < $scope.newPages; i++) {
            $scope.pageList.push(i + 1);
        }
        // 打印当前选中页的索引
        $scope.selectPage = function(page) {
            // 不能小于1，大于最大值
            if (page < 1 || page > $scope.pages) return;
            // 最多显示5个分页
            if (page > 2) {
                // 因为只显示5个页数，大于2页开始分页转换
                var newPageList = [];
                for (var i = (page - 3); i < ((page + 2) > $scope.pages ? $scope.pages : (page + 2)); i++) {
                    newPageList.push(i + 1);
                }
                $scope.pageList = newPageList;
            }
            $scope.selPage = page;
            $scope.setData();
            $scope.isActivePage(page);
            // $log.log("选择的页：" + page);
        };
        // 设置选中页样式
        $scope.isActivePage = function(page) {
            return $scope.selPage == page;
        };
        // 上一页点击事件
        $scope.Previous = function() {
                $scope.selectPage($scope.selPage - 1);
            }
            // 下一页点击事件
        $scope.Next = function() {
            $scope.selectPage($scope.selPage + 1);
        }
    }
})