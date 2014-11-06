#include "AVIX.h"

//#include "Define.h"
//#include "CONFIGbits.h"
#include "ELBv21_HardwareConfig.h"


//Module wise includes
#include "master.h"
#include "astar_thread.h"
#include "ping.h"
#include "servo.h"
#include "imu.h"
#include "xbee.h"
#include "motor.h"
#include "std_int.h"
//	-----------------------------------------------------------------------------------------------
//	External function declarations.
//	-----------------------------------------------------------------------------------------------
extern void systemSetup(void);


//	===============================================================================================
//	FUNCTION:	myErrorFunc
//	=======================
//	Central AVIX error handler. Set breakpoint at while loop to catch errors in development
//	environment
//	===============================================================================================
//
void myErrorFunc(tavixErrorCode errorCode)
{
    printf("%d\n",errorCode);
	while(1);
}



//	===============================================================================================
//	FUNCTION:	avixMain
//	====================
//	Main function for AVIX based project. From here specific selected tutorial function is called.
//	===============================================================================================
//


void avixMain(void)
{
     //---------------------------------------------------------------------------------------------
     // Setup the system and install an AVIX central error handler.
     //---------------------------------------------------------------------------------------------
     systemSetup();
     avixError_SetHandler(myErrorFunc);
     LCD_INIT();
     LED2_DIR = DIR_OUT;
     LED3_DIR = DIR_OUT;
     avixExch_Create("degrees", sizeof(F32), NULL);
     avixExch_Create("map", HEIGHT*WIDTH*sizeof(uint8_t), NULL);
     avixThread_Create("master_thread", master_thread, NULL, 1,500, AVIX_THREAD_READY);
     avixThread_Create("imu_thread", imu_thread, NULL, 1,500, AVIX_THREAD_READY);
     avixThread_Create("motor_thread", motor_thread, NULL, 1,500, AVIX_THREAD_READY);
     avixThread_Create("servo_thread", servo_thread, NULL, 1,500, AVIX_THREAD_READY);
     avixThread_Create("xbee_thread", xbee_thread, NULL, 1,500, AVIX_THREAD_READY);
}


