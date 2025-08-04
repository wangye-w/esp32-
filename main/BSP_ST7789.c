#include "BSP_ST7789.h"

static const char *TAG = "BSP_ST7789";

void bsp_st7789_init(void)
{
    //  配置SPI总线
    spi_bus_config_t buscfg = {
        .sclk_io_num = BSP_LCD_SPI_CLK,
        .mosi_io_num = BSP_LCD_SPI_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = BSP_LCD_H_RES * BSP_LCD_V_RES * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(BSP_LCD_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO));

    //  创建LCD IO句柄
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = BSP_LCD_DC,
        .cs_gpio_num = BSP_LCD_SPI_CS,
        .pclk_hz = BSP_LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 2,
        .trans_queue_depth = 10,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)BSP_LCD_SPI_HOST, &io_config, &io_handle));

    //  安装 ST7789 面板驱动
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = BSP_LCD_RST,
        .color_space = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    //  复位 & 初始化
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    //  设置方向（0 表示正常，1/2/3 表示旋转）
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, false));

    //  开启背光
    gpio_set_direction(BSP_LCD_BCKL, GPIO_MODE_OUTPUT);
    gpio_set_level(BSP_LCD_BCKL, 1);

    //  填充颜色测试（红色）
    uint16_t *color_buf = heap_caps_malloc(BSP_LCD_V_RES * BSP_LCD_V_RES * sizeof(uint16_t), MALLOC_CAP_DMA);
    for (int i = 0; i < BSP_LCD_H_RES * BSP_LCD_V_RES; i++) {
        color_buf[i] = 0xF800; // 红色
    }
    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, BSP_LCD_V_RES, BSP_LCD_V_RES, color_buf));

    ESP_LOGI(TAG, "ST7789 init done, screen is red");
}