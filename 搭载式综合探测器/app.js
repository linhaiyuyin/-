App({
  onLaunch() {
    console.log('App.onLaunch()');
  },
  onShow: function () {
  },
  onHide: function () {
  },

  //本应用全局数据
  globalData: {
    temperature: {},
    light: {},
    humidity: {} ,
    distance: {},
    weather:{}
  },

//app.js  


  //第一种底部  
  editTabBar: function () {
    //使用getCurrentPages可以获取当前加载中所有的页面对象的一个数组，数组最后一个就是当前页面。

    var curPageArr = getCurrentPages();    //获取加载的页面
    var curPage = curPageArr[curPageArr.length - 1];    //获取当前页面的对象
    var pagePath = curPage.route;    //当前页面url
    if (pagePath.indexOf('/') != 0) {
      pagePath = '/' + pagePath;
    }

    var tabBar = this.globalData.tabBar;
    for (var i = 0; i < tabBar.list.length; i++) {
      tabBar.list[i].active = false;
      if (tabBar.list[i].pagePath == pagePath) {
        tabBar.list[i].active = true;    //根据页面地址设置当前页面状态    
      }
    }
    curPage.setData({
      tabBar: tabBar
    });
  },
  
  globalData: {
    //第一种底部导航栏显示
    tabBar: {
      "color": "#9E9E9E",
      "selectedColor": "#f00",
      "backgroundColor": "#fff",
      "borderStyle": "#ccc",
      "list": [
        {
          "pagePath": "/pages/first-psgr/first",
          "text": "首页简介",
          "clas": "menu-item",
          "selectedColor": "#4EDF80",
          active: true
        },
        {
          "pagePath": "/pages/formalAPI/formalAPI",
          "text": "当前位置",
          "selectedColor": "#4EDF80",
          "clas": "menu-item",
          active: false
        },
        {
          "pagePath": "/pages/start/start",
          "text": "监测和后续",
          "selectedColor": "#4EDF80",
          "clas": "menu-item",
          active: false
        }
      ],
      "position": "bottom"
    },
    }
  
})

