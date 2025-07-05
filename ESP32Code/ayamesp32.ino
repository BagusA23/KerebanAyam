#include "BluetoothSerial.h"
#include <HardwareSerial.h>

// --- KONFIGURASI BLUETOOTH ---
BluetoothSerial SerialBT;
String deviceName = "SmartFarm_ESP32";

// --- KONFIGURASI KOMUNIKASI DENGAN ARDUINO ---
HardwareSerial ArduinoSerial(2); // Menggunakan UART2
#define RX_PIN 16  // Pin RX ESP32 dari TX Arduino
#define TX_PIN 17  // Pin TX ESP32 ke RX Arduino

// --- LED STATUS ---
#define LED_BLUETOOTH 2
#define LED_BUILTIN 2

// --- VARIABEL STATUS ---
bool bluetoothConnected = false;

void setup() {
  Serial.begin(115200);
  
  // Setup komunikasi dengan Arduino
  ArduinoSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  
  // Setup LED
  pinMode(LED_BLUETOOTH, OUTPUT);
  digitalWrite(LED_BLUETOOTH, LOW);
  
  // Inisialisasi Bluetooth
  SerialBT.begin(deviceName);
  
  Serial.println("ESP32 Bluetooth Bridge Started");
  Serial.println("Device Name: " + deviceName);
  Serial.println("Waiting for Bluetooth connection...");
  
  // Callback untuk status koneksi Bluetooth
  SerialBT.register_callback(bluetoothCallback);
  
  // Indikator siap
  blinkLED(3);
}

void loop() {
  // Cek perintah dari Bluetooth dan teruskan ke Arduino
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim(); // Hapus whitespace
    
    if (command.length() > 0) {
      prosesPerintahBluetooth(command);
    }
  }
  
  // Cek data dari Arduino dan teruskan ke Bluetooth (opsional)
  if (ArduinoSerial.available()) {
    String data = ArduinoSerial.readStringUntil('\n');
    data.trim();
    
    if (data.length() > 0) {
      Serial.println("Arduino: " + data);
      
      // Teruskan ke Bluetooth jika terkoneksi
      if (bluetoothConnected) {
        SerialBT.println(data);
      }
    }
  }
  
  // Update LED status
  digitalWrite(LED_BLUETOOTH, bluetoothConnected);
}

void prosesPerintahBluetooth(String perintah) {
  Serial.println("Bluetooth: " + perintah);
  
  // Perintah khusus ESP32
  if (perintah == "PING") {
    SerialBT.println("PONG");
    return;
  }
  
  if (perintah == "STATUS") {
    SerialBT.println("ESP32_OK");
    return;
  }
  
  // Perintah untuk Arduino (single character)
  if (perintah.length() == 1) {
    char cmd = perintah.charAt(0);
    
    // Validasi perintah yang valid
    if (isValidCommand(cmd)) {
      // Kirim ke Arduino
      ArduinoSerial.print(cmd);
      
      // Konfirmasi ke Bluetooth
      SerialBT.println("OK:" + perintah);
      
      Serial.println("Command sent to Arduino: " + perintah);
    } else {
      SerialBT.println("ERROR:INVALID_COMMAND");
      Serial.println("Invalid command: " + perintah);
    }
  }
  // Perintah multi-character
  else {
    // Jika ingin mengirim string lengkap ke Arduino
    ArduinoSerial.println(perintah);
    SerialBT.println("SENT:" + perintah);
  }
}

bool isValidCommand(char cmd) {
  // Daftar perintah yang valid untuk Arduino
  char validCommands[] = {'L', 'l', 'M', 'A', 'a', 'B', 'b', 'D'};
  
  for (int i = 0; i < sizeof(validCommands); i++) {
    if (cmd == validCommands[i]) {
      return true;
    }
  }
  return false;
}

void bluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    Serial.println("Bluetooth Client Connected");
    bluetoothConnected = true;
    
    // Kirim pesan selamat datang
    SerialBT.println("CONNECTED:" + deviceName);
    SerialBT.println("READY");
    
    // Blink LED sebagai indikator
    blinkLED(2);
    
  } else if (event == ESP_SPP_CLOSE_EVT) {
    Serial.println("Bluetooth Client Disconnected");
    bluetoothConnected = false;
  }
}

void blinkLED(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(LED_BLUETOOTH, HIGH);
    delay(200);
    digitalWrite(LED_BLUETOOTH, LOW);
    delay(200);
  }
}