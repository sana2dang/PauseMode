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


코어이름이 "lr"로 시작하는경우에만 작동합니다.

셀렉트 + 스타트키로 할당되어 있음


일시정지를 불러오는 키를 바꾸려면( 현재는 gpio 키 index로 되어있음 10번 : 셀렉트 11번 : 스타트 0번 : A버튼 )

아래 경로의 파일을 열어서

/opt/retropie/configs/all/runcommand-onstart.sh


/opt/retropie/configs/all/PauseMode/PauseMode /dev/input/js0 10 11 0 &    <==== 요놈에서

10 11 0 <=== 요부분을 바꿔준다.
== 자신의 key index 확인 방법

jstest /dev/input/js0     <== 을 통해서 키값을 알아내서 넣는다.
