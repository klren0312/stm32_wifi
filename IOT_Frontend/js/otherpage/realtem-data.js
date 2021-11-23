 app.directive('realtemData', function() {
     return {
         scope: {
             id: "@",
             legend: "=",
             item: "=",
             temdata: "="
         },
         restrict: 'E',
         template: '<div class="real-data-charts"></div>',
         replace: true,
         link: function($scope, element, attrs, controller) {
             $scope.e = [1, 2, 3, 4, 5, "the newest"]
             var socket = io('http://119.28.84.27:5000')
             $scope.temdata = [30, 30, 30, 30, 33, 31]
             socket.on('tem', function(data) {
                 console.log(data)
                 var t = new Date().toLocaleTimeString()
                 $scope.e.shift()
                 $scope.e.push(t)
                 $scope.temdata.shift()
                 $scope.temdata.push(data)
                 myChart.setOption(option);
             })
             var option = {
                 color: ['#CD3700'],
                 tooltip: {
                     trigger: 'axis',
                     axisPointer: { // 坐标轴指示器，坐标轴触发有效
                         type: 'shadow' // 默认为直线，可选为：'line' | 'shadow'
                     }
                 },
                 legend: {
                     data: ['温度'],
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
                     data: $scope.e,
                     axisTick: {
                         alignWithLabel: true
                     }
                 }],
                 yAxis: [{
                     type: 'value'
                 }],
                 series: [{
                     name: '温度',
                     type: 'line',
                     barWidth: '60%',
                     data: $scope.temdata
                 }]
             };
             var myChart = echarts.init(document.getElementById($scope.id), 'macarons');
             myChart.setOption(option);

         }
     };
 });