var myCharts = require("../../utils/wxcharts.js")//引入一个绘图的插件
var lineChart_distance = null

var app = getApp()

Page({
  data: {
  },
  onPullDownRefresh: function () {
    console.log('onPullDownRefresh', new Date())
  },


  //把拿到的数据转换成绘图插件需要的输入格式
  convert: function () {
    var categories = [];
    var distance = [];


    var length = app.globalData.distance.datapoints.length
    for (var i = 0; i < length; i++) {
      categories.push(app.globalData.distance.datapoints[i].at.slice(11, 19));
      distance.push(app.globalData.distance.datapoints[i].value);

    }
    return {
      categories: categories,
      distance: distance,

    }
  },

  onLoad: function () {
    var wheatherdata = this.convert();

    //得到屏幕宽度
    var windowWidth = 320;
    try {
      var res = wx.getSystemInfoSync();
      windowWidth = res.windowWidth;
    } catch (e) {
      console.error('getSystemInfoSync failed!');
    }

    var wheatherdata = this.convert();

    //新建距离图表
    lineChart_distance = new myCharts({
      canvasId: 'distance',
      type: 'line',
      categories:wheatherdata.categories,
      animation: true,
      background: '#f5f5f5',
      series: [{
        name: 'distance forward',
        data: wheatherdata.distance,
        format: function (val, name) {
          return val.toFixed(2);
        }
      }],
      xAxis: {
        disableGrid: true
      },
      yAxis: {
        title: '距离 (m)',
        format: function (val) {
          return val.toFixed(2);
        },
        min: 55
      },
      width: windowWidth,
      height: 200,
      dataLabel: false,
      dataPointShape: true,
      extra: {
        lineStyle: 'curve'
      }
    });

    
  },


})
