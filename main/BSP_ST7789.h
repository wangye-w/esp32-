#ifndef __BSP_ST7789_H
#define __BSP_ST7789_H

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "esp_err.h"

#define BSP_LCD_SPI_HOST                    (SPI3_HOST)  // ESP32-S3 的 HSPI
#define LCD_PIXEL_CLOCK_HZ          (80 * 1000 * 1000)
#define BSP_LCD_SPI_MOSI            (GPIO_NUM_40)
#define BSP_LCD_SPI_CLK             (GPIO_NUM_41)
#define BSP_LCD_SPI_CS              (GPIO_NUM_NC)
#define BSP_LCD_DC                  (GPIO_NUM_39)
#define BSP_LCD_RST                 (GPIO_NUM_NC)
#define BSP_LCD_BCKL                (GPIO_NUM_42)

#define BSP_LCD_H_RES               (320)
#define BSP_LCD_V_RES               (240)


void bsp_st7789_init(void);

#endif