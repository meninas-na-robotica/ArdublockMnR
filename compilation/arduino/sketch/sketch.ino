long random_int(int a,int b) {
  if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
  return random(a,b);
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {
    Serial.println(random_int(0, 100));

}