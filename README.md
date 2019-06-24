# autocar

##Prerequisite
  
1. Setting up the Arduino IDE [at](https://www.instructables.com/id/Setting-Up-the-Arduino-IDE-to-Program-the-ESP8266-/)

2. Install plugin into Arduino
	- Find and download the zip file from main source.
	- Unzip the file.
	- Drop the *.jar file into Arduino tool directory (the path point to sketchbook location in File->Preferences)
		We need to create tools directory inside this folder.
	- Restart Arduino IDE.
	
	- Our plugin: [FileSystem Uploader](https://github.com/esp8266/arduino-esp8266fs-plugin)
		, [Throw binary exception](https://arduino-esp8266.readthedocs.io/en/latest/faq/a02-my-esp-crashes.html)

3. Install libraries which locate in File->Preferences->Sketchbook Location
	- ArduinoJson
	- arduinoWebSockets [at](https://github.com/Links2004/arduinoWebSockets)
	- PubSubClient

4. Connecting to MQTT broker [at](https://techtutorialsx.com/2017/04/09/esp8266-connecting-to-mqtt-broker/)	

## Project structure
Arduino Uno -> ESP8266 -> Broker Server

1. Arduino Uno call the command to control two wheels up, down, left, right direction
2. ESP8266 subscribe the topic upon Broker Server, handle received data then send back the Arduino
3. ESP8266 publish topic to update status on web.


