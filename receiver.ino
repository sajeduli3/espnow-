#include <Adafruit_NeoPixel.h>
#include <esp_now.h>
#include <WiFi.h>
#define PIN 2
#define NUMPIXELS 60
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 40
int val = 0;
//const int led = 2;


struct __attribute__((packed)) dataPacket {

  int state = 0;
};
// callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info* info, const uint8_t* incomingData, int len) {

  dataPacket packet;
  memcpy(&packet, incomingData, sizeof(packet));
  Serial.print("button: ");
  Serial.println(packet.state);
  //digitalWrite(led,(packet.state));
  if (packet.state == 1) {
    val = 1;
  } else {
    val = 0;
  }
}



void setup() {

  // Initialize Serial Monitor
  Serial.begin(115200);
  // pinMode(led, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
  if (val == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(150, 150, 200));
      pixels.show();
      delay(DELAYVAL);
    }
    val = 0;
  }
  else{
    
    pixels.show();
    pixels.clear();
    }
  }
