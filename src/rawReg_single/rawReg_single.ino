// GPIO enable
unsigned int *gpio_enable_reg = (unsigned int*)(0x3FF44020);
unsigned int gpio_initial_values;
unsigned int gpio_new_values;

// W1TS GPIO register
unsigned int*gpio_w1ts_reg = (unsigned int*)(0x3FF44008);

// W1TC GPIO register
unsigned int*gpio_w1tc_reg = (unsigned int*)(0x3FF4400C);

void setup() {
    gpio_initial_values = *gpio_enable_reg; 
    gpio_new_values = gpio_initial_values | (1 << 5);
    *gpio_enable_reg = gpio_new_values;
}

void loop() {
    *gpio_w1ts_reg = (1<<5);
    *gpio_w1tc_reg = (1<<5);
}
