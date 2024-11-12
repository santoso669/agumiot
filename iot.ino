#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Konfigurasi sensor dan pin
#define DHT_PIN 8
#define DHT_TYPE DHT22
#define LED_GREEN_PIN 5
#define LED_YELLOW_PIN 10
#define LED_RED_PIN 12
#define RELAY_PIN 7
#define BUZZER_PIN 9

DHT dht(DHT_PIN, DHT_TYPE);

// Pengaturan WiFi dan MQTT
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";
const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

// Fungsi untuk menghubungkan ke WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

// Fungsi untuk menghubungkan ke broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("HidroponikDevice")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

// Setup awal
void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

// Loop utama
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca data sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float ph = random(5, 8) + (random(0, 9) / 10.0);  // Simulasi data pH
  float turbidity = random(1, 10);  // Simulasi data turbidity

  // Mengirimkan data ke broker MQTT
  String payload = String("{\"temperature\":") + temperature + ",\"humidity\":" + humidity + ",\"ph\":" + ph + ",\"turbidity\":" + turbidity + "}";
  client.publish("hidroponik/sensor_data", payload.c_str());

  // Menentukan status LED berdasarkan kondisi
  if (temperature > 30) {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
  } else if (temperature > 25) {
    digitalWrite(LED_YELLOW_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
  } else {
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
  }

  // Mengontrol pompa jika kelembapan kurang dari 40%
  if (humidity < 40) {
    digitalWrite(RELAY_PIN, HIGH);  // Nyalakan pompa
    digitalWrite(BUZZER_PIN, HIGH); // Nyalakan buzzer
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Matikan pompa
    digitalWrite(BUZZER_PIN, LOW);  // Matikan buzzer
  }

  delay(10000);  // Tunggu 10 detik sebelum pembacaan berikutnya
}
