#pragma once

#include "gpio.h"
#include <stdint.h>

#define GPIO_MX_COUNT 10

/**
 * @brief 外部中断类型枚举
 *
 */
typedef enum {
    GPIO_EXIT_RISING = 0,
    GPIO_EXIT_FALLING,
    GPIO_EXIT_RISINGFALLING,
    GPIO_EXIT_NONE,
} GPIO_EXIT_e;

/**
 * @brief gpio引脚实例定义
 *
 */
typedef struct tygpio {
    GPIO_TypeDef* GPIOx;                        // 分组
    GPIO_PinState pin_state;                    // 引脚电平状态
    GPIO_EXIT_e exit_mode;                      // 中断触发模式
    uint16_t pin;                               // 引脚号

    void (*gpio_exit_callback)(struct tygpio*); // 中断回调函数
    void* id;                                   // gpioID号
} GPIOInstance;

/**
 * @brief gpio初始化参数定义
 *
 */
typedef struct {
    GPIO_TypeDef* GPIOx;                       // 分组
    GPIO_PinState pin_state;                   // 引脚电平状态
    GPIO_EXIT_e exit_mode;                     // 中断触发模式
    uint16_t pin;                              // 引脚号

    void (*gpio_exit_callback)(GPIOInstance*); // 中断回调函数
    void* id;                                  // gpioID号
} GPIO_InitConfig_t;

/**
 * @brief GPIO注册实例
 *
 * @param gpio_config
 * @return GPIOInstance*
 */
GPIOInstance* GPIORegister(GPIO_InitConfig_t* gpio_config);
/**
 * @brief 反转电平
 *
 * @param instance
 */
void GPIOTogglePin(GPIOInstance* instance);
/**
 * @brief 拉高电平
 *
 * @param instance
 */
void GPIOSetPin(GPIOInstance* instance);
/**
 * @brief 拉低电平
 *
 * @param instance
 */
void GPIOResetPin(GPIOInstance* instance);
/**
 * @brief 读取电平
 *
 * @param instance
 * @return GPIO_PinState
 */
GPIO_PinState GPIOReadPin(GPIOInstance* instance);
