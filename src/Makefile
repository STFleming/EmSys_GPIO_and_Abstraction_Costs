PORT=/dev/ttyUSB0
EMSYS_COMP=~/EmSys/arduino-cli compile --fqbn esp32:esp32:tinypico
EMSYS_UPLOAD=~/EmSys/arduino-cli upload --fqbn esp32:esp32:tinypico

.PHONY: live

live: live/live.ino
		$(EMSYS_COMP) live 
		$(EMSYS_UPLOAD) -p $(PORT) live 

rawreg_single: rawReg_single/rawReg_single.ino
		$(EMSYS_COMP) rawReg_single
		$(EMSYS_UPLOAD) -p $(PORT) rawReg_single 

rawreg_quad: rawReg_quad/rawReg_quad.ino
		$(EMSYS_COMP) rawReg_quad
		$(EMSYS_UPLOAD) -p $(PORT) rawReg_quad 

pintoggle_1Hz: pinToggle_1Hz/pinToggle_1Hz.ino
		$(EMSYS_COMP) pinToggle_1Hz
		$(EMSYS_UPLOAD) -p $(PORT) pinToggle_1Hz

pintoggle_fast: pinToggle_fast/pinToggle_fast.ino
		$(EMSYS_COMP) pinToggle_fast
		$(EMSYS_UPLOAD) -p $(PORT) pinToggle_fast

pintoggle_fast_flipped: pinToggle_fast_flipped/pinToggle_fast_flipped.ino
		$(EMSYS_COMP) pinToggle_fast_flipped
		$(EMSYS_UPLOAD) -p $(PORT) pinToggle_fast_flipped

pintoggle_dual: pinToggle_dual/pinToggle_dual.ino
		$(EMSYS_COMP) pinToggle_dual
		$(EMSYS_UPLOAD) -p $(PORT) pinToggle_dual

pintoggle_quad: pinToggle_quad/pinToggle_quad.ino
		$(EMSYS_COMP) pinToggle_quad
		$(EMSYS_UPLOAD) -p $(PORT) pinToggle_quad

gpio_enable_bm: gpio_enable_bm/gpio_enable_bm.ino
		$(EMSYS_COMP) gpio_enable_bm
		$(EMSYS_UPLOAD) -p $(PORT) gpio_enable_bm 
