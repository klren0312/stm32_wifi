 app.directive('realhumData', function() {
     return {
         scope: {
             id: "@",
             legend: "=",
             item: "=",
             humdata: "="
         },
         restrict: 'E',
         template: '<div class="real-data-charts"></div>',
         replace: true,
         link: function($scope, element, attrs, controller) {
             $scope.legend = [1, 2, 3, 4, 5, "the newest"]
             var socket = io('http://119.28.84.27:5000')
             $scope.humdata = [55, 54, 44, 56, 66, 52]
             socket.on('hum', function(data) {
                 console.log(data)
                 var time = new Date().toLocaleTimeString()
                 $scope.legend.shift()
                 $scope.legend.push(time)
                 $scope.humdata.shift()
                 $scope.humdata.push(data)
                 myChart.setOption(option);
             })
             var option = {
                 color: ['#00688B'],
                 tooltip: {
                     trigger: 'axis',
                     axisPointer: { // 坐标轴指示器，坐标轴触发有效
                         type: 'shadow' // 默认为直线，可选为：'line' | 'shadow'
                     }
                 },
                 legend: {
                     data: ['湿度'],
                 },
                 label: {
                     normal: {
                         show: true
                     }
                 },
                 grid: {
                     left: '3%',
                     right: '4%',
                     bottom: '3%',
                     containLabel: true
                 },
                 xAxis: [{
                     type: 'category',
                     data: $scope.legend,
                     axisTick: {
                         alignWithLabel: true
                     }
                 }],
                 yAxis: [{
                     type: 'value',
                 }],
                 series: [{
                     name: '湿度',
                     type: 'line',
                     barWidth: '60%',
                     data: $scope.humdata
                 }]
             };
             var myChart = echarts.init(document.getElementById($scope.id), 'macarons');
             myChart.setOption(option);

         }
     };
 });