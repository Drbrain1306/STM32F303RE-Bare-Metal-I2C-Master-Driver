#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

typedef struct {
    uint32_t dma1_en     : 1;  /* Bit 0  : DMA1 clock enable */
    uint32_t dma2_en     : 1;  /* Bit 1  : DMA2 clock enable */
    uint32_t sram_en     : 1;  /* Bit 2  : SRAM interface clock enable */
    uint32_t reserved1   : 1;  /* Bit 3  : Reserved */
    uint32_t flitf_en    : 1;  /* Bit 4  : FLITF clock enable */
    uint32_t fmc_en      : 1;  /* Bit 5  : FMC clock enable (STM32F303xD/E) */
    uint32_t crc_en      : 1;  /* Bit 6  : CRC clock enable */
    uint32_t reserved2   : 9;  /* Bits 15:7 : Reserved */
    uint32_t gpioh_en    : 1;  /* Bit 16 : IO port H clock enable (STM32F303xD/E) */
    uint32_t gpioa_en    : 1;  /* Bit 17 : IO port A clock enable */
    uint32_t gpiob_en    : 1;  /* Bit 18 : IO port B clock enable */
    uint32_t gpioc_en    : 1;  /* Bit 19 : IO port C clock enable */
    uint32_t gpiod_en    : 1;  /* Bit 20 : IO port D clock enable */
    uint32_t gpioe_en    : 1;  /* Bit 21 : IO port E clock enable */
    uint32_t gpiof_en    : 1;  /* Bit 22 : IO port F clock enable */
    uint32_t gpiog_en    : 1;  /* Bit 23 : IO port G clock enable (STM32F303xD/E) */
    uint32_t tsc_en      : 1;  /* Bit 24 : Touch sensing controller clock enable */
    uint32_t reserved3   : 3;  /* Bits 27:25 : Reserved */
    uint32_t adc12_en    : 1;  /* Bit 28 : ADC1 and ADC2 clock enable */
    uint32_t adc34_en    : 1;  /* Bit 29 : ADC3 and ADC4 clock enable */
    uint32_t reserved4   : 2;  /* Bits 31:30 : Reserved */
} RCC_AHBENR_t;

typedef struct {
    uint32_t moder0  : 2;  /* Bits 1:0   - Pin 0 mode configuration */
    uint32_t moder1  : 2;  /* Bits 3:2   - Pin 1 mode configuration */
    uint32_t moder2  : 2;  /* Bits 5:4   - Pin 2 mode configuration */
    uint32_t moder3  : 2;  /* Bits 7:6   - Pin 3 mode configuration */
    uint32_t moder4  : 2;  /* Bits 9:8   - Pin 4 mode configuration */
    uint32_t moder5  : 2;  /* Bits 11:10 - Pin 5 mode configuration */
    uint32_t moder6  : 2;  /* Bits 13:12 - Pin 6 mode configuration */
    uint32_t moder7  : 2;  /* Bits 15:14 - Pin 7 mode configuration */
    uint32_t moder8  : 2;  /* Bits 17:16 - Pin 8 mode configuration */
    uint32_t moder9  : 2;  /* Bits 19:18 - Pin 9 mode configuration */
    uint32_t moder10 : 2;  /* Bits 21:20 - Pin 10 mode configuration */
    uint32_t moder11 : 2;  /* Bits 23:22 - Pin 11 mode configuration */
    uint32_t moder12 : 2;  /* Bits 25:24 - Pin 12 mode configuration */
    uint32_t moder13 : 2;  /* Bits 27:26 - Pin 13 mode configuration */
    uint32_t moder14 : 2;  /* Bits 29:28 - Pin 14 mode configuration */
    uint32_t moder15 : 2;  /* Bits 31:30 - Pin 15 mode configuration */
} GPIOx_MODER_t;

typedef struct {
    uint32_t odr0      : 1;  /* Bit 0     - Pin 0 output data */
    uint32_t odr1      : 1;  /* Bit 1     - Pin 1 output data */
    uint32_t odr2      : 1;  /* Bit 2     - Pin 2 output data */
    uint32_t odr3      : 1;  /* Bit 3     - Pin 3 output data */
    uint32_t odr4      : 1;  /* Bit 4     - Pin 4 output data */
    uint32_t odr5      : 1;  /* Bit 5     - Pin 5 output data */
    uint32_t odr6      : 1;  /* Bit 6     - Pin 6 output data */
    uint32_t odr7      : 1;  /* Bit 7     - Pin 7 output data */
    uint32_t odr8      : 1;  /* Bit 8     - Pin 8 output data */
    uint32_t odr9      : 1;  /* Bit 9     - Pin 9 output data */
    uint32_t odr10     : 1;  /* Bit 10    - Pin 10 output data */
    uint32_t odr11     : 1;  /* Bit 11    - Pin 11 output data */
    uint32_t odr12     : 1;  /* Bit 12    - Pin 12 output data */
    uint32_t odr13     : 1;  /* Bit 13    - Pin 13 output data */
    uint32_t odr14     : 1;  /* Bit 14    - Pin 14 output data */
    uint32_t odr15     : 1;  /* Bit 15    - Pin 15 output data */
    uint32_t reserved  : 16; /* Bits 31:16 - Reserved (keep at reset value) */
} GPIOx_ODR_t;

typedef struct {
    uint32_t pupdr0  : 2;  /* Bits 1:0   - Pin 0 pull-up/pull-down */
    uint32_t pupdr1  : 2;  /* Bits 3:2   - Pin 1 pull-up/pull-down */
    uint32_t pupdr2  : 2;  /* Bits 5:4   - Pin 2 pull-up/pull-down */
    uint32_t pupdr3  : 2;  /* Bits 7:6   - Pin 3 pull-up/pull-down */
    uint32_t pupdr4  : 2;  /* Bits 9:8   - Pin 4 pull-up/pull-down */
    uint32_t pupdr5  : 2;  /* Bits 11:10 - Pin 5 pull-up/pull-down */
    uint32_t pupdr6  : 2;  /* Bits 13:12 - Pin 6 pull-up/pull-down */
    uint32_t pupdr7  : 2;  /* Bits 15:14 - Pin 7 pull-up/pull-down */
    uint32_t pupdr8  : 2;  /* Bits 17:16 - Pin 8 pull-up/pull-down */
    uint32_t pupdr9  : 2;  /* Bits 19:18 - Pin 9 pull-up/pull-down */
    uint32_t pupdr10 : 2;  /* Bits 21:20 - Pin 10 pull-up/pull-down */
    uint32_t pupdr11 : 2;  /* Bits 23:22 - Pin 11 pull-up/pull-down */
    uint32_t pupdr12 : 2;  /* Bits 25:24 - Pin 12 pull-up/pull-down */
    uint32_t pupdr13 : 2;  /* Bits 27:26 - Pin 13 pull-up/pull-down */
    uint32_t pupdr14 : 2;  /* Bits 29:28 - Pin 14 pull-up/pull-down */
    uint32_t pupdr15 : 2;  /* Bits 31:30 - Pin 15 pull-up/pull-down */
} GPIOx_PUPDR_t;

#endif /* MAIN_H_ */
