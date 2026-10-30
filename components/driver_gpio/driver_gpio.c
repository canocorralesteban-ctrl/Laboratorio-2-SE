/** 
 * @subject: Software Embebido
 * @file: driver_gpio.c
 * @hardware: ESP32 (PANTHER48)
 * @author: Esteban Cano, Paulina Cabriales
 * @date: 22/Octubre/2026
 * @descripcion: driver de GPIO para la placa Panther48
 * @brief: Implementación del driver de GPIO
 */

#include "esp_log.h"
#include "driver_gpio.h"
#include "driver_gpio_config.h"

static const char *TAG = "driver_gpio";

static const uint32_t IOMUX_ADDR[] =
{
    [0]  = 0x3FF49044,
    [1]  = 0x3FF49088,
    [2]  = 0x3FF49040,
    [3]  = 0x3FF49084,
    [4]  = 0x3FF49048,
    [5]  = 0x3FF4906C,
    [6]  = 0x3FF49060,
    [7]  = 0x3FF49064,
    [8]  = 0x3FF49068,
    [9]  = 0x3FF49054,
    [10] = 0x3FF49058,
    [11] = 0x3FF4905C,
    [12] = 0x3FF49034,
    [13] = 0x3FF49038,
    [14] = 0x3FF49030,
    [15] = 0x3FF4903C,
    [16] = 0x3FF4904C,
    [17] = 0x3FF49050,
    [18] = 0x3FF49070,
    [19] = 0x3FF49074,

    [21] = 0x3FF4907C,
    [22] = 0x3FF49080,
    [23] = 0x3FF4908C,

    [25] = 0x3FF49024,
    [26] = 0x3FF49028,
    [27] = 0x3FF4902C,

    [32] = 0x3FF4901C,
    [33] = 0x3FF49020,
    [34] = 0x3FF49014,
    [35] = 0x3FF49018,
    [36] = 0x3FF49004,
    [37] = 0x3FF49008,
    [38] = 0x3FF4900C,
    [39] = 0x3FF49010
};


// Regresa el registro IO MUX del pin
static volatile uint32_t *iomux_reg(uint8_t num)
{
    return (volatile uint32_t *)IOMUX_ADDR[num];
}

static esp_err_t valid_pin(uint8_t num)
{
    if (IS_GPIO(num))
        return ESP_OK;

    ESP_LOGE(TAG, "GPIO invalido: %d", num);
    return ESP_ERR_INVALID_ARG;
}

static esp_err_t valid_gpio_out (uint8_t num) 
{
    if(!IS_GPIO(num) || IS_ONLY_IN(num)) {
        ESP_LOGE(TAG, "Error: %d GPIO no puede ser salida", num);
        return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}

esp_err_t gpio_output(uint8_t num)
{
    if (valid_gpio_out(num) != ESP_OK)
        return ESP_ERR_INVALID_ARG;

    volatile uint32_t *reg = iomux_reg(num);
    *reg &= ~MCU_SEL_MASK;
    *reg |= MCU_SEL_GPIO;

    // Se habilita la salida
    if (num < 32)
        GPIO_REGS->enable_w1ts = _BIT(num);
    else
        GPIO_REGS->enable1_w1ts = _BIT(num - 32);

    return ESP_OK;
}

esp_err_t gpio_input(uint8_t num, driver_pull_t pull)
{
    if (valid_pin(num) != ESP_OK)
        return ESP_ERR_INVALID_ARG;

    // Los pines 34 a 39 no tienen pull interno, no se les debe de dar up o down
    if (IS_ONLY_IN(num) && pull != DRIVER_NONE_PULL) {
        ESP_LOGE(TAG, "GPIO %d no tiene pull interno", num);
        return ESP_ERR_INVALID_ARG;
    }

    // Se deshabilita como salida
    if (num < 32)
        GPIO_REGS->enable_w1tc = _BIT(num);
    else
        GPIO_REGS->enable1_w1tc = _BIT(num - 32);

    // Configuracion del IO MUX
    volatile uint32_t *reg = iomux_reg(num);
    *reg &= ~(MCU_SEL_MASK | FUN_WPU | FUN_WPD);    // se limpia funcion y pulls
    *reg |= MCU_SEL_GPIO | FUN_IE;                  // funcion GPIO y entrada habilitada

    if (pull == DRIVER_PULL_UP)
        *reg |= FUN_WPU;
    else if (pull == DRIVER_PULL_DOWN)
        *reg |= FUN_WPD;

    return ESP_OK;
}

esp_err_t gpio_write(uint8_t num, bool state)
{
    if (valid_gpio_out(num) != ESP_OK)
        return ESP_ERR_INVALID_ARG;

    if (num < 32) {
        if (state)
            GPIO_REGS->out_w1ts = _BIT(num);
        else
            GPIO_REGS->out_w1tc = _BIT(num);
    } else {
        if (state)
            GPIO_REGS->out1_w1ts = _BIT(num - 32);
        else
            GPIO_REGS->out1_w1tc = _BIT(num - 32);
    }

    return ESP_OK;
}


bool gpio_read(uint8_t num)
{
    if (valid_pin(num)!= ESP_OK)
        return false;

    if (num < 32)
        return (GPIO_REGS->in >> num) & 0x01;

    return (GPIO_REGS->in1 >> (num - 32)) & 0x01;
}