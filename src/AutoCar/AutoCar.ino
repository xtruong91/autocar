#include "Controller.h"
#include "Debug.h"
#include "ESP8266.h"


UART *uart;
ESP8266 *esp;

Controller control;
//Debug debug;
void setup() {
  // put your setup code here, to run once:
  control.Init();
  uart = UART::Instance();
  uart->Init();
  esp = new ESP8266(uart);  
  uart->RegisterOb(esp);
  //debug.Init();
}

void loop() {
  //control.Run();
  //debug.printf("detect: %d", 10);
  //delay(1000);
  // put your main code here, to run repeatedly:

}
