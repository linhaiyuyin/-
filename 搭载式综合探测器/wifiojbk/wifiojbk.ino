#define SSID        "lhyy" //改为你的Wi-Fi名称
#define PASSWORD    "linhaiyuyin"//Wi-Fi密码
#define HOST_NAME   "api.heclouds.com"
#define DEVICEID    "505096744" //OneNet上的设备ID
#define PROJECTID   "183688" //OneNet上的产品ID
#define HOST_PORT   (80)
String apiKey="5Mwc7R5tBULd3JWiBA43tw=u5Ko=";//与你的设备绑定的APIKey

#define INTERVAL_SENSOR   1000             //定义传感器采样时间间隔  597000
#define INTERVAL_NET      1000             //定义发送时间
  
#include <Wire.h>                                  //调用库  
#include <ESP8266.h>

#define Trig1 9
#define Echo1 8


#define IDLE_TIMEOUT_MS  3000 
char buf[10];

#define INTERVAL_sensor 2000
unsigned long sensorlastTime = millis();
                                                                                                                      
float distance,pix2,temp1;

#define INTERVAL_OLED 1000

String mCottenData;
String jsonToSend;
char  distance_c[7],pix2_c[7];

#include <SoftwareSerial.h>
#define EspSerial mySerial
#define UARTSPEED  9600
SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */
ESP8266 wifi(&EspSerial);
//ESP8266 wifi(Serial1);                                      //定义一个ESP8266（wifi）的对象
unsigned long net_time1 = millis();                          //数据上传服务器时间
unsigned long sensor_time = millis();          

String postString;   

void setup(void)     //初始化函数  
{       
  //初始化串口波特率  
    Wire.begin();
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
    Serial.print(F("setup begin\r\n"));
    delay(100);
    
    pinMode(Echo1, INPUT);
    pinMode(Trig1,OUTPUT);
  
    pinMode(11,OUTPUT);

     WifiInit(EspSerial, UARTSPEED);

  Serial.print(F("FW Version:"));
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print(F("to station + softap ok\r\n"));
  } else {
    Serial.print(F("to station + softap err\r\n"));
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print(F("Join AP success\r\n"));

    Serial.print(F("IP:"));
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print(F("Join AP failure\r\n"));
  }

  if (wifi.disableMUX()) {
    Serial.print(F("single ok\r\n"));
  } else {
    Serial.print(F("single err\r\n"));
  }

  Serial.print(F("setup end\r\n"));
    
  
}

void loop(void)     //循环函数  
{   
  if (sensor_time > millis())  sensor_time = millis();  
    
  if(millis() - sensor_time > INTERVAL_SENSOR)              //传感器采样时间间隔  
  {  
    getSensorData();                                        //读串口中的传感器数据
    sensor_time = millis();
  }  

    
  if (net_time1 > millis())  net_time1 = millis();
  
  if (millis() - net_time1 > INTERVAL_NET)                  //发送数据时间间隔
  {                
    updateSensorData();                                     //将数据上传到服务器的函数
    net_time1 = millis();
  }
  
}

void getSensorData(){  
    
    digitalWrite(Trig1,LOW);
    delayMicroseconds(2);
    digitalWrite(Trig1,HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig1,LOW);

    temp1=float(pulseIn(Echo1,HIGH));
    distance=(temp1*17)/1000;
    pix2=1;
    digitalWrite(11,LOW);
    
    delay(100);
    dtostrf(distance, 2, 1, distance_c);
 
    dtostrf(pix2, 2, 1, pix2_c);
}

void updateSensorData() {
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
    Serial.print("create tcp ok\r\n");

    jsonToSend="{\"distance\":";
    dtostrf(distance, 1, 2, buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+=",\"pix2\":";
    dtostrf(pix2, 1, 2, buf);
    jsonToSend+="\""+String(buf)+"\"";
    jsonToSend+="}";

    postString="POST /devices/";
    postString+=DEVICEID;
    postString+="/datapoints?type=3 HTTP/1.1";
    postString+="\r\n";
    postString+="api-key:";
    postString+=apiKey;
    postString+="\r\n";
    postString+="Host:api.heclouds.com\r\n";
    postString+="Connection:close\r\n";
    postString+="Content-Length:";
    postString+=jsonToSend.length();
    postString+="\r\n";
    postString+="\r\n";
    postString+=jsonToSend;
    postString+="\r\n";
    postString+="\r\n";
    postString+="\r\n";

    const char *postArray = postString.c_str();                 //将str转化为char数组
  Serial.println(postArray);
  wifi.send((const uint8_t*)postArray, strlen(postArray));    //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
  Serial.println("send success");   
     if (wifi.releaseTCP()) {                                 //释放TCP连接
        Serial.print("release tcp ok\r\n");
        } 
     else {
        Serial.print("release tcp err\r\n");
        }
      postArray = NULL;                                       //清空数组，等待下次传输数据
  
  } else {
    Serial.print("create tcp err\r\n");
  }
}
    
    
