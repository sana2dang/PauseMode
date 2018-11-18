#!/usr/bin/env bash
# added and modified by zzeromin, zerocool ( 2016-10-13 )
# special thanks to zerocool
# Reference:
# runcommand of Retorpie:  https://github.com/retropie/retropie-setup/wiki/runcommand
# basic script:  https://retropie.org.uk/forum/topic/3731/solved-variables-with-runcommand-onstart-sh/9
# edit and path: $ sudo nano /opt/retropie/configs/all/runcommand-onstart.sh

# get the system name
system=$1

# get the emulator name
emul=$2

# get the full path filename of the ROM
rom=$3

echo $2 > /opt/retropie/configs/all/log.txt

/opt/retropie/configs/all/PauseMode/PauseMode /dev/input/js0 10 11 0 &