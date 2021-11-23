 app.directive('indoorAnalysis', function() {
     return {
         scope: {
             id: "@",
             data: "="
         },
         restrict: 'E',
         template: '<div class="real-data-charts"></div>',
         replace: true,
         link: function($scope, element, attrs, controller, $http) {
             console.log($scope.d08)
             var option = {
                 backgroundColor: '#2c343c',

                 title: {
                     text: '爱宠离屋分析',
                     left: 'center',
                     top: 20,
                     textStyle: {
                         color: '#ccc'
                     }
                 },

                 tooltip: {
                     trigger: 'item',
                     formatter: "{a} <br/>{b} : {c} ({d}%)"
                 },

                 visualMap: {
                     show: false,
                     min: 80,
                     max: 600,
                     inRange: {
                         colorLightness: [0, 1]
                     }
                 },
                 series: [{
                     name: '在屋内时段',
                     type: 'pie',
                     radius: '55%',
                     center: ['50%', '50%'],
                     data: [
                         { value: $scope.data.d08, name: '0点~8点' },
                         { value: $scope.data.d912, name: '9点~12点' },
                         { value: $scope.data.d1318, name: '13点~18点' },
                         { value: $scope.data.d1923, name: '19点~23点' },
                     ].sort(function(a, b) { return a.value - b.value; }),
                     roseType: 'radius',
                     label: {
                         normal: {
                             textStyle: {
                                 color: 'rgba(255, 255, 255, 0.3)'
                             }
                         }
                     },
                     labelLine: {
                         normal: {
                             lineStyle: {
                                 color: 'rgba(255, 255, 255, 0.3)'
                             },
                             smooth: 0.2,
                             length: 10,
                             length2: 20
                         }
                     },
                     itemStyle: {
                         normal: {
                             color: '#c23531',
                             shadowBlur: 200,
                             shadowColor: 'rgba(0, 0, 0, 0.5)'
                         }
                     },

                     animationType: 'scale',
                     animationEasing: 'elasticOut',
                     animationDelay: function(idx) {
                         return Math.random() * 200;
                     }
                 }]
             };
             var myChart = echarts.init(document.getElementById($scope.id), 'macarons');
             myChart.setOption(option);

         },
         controller: function($http, $log, $scope) {
             //离屋分析
             var eattimesUrl = "http://www.zzes1314.cn:3000/getIndoorAnalysis"
             $http({
                 method: "get",
                 url: eattimesUrl,
                 headers: {
                     "content-type": "application/json"
                 }
             }).then(function(req) {
                 $log.log(req.data[0])
                 var data = req.data[0]
                 $scope.d08 = data.d08
                 $scope.d912 = data.d912
                 $scope.d1318 = data.d1318
                 $scope.d1923 = data.d1923


                 $scope.date = new Date(data.updatetime).toLocaleString()
             })
         }
     };
 });