# valeur-limite-2021

## RPi setup:

The disk image for the Raspberry Pi can be found there

https://downloads.raspberrypi.org/raspios_armhf/images/raspios_armhf-2020-08-24/

___
## 4DPI-32 setup:

Once installed, launch the Raspberry Pi and open a terminal window

Type sudo raspi-config

Using the arrow keys open the submenu "7 Advanced Options" and select "A1 Expand Filesystem"

Once done, exit the config menu by pressing the Esc key

Type "sudo reboot", and wait for the Pi to reboot

Once rebooted, open a terminal window

Type "sudo wget https://wget https://4dsystems.com.au/media/downloads/4DPi/All/gen4-hats_5-4-68.tar.gz"

Type "sudo tar --no-same-owner --keep-directory-symlink -xzvf gen4-hats_5-4-68.tar.gz -C /"

Type "sudo poweroff", unplug the Raspberry Pi, install the LCD, and power it again

___
## SSH control:

As the display is quite small, it can be handy to enable remote control via SSH

Open a terminal window and type "hostname -I" to fetch the IP adress of the Raspberry Pi, note the IP adress

Type "sudo systemctl enable ssh"

Type "sudo systemctl start ssh"

Open a terminal window on another computer and type "ssh 10.113.10.207 -l pi" (replace the IP adress by the one of the Raspberry Pi)

The terminal should ask if you wish to connect to the Pi and ask for the Pi's password

Your terminal should display "pi@raspberrypi:~ $", you can then use the command line to control the Raspberry Pi

___
## Install Arduino:

Type "sudo wget https://downloads.arduino.cc/arduino-1.8.16-linuxarm.tar.xz"

Type "sudo tar -xf arduino-1.8.16-linuxarm.tar.xz"

Type "sudo mv arduino-1.8.16 /opt"

Type "sudo /opt/arduino-1.8.16/install.sh"
