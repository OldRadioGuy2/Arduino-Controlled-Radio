# Arduino Controlled Radio Functional Specification
## Introduction
The Arduino Controlled Radio can be used for a variety of purposes but it's primary use case is to replace the electronics of a "worn out" vintage radio while
maintaining the radio's user controls. The Arduino determines the positions of the tuning capacitor, volume control, and band switch (if any) and translates them
into commands that are sent to the Si4735 AM/SW/FM receiver IC. The output of the IC is buffered for use with headphones or external stereo amplifier while an 
optional Class D amplifier module provides sufficient power to drive a modern speaker placed in the cabinet.

In addition to responding to the radios controls, the Arduino also monitors the serial port and a Bluetooth receiver for various commands so that the board can be configured and operated from a PC or Android/iPhone acting as a "remote control."

## Hardware
The hardware consists of the following major components:

- An Arduino Nano processor
- An HC-06 Bluetooth receiver
- A Skyworks SI4735 AM/SW/FM receiver IC
- A TL082 based stereo headphone buffer amplifier
- A TPA3118 based class D monophonic amplifier module (multi-sourced)

### Arduino Nano I/O
Arduino pins D3-D9 and A0-A3 are brought out to the board edge as I/O resources. An additional input is used to determine the position of the host radio's tuning dial by measuring value of the variable capacitor using an NE555C as a timer in one-shot mode with the capacitor controlling the pulse time. D13 triggers the one shot and A7 is used as a digital input to measure the pulse width.

D11(TxD out) and D12(RxD in) are used as a software serial port to communicate with the HC-06.

A4(SDIO) and A5(SCLK) are used as an I2C interface to the SI4735 while D2 is the  device reset.

### HC-06
The HC-06 is a slave only Bluetooth receiver with a serial interface that defaults to 9600 Baud. The module supports a limited AT command set. Of interest to us:

- **Set Name:**  *AT+NAMEnewname* sets the Bluetooth device name. This should return *OKnewname*
- **AT+PINxxxx:** *AT+PINxxxx* sets the pairing pin. This should return *OKxxxx*

### SI4735
The SI4735 is a general purpose single chip receiver with a number of features:  
  
- Worldwide FM band support (64–108 MHz)
- Worldwide AM band support (520–1710 kHz)
- SW band support (2.3–26.1 MHz)
- LW band support (153–279 kHz)
- Excellent real-world performance
- Freq synthesizer with integrated VCO
- Advanced seek tuning
- Automatic frequency control (AFC)
- Automatic gain control (AGC)
- Digital FM stereo decoder
- Programmable AVC max gain
- Programmable de-emphasis
- Seven selectable AM channel filters
- AM/FM/SW/LW digital tuning
- Programmable reference clock
- Volume control
- Adjustable soft mute control
- RDS/RBDS processor (Si4735)
- Optional digital audio out (Si4735)
- 2-wire and 3-wire control interface
- Wide range of ferrite loop sticks and
air loop antennas supported

It has an extensive programming command set which can be found here:
https://www.skyworksinc.com/-/media/Skyworks/SL/documents/public/application-notes/AN332.pdf

This project will use a (possibly modified) version of the interface library written in 2019 by Ricardo Lima Caratti.


## Software
The Software Consists of the following primary components:  
  
- **Setup:** Initializes the hardware, loads the stored configuration
- **Loop:** Performs the repetitive tasks needed to implement the following functionality:
    + **Check the tuner position (if enabled):** trigger and time the NE555C. Calculate the current position using the stored calibration points. If changed from last reading by more than the (band dependent) threshold, update the receiver frequency.
	+ **Check volume control (if enabled):** Read the configured Analog input and convert to position. If changed more than the threshold, update the volume.
	+ **Check the band switch (if enabled):** The bandswitch will be wired as a voltage divider so that each position will register a discrete voltage. Read the configured Analog input and convert to band #. Get the current band parameters from the configuration store.
	+ **Check the Arduino Serial Port for a command: ** If one was received call the *Command Processor*
	+ **If the Bluetooth receiver is paired, check its Serial Port for a command: ** If one was received call the *Command Processor*.
- **Command Processor:** Translates the received commands into actions. The key action classes are:
	+ **Get/Set SI4735 parameter:** Examples include changing frequency, volume, band, etc.
	+ **Get/Set Configuration Parameter:** Examples include defining bands, features used, etc.
	+ **Calibrate:** Determine physical to internal conversions such as NE555C pulse width vs tuner position, voltage values for band switch, etc.
- **Storage Manager** - Get/Set parameters in non-volatile storage.

