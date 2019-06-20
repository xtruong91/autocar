
#include "UART.h"
#include "MessageHandler.h"

//Controller control;

UART* uart;
MessageHandler msgHandler;
UartConfig cfg = {9600, 100};

//Debug debug;
void setup() {
  // put your setup code here, to run once:
  //control.Init();
  uart = UART::instance();
  uart -> init(cfg);

  uart->registerRxObs(&msgHandler);
  //uart->nit();
  //esp = new ESP8266(uart);  
  //uart->RegisterOb(esp);
  //debug.Init();
}

void loop() {
  //control.Run();
  //debug.printf("detect: %d", 10);
  //delay(1000);
  // put your main code here, to run repeatedly:

}
