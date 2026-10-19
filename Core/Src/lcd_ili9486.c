/*
 * lcd_ili9486.c
 *
 *  Created on: Oct 19, 2026
 *      Author: Dennis
 */


#include "lcd_ili9486.h"

#include "main.h"

extern SPI_HandleTypeDef hspi1;




bool lcd_init()
{
	lcd_nreset();

	// startup sequence
	lcd_cmd(0xf2);
	lcd_data(0x18);
	lcd_data(0xA3);
	lcd_data(0x12);
	lcd_data(0x02);
	lcd_data(0xB2);
	lcd_data(0x12);
	lcd_data(0xFF);
	lcd_data(0x10);
	lcd_data(0x00);

	lcd_cmd(0xf8);
	lcd_data(0x21);
	lcd_data(0x04);
	lcd_data(0x04);

	lcd_cmd(0xf8);
	lcd_data(0x00);
	lcd_data(0x08);

	lcd_cmd(LCD_CMD_MEM_ACCESS_CTR);
	lcd_data(0x08);

	lcd_cmd(LCD_CMD_DISP_INV_CTR);
	lcd_data(0x00);

	lcd_cmd(LCD_CMD_DISP_FUNC_CTR);
	lcd_data(0x02);
	lcd_data(0x22);

	lcd_cmd(LCD_CMD_PWR_CTR2);
	lcd_data(0x41);

	lcd_cmd(LCD_CMD_VCOM_CTR1);
	lcd_data(0x00);
	lcd_data(0x18);

	lcd_cmd(LCD_CMD_PGAMCTRL);
	lcd_data(0x0F);
	lcd_data(0x1F);
	lcd_data(0x1C);
	lcd_data(0x0C);
	lcd_data(0x0F);
	lcd_data(0x08);
	lcd_data(0x48);
	lcd_data(0x98);
	lcd_data(0x37);
	lcd_data(0x0A);
	lcd_data(0x13);
	lcd_data(0x04);
	lcd_data(0x11);
	lcd_data(0x0D);
	lcd_data(0x00);

	lcd_cmd(LCD_CMD_NGAMCTRL);
	lcd_data(0x0F);
	lcd_data(0x32);
	lcd_data(0x2E);
	lcd_data(0x0B);
	lcd_data(0x0D);
	lcd_data(0x05);
	lcd_data(0x47);
	lcd_data(0x75);
	lcd_data(0x37);
	lcd_data(0x06);
	lcd_data(0x10);
	lcd_data(0x03);
	lcd_data(0x24);
	lcd_data(0x20);
	lcd_data(0x00);

	lcd_cmd(LCD_CMD_SLEEP_OUT);
	HAL_Delay(120);

	lcd_cmd(LCD_CMD_DISP_ON);
	return true;
}

void lcd_nreset()
{
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
	HAL_Delay(120);
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

void lcd_data_bulk(uint8_t* p_data, uint32_t size)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, p_data, size, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

}

void lcd_window_set(uint16_t col_start,uint16_t col_end, uint16_t row_start, uint16_t row_end)
{

	lcd_col_set(col_start, col_end);
	lcd_row_set(row_start, row_end);
}

void lcd_row_set(uint16_t row_start, uint16_t row_end)
{
	uint8_t y_start_high = (row_start >> 8) & 0xFF;
	uint8_t y_start_low = row_start & 0xFF;

	uint8_t y_end_high = (row_end >> 8) & 0xFF;
	uint8_t y_end_low = row_end & 0xFF;

	lcd_cmd(LCD_CMD_PAGE_ADDR_SET);
	lcd_data(y_start_high);
	lcd_data(y_start_low);
	lcd_data(y_end_high);
	lcd_data(y_end_low);
}

void lcd_col_set(uint16_t col_start,uint16_t col_end)
{
	uint8_t x_start_high = (col_start >> 8) & 0xFF;
	uint8_t x_start_low = col_start & 0xFF;

	uint8_t x_end_high = (col_end >> 8) & 0xFF;
	uint8_t x_end_low = col_end & 0xFF;

	lcd_cmd(LCD_CMD_COL_ADDR_SET);
	lcd_data(x_start_high);
	lcd_data(x_start_low);
	lcd_data(x_end_high);
	lcd_data(x_end_low);
}

void lcd_window_write(uint16_t* p_data, uint32_t size )
{
	lcd_cmd(LCD_CMD_MEM_WRITE);
	lcd_data_bulk((uint8_t*)p_data, size * 2);
}
