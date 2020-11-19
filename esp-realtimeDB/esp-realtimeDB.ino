#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h> 
#include <DHT.h>
                                           

#define FIREBASE_HOST "esprealtimedb.firebaseio.com"                         
#define FIREBASE_AUTH "GEhbDHojbC8ccEGPOcrackwokjLo5Jx6I55AoXEJ"                    
#define WIFI_SSID "mr.TranL"                                          
#define WIFI_PASSWORD "0123456789" 
// kết nối chân data DHT D4   
#define DHTPIN D4  
// Chọn loại DHT 11 (DHT11 và DHT22)          
//#define DHTTYPE DHT11  
//DHT dht (DHTPIN, DHTTYPE);                
// Biến lưu status từ firebase
String ledStatus = "";                                                                                                                
void setup() {
  Serial.begin(115200); 
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT); //chan xuat tin hieu
//  dht.begin();
  
//ket noi toi wifi             
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     
  Serial.print("Kết nối tới ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Đã kết nối tới ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address: ");
  //print local IP address
  Serial.println(WiFi.localIP());  
//ket noi toi firebase thong qua xac thuc ID host va key Auth
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   
                                   
//  Firebase.setString("ledStatus", "OFF");                                         
}

void loop() {
// lấy giá trị (dạng chuỗi) trạng thái được input từ firebase và lưu giá trị vào biến
  ledStatus = Firebase.getString("LED/ledStatus");                           
  Serial.println(ledStatus);
// gửi giá trị (chuỗi) lên firebases
//nhietdoStatus = Firebase.setString ("nhietdoStatus","hanguyentieuyen");

  

  
// so sánh trạng thái led dc input từ firebase
  if (ledStatus == "1") {                                                      
    Serial.println("Led bật");                         
    digitalWrite(LED_BUILTIN, LOW);                                                                                                
  } 

  else if (ledStatus == "0") {                                                 
    Serial.println("Led tắt");
    digitalWrite(LED_BUILTIN, HIGH);                                            
  }
  else {
    Serial.println("Chưa nhận giá trị on off");
  }

//////////////////////////////////////////////////  

//  float doam = dht.readHumidity();
//  float nhietdo = dht.readTemperature();
//  Serial.println("Do am: ");
//  Serial.println(doam);
//  Serial.println("Nhiet do: ");
//  Serial.println(nhietdo);
//  Firebase.setFloat("nhietdo",nhietdo);
//  Firebase.setFloat("doam",doam);
}
