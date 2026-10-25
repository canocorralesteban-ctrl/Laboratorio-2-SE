/******************************** Timer STRUCT Configuration **************************************
 * @subject: Software Embebido
 * @file: driver_gpio.c
 * @hardware: ESP32 (PANTHER48)
 * @author: Esteban Cano, Paulina Cabriales
 * @date: 22/Octubre/2026
 * @descripcion: driver de GPIO para la placa Panther48
 * @brief: Implementación del driver de GPIO
 *********************************************************************************************/

#include "driver_gpio.h"
#include "driver_gpio_config.h"

// validacion de pines
static bool valid_pin(uint8_t num)
{
    if (num <= 19)
        return true;
    if (num >= 21 && num <= 23)
        return true;
    if (num >= 25 && num <= 27)
        return true;
    if (num >= 32 && num <= 39)
        return true;
    return false;
}

// Los pines 34 a 39 solo sirven como entrada
static bool pin_only_input(uint8_t num)
{
    return (num >= 34 && num <= 39);
}