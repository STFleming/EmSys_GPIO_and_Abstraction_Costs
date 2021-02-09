
unsigned int *gpio_enable_bm = (unsigned int*)(0x3FF44020);
unsigned int gpio_initial_value;

void setup() {
    Serial.begin(115200);
    gpio_initial_value = *gpio_enable_bm;
    Serial.println(gpio_initial_value, BIN);
}


void loop() {

}
