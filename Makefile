.PHONY: install-tools install removeall install-core-lib remove-core-lib

RM=rm -rf

CORELIB=STEM_Du

SRCHARDWARE=hardware
SRCLIBS=$(SRCHARDWARE)/STEMDu/avr/libraries

DSTBASE=~tairo/Documents/Arduino
DSTHARDWARE=$(DSTBASE)/hardware
DSTLIBS=$(DSTHARDWARE)/STEMDu/avr/libraries

DSTLIBS_ESP32=$(DSTHARDWARE)/STEMDu/esp32/libraries

install-all:
	cd hardware/;tar cvf - . | (cd ~tairo/Documents/Arduino/hardware;tar xvf -)
	cd ~tairo/Documents/Arduino/hardware/STEMDu;cp -r avr/libraries/* esp32/libraries/
	cd ~tairo/Documents/Arduino/hardware/STEMDu/esp32/tools/;python get.py

install:
	cd hardware/;tar cvf - . | (cd ~tairo/Documents/Arduino/hardware;tar xvf -)
	cd ~tairo/Documents/Arduino/hardware/STEMDu;cp -r avr/libraries/* esp32/libraries/

install-stemdulib:
	cd hardware/STEMDu/avr/libraries/;cp -r STEM_Du ~tairo/Documents/Arduino/hardware/STEMDu/avr/libraries/
	cd hardware/STEMDu/avr/libraries/;cp -r STEM_Du ~tairo/Documents/Arduino/hardware/STEMDu/esp32/libraries/

removeall:
	cd $(DSTHARDWARE);$(RM) STEMDu

install-core-lib:
	cd $(SRCLIBS)/;tar cvf - $(CORELIB) | (cd $(DSTLIBS);tar xvf -)
	cd $(SRCLIBS)/;tar cvf - $(CORELIB) | (cd $(DSTLIBS_ESP32);tar xvf -)

remove-core-lib:
	$(RM) $(DSTLIBS)/$(CORELIB)
	$(RM) $(DSTLIBS_ESP32)/$(CORELIB)
