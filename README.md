# przestszept-arduino
Arduino code for the przestszept interactive installation

`sketch.ino` reads the state from sensors conected to Mega's 2-50 digital
pins (49 total; 7x7 sensor matrix) and acts as a keyboard. It is
connected via USB to RaspberryPi computer which reacts to keypresses by
playing audio samples. Code for the RasPi part can be found in
[przestszept-raspi repo](https://github.com/mczyzewski/przestszept-raspi).

`dfu-howto.txt` describes how to flash Arduino's DFU bootloader to
simulate keyboard behaviour. Hex files:
 - `Arduino-usbserial-mega.hex` (included; normal serial mode for Arduino
   programming)
 - [Arduino-keyboard.hex from harlequin-tech/arduino-usb](https://github.com/harlequin-tech/arduino-usb/blob/master/firmwares/Arduino-keyboard.hex) (keyboard mode)
