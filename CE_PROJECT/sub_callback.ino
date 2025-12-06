void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message: ");
  Serial.println(message);
  Serial.println("-----------------------");

  if (strcmp(topic, topic_move) == 0){
    if(message == "front"){
      Mforward();
      delay(2000);
      stop();
      Serial.println("เดินหน้าจ่ะ");
    }

    if(message == "left"){
      Mleft();
      delay(2000);
      stop();
      Serial.println("เลี้ยวซ้ายจ่ะ");
    }

    if(message == "right"){
      Mright();
      delay(2000);
      stop();
      Serial.println("เลี้ยวซ้ายจ่ะ");
    }

    if(message == "back"){
      Mbackward();
      delay(2000);
      stop();
      Serial.println("ถอยหลังจ่ะ");
    }

    else{
      stop();

    }
  }
}


void reconnect() {
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());

    if (client.connect(client_id.c_str())) {
      Serial.println("Public MQTT broker connected");
      client.subscribe(topic_move);

    } else {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}