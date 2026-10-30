/**
 * @subject: Software Embebido
 * @file: bsp.h
 * @hardware: ESP32 (PANTHER48)
 * @author: Esteban Cano, Paulina Cabriales
 * @date: 22/Octubre/2026
 * @descripcion: BSP de la placa Panther48
 * @brief: Interfaz del BSP
 */

#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

// Pines de los leds
typedef enum {
    LED_2  = 2,
    LED_4  = 4,
    LED_5  = 5,    
    LED_16 = 16,
    LED_17 = 17
} led_t;

// Pines de los leds rgb
typedef enum {
    RGB_R = 14,
    RGB_G = 13,
    RGB_B = 12
} rgb_t;

// Pines de los botones
typedef enum {
    BTN_1 = 18,
    BTN_2 = 19
} button_t;

// Prototipo de las funciones del bsp
esp_err_t bsp_init(void);
void bsp_led_on(led_t led);
void bsp_led_off(led_t led);
void bsp_rgb_set(rgb_t rgb, bool state);
bool bsp_btn_pressed(button_t btn);
esp_err_t bsp_timer_start(uint32_t period_ms);
void bsp_timer_stop(void);
bool bsp_timer_expired(void);

#endif