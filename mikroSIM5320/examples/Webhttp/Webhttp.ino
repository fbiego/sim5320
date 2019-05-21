#include <sim5320.h>

sim5320 sim(39, 4800);
unsigned long cur_time, old_time;
String host = "example.com";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sim.rstSIM();
  delay(1000);
  String txt = sim.getModemInfo();
  Serial.print("modem: ");
  Serial.println(txt);
  delay(1000);
  sim.hasSSL();delay(1000);
  sim.netReg();delay(1000);      
}

void loop() {
  // put your main code here, to run repeatedly:

  cur_time = millis();
  if ( cur_time - old_time >= 20000){
    delay(1000);
    if(!sim.netReg()){
      Serial.println(F("network fail"));
    }
    Serial.println(F("network ok"));
    
    delay(1000);
    if(!sim.conAPN()){
      Serial.println(F("no internet"));
    }
    Serial.println(F("internet ok"));
    
    delay(1000);
    String url = "/pln/i.php?temp=30&hum=78\r"; 
    sim.pushData(host,url);
  }
}