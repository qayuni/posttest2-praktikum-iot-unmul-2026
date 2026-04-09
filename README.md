# posttest2-praktikum-iot-unmul-2026
# 🏠 Smart Kos Monitoring & Control Berbasis IoT dan Telegram Bot

## 👥 Nama dan NIM Anggota Kelompok
- Qurrata A'yuni — 2309106001  
- Nur Juzieatul Alifah — 2309106040  
- Tiara Kasma Wati Putri — 2309106080  

---

## 📌 Judul Studi Kasus
Sistem Monitoring dan Kontrol Lampu serta Deteksi Gas pada Kos Menggunakan IoT Berbasis Telegram Bot

---

## 📖 Deskripsi
Proyek ini merupakan sistem Smart Kos berbasis Internet of Things (IoT) yang memungkinkan penghuni kos untuk mengontrol lampu kamar dan ruang tamu serta memonitor kondisi lingkungan secara real-time menggunakan Telegram Bot.

Sistem menggunakan ESP32 yang terhubung ke jaringan WiFi dan Telegram Bot sebagai media komunikasi. Setiap penghuni dapat mengontrol lampu kamar masing-masing secara privat, sedangkan lampu ruang tamu dapat dikontrol oleh semua pengguna.

Selain itu, sistem dilengkapi dengan sensor:
- DHT11 untuk membaca suhu dan kelembapan
- MQ-2 untuk mendeteksi keberadaan gas berbahaya

Jika terdeteksi gas melebihi ambang batas, sistem akan otomatis mengirimkan notifikasi ke seluruh pengguna sebagai peringatan.

---

## 🧩 Pembagian Tugas
- Qurrata A'yuni (2309106001)  
  Membuat program (coding) dan melakukan debugging sistem

- Nur Juzieatul Alifah (2309106040)  
  Membuat rangkaian alat serta membantu debugging code

- Tiara Kasma Wati Putri (2309106080)  
  Membuat board schematic menggunakan Wokwi dan mengedit video dokumentasi

---

## 🔧 Komponen yang Digunakan
- ESP32  
- Sensor DHT11 (Suhu & Kelembapan)  
- Sensor MQ-2 (Gas)  
- LED (4 buah sebagai simulasi lampu)  
- Breadboard  
- Kabel jumper  
- WiFi (Internet)  
- Telegram Bot API  

---

## ⚙️ Fitur Sistem
- Kontrol lampu kamar masing-masing user (akses privat)
- Kontrol lampu ruang tamu (akses bersama)
- Monitoring suhu dan kelembapan
- Deteksi kebocoran gas
- Notifikasi otomatis ke seluruh pengguna jika gas terdeteksi
- Kontrol dan monitoring melalui Telegram Bot

---

## 💬 Perintah Telegram Bot

Berikut adalah daftar perintah yang dapat digunakan pada Telegram Bot:

- `/start`  
  Menampilkan pesan sambutan dan informasi awal penggunaan bot

- `/menu`  
  Menampilkan daftar semua perintah yang tersedia

### 💡 Kontrol Lampu Kamar
- `/KamarYunew_on`  
  Menyalakan lampu kamar Ayuni (khusus Ayuni)

- `/KamarYunew_off`  
  Mematikan lampu kamar Ayuni

- `/KamarElloy_on`  
  Menyalakan lampu kamar Elly (khusus Elly)

- `/KamarElloy_off`  
  Mematikan lampu kamar Elly

- `/KamarTiwiwi_on`  
  Menyalakan lampu kamar Tiara (khusus Tiara)

- `/KamarTiwiwi_off`  
  Mematikan lampu kamar Tiara

### 🏠 Lampu Ruang Tamu
- `/ruangtamu_on`  
  Menyalakan lampu ruang tamu (bisa oleh semua user)

- `/ruangtamu_off`  
  Mematikan lampu ruang tamu

### 🌡️ Monitoring
- `/cek_suhu`  
  Menampilkan suhu dan kelembapan dari sensor DHT11

- `/status_Kos`  
  Menampilkan status semua lampu di kos (nyala/mati)

---

## 🖼️ Gambar Board Schematic
![postest2](https://github.com/user-attachments/assets/ac32b311-bc17-46aa-8e10-71b9c996e662)

Berikut adalah konfigurasi pin yang digunakan pada ESP32:

### 💡 LED (Lampu)
- LED Kamar Yunew → GPIO 16  
- LED Kamar Elloy → GPIO 17  
- LED Kamar Tiwiwi → GPIO 18  
- LED Ruang Tamu → GPIO 19  

### 🌡️ Sensor DHT11
- VCC → 3.3V  
- GND → GND  
- Data → GPIO 15  

### 💨 Sensor MQ-2 (Gas)
- VCC → 5V  
- GND → GND  
- Analog Output → GPIO 34 

---

## 🚀 Cara Kerja Sistem
1. ESP32 terhubung ke jaringan WiFi  
2. ESP32 terhubung dengan Telegram Bot  
3. User mengirim perintah melalui Telegram  
4. Sistem memproses perintah:
   - Mengontrol lampu (LED)
   - Membaca suhu & kelembapan (DHT11)
   - Membaca nilai gas (MQ-2)  
5. Jika gas melebihi batas:
   - Sistem mengirim notifikasi ke semua user  

---

## ⚠️ Catatan
- Sistem tidak menggunakan resistor dalam rangkaian  
- Setiap user hanya bisa mengontrol lampu kamar masing-masing  
- Lampu ruang tamu dapat dikontrol oleh semua user  
- Sistem membutuhkan koneksi internet agar Telegram Bot dapat bekerja  
