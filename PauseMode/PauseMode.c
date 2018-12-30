/* 
 *  Pause System
 *  Author       	: sana2dang ( fly9p ) - sana2dang@naver.com / sana2dang@gmail.com
 *  Creation Date	: 2018 - 11 - 17
 *  Cafe         	: http://cafe.naver.com/raspigamer
 * 
 * - Reference -
 * 
 * jstest
 * https://github.com/flosse/linuxconsole/blob/master/utils/jstest.c
 *
 * raspidmx
 * https://github.com/AndrewFromMelbourne/raspidmx
 *
 * - complie -
 * sudo gcc PauseMode.c -o PauseMode
 * - default execmd - 
 * ./Pause /dev/input/js0 START_BTN SELECT_BTN A_BTN
 * ./Pause /dev/input/js0 10 11 0
 *
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/joystick.h>

#define NAME_LENGTH		128
#define PATH_PNGPAUSE	"/opt/retropie/configs/all/PauseMode/pngpause"		
#define PATH_PNGBG		"/opt/retropie/configs/all/PauseMode/pngbg"
#define PATH_PAUSE_RESUME	"/opt/retropie/configs/all/PauseMode/pause_resume.png"    	
#define PATH_PAUSE_STOP	"/opt/retropie/configs/all/PauseMode/pause_stop.png"    	
#define PATH_PAUSE_BG	"/opt/retropie/configs/all/PauseMode/pause_bg.png"    	


int main (int argc, char **argv)
{
	int fd, i;
	unsigned char axes = 2;
	unsigned char buttons = 2;
	int version = 0x000800;
	char name[NAME_LENGTH] = "Unknown";
	char romnm[NAME_LENGTH] = "";
	
	if (argc != 5) 
	{
		puts("");
		puts("PauseMode");
		puts("");
		puts("ex) ./PauseMode <#joystick> <select_btn_index> <start_btn_index> <a_btn_index>");
		puts("ex) ./PauseMode /dev/input/js0 10 11 0");
		puts("");
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("jstest");
		return 1;
	}

	ioctl(fd, JSIOCGVERSION, &version);
	ioctl(fd, JSIOCGAXES, &axes);
	ioctl(fd, JSIOCGBUTTONS, &buttons);
	ioctl(fd, JSIOCGNAME(NAME_LENGTH), name);

	//printf("Driver version is %d.%d.%d.\n",		version >> 16, (version >> 8) & 0xff, version & 0xff);
	//printf("Testing ... (interrupt to exit)\n");


/*
 * Event interface, single line readout.
 */

	if (argc == 5) {

		int *axis;
		char *button;
		int i;
		struct js_event js;
		
		int SELECT_BTN_ON = 0;
		int START_BTN_ON = 0;
		int PAUSE_MODE_ON = 0;
		int UP_DOWN_ON = 0;	
		char cmd[1024] = "";

		axis = calloc(axes, sizeof(int));
		button = calloc(buttons, sizeof(char));

		while (1) {
			if (read(fd, &js, sizeof(struct js_event)) != sizeof(struct js_event)) {
				perror("\njstest: error reading");
				return 1;
			}

			switch(js.type & ~JS_EVENT_INIT) {
			case JS_EVENT_BUTTON:
				button[js.number] = js.value;
				break;
			case JS_EVENT_AXIS:
				axis[js.number] = js.value;
				break;
			}

			if( axis[1] > 0)
			{
				if( PAUSE_MODE_ON == 1 )
				{
					UP_DOWN_ON = 0;	// down
					//printf("DOWN\n");
					system("sudo killall pngpause");
					sprintf(cmd, "%s -b0x0000 -l30000 %s &", PATH_PNGPAUSE, PATH_PAUSE_STOP);
					system(cmd);
					// system("/opt/retropie/configs/all/pngpause -b0 -l30000 /opt/retropie/configs/all/pause_stop.png &");
				}					
			}
			if( axis[1] < 0)
			{
				if( PAUSE_MODE_ON == 1 )
				{
					UP_DOWN_ON = 1;	// up
					//printf("UP\n");
					system("sudo killall pngpause");
					sprintf(cmd, "%s -b0x0000 -l30000 %s &", PATH_PNGPAUSE, PATH_PAUSE_RESUME);
					system(cmd);
					// system("/opt/retropie/configs/all/pngpause -b0x0000 -l30000 /opt/retropie/configs/all/pause_resume.png &");
				}
			}
			
			// A버튼
			if( button[atoi(argv[4])] == 1 )
			{
				if( PAUSE_MODE_ON == 1 && UP_DOWN_ON == 1)
				{
					//printf("restart\n");
					system("sudo killall pngpause");
					system("sudo killall pngbg");
					system("ps -ef | grep emulators | grep -v grep | awk '{print $2}' | xargs kill -SIGCONT &");
					PAUSE_MODE_ON = 0;
				}
				if( PAUSE_MODE_ON == 1 && UP_DOWN_ON == 0)
				{
					//printf("exit\n");
					system("sudo killall pngpause");
					system("sudo killall pngbg");
					system("ps -ef | grep emulators | grep -v grep | awk '{print $2}' | xargs kill -SIGCONT &");
					system("ps -ef | grep emulators | grep -v grep | awk '{print $2}' | xargs kill -SIGINT");
					exit(0);
				}
				
			}

			/// Select 버튼
			if( button[atoi(argv[2])] == 1 )
			{
				SELECT_BTN_ON = 1;
			}
			else
			{
				SELECT_BTN_ON = 0;
			}		
			// Start 버튼
			if( button[atoi(argv[3])] == 1 )
			{
				START_BTN_ON = 1;
			}
			else
			{
				START_BTN_ON = 0;
			}
			
			if( SELECT_BTN_ON == 1 && START_BTN_ON == 1 )
			{
				if( PAUSE_MODE_ON == 0)
				{
					PAUSE_MODE_ON = 1;
					UP_DOWN_ON = 1;	// up
					SELECT_BTN_ON = 0;
					START_BTN_ON = 0;
					sprintf(cmd, "%s -b0x0000 -l30000 %s &", PATH_PNGPAUSE, PATH_PAUSE_RESUME);
					system(cmd);
					sprintf(cmd, "%s -b0x0007 -l30000 %s &", PATH_PNGBG, PATH_PAUSE_BG);
					system(cmd);
					//system("/opt/retropie/configs/all/pngpause -b0x0000 -l30000 /opt/retropie/configs/all/pause_resume.png &");
					system("ps -ef | grep emulators | grep -v grep | awk '{print $2}' | xargs kill -SIGSTOP &");
				}
			}

			fflush(stdout);
		}
	}

	return -1;
}
