install:
	cd hardware/;tar cvf - . | (cd ~tairo/Documents/Arduino/hardware;tar xvf -)
	cd ~tairo/Documents/Arduino/hardware/STEMDu;cp -r avr/libraries/* esp32/libraries/