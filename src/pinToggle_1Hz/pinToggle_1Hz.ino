// pinToggle
// toggles a GPIO pin as fast as it can

void setup() {
    pinMode(23, OUTPUT);
}


void loop() {
    digitalWrite(23, HIGH);
    delay(500);
    digitalWrite(23, LOW);
    delay(500);
}
