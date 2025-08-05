#include <stdio.h>
#include "BSP_ST7789.h"
#include "BSP_IO_Extension.h"

void app_main(void)
{
    pca9557_init(void);
    bsp_lcd_init();
}
