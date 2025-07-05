#include <SoftwareSerial.h>
#include <DHT.h>

// --- KONFIGURASI PIN ---
#define DHT_PIN 4
#define LDR_PIN 3         // Menggunakan pin digital, bukan pin analog
#define RELAY_LAMP 8
#define RELAY_POMPA_MINUM 9
#define RELAY_POMPA_SIRAM 10

// --- KONFIGURASI SENSOR & KOMUNIKASI ---
#define DHT_TYPE DHT11
SoftwareSerial espSerial(11, 12); // RX Arduino ke TX ESP, TX Arduino ke RX ESP

// --- INISIALISASI OBJEK ---
DHT dht(DHT_PIN, DHT_TYPE);

// --- BATAS-BATAS & PENGATURAN WAKTU ---
const long INTERVAL_BACA_SENSOR = 2000; // Jeda waktu pembacaan sensor (2 detik)
const long INTERVAL_KIRIM_STATUS = 5000; // Jeda waktu kirim status DHT (5 detik)
unsigned long previousMillis = 0;
unsigned long previousStatusMillis = 0;

// --- VARIABEL KONTROL MODE OTOMATIS/MANUAL ---
bool modeLampuOtomatis = true;
// Mode siram otomatis dihapus karena DHT22 tidak lagi mengontrol pompa

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  dht.begin();

  // Atur pin relay sebagai OUTPUT
  pinMode(RELAY_LAMP, OUTPUT);
  pinMode(RELAY_POMPA_MINUM, OUTPUT);
  pinMode(RELAY_POMPA_SIRAM, OUTPUT);

  // Atur pin LDR sebagai INPUT
  // Asumsi rangkaian LDR akan memberikan sinyal LOW saat gelap
  pinMode(LDR_PIN, INPUT);

  // Kondisi awal: Semua relay OFF (Relay aktif saat LOW)
  digitalWrite(RELAY_LAMP, HIGH);
  digitalWrite(RELAY_POMPA_MINUM, HIGH);
  digitalWrite(RELAY_POMPA_SIRAM, HIGH);

  Serial.println("Sistem Siap.");
  Serial.println("Mode Lampu: OTOMATIS");
  Serial.println("DHT22: Status monitoring only");
}

void loop() {
  // Cek perintah dari Bluetooth/ESP tanpa henti (non-blocking)
  cekPerintahBluetooth();

  // Jalankan pembacaan sensor dan logika otomatisasi setiap 'INTERVAL_BACA_SENSOR'
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL_BACA_SENSOR) {
    previousMillis = currentMillis;
    bacaSensorDanOtomatisasi();
  }

  // Kirim status DHT22 secara berkala
  if (currentMillis - previousStatusMillis >= INTERVAL_KIRIM_STATUS) {
    previousStatusMillis = currentMillis;
    kirimStatusDHT();
  }
}

void bacaSensorDanOtomatisasi() {
  // --- Otomatisasi Lampu Berdasarkan LDR (jika mode otomatis aktif) ---
  if (modeLampuOtomatis) {
    // Baca status digital dari LDR
    int statusCahaya = digitalRead(LDR_PIN); // Hasilnya akan HIGH atau LOW

    // Logika: Jika pin LDR bernilai LOW, artinya gelap
    if (statusCahaya == LOW) {
      digitalWrite(RELAY_LAMP, HIGH); // Gelap -> Nyalakan Lampu
    } else {
      digitalWrite(RELAY_LAMP, LOW); // Terang -> Matikan Lampu
    }
  }

  // DHT22 tidak lagi mengontrol pompa siram otomatis
  // Hanya untuk monitoring status
}

void kirimStatusDHT() {
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  // Cek jika pembacaan sensor valid
  if (!isnan(suhu) && !isnan(kelembaban)) {
    // Tampilkan status di Serial Monitor
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print("°C, Kelembaban: ");
    Serial.print(kelembaban);
    Serial.println("%");

    // Kirim status ke ESP/Bluetooth dalam format yang mudah diparsing
    espSerial.print("TEMP:");
    espSerial.print(suhu);
    espSerial.print(",HUM:");
    espSerial.println(kelembaban);
  } else {
    Serial.println("Gagal membaca data dari sensor DHT22!");
    espSerial.println("DHT:ERROR");
  }
}

void cekPerintahBluetooth() {
  if (espSerial.available()) {
    char cmd = espSerial.read();

    switch (cmd) {
      // --- Kontrol Manual Lampu ---
      case 'L': // NYALAKAN Lampu (Manual)
        modeLampuOtomatis = false; // Nonaktifkan mode otomatis
        digitalWrite(RELAY_LAMP, LOW);
        Serial.println("Mode Lampu: MANUAL ON");
        break;
      case 'l': // MATIKAN Lampu (Manual)
        modeLampuOtomatis = false; // Nonaktifkan mode otomatis
        digitalWrite(RELAY_LAMP, HIGH);
        Serial.println("Mode Lampu: MANUAL OFF");
        break;
      case 'M': // Aktifkan kembali mode OTOMATIS Lampu
        modeLampuOtomatis = true;
        Serial.println("Mode Lampu: OTOMATIS");
        break;

      // --- Kontrol Pompa Minum ---
      case 'A': // NYALAKAN Pompa Minum
        digitalWrite(RELAY_POMPA_MINUM, LOW);
        Serial.println("Pompa Minum: ON");
        break;
      case 'a': // MATIKAN Pompa Minum
        digitalWrite(RELAY_POMPA_MINUM, HIGH);
        Serial.println("Pompa Minum: OFF");
        break;

      // --- Kontrol Manual Pompa Siram ---
      case 'B': // NYALAKAN Pompa Siram (Manual)
        digitalWrite(RELAY_POMPA_SIRAM, LOW);
        Serial.println("Pompa Siram: MANUAL ON");
        break;
      case 'b': // MATIKAN Pompa Siram (Manual)
        digitalWrite(RELAY_POMPA_SIRAM, HIGH);
        Serial.println("Pompa Siram: MANUAL OFF");
        break;

      // --- Perintah untuk request status DHT22 ---
      case 'D': // Request status DHT22
        kirimStatusDHT();
        break;
    }
  }
}