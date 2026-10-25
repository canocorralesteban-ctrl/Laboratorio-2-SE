/**
 * @subject: Software Embebido
 * @file: driver_timer.h
 * @hardware: ESP32 (PANTHER48)
 * @authors: Esteban Cano, Paulina Cabriales
 * @date: 25/Octubre/2026
 * @descripcion: Prototipos de las funciones del driver Timer
 */

#ifndef DRIVER_TIMER_H
#define DRIVER_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

esp_err_t driver_timer_init(void);
esp_err_t driver_timer_start(uint32_t period_us);
void driver_timer_stop(void);
bool driver_timer_expired(void);

#endif
