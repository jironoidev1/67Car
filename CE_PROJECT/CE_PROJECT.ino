#include <WiFi.h>
#include <PubSubClient.h>

#define in1 26
#define in2 27
#define in3 32
#define in4 33
#define PWMPin1 34
#define PWMPin2 35

// WiFi และ MQTT Configuration
const char* ssid = "Pak24";//CE-NextGen
const char* password = "xit9^ohe";//##CEnextgen2024
const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;
const char* topic_state = "mqtt/state";
const char* topic_move = "mqtt/move";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(19, INPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  
  reconnect();

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  if(digitalRead(19) == LOW){
    client.publish(topic_state, "มีคน");
  }else{
    client.publish(topic_state, "ไม่มีคน");
  }
  
  client.loop();
}
