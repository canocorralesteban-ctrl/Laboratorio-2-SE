/**
 * @subject: Software Embebido
 * @file: driver_timer_config.h
 * @hardware: ESP32 (PANTHER48)
 * @authors: Esteban Cano, Paulina Cabriales
 * @date: 25/Octubre/2026
 * @descripcion: Mapeo de registros de Timer con estructura
 */

#ifndef DRIVER_TIMER_CONFIG_H
#define DRIVER_TIMER_CONFIG_H

#include <stdint.h>

// Estructura con los registros del Timer Group
typedef struct {
    volatile uint32_t t0config;        
    volatile uint32_t t0lo;            
    volatile uint32_t t0hi;            
    volatile uint32_t t0update;        
    volatile uint32_t t0alarmlo;       
    volatile uint32_t t0alarmhi;       
    volatile uint32_t t0loadlo;        
    volatile uint32_t t0loadhi;        
    volatile uint32_t t0load;        
    volatile uint32_t reserved[29];    
    volatile uint32_t int_ena;        
    volatile uint32_t int_raw;       
    volatile uint32_t int_st;       
    volatile uint32_t int_clr;
} timer_regs_t;

#define TIMG0_BASE  0x3FF5F000
#define TIMG0_REGS  ((timer_regs_t *)TIMG0_BASE)

// mascaras de t0config
#define TIMER_ALARM_EN    (1UL<<10)       // habilita la alarma (se apaga sola al disparar)
#define TIMER_LEVEL_INT   (1UL<<11)       // Interrupcion por nivel
#define TIMER_EDGE_INT    (1UL<<12)       // Interrupcion por flanco
#define TIMER_DIVIDER     (0xFFFFUL<<13)  // Limpia los bits del divisor para poder cargar
#define TIMER_DIV_80      (80UL<<13)      // 80 MHz / 80 = 1 MHz, 1 tick = 1 us
#define TIMER_AUTORELOAD  (1UL<<29)       // Autoreload: al llegar a la alarma vuelve a cargar el valor inicial
#define TIMER_INCREASE    (1UL<<30)       // cuenta hacia arriba
#define TIMER_EN          (1UL<<31)       // enciender

// bit del timer 0 en int_raw e int_clr
#define TIMER_T0_INT      (1UL<<0)

#endif
