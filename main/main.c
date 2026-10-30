/**
 * @subject: Software Embebido
 * @file: main.c
 * @hardware: ESP32 (PANTHER48)
 * @author: Esteban Cano, Paulina Cabriales
 * @date: 30/Octubre/2026
 * @descripcion: App de prueba del firmware
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bsp.h"

void app_main(void)
{
    if (bsp_init() != ESP_OK) {
        printf("Error al iniciar el bsp\n");
        return;
    }

    while (true) {

            bsp_rgb_set(RGB_G, true);
            bsp_rgb_set(RGB_B, true);
             bsp_rgb_set(RGB_R, false);
           
        if (bsp_btn_pressed(BTN_2))
        {
            bsp_led_on(LED_4);
        }
            
        else
        {
            bsp_led_off(LED_4);
        }
            
        

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
