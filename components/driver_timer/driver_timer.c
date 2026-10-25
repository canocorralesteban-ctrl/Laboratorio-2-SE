/**
 * @subject: Software Embebido
 * @file: driver_timer.c
 * @hardware: ESP32 (PANTHER48)
 * @authors: Esteban Cano, Paulina Cabriales
 * @date: 25/Octubre/2026
 * @descripcion: Implementacion del driver de Timer para la placa Panther48
 */

#include "driver_timer.h"
#include "driver_timer_config.h"

// Deja el timer 0 configurado pero apagado
esp_err_t driver_timer_init(void) {
    TIMG0_REGS->t0config &= ~TIMER_EN;          // Timer apagado para poder configurar
    TIMG0_REGS->t0config &= ~TIMER_DIVIDER;     // limpiar el divisor antes de cargarlo
    TIMG0_REGS->t0config &= ~TIMER_EDGE_INT;
    TIMG0_REGS->t0config |= TIMER_DIV_80 | TIMER_AUTORELOAD | TIMER_INCREASE | TIMER_LEVEL_INT;
    return ESP_OK;
}

// Arranca la cuenta y avisa cuando pasen period_us microsegundos
esp_err_t driver_timer_start(uint32_t period_us) {
    if (period_us == 0)
        return ESP_ERR_INVALID_ARG;

    // El contador es de 64 bits y el CPU de 32, por eso se carga en dos mitades
    TIMG0_REGS->t0loadlo = 0;
    TIMG0_REGS->t0loadhi = 0;
    TIMG0_REGS->t0load = 1;             

    TIMG0_REGS->t0alarmlo = period_us;
    TIMG0_REGS->t0alarmhi = 0;

    TIMG0_REGS->int_clr = TIMER_T0_INT;
    TIMG0_REGS->t0config |= TIMER_ALARM_EN | TIMER_EN;
    return ESP_OK;
}

void driver_timer_stop(void) {
    TIMG0_REGS->t0config &= ~TIMER_EN;
}

// Devuelve true una vez por cada periodo cumplido
bool driver_timer_expired(void) {
    if (!(TIMG0_REGS->int_raw & TIMER_T0_INT))
        return false;

    TIMG0_REGS->int_clr = TIMER_T0_INT;         
    TIMG0_REGS->t0config |= TIMER_ALARM_EN;
    return true;
}
