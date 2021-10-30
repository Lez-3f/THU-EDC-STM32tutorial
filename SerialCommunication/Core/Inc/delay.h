/*
 * @Autor: Zel
 * @Email: 2995441811@qq.com
 * @Date: 2021-10-24 16:17:46
 * @LastEditors: Zel
 * @LastEditTime: 2021-10-26 23:12:32
 */
#ifndef DELAY_H
#define DELAY_H

#include "main.h"
#include "stm32_hal_legacy.h"

void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

#endif