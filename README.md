# autocar

## Prerequisite
  
1. Setting up the Arduino IDE
	- Downloading and installing the Arduino IDE
	- Select File->Preferences->Settings tab enter the following URL into the 'Additional Boards Manager URLs'
		http://arduino.esp8266.com/stable/package_esp8266com_index.json
	- From the 'Boards Manager' Dialog, install ESP8266
	
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
	- [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets)
	- PubSubClient

4. Connecting to [MQTT broker](https://techtutorialsx.com/2017/04/09/esp8266-connecting-to-mqtt-broker/)	

## How to Upload Files to your ESP8266 SPIFFS

1. Ensure you have a sub-directory within your sketch directory named 'data'
2. Compress all uploading files into *.gz file
3. Place the files you wish to upload into the 'data' directory
4. From 'Tool' menu, select the correct ESP8266 device and choose the 'Flash Size' with the SPIFFS you require
5. Ensure the serial monitor dialogue box is closed.
6. Prepare the ESP8266  devide for upload:
	1. Hold down 'Flash'
	2. Press 'Reset'
	3. Release 'Flash'
7. From Tools menu select 'ESP8266 Sketch Data Upload'
8. Once upload is complete. Arduino IDE message windown will show 100% upload.

## ESP8266 Multicast DNS

- Your operating system/client machines must support MDNS, you need install [Bonjour](https://support.apple.com/kb/DL999?locale=en_US) for window
	and [Avahi](https://www.avahi.org/) for linux
- Include the ESP8266mDNS library in the sketch
- To advertise DNS, call MDNS.addService(service, proto, port) where service and proto are strings with service
and protocol name (e.g "http", "tcp") and port is an integer port number for this service.
- Add service to MDNS-SD: MDNS.addService("http", "tcp", 80);
- Add function at loop: MDNS.update();
## Project structure

Arduino Uno -> ESP8266 -> Broker Server
1. Arduino Uno call the command to control two wheels up, down, left, right direction
2. ESP8266 subscribe the topic upon Broker Server, handle received data then send back the Arduino
3. ESP8266 publish topic to update status on web.


