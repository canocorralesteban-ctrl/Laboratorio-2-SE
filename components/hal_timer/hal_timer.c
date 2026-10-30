/**
 * @subject: Software Embebido
 * @file: hal_timer.c
 * @hardware: ESP32 (PANTHER48)
 * @authors: Esteban Cano, Paulina Cabriales
 * @date: 25/Octubre/2026
 * @descripcion: Se conectan el hal y el driver de timer
 */

#include "hal_timer.h"
#include "driver_timer.h"

esp_err_t hal_timer_init(void) {
    return driver_timer_init();
}

// El driver trabaja en microsegundos, aqui se pasa de ms a us
esp_err_t hal_timer_start(uint32_t period_ms) {
    if (period_ms == 0)
        return ESP_ERR_INVALID_ARG;

    return driver_timer_start(period_ms * 1000);
}

void hal_timer_stop(void) {
    driver_timer_stop();
}

bool hal_timer_expired(void) {
    return driver_timer_expired();
}
