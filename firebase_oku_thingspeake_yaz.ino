//Firebase Realtime Databese'e DHT11den okudugumuz sicaklik verisi yazma
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "ThingSpeak.h"
//*******************************************
const char *ssid = "DSMART_4DB33C";      // baglanilacak olan wifi aginin adi  
const char *password = "cEqyYrzx";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "iot-2-84223-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "C5pZ0hHt2ApE0i5lPioAAtobW06SIplf9fGZjC3h" //gizli anahtar
#define SECRET_CH_ID 1279812 //Proje adinin altinda 
const char *SECRET_WRITE_APIKEY = "UKBQXSNE6S8U7QL7"; //API Keys bolumunde
WiFiClient wifi_istemci;

int firebase_oku = 0;
//************************************************************
void setup() {
  
  Serial.begin(9600);                   //seri portu baslat
  delay(1500);                          // 1500 ms = 1.5sn
  Serial.println("Wifi agına baglanıyor");
  
  WiFi.mode(WIFI_STA);                  // istasyon modunda çalış
  WiFi.begin(ssid, password);           // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(5000);                         // 5000 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());       // wifi agindan alinan IP adresini yazdir.

  Serial.println("Yasins");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
}
//************************************************************
void loop() 
{
   
   firebase_oku = Firebase.getInt("iot");
  
   if(Firebase.failed()){
    Serial.print("Hata kodu:");
    Serial.println(Firebase.error());
    return;
  }
  delay(15000);

 ThingSpeak.begin(wifi_istemci);

  int x = ThingSpeak.writeField(SECRET_CH_ID, 1, firebase_oku, SECRET_WRITE_APIKEY); 
  
  if(x == 200){
    Serial.println("Kanala veri yazildi");
  }
  else{
    Serial.println("Kanala yazma basarisiz. HTTP error code " + String(x));
  }
  delay(5000); 

}
