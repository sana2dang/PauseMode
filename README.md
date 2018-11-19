# PauseMode
라즈베리파이 게임 PauseMode

== 설치방법 ==

git clone https://github.com/sana2dang/PauseMode

cd PauseMode

sudo chmod 755 ./install.sh

./install.sh


== 수동으로 해줘야하는 작업 ==

아래 경로에서 자신이 사용하는 조이스틱 cfg 파일을 열어서 " input_exit_emulator_btn 부분을 주석처리 한다 "

경로 : /opt/retropie/configs/all/retroarch/autoconfig

input_exit_emulator_btn = "11"   <<=== 요놈을

#input_exit_emulator_btn = "11"   <=== 요렇게 바꿔야 한다.( # 붙이기 )


== GPIO 가 아닌 다른 컨트롤러 사용시 해줘야하는 작업 ==

기본적으로 GPIO의 10번, 11번, 0번 index에 할당된 키를 사용합니다.( 10번 : select , 11번 : start, 0번 : A )

GPIO가 아닌 컨트롤러 사용시 아래명령어로 자신의 컨트롤러의 셀렉트,스타트,A버튼의 index를 확인합니다.

jstest /dev/input/js0


확인했으면 아래경로의 파일을 열어 편집합니다.

경로 : /opt/retropie/configs/all/runcommand-onstart.sh


/opt/retropie/configs/all/PauseMode/PauseMode /dev/input/js0 10 11 0 &    <==== 요놈에서

10 11 0 <=== 이부분을 자신의 컨트롤러에서 확인한 index값으로 바꿔줍니다. ( 셀렉트, 스타트, A버튼 순서 )


== 이미지 변경방법 ==

아래 경로의 파일을 바꿔준다.

경로 : /opt/retropie/configs/all/PauseMode

계속하기 - pause_resume.png

게임종료 - pause_stop.png
