// pinToggle
// toggles a GPIO pin as fast as it can

void setup() {
    pinMode(23, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(5, OUTPUT);
}


void loop() {
    digitalWrite(23, HIGH);
    digitalWrite(19, HIGH);
    digitalWrite(18, HIGH);
    digitalWrite(5, HIGH);

    digitalWrite(23, LOW);
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    digitalWrite(5, LOW);
}
