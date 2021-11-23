app.config(function($stateProvider, $urlRouterProvider) {
    $stateProvider
    //主页路由
        .state("index", {
        url: '/',
        templateUrl: "home.html"
    })

    //实时数据路由
    .state("real", {
        url: '/real',
        templateUrl: "realdata.html"
    })

    //历史数据路由
    .state("history", {
        url: '/history',
        templateUrl: "historydata.html"
    })

    //定时路由
    .state("time", {
        url: '/time',
        templateUrl: "time.html"
    })

    //api测试页面路由
    .state("apiTest", {
        url: '/apiTest',
        templateUrl: "apiTest.html"
    })

    $urlRouterProvider.otherwise('/');
})