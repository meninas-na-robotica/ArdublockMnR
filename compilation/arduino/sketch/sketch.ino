long ultrason_10() {
   long duration, distance;
   digitalWrite(10,LOW);
   delayMicroseconds(2);
   digitalWrite(10, HIGH);
   delayMicroseconds(10);
   digitalWrite(10, LOW);
   duration = pulseIn(11, HIGH);
   distance = duration/58;
   return distance;
}


void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);

}

void loop() {
    if (ultrason_10() <= 15) {
      pinMode(6, OUTPUT);
       digitalWrite(6, 0);
      pinMode(7, OUTPUT);
       digitalWrite(7, 1);
      pinMode(8, OUTPUT);
       digitalWrite(8, 1);
      pinMode(9, OUTPUT);
       digitalWrite(9, 0);
    } else {
      pinMode(6, OUTPUT);
       digitalWrite(6, 0);
      pinMode(7, OUTPUT);
       digitalWrite(7, 1);
      pinMode(8, OUTPUT);
       digitalWrite(8, 0);
      pinMode(9, OUTPUT);
       digitalWrite(9, 1);
    }
    delay(1000);

}