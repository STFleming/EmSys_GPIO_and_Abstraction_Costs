// pinToggle
// toggles a GPIO pin as fast as it can

void setup() {
    pinMode(23, OUTPUT);
    pinMode(19, OUTPUT);
}


void loop() {
    digitalWrite(23, HIGH);
    digitalWrite(19, HIGH);
    digitalWrite(23, LOW);
    digitalWrite(19, LOW);
}
