#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// 0x27: địa chỉ I2C của mạch chuyển I2C cho LCD
#define DHTPIN D5 // kết nối chân data DHT D5
#define DHTTYPE DHT11 //Sử dụng DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
//fire base
#define FIREBASE_HOST "esprealtimedb.firebaseio.com"
#define FIREBASE_AUTH "[Your key secret realtime database"
#define WIFI_SSID "Lau_2_new" //Your SSID Wifi
#define WIFI_PASSWORD "danghuynhkienvan"  //Your Password Wifi
#define relay1 D6
#define relay2 D7

unsigned int NhietDo = 0, DoAm = 0;
unsigned int delayDocNhietDo = 1000;  //ms
unsigned long lastReadTemp;
byte degree[8] = {  // dùng để hiển thị dấu độ
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
// Biến lưu status từ firebase
String ledStatus = "";
String ledStatus1 = "";

/***************************************************************************************************/

// Chương trình kiểm tra và hiển thị nhiệt độ LCD
void KtVaHienThiNhietDo() {
  if ( ((unsigned long) (millis() - lastReadTemp)) > delayDocNhietDo) {   // neu lan truoc doc cach day > delayDocNhietDo
    //
    unsigned int NhietDoTam = NhietDo;
    unsigned int DoAmTam = DoAm;
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println("Error reading temperature!");
    }
    else {
      Serial.print("Temperature: ");
      NhietDoTam = event.temperature;
      Serial.print(NhietDoTam);
      if (NhietDoTam != NhietDo) {
        NhietDo = NhietDoTam;
        lcd.setCursor(0, 0);
        lcd.print("Nhiet Do:       ");
        lcd.setCursor(10, 0);
        lcd.print(NhietDo);
        lcd.print(" ");
        lcd.write(1);
        lcd.print("C");
      }
      Serial.println(" *C");
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println("Error reading humidity!");
    }
    else {
      Serial.print("Humidity: ");
      DoAmTam = event.relative_humidity;
      Serial.print(DoAmTam);
      if (DoAmTam != DoAm) {
        DoAm = DoAmTam;
        lcd.setCursor(0, 1);
        lcd.print("Do Am:          ");
        lcd.setCursor(10, 1);
        lcd.print(DoAm);
        lcd.setCursor(13, 1);
        lcd.print("%");
      }
      Serial.println("%");
    }
    lastReadTemp = millis();
  }
}


/*************************************************************************************************/

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT); //chan xuat tin hieu 
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay2, LOW);
  // Setup LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do:       ");
  lcd.setCursor(0, 1);
  lcd.print("Do am:          ");
// Setup DHT11
  dht.begin();
//  Serial.println("DHTxx Unified Sensor Example");
// Print temperature sensor details.
//  sensor_t sensor;
//  dht.temperature().getSensor(&sensor);
//  Serial.println("------------------------------------");
//  Serial.println("Temperature");
//  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
//  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
//  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
//  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
//  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
//  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
//  Serial.println("------------------------------------");
// Print humidity sensor details.
//  dht.humidity().getSensor(&sensor);
//  Serial.println("------------------------------------");
//  Serial.println("Humidity");
//  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
//  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
//  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
//  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
//  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
//  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
//  Serial.println("------------------------------------");
  lcd.createChar(1, degree);
  
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

/*************************************************************************************/

void loop() {
   KtVaHienThiNhietDo();
   
  // lấy giá trị (dạng chuỗi) trạng thái được input từ firebase và lưu giá trị vào biến
  
  ledStatus = Firebase.getString("LED/ledStatus");
  ledStatus1 = Firebase.getString("LED/ledStatus1");
  Serial.println(ledStatus);

  // so sánh trạng thái led dc input từ firebase
  if (ledStatus == "1") {
    Serial.println("Led bật");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite (relay1,HIGH);
  }
  else if (ledStatus == "0") {
    Serial.println("Led tắt");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite (relay1,LOW);
  }
  else {
    Serial.println("Chưa nhận giá trị on off");
  }


  if (ledStatus1 == "1") {
    Serial.println("Led bật");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite (relay2,HIGH);
  }
  else if (ledStatus1 == "0") {
    Serial.println("Led tắt");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite (relay2,LOW);
  }
  else {
    Serial.println("Chưa nhận giá trị on off");
  }

  // gửi giá trị nhiệt độ và độ ẩm lên firebases
  Firebase.setFloat("DHT11/Temp",NhietDo);
  Firebase.setFloat("DHT11/Hum",DoAm);
 
}
