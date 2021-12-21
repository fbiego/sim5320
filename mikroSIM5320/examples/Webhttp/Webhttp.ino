#include <sim5320.h>

sim5320 sim(25, 115200);
unsigned long cur_time, old_time;
String host = "hydrate2.acmegh.com";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sim.rstSIM();
  delay(1000);
  String txt = sim.getModemInfo();
  Serial.print("modem: ");
  Serial.println(txt);
  delay(1000); 
}

void loop() {
  // put your main code here, to run repeatedly:

  cur_time = millis();
  if ( cur_time - old_time >= 5000){
    String url = "/api/v2/water/balance?serial_number=18543230135\r"; 
    if(!sim.pushHTTP(host, url)){
      Serial.println("fail post");
    }
    old_time = cur_time;
  }
}
