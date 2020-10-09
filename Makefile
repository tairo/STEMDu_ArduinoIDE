install-tools:
	cd hardware/;tar cvf - . | (cd ~tairo/Documents/Arduino/hardware;tar xvf -)
	cd ~tairo/Documents/Arduino/hardware/STEMDu;cp -r avr/libraries/* esp32/libraries/
	cd ~tairo/Documents/Arduino/hardware/STEMDu/esp32/tools/;python get.py

install:
	cd hardware/;tar cvf - . | (cd ~tairo/Documents/Arduino/hardware;tar xvf -)
	cd ~tairo/Documents/Arduino/hardware/STEMDu;cp -r avr/libraries/* esp32/libraries/

removeall:
	cd ~tairo/Documents/Arduino/hardware/;rm -rf STEMDu
