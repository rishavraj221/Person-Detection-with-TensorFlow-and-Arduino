if (peripheral.connected()) {
 if (sendsignal > 0){
  alertLevelChar.writeValue((byte)0x02);
  Serial.println("Wrote high alert");
 }
 else{
  alertLevelChar.writeValue((byte)0x00);
  Serial.println("Wrote low alert");
 }
}
