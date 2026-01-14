# bbn_compass
NMEA compass with IMU. The device will transmit NMEA 0183 sentences for magnetic heading, roll, pitch, rate of turn. 
It can be used directly with OpenCPN running on Windows or Linux.

<p align="center">
<img src="./images/bbn_compass_screen.jpg?raw=true" style="width: 75%; height: auto;" alt="BBN Compass pic1" />
</p>

## Hardware

- M5Stack __AtomS3R__ esp32: https://docs.m5stack.com/en/core/AtomS3R
- M5stack __ATOMIC PortABC Extension Base__: https://shop.m5stack.com/products/atomic-portabc-extension-base

### Enclosure, etc

- Waterproof IP67 box 4.7"x3.5"x2.7" or bigger. Hinged with transparent lid, base plate and legs
- Various cable glands
- M3 standoffs
- USB-C to USB-A cables with small support tang on USB-C end


## Firmware 

atomS3R_compass.ino in atomS3R is an ArduinoIDE sketch which you would need to compile and load to
atomS3R.

For required libraries and their versions check:
.github/workflows/build.yaml

## Calibration

Calibration is performed directly on AtomS3R in three steps:

- Accelerometer. Follow instructions on the screen. On AtomS3R screen is a button (BntA). You will need to to device in 6 poses (still).
- Gyroscope calibration is performed by putting device still with screen up.
- Magnetometer calibration achived by rotating device around all axises for around 45 seconds.

<p align="center">
<img src="./images/bbn_compass_calibration.jpg?raw=true" style="width: 75%; height: auto;" alt="BBN Compass pic2" />
</p>

