/**
 * @subject: Software Embebido
 * @file: bsp.c
 * @hardware: ESP32 (PANTHER48)
 * @authors: Esteban Cano, Paulina Cabriales
 * @date: 22/Octubre/2026
 * @descripcion: Archivo bsp.c de la placa Panther48
 */

#include "bsp.h"
#include "hal_gpio.h"

esp_err_t bsp_init(void) {

    static const led_t leds[] = {LED_2, LED_4, LED_5, LED_16, LED_17};
    static const button_t buttons[] = {BTN_1, BTN_2};

    for(unsigned int i = 0; i < sizeof(leds) / sizeof (leds[0]); i++) {
        if(hal_gpio_init(leds[i], HAL_OUTPUT, HAL_NONE_PULL) != ESP_OK)
            return ESP_FAIL;
        hal_gpio_write(leds[i], false);
    }

    for(unsigned int i = 0; i < sizeof(buttons) / sizeof (buttons[0]); i++) {
        if(hal_gpio_init(buttons[i], HAL_INPUT, HAL_PULL_UP) != ESP_OK)
            return ESP_FAIL;
    }

    return ESP_OK;
}

void bsp_led_on(led_t led) {
    hal_gpio_write(led, true);
}

void bsp_led_off(led_t led) {
    hal_gpio_write(led, false);
}

bool bsp_btn_pressed(button_t btn) {
    return !hal_gpio_read(btn);
}