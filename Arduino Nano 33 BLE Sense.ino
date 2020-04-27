while (central.connected()) {
 //Serial.println("Getting Alert Level:");
 if (alertLevelChar.written()){
  if (alertLevelChar.value()){
   digitalWrite(relay, HIGH);
   Serial.println("Set relay to HIGH");
  } else {
   digitalWrite(relay, LOW);
   Serial.println("Set relay to LOW");
  }
 }
}
