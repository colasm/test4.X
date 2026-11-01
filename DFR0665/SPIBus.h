/*
 * File: SPIBus.h
 *
 * Chip-select arbitration for the DFR0665 board's shared SPI1 bus
 * (LCD, touch controller and SD slot sit on the same bus).
 */

#ifndef SPIBUS_H
#define	SPIBUS_H

#include "../mcc_generated_files/system/pins.h"

/**
 * @brief Deselects every slave sharing the SPI1 bus (LCD, touch, SD).
 * @note  Must be called once before the first transaction (all LATx reset
 *        low at power-up) and before selecting a new slave.
 */
static inline void SPIBus_DisableAllCS(void)
{
    CS_LCD_SetHigh();
    CS_TOUCH_SetHigh();
    CS_SD_SetHigh();
}

#endif	/* SPIBUS_H */
