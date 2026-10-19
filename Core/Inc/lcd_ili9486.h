/*
 * lcd_driver.h
 *
 *  Created on: Oct 19, 2026
 *      Author: Dennis
 */

#ifndef INC_LCD_ILI9486_H_
#define INC_LCD_ILI9486_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define LCD_SCREEN_WIDTH 320U
#define LCD_SCREEN_HEIGHT 480U



bool lcd_init();

void lcd_nreset();
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);




#endif /* INC_LCD_ILI9486_H_ */
