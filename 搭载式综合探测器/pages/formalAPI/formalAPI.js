Page({
  data: {
    latitude: 40.219994,
    longitude: 116.234920,
    markers: [{
      id: 1,
      latitude: 40.219994,
      longitude: 116.234520,
      name: 'T.I.T BUPT'
    }],
    covers: [{
      latitude: 40.219994,
      longitude: 116.234520,
      iconPath: '../images/location.png'
    }, {
      latitude: 40.219994,
      longitude: 116.234520,
      iconPath: '../images/location.png'
    }]
  },
  onReady: function (e) {
    this.mapCtx = wx.createMapContext('myMap')
  },
  getCenterLocation: function () {
    this.mapCtx.getCenterLocation({
      success: function (res) {
        console.log(res.longitude)
        console.log(res.latitude)
      }
    })
  },
  moveToLocation: function () {
    this.mapCtx.moveToLocation()
  },
  translateMarker: function () {
    this.mapCtx.translateMarker({
      markerId: 1,
      autoRotate: true,
      duration: 1000,
      destination: {
        latitude: 40.220994,
        longitude: 116.234520,
      },
      animationEnd() {
        console.log('animation end')
      }
    })
  },
  back: function () {
    //return
    wx.navigateTo({
      url: '../index/index',
    })
  },
  includePoints: function () {
    this.mapCtx.includePoints({
      padding: [10],
      points: [{
        latitude: 40.219994,
        longitude: 116.234520,
      }, {
          latitude: 40.219994,
          longitude: 116.234520,
      }]
    })
  }
})