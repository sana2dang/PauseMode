# PauseMode
레트로아크 PauseMode

git clone https://github.com/sana2dang/PauseMode
cd PauseMode
sudo chmod 755 ./install.sh
./install.sh


--- 레트로아크 기본 핫키+스타트버튼 종료를 비활성화 시키기

---- 아래 경로의 컨피그 파일을 열어서
/opt/retropie/configs/all/retroarch/autoconfig

input_exit_emulator_btn = "11"   <<=== 요놈을

#input_exit_emulator_btn = "11"   <=== 요렇게 바꿔야 한다.

