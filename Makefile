.PHONY: install-tools install removeall install-core-lib remove-core-lib

RM=rm -rf

CORELIB=STEM_Du

SRCHARDWARE=hardware
SRCLIBRALY=library
SRCBOARDS=boards
SRCVARIANTS=variants

DSTBASE=~tairo/Documents/Arduino

SRCLIBS_STEMDU=$(SRCLIBRALY)/core
SRCLIBS_COMMON=$(SRCLIBRALY)/common
SRCLIBS_AVR=$(SRCLIBRALY)/avr
SRCLIBS_ESP32=$(SRCLIBRALY)/esp32
SRCBOARDS_ESP32=$(SRCBOARDS)/boards_esp32.txt
SRCVARIANTS_ESP32=$(SRCVARIANTS)/esp32

DSTHARDWARE=$(DSTBASE)/hardware

DSTLIBS_AVR=$(DSTHARDWARE)/STEMDu/avr/libraries/
DSTLIBS_ESP32=$(DSTHARDWARE)/STEMDu/esp32/libraries/

install-all: install
	cd $(DSTBASE)/hardware/STEMDu/esp32/tools/;python get.py

install: install-core install-stemdulib
	cp -r $(SRCLIBS_COMMON)/* $(DSTLIBS_AVR)
	cp -r $(SRCLIBS_AVR)/* $(DSTLIBS_AVR)
	cp -r $(SRCLIBS_COMMON)/* $(DSTLIBS_ESP32)
	cp -r $(SRCLIBS_ESP32)/* $(DSTLIBS_ESP32)
	cp -f $(SRCBOARDS_ESP32) $(DSTHARDWARE)/STEMDu/esp32/boards.txt
	cp -r $(SRCVARIANTS_ESP32)/* $(DSTHARDWARE)/STEMDu/esp32/variants/

install-core:
	cd $(SRCHARDWARE)/;tar cvf - . | (cd $(DSTHARDWARE);tar xvf -)

install-stemdulib:
	cp -r $(SRCLIBS_STEMDU)/* $(DSTLIBS_AVR)
	cp -r $(SRCLIBS_STEMDU)/* $(DSTLIBS_ESP32)

remove-stemdulib:
	$(RM) $(DSTLIBS_AVR)/$(CORELIB)
	$(RM) $(DSTLIBS_ESP32)/$(CORELIB)

removeall:
	cd $(DSTHARDWARE);$(RM) STEMDu
