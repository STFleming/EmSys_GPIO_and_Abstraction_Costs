![](imgs/EmSysLogo.svg)

## Lecture 3: GPIO Deep Dive and Abstraction Costs 

__Learning outcomes:__
* Understanding of abstraction overheads in Embedded Systems
* Understanding the limits of hardware interacting with I/O
* A deeper appreciation of memory-mapped I/O, expanding on the introduction from last lecture.
* Bit-manipulation techniques in C

__Outline:__
* Recap how to write to digital pins on the ESP32 with Arduino
* Recap reading and writing to memory mapped I/O and hardware
* The limits of how fast we can pulse pins in Arduino
* What happens when we call a function?
* Estimating the overheads of a function call.
* The GPIO register map
* Directly interact with the GPIO
* New maximum frequency 
* Generating multiple waves simultaneously

__Ideas:__
* FM transmission on a GPIO pin
* Asking questions in sli.do

---------------------------------------------

## Generating a Square Wave 

In this Lecture we will look deeply at the General Purpose Input Output (GPIO) pins of our TinyPico device.

![](imgs/ESP32_Function_Block_Diagram_highlight_GPIO_smaller.svg)

The TinyPico has 34 physical General Purpose Input Output (GPIO) pins, sometimes referred to as pads. 
These pins can be connected to various hardware peripheras in our ESP32, such as communication protocol hardware like UART or I2C. 
In this lecture we are going to try and push the GPIO of our TinyPico to it's limits and look underneath the hood.  

__Experimental Setup:__

![](imgs/wiring_diagram.svg)

### Recap of last lecture

Last lecture we looked at how software can interact directly with hardware through reading and writing to memory addresses.

## Experiment 1: Toggle a pin as fast as possible

Let's write a quick Arduino sketch to toggle a pin:

```C
void setup() {
    pinMode(23, OUTPUT);
}


void loop() {
    digitalWrite(23, HIGH);
    delay(500);
    digitalWrite(23, LOW);
    delay(500);
}
```

Let's recap what all of this means:
* ``pinMode(23, OUTPUT);`` -- this function setup the GPIO pin 23 as a digital output
* ``digitalWrite(23, HIGH);`` -- this function writes a ``HIGH`` value to pin 23 (+5v/+3.3v)
* ``digitalWrite(23, LOW);`` -- this function writes a ``LOW`` value to pin 23 (0V)
* ``delay(500)`` -- this function delays the execution of the ESP32 by 500ms

Let's look at the LA (Logic Analyser) trace to see what this looks like: 

![](imgs/delayed_digi_write_square_wave_pulseview.png)

Measuring the period of the wave we can see that we get a square wave on channel 0, which is monitoring pin 23 of our TinyPico. This square wave is roughly 1 Hz, which makes sense, we are keeping the signal high for 500ms and low for 500ms and 1/(1000ms) = 1 Hz. However, we are not exactly at 1 Hz but rather 0.998Hz, why do you think that is?

The reason for this is because of the small overheads involved in the various bits of code that we have written. We will have:

* __function call overheads:__ when we call functions such as ``digitalWrite()`` or ``delay()``.
* __looping overheads:__ when we reach the end of our ``loop()`` function we have a branch instruction where our ``loop()`` function is called again. 

You'd expect these to be small, afterall our ESP32 is running at ``240MHz``. But it's effects are still measurable even when only generating a 1Hz wave.

__Let's see what happens when we try to go as fast as we can__

To make the square wave oscillate faster the first thing we should do is remove the calls to ``delay(500);`` in the loop body. Let's see what waveform the following code produces:

```C
void setup() {
    pinMode(23, OUTPUT);
}


void loop() {
    digitalWrite(23, HIGH);
    digitalWrite(23, LOW);
}
```

Capturing and measuring this signal on pulseview we get the following:

![](imgs/digi_write_as_fast_as_poss.png)

__As expected this is much faster.__ We now have a square wave that is oscillating at pretty much exactly 3MHz. However, we can notice some slightly odd things about this waveform, the amount of time LOW is greater than the amount of time HIGH. In electronic engineering speak, this is called the _mark-to-space_ ratio.

![](imgs/mark_time.png)

Focussing just on the time that the pin spends high we can see that it remains high for 125ns.

![](imgs/space_time.png)

And if we look at the amount of time that the pin spends low, we can see that is is low for 208.33ns.
This makes sense if we think about the overheads that we still have remaining:
* __Function call overheads__ -- incurred from calling ``digitalWrite(23, HIGH)`` and ``digitalWrite(23,LOW)``.
* __Loop overheads__ -- incurred from the branch operations and recalling of the ``loop()`` function within Arduino

In the code the following is happening, starting from the very top of the ``loop()`` function body:
1. We call the ``digitalWrite(23, HIGH);`` function.
2. After some delay, due to the function call overhead, pin 23 goes __HIGH__ at the output.
3. We call the ``digitalWrite(23, LOW);`` function.
4. After some delay, due to the function call overhead, pin 23 goes __LOW__ at the output. 
5. We exit the loop function
6. In the Arduino runtime (currently invisible to us) there is a branch instruction, i.e. the ``loop()`` function is called within a loop.
7. The Arduino runtime calls our ``loop()`` function.
8. After some delay, due to the ``loop()`` function call overhead, we are back at position 1

Points 6,7, and 8 combine to form the __loop overheads__ I was discussing above. What we can see is that after the pin has been set low these loop overheads increase the length of time that the signal is low for. What if we flip the order of our ``digitalWrite()`` calls and execute this code instead:

```C
void setup() {
    pinMode(23, OUTPUT);
}


void loop() {
    digitalWrite(23, LOW);
    digitalWrite(23, HIGH);
}
```

In this case we get the following waveform: 

![](imgs/digi_write_flipped.png)

As expected, now the loop overheads are being added to the time that the pin is spent high. 

The difference in the mark to space ratio allows us to calculate our first estimate for the __loop overheads__ of our system, by simply calculating the difference between our time spent HIGH and LOW.

In the case above the signal is high for 208.33ns and is low for 125ns, giving us an estimate of 83.33ns overhead for the loop call.
 
The time the signal is low is the ``digitalWrite()`` function call overheads which is 125ns.


