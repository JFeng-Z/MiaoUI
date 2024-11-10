#include <Arduino.h>
#include "HAL_Button.h"
#include "display/dispDirver.h"
#include "core/ui.h"
#include "ui_conf.h"

ui_t ui;
int Wave_TestData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dispInit();
  MiaoUi_Setup(&ui);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wave_TestData = rand() % 600;
  ui_loop(&ui);
}
