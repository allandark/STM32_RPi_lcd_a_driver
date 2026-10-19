/*
 * lcd_ili9486.c
 *
 *  Created on: Oct 19, 2026
 *      Author: Dennis
 */


#include "lcd_ili9486.h"

extern SPI_HandleTypeDef hspi1;




bool lcd_init()
{

	return true;
}

void lcd_nreset()
{
	GPIO_PinState pin_state = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, pin_state);
}

void lcd_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

}

void lcd_data(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
