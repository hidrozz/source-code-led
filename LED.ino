#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Isikan nama SSID dan password
const char* ssid = "Mew";
const char* password = "polopolo1234";

// Initialize Telegram BOT
#define BOTtoken "6195194009:AAEMR9zQCoczLqLn97K30Vox9aQZt-h_AZs" // ganti dengan API Token dari bot telegram yang dibuat
#define CHAT_ID "1878609495" //ganti dengan ID yang didapatkan dari IDBot telegram

#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//menentukan delay 1 detik untuk memeriksa apakah ada pesan baru
int bot_delay = 1000;
unsigned long lastTimeBotRan;

const int ledPin1 = D5; //LED L1 pada board NodeMCU
bool ledState1 = LOW; //memberikan logika 0 pada LED L1
const int ledPin2 = D6; //LED L2 pada board NodeMCU
bool ledState2 = LOW; //memberikan logika 0 pada LED L2
const int ledPin3 = D7; //LED L3 pada board NodeMCU
bool ledState3 = LOW; //memberikan logika 0 pada LED L3
const int ledPin4 = D8; //LED L4 pada board NodeMCU
bool ledState4 = LOW; //memberikan logika 0 pada LED L4

//Ketika ada pesan telegram masuk
void handleNewMessages(int numNewMessages) {
  Serial.println("Handling New Message");
  Serial.println(String(numNewMessages));
  for (int i = 0; i < numNewMessages; i++) {
    //memeriksa ID telegram yang mengirimkan pesan
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    //cetak pesan yang masuk pada Serial Monitor
    String user_text = bot.messages[i].text;
    Serial.println(user_text);
    String your_name = bot.messages[i].from_name;
    //Membuat pesan instruksi (welcome message)
    if (user_text == "/start") {
      String welcome = "Selamat datang, " + your_name + ".\n";
      welcome += "Gunakan perintah berikut untuk menyalakan LED.\n\n";
      welcome += "Kirim /L1_nyala untuk menyalakan LED L1\n";
      welcome += "Kirim /L1_mati untuk mematikan LED L1\n";
      welcome += "Kirim /L2_nyala untuk menyalakan LED L2\n";
      welcome += "Kirim /L2_mati untuk mematikan LED L2\n";
      welcome += "Kirim /L3_nyala untuk menyalakan LED L3\n";
      welcome += "Kirim /L3_mati untuk mematikan LED L3\n";
      welcome += "Kirim /L4_nyala untuk menyalakan LED L4\n";
      welcome += "Kirim /L4_mati untuk mematikan LED L4\n";      
      welcome += "Kirim /statusL1 untuk melihat status L1\n";
      welcome += "Kirim /statusL2 untuk melihat status L2\n";
      welcome += "Kirim /statusL3 untuk melihat status L3\n";
      welcome += "Kirim /statusL4 untuk melihat status L4\n";
      
      welcome += "Kirim /ON untuk menyalakan semua lampu\n";
      welcome += "Kirim /OFF untuk menyalakan semua lampu\n";
      bot.sendMessage(chat_id, welcome, "");
    }
    //LED 1
    if (user_text == "/L1_nyala") {
      bot.sendMessage(chat_id, "L1 dinyalakan", "");
      ledState1 = HIGH;
      digitalWrite(ledPin1, ledState1);
    }
    if (user_text == "/L1_mati") {
      bot.sendMessage(chat_id, "L1 dimatikan", "");
      ledState1 = LOW;
      digitalWrite(ledPin1, ledState1);
    }
    if (user_text == "/statusL1") {
      if (digitalRead(ledPin1)) {
        bot.sendMessage(chat_id, "L1 menyala", "");
      } else {
        bot.sendMessage(chat_id, "L1 mati", "");
      }
    }

    //LED 2
    if (user_text == "/L2_nyala") {
      bot.sendMessage(chat_id, "L2 dinyalakan", "");
      ledState2 = HIGH;
      digitalWrite(ledPin2, ledState2);
    }
    if (user_text == "/L2_mati") {
      bot.sendMessage(chat_id, "L2 dimatikan", "");
      ledState2 = LOW;
      digitalWrite(ledPin2, ledState2);
    }
    if (user_text == "/statusL2") {
      if (digitalRead(ledPin2)) {
        bot.sendMessage(chat_id, "L2 menyala", "");
      } else {
        bot.sendMessage(chat_id, "L2 mati", "");
      }
    }

    //LED 3
    if (user_text == "/L3_nyala") {
      bot.sendMessage(chat_id, "L3 dinyalakan", "");
      ledState3 = HIGH;
      digitalWrite(ledPin3, ledState3);
    }
    if (user_text == "/L3_mati") {
      bot.sendMessage(chat_id, "L3 dimatikan", "");
      ledState3 = LOW;
      digitalWrite(ledPin3, ledState3);
    }
    if (user_text == "/statusL3") {
      if (digitalRead(ledPin3)) {
        bot.sendMessage(chat_id, "L3 menyala", "");
      } else {
        bot.sendMessage(chat_id, "L3 mati", "");
      }
    }

    //LED 4
    if (user_text == "/L4_nyala") {
      bot.sendMessage(chat_id, "L4 dinyalakan", "");
      ledState4 = HIGH;
      digitalWrite(ledPin4, ledState4);
    }
    if (user_text == "/L4_mati") {
      bot.sendMessage(chat_id, "L4 dimatikan", "");
      ledState4 = LOW;
      digitalWrite(ledPin4, ledState4);
    }
    if (user_text == "/statusL4") {
      if (digitalRead(ledPin4)) {
        bot.sendMessage(chat_id, "L4 menyala", "");
      } else {
        bot.sendMessage(chat_id, "L4 mati", "");
      }
    }

    // Menyalakan semua LED
        if (user_text == "/ON") {
      bot.sendMessage(chat_id, "Semua lampu dinyalakan", "");
      ledState1 = HIGH;
      digitalWrite(ledPin1, ledState1);
      ledState2 = HIGH;
      digitalWrite(ledPin2, ledState2);
      ledState3 = HIGH;
      digitalWrite(ledPin3, ledState3);                  
      ledState4 = HIGH;
      digitalWrite(ledPin4, ledState4);
    }
    if (user_text == "/OFF") {
      bot.sendMessage(chat_id, "Semua lampu dimatikan", "");
      ledState1 = LOW;
      digitalWrite(ledPin1, ledState1);
      ledState2 = LOW;
      digitalWrite(ledPin2, ledState2);
      ledState3 = LOW;
      digitalWrite(ledPin3, ledState3);
      ledState4 = LOW;
      digitalWrite(ledPin4, ledState4);
    }  
  }
}

void setup() {
  Serial.begin(115200);
    
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");
    client.setTrustAnchors(&cert);
  #endif
  
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, ledState1);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, ledState2);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, ledState3);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin4, ledState4); 

  // koneksi ke Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // menampilkan lokal IP di Serial Monitor
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + bot_delay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("Got Response!");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
