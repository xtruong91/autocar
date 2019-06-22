#include "Debug.h"

//Controller control;
#include "ControllerConfig.h"
#include "Controller.h"
#include "Debug.h"


ControllerConfig *cfg = ControllerConfig::instance();
Controller centerController(*cfg);
Debug *debug = Debug::instance();

//Debug debug;
void setup() {
  debug->init(); 
  centerController.init();
}

void loop() {
  centerController.run();
  //delay(1000);
}
