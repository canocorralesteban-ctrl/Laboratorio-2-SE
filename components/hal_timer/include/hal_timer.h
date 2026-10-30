/**
 * @subject: Software Embebido
 * @file: hal_timer.h
 * @hardware: ESP32 (PANTHER48)
 * @authors: Esteban Cano, Paulina Cabriales
 * @date: 25/Octubre/2026
 * @descripcion: Prototipos del HAL de timer
 */

#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

esp_err_t hal_timer_init(void);
esp_err_t hal_timer_start(uint32_t period_ms);
void hal_timer_stop(void);
bool hal_timer_expired(void);

#endif
