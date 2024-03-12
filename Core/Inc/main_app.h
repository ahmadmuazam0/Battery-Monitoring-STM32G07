<<<<<<< HEAD
/*
 * main_app.h
 *
 *  Created on: Jun 11, 2023
 *      Author: Ahmad Muazam
 */

#ifndef INC_MAIN_APP_H_
#define INC_MAIN_APP_H_

=======
#ifndef __MAIN_APP_H
#define __MAIN_APP_H

#ifdef __cplusplus
extern "C" {
#endif
>>>>>>> 3eca1d0bbe1aa4dfc8139960ad98441eb06ff2c8

    #include "main.h"
	#include "Variables.h"
	#include "stdbool.h"


 typedef union							// module send to Lop
{	uint8_t data;
	struct
	{
		uint8_t B0				:1;
		uint8_t B1				:1;
		uint8_t B2				:1;
		uint8_t B3				:1;
		uint8_t B4				:1;
		uint8_t B5				:1;
		uint8_t B6				:1;
		uint8_t B7				:1;
	}bit;

}Flag8_t;

typedef enum
{
	oneClick = 0,
	Hold,
	ButtonStatus_notPressed
}ButtonStatus_e;

typedef struct
{
	uint16_t 			buttonTimer;
	bool 				buttonTimerEnable;
	ButtonStatus_e	    buttonStatus;
	Flag8_t 			buttonFlag;
	uint8_t 			HoldPressCounter;
}MenuButton_t;

// Brightness Mode for LEDS
typedef enum
{
    brightnessMode_LOW = 0,
    brightnessMode_MID,
    brightnessMode_HIGH,
    brightnessMode_SOS,
    MCU_sleep
}BrightnessMode_t;

// Colors of Leds
<<<<<<< HEAD
typedef enum
=======
typedef enum 
>>>>>>> 3eca1d0bbe1aa4dfc8139960ad98441eb06ff2c8
{
    /* data */
    Red = 0,
    Green,
    Blue,
    Yellow,
    Magenta,
    Cyan,
    White
}RGBColors_t;

typedef enum
{
	High = 0,
	Med,
	Low,
	SOS
}RGBModes_t;

    void main_app(void);

<<<<<<< HEAD


#endif /* INC_MAIN_APP_H_ */
=======
#ifdef __cplusplus
}
#endif
#endif  /*  MAIN_APP_H  */
>>>>>>> 3eca1d0bbe1aa4dfc8139960ad98441eb06ff2c8
