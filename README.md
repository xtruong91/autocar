# autocar

Arduino Uno -> ESP8266 -> Broker Server

1. Arduino Uno call the command to control two wheels up, down, left, right direction
2. ESP8266 subscribe the topic upon Broker Server, handle received data then send back the Arduino
3. ESP8266 publish topic to update status on web.

Broker Server -> Web Server.
