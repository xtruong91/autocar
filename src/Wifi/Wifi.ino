#include "MessageDispatcher.h"

MessageDispatcher dispatcher;

void setup() {
  // put your setup code here, to run once:
  dispatcher.init();
}

void loop() {
  dispatcher.run();
  //delay(1000);
   // put your main code here, to run repeatedly:

}
