/*
 * main_app.c
 *
 *  Created on: Jun 11, 2023
 *      Author: Ahmad Muazam
 */


#include "main_app.h"

uint16_t  timer = 0;
 uint16_t adcValue = 0;   // ADC value read from battery
 uint8_t batteryPercentage = 0;   // Battery percentage calculated from ADC value
 uint8_t Color_sel = 0;    // Current LED color (0-3)
 uint8_t Brightness = 100;    // Current LED brightness (0-100)
 uint16_t *sleepTimer;
bool colorFlag = false;
uint32_t duty;
uint32_t SOS_duty = 99;
uint8_t colorState = 0;
uint8_t RGBmode = 0;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;
MenuButton_t hMode_Sel, hColor_Sel;

/*	====================
	To get sysTick value
	====================	*/
void setTimer(uint16_t* timer)
{
	*timer = HAL_GetTick();
}

/*	================================================
	To chek the pushbutton timer to get button state
	================================================	*/
uint8_t checkTimer(uint16_t* timer, uint16_t msTime)
{
	uint8_t ret = RESET;
	ret = ((HAL_GetTick() - *timer) > msTime)  ? ENABLE : DISABLE;
	return ret;
}

/*	===============================
	To put the system in sleep Mode
	===============================	*/

void GoToSleep(){

	// Any prephiral intrupt acknowledged by the NVIC can wake up the device  Refer to: STM32G0x0 Reference manual (Page: 93,98)
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI) ;

}
/*	========================================================
	Function to control the LEDs based on battery percentage
	========================================================	*/
void controlLEDs()
{
    if (batteryPercentage >= 10) {
        if (batteryPercentage >= 75) {
            HAL_GPIO_WritePin(GPIOA,LED_1_Pin,SET);
            HAL_GPIO_WritePin(GPIOA,LED_2_Pin,SET);
            HAL_GPIO_WritePin(GPIOA,LED_3_Pin,SET);
            HAL_GPIO_WritePin(GPIOA,LED_4_Pin,SET);


        } else if(batteryPercentage <= 74  && batteryPercentage >= 51) {

            HAL_GPIO_WritePin(GPIOA,LED_1_Pin,SET);
			HAL_GPIO_WritePin(GPIOA,LED_2_Pin,SET);
			HAL_GPIO_WritePin(GPIOA,LED_3_Pin,SET);
			HAL_GPIO_WritePin(GPIOA,LED_4_Pin,RESET);

        }
		else if (batteryPercentage <= 50  && batteryPercentage >= 26)
		{
			HAL_GPIO_WritePin(GPIOA,LED_1_Pin,SET);
			HAL_GPIO_WritePin(GPIOA,LED_2_Pin,SET);
			HAL_GPIO_WritePin(GPIOA,LED_3_Pin,RESET);
			HAL_GPIO_WritePin(GPIOA,LED_4_Pin,RESET);

		}
		else if (batteryPercentage <= 25  && batteryPercentage >= 10)
		{
			HAL_GPIO_WritePin(GPIOA,LED_1_Pin,SET);
			HAL_GPIO_WritePin(GPIOA,LED_2_Pin,RESET);
			HAL_GPIO_WritePin(GPIOA,LED_3_Pin,RESET);
			HAL_GPIO_WritePin(GPIOA,LED_4_Pin,RESET);

		}


    } else {

    		HAL_GPIO_WritePin(GPIOA,LED_1_Pin,RESET);
			HAL_GPIO_WritePin(GPIOA,LED_2_Pin,RESET);
			HAL_GPIO_WritePin(GPIOA,LED_3_Pin,RESET);
			HAL_GPIO_WritePin(GPIOA,LED_4_Pin,RESET);
    }
}

/*	==================================================
	To calculate the battery percentage from ADC value
	==================================================	*/
inline void calculateBatteryPercentage()
{
    batteryPercentage = (adcValue * 100) / 12;
}

/*	=========================================
	To get the ADC value from the ADC intrupt
	=========================================	*/

void getBatteryValue(){
	adcValue = HAL_ADC_GetValue(&hadc1);
	calculateBatteryPercentage(); // Calculate battery percentage
	controlLEDs(); // Control LEDs based on battery percentage

}


/*	========================================
	To avoid the false input of push buttons
	========================================	*/

uint8_t Button_Debounce(GPIO_TypeDef *GPIO_Port, uint8_t GPIO_Pin)
{
	uint8_t 		ret = DISABLE;
	static uint16_t Level = Restart_Level;
	if(!HAL_GPIO_ReadPin(GPIO_Port, GPIO_Pin))
	{
		++Level;
	}
	else
	{
		--Level;
		if(Level <= Restart_Level)
		{
			Level = Restart_Level;
		}
	}
	if(Level >= 4000)
	{
		Level = Acceptance_Level;
		ret = ENABLE;
	}
	return ret;
}

/*	=============================
	To get the button press state
	=============================	*/

void  Button_press(MenuButton_t *Button, GPIO_TypeDef *GPIO_Port, uint8_t GPIO_Pin)
{

		  if(Button_Debounce(GPIO_Port,GPIO_Pin))											//Apply de-bounce algorithm before taking any action
		  {
			  Button->buttonFlag.bit.B0 = RESET;						//Reset interrupt flag

			  if(Button->buttonTimerEnable != SET)						//Start timer when the menu button gets pressed for the first time
			  {
				  Button->buttonTimerEnable = SET;						//Enable software timer
				  Button->buttonStatus = oneClick;		//The menu button has been pressed for one time
				  setTimer(&Button->buttonTimer);						//Start software timer
			  }
		  }

	  if(checkTimer(&Button->buttonTimer, (uint16_t)(5 * Button->HoldPressCounter)) &&( Button->buttonStatus == oneClick))
	  {																		//If the menu button has been pressed, take logic sample every 10 ms from the button read pin
		  if(!HAL_GPIO_ReadPin(GPIO_Port, GPIO_Pin))		//To check if the button is still pressed
		  {
			  ++Button->HoldPressCounter;						//Increment samples number
		  }
		  Button->buttonStatus = (Button->HoldPressCounter >= Hold_Time)  ? Hold : Button->buttonStatus;	//If the button is held pressed change button status
	  }
}


/*
 * 	Change RGB Color
 */
void changeColor(){
	if(colorState == Red && colorFlag == true){
		colorState = Green;
		colorFlag = false;
	}
	else if(colorState == Green && colorFlag == true){
		colorState = Blue;
		colorFlag = false;
	}
	else if(colorState == Blue && colorFlag == true){
			colorState = Yellow;
			colorFlag = false;
		}
	else if(colorState == Yellow && colorFlag == true){
			colorState = Magenta;
			colorFlag = false;
		}
	else if(colorState == Magenta && colorFlag == true){
			colorState = Cyan;
			colorFlag = false;
		}
	else if(colorState == Cyan && colorFlag == true){
			colorState = White;
			colorFlag = false;
		}
	else if(colorState == White && colorFlag == true){
			colorState = Red;
			colorFlag = false;
		}
}

/*	================
	Control RGB LEDs
	================	*/

	void controlRGB(RGBColors_t color){

		switch (color)
		{
		case Red:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t *)duty, sizeof(duty));
			break;
		case Green:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_2,(uint32_t *)duty, sizeof(duty));
		case Blue:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_3,(uint32_t *)duty, sizeof(duty));
			break;
		case White:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)duty, sizeof(duty));
			break;
		case Yellow:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t *)duty, sizeof(duty));
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_2,(uint32_t *)duty, sizeof(duty));
			break;
		case Magenta:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t *)duty, sizeof(duty));
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_3,(uint32_t *)duty, sizeof(duty));
			break;
		case Cyan:
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
			HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_2,(uint32_t *)duty, sizeof(duty));
			HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_3,(uint32_t *)duty, sizeof(duty));
			break;
		default:
			break;
		}
	}
/*
 * Defination of SOS Mode
 */

void SOS_Mode(){

	while (RGBmode == SOS)
	{

		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));	// Dot
		HAL_Delay(200);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(200);
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));
		HAL_Delay(200);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(200);
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));
		HAL_Delay(200);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(400);																// Short Pause
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));	// Dash
		HAL_Delay(400);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(400);
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));
		HAL_Delay(400);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(400);
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));
		HAL_Delay(400);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(400);																// Short Puase
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));	// Dot
		HAL_Delay(200);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(200);
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));
		HAL_Delay(200);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(200);
		HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_4,(uint32_t *)SOS_duty, sizeof(SOS_duty));
		HAL_Delay(200);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		HAL_Delay(1500);															// Long Pause
	}
}
/*	=================
	Modes of RGB LEDs
	=================	*/

void RGB_Modes(RGBModes_t mode){

	switch (mode)
	{
	case High:
		duty = HIGH_Mode;
		break;
	case Med:
		duty = MED_Mode;
		break;
	case Low:
		duty = LOW_Mode;
		break;
	case SOS:
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_2);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_3);
		HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_4);
		SOS_Mode();
		break;
	}

}



void main_app(){

	// If there's not operation for 3 seconds the system will get into sleep mode
	// And wait for the intrupt to wake-up the system again
	if ((hColor_Sel.buttonStatus & hMode_Sel.buttonStatus) == ButtonStatus_notPressed)
	{
		setTimer(sleepTimer);
		if ((hColor_Sel.buttonStatus & hMode_Sel.buttonStatus) == ButtonStatus_notPressed && (HAL_GetTick() - (uint32_t)(&sleepTimer)>= sleepCycleTime)){

			HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI) ; // Put the system in sleep mode after 3 seconds of inactivity

		}
	}

	// If any of the intrupt get registerd on pushing the button the regarding operations will be performed

	if( hMode_Sel.buttonFlag.bit.B0 )			Button_press(&hMode_Sel, Mode_Sel_GPIO_Port, Mode_Sel_Pin);		//When the mode select intrupt will be called
	else if ( hColor_Sel.buttonFlag.bit.B0 )	Button_press(&hColor_Sel, Color_Sel_GPIO_Port, Color_Sel_Pin);	//When the Color select intrupt will be called

	if(hMode_Sel.buttonTimerEnable)
	  {																		//Take decision after 300 ms whether one click or held pressed event has occured
		  switch(hMode_Sel.buttonStatus)
		  {
		  	case    oneClick:
					getBatteryValue();
					if(RGBmode == 4) RGBmode=0;
					RGB_Modes(RGBmode);
					RGBmode++;
		  		  break;
		  	case    Hold:
					GoToSleep();
		  		 break;
		  	case    ButtonStatus_notPressed:
		  		 break;

		  }
		  hMode_Sel.buttonTimerEnable 			= RESET;					//Disable software timer
		  hMode_Sel.HoldPressCounter 			= RESET;					//Reset counter
		  hMode_Sel.buttonStatus 				= ButtonStatus_notPressed;
		  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	//button status is set to no press to avoid misbehavior of the button functionality

	  }

	if ( hColor_Sel.buttonTimerEnable)
		{
			// Change Color
			switch(hMode_Sel.buttonStatus)
		  {
		  	case    oneClick:
		  			colorState++;
					if (colorState == 7) colorState = 0;
					colorFlag = true;
					changeColor();
					controlRGB(colorState);
		  		  break;
		  	case    Hold:
		  		 break;
		  	case    ButtonStatus_notPressed:
		  		 break;

		  }
			hColor_Sel.buttonTimerEnable	= RESET;
			hMode_Sel.HoldPressCounter		= RESET;
			hColor_Sel.buttonStatus			= ButtonStatus_notPressed;
		}

}
