sudo cp ./libraspidmx.so.1 /usr/lib

mkdir /opt/retropie/configs/all/PauseMode/
cp -f -r ./PauseMode /opt/retropie/configs/all/

sudo chmod 755 /opt/retropie/configs/all/PauseMode/PauseMode
sudo chmod 755 /opt/retropie/configs/all/PauseMode/pngpause
sudo chmod 755 /opt/retropie/configs/all/PauseMode/pngbg

sudo sed -i '/PauseMode/d' /opt/retropie/configs/all/runcommand-onstart.sh
echo '/opt/retropie/configs/all/PauseMode/PauseMode /dev/input/js0 10 11 0 &' >> /opt/retropie/configs/all/runcommand-onstart.sh

sudo sed -i '/pngpause/d' /opt/retropie/configs/all/runcommand-onend.sh
sudo sed -i '/pngbg/d' /opt/retropie/configs/all/runcommand-onend.sh
sudo sed -i '/PauseMode/d' /opt/retropie/configs/all/runcommand-onend.sh

echo 'sudo killall pngpause' >> /opt/retropie/configs/all/runcommand-onend.sh
echo 'sudo killall pngbg' >> /opt/retropie/configs/all/runcommand-onend.sh
echo 'sudo killall PauseMode' >> /opt/retropie/configs/all/runcommand-onend.sh

echo 'good luck'
