#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "DHT.h"

// ================= WIFI =================
#define WIFI_SSID "Universitas Mulawarman"
#define WIFI_PASSWORD ""

// ================= TELEGRAM =================
#define BOT_TOKEN "7962395072:AAHiFy4zuy85VhZ0rvxwOU-8mwbg4h50FwM"

// ================= USER ID =================
#define USER_A "5193349682"   // Yunew
#define USER_B "1962654050"   // Elloy
#define USER_C "1332401006"   // Tiwiwi

// ================= PIN =================
#define LED_A 16
#define LED_B 17
#define LED_C 18
#define LED_UTAMA 19

#define MQ2_PIN 34
#define DHTPIN 15
#define DHTTYPE DHT11

// ================= OBJECT =================
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
DHT dht(DHTPIN, DHTTYPE);

// ================= USER ARRAY =================
String allUsers[] = {USER_A, USER_B, USER_C};
int totalUsers = 3;

// ================= VAR =================
unsigned long lastTime = 0;
unsigned long interval = 2000;

int gasThreshold = 1000;
bool gasWarningSent = false;

// ================= FUNCTION =================
void sendToAllUsers(String message) {
  for (int i = 0; i < totalUsers; i++) {
    bot.sendMessage(allUsers[i], message, "");
  }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_UTAMA, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  client.setInsecure();

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  dht.begin();
}

// ================= HANDLE COMMAND =================
void handleCommand(String text, String chat_id, String user_id) {

  // ===== START / WELCOME =====
  if (text.equals("/start") || text.equals("/menu")) {
    String nama = "User";

    if (user_id == USER_A) nama = "Yunew";
    else if (user_id == USER_B) nama = "Elloy";
    else if (user_id == USER_C) nama = "Tiwiwi";

    String msg = "👋 Halo, " + nama + "Selamat Datang di KOS MBA SALMA Bot!\n\n";

    msg += "🏠 Kamu bisa mengontrol Ruangan dengan perintah berikut:\n\n";

    msg += "💡 Lampu Kamar:\n";
    msg += "/KamarYunew_on\n/KamarYunew_off\n";
    msg += "/KamarElloy_on\n/KamarElloy_off\n";
    msg += "/KamarTiwiwi_on\n/KamarTiwiwi_off\n\n";

    msg += "🏠 Lampu Ruang Tamu:\n";
    msg += "/ruangtamu_on\n /ruangtamu_off\n\n";

    msg += "🌡️ Cek Suhur:\n";
    msg += "/cek_suhu\n\n";

    msg += "📊 Lainnya:\n";
    msg += "/status_Kos\n";
    msg += "/menu\n\n";

    msg += "✨ Gunakan dengan bijak ya!";

    bot.sendMessage(chat_id, msg, "");
    return;
  }


  // ===== KAMAR YUNEW =====
  if (text == "/KamarYunew_on") {
    if (user_id == USER_A) {
      digitalWrite(LED_A, HIGH);
      bot.sendMessage(chat_id, "💡 Lampu Yunew ON ✨", "");
      bot.sendMessage(USER_A, "🏠 Lampu kamar kamu dinyalakan!", "");
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! (YUNEW ONLY!)", "");
    }
  }

  if (text == "/KamarYunew_off") {
    if (user_id == USER_A) {
      digitalWrite(LED_A, LOW);
      bot.sendMessage(chat_id, "🌙 Lampu Yunew OFF 😴", "");
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK!", "");
    }
  }

  // ===== KAMAR ELLOY =====
  if (text == "/KamarElloy_on") {
    if (user_id == USER_B) {
      digitalWrite(LED_B, HIGH);
      bot.sendMessage(chat_id, "💡 Lampu Elloy ON ✨", "");
      bot.sendMessage(USER_B, "🏠 Lampu kamar kamu dinyalakan!", "");
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! (ELLOY ONLY!)", "");
    }
  }

  if (text == "/KamarElloy_off") {
    if (user_id == USER_B) {
      digitalWrite(LED_B, LOW);
      bot.sendMessage(chat_id, "🌙 Lampu Elloy OFF 😴", "");
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK!", "");
    }
  }

  // ===== KAMAR TIWIWI =====
  if (text == "/KamarTiwiwi_on") {
    if (user_id == USER_C) {
      digitalWrite(LED_C, HIGH);
      bot.sendMessage(chat_id, "💡 Lampu Tiwiwi ON ✨", "");
      bot.sendMessage(USER_C, "🏠 Lampu kamar kamu dinyalakan!", "");
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! (TIWIWI ONLY!)", "");
    }
  }

  if (text == "/KamarTiwiwi_off") {
    if (user_id == USER_C) {
      digitalWrite(LED_C, LOW);
      bot.sendMessage(chat_id, "🌙 Lampu Tiwiwi OFF 😴", "");
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK!", "");
    }
  }

  // ===== RUANG TAMU =====
  if (text == "/ruangtamu_on") {
    digitalWrite(LED_UTAMA, HIGH);
    sendToAllUsers("🏠 Lampu ruang tamu dinyalakan ✨");
  }

  if (text == "/ruangtamu_off") {
    digitalWrite(LED_UTAMA, LOW);
    sendToAllUsers("🌑 Lampu ruang tamu dimatikan");
  }

  // ===== CEK SUHU =====
  if (text == "/cek_suhu") {
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    String msg = "🌡️ Suhu: " + String(t) + "°C\n";
    msg += "💧 Kelembapan: " + String(h) + "%\n";

    if (t > 30) msg += "🔥 Panas banget!";
    else msg += "😊 Nyaman";

    bot.sendMessage(chat_id, msg, "");
  }

  // ===== STATUS =====
  String msg = "🏡 STATUS Kos\n\n";
  if (text == "/status_Kos") {
  
    msg += "💡 Lampu Kamar Yunew: " + String(digitalRead(LED_A) ? "Nyala 💡" : "Mati ❌") + "\n";
    msg += "💡 Lampu Kamar Elloy: " + String(digitalRead(LED_B) ? "Nyala 💡" : "Mati ❌") + "\n";
    msg += "💡 Lampu Kamar Tiwiwi: " + String(digitalRead(LED_C) ? "Nyala 💡" : "Mati ❌") + "\n";
    msg += "🏠 Lampu Ruang Tamu: " + String(digitalRead(LED_UTAMA) ? "Nyala 💡" : "Mati ❌") + "\n";
  
    bot.sendMessage(chat_id, msg, "");
  }
}

// ================= LOOP =================
void loop() {

  // ===== TELEGRAM =====
  if (millis() > lastTime + interval) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      for (int i = 0; i < numNewMessages; i++) {

        String text = bot.messages[i].text;
        String chat_id = bot.messages[i].chat_id;
        String user_id = String(bot.messages[i].from_id);

        handleCommand(text, chat_id, user_id);
      }

      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTime = millis();
  }

  // ===== MQ-2 GAS =====
  int gasValue = analogRead(MQ2_PIN);
  Serial.println(gasValue);

  if (gasValue > gasThreshold && !gasWarningSent) {
    sendToAllUsers("🚨 PERINGATAN!\n💨 Gas terdeteksi tinggi!\nSegera cek Kos!");
    gasWarningSent = true;
  }

  if (gasValue < gasThreshold) {
    gasWarningSent = false;
  }

  delay(500);
}