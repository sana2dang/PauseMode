mkdir /opt/retropie/configs/all/PauseMode/
sudo cp -f -r ./ /opt/retropie/configs/all/PauseMode/

sudo chmod 755 /opt/retropie/configs/all/PauseMode/PauseMode
sudo chmod 755 /opt/retropie/configs/all/PauseMode/pngview

sudo sed -i '/PauseMode/d' /opt/retropie/configs/all/runcommand-onstart.sh
echo '/opt/retropie/configs/all/PauseMode/PauseMode /dev/input/js0 10 11 0 &' >> /opt/retropie/configs/all/runcommand-onstart.sh

sudo sed -i '/pngview/d' /opt/retropie/configs/all/runcommand-onend.sh
sudo sed -i '/PauseMode/d' /opt/retropie/configs/all/runcommand-onend.sh

echo 'sudo killall pngview' >> /opt/retropie/configs/all/runcommand-onend.sh
echo 'sudo killall PauseMode' >> /opt/retropie/configs/all/runcommand-onend.sh
