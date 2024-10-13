#include "bsp_gpio.h"
#include "main.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

static uint8_t gpio_index;
static GPIOInstance* gpio_instance[GPIO_MX_COUNT] = {NULL};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    GPIOInstance* instance = NULL;
    for (size_t idx = 0; idx < gpio_index;) {
        instance = gpio_instance[idx];
        if (instance->pin == GPIO_Pin && instance->gpio_exit_callback != NULL) {
            instance->gpio_exit_callback(instance);
        }
    }
}

/**
 * @brief 注册一个GPIO实例
 *
 * @param gpio_config
 * @return GPIOInstance*
 */
GPIOInstance* GPIORegister(GPIO_InitConfig_t* gpio_config) {

    GPIOInstance* gpio_ins = NULL;

    gpio_ins->GPIOx              = gpio_config->GPIOx;
    gpio_ins->pin_state          = gpio_config->pin_state;
    gpio_ins->pin_state          = gpio_config->pin_state;
    gpio_ins->exit_mode          = gpio_config->exit_mode;
    gpio_ins->pin                = gpio_config->pin;
    gpio_ins->gpio_exit_callback = gpio_config->gpio_exit_callback;

    gpio_instance[gpio_index++] = gpio_ins;
    return gpio_ins;
}

void GPIOTogglePin(GPIOInstance* instance) { HAL_GPIO_TogglePin(instance->GPIOx, instance->pin); }

void GPIOSetPin(GPIOInstance* instance) {
    HAL_GPIO_WritePin(instance->GPIOx, instance->pin, GPIO_PIN_SET);
}

void GPIOResetPin(GPIOInstance* instance) {
    HAL_GPIO_WritePin(instance->GPIOx, instance->pin, GPIO_PIN_RESET);
}

GPIO_PinState GPIOReadPin(GPIOInstance* instance) {
    return HAL_GPIO_ReadPin(instance->GPIOx, instance->pin);
}