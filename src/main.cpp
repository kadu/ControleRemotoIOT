#include <Homie.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;
IRsend irsend(kIrLed);

HomieNode ircontrolNode("InfraRed", "InfraRed", "infrared");

bool irHandler(const HomieRange& range, const String& value) {
  unsigned long ul;
  ul = strtoul (value.c_str(), NULL, 0);
  irsend.sendNEC(ul);
  ircontrolNode.setProperty("code").send(value);
  Homie.getLogger() << "IRCode " << value << endl;
  return true;
}

void setupHandler() {
  irsend.begin();
}


void setup() {
  Serial.begin(115200);

  Serial << endl << endl;
  Homie_setFirmware("refletorIOT", "1.0.0");
  Homie.setSetupFunction(setupHandler);

  ircontrolNode.advertise("code")
    .setName("Code")
    .setDatatype("string")
    .settable(irHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}