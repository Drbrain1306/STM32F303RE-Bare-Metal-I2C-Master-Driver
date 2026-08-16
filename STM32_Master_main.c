#include <stdint.h>
#include "main.h"

// GPIOB Base adr - 0x48000400
#define GPIOB_MODER   0x48000400
#define GPIOB_OTYPER  0x48000404
#define GPIOB_PUPDR   0x4800040C
#define GPIOB_AFRH    0x48000424

// RCC Base adr - 0x40021000
#define RCC_AHBENR    0x40021014
#define RCC_APB1ENR   0x4002101C

// I2C1 Base adr - 0x40005400
#define I2C1_CR1      0x40005400
#define I2C1_CR2      0x40005404
#define I2C_TIMINGR   0x40005410
#define I2C_ISR       0x40005418
#define I2C_ICR       0x4000541C
#define I2C_TXDR      0x40005428

// Simple Delay function
void delay_ms(volatile uint32_t count) {
    while(count--) {
        for(volatile int i = 0; i < 1000; i++);
    }
}

// Master byte transmitter function
void I2C1_Master_Transmit(uint8_t slave_adr, uint8_t *pData, uint32_t byte_length) {
    volatile uint32_t *const pI2C1_CR2 = (uint32_t*) I2C1_CR2;
    volatile uint32_t *const pI2C_TXDR = (uint32_t*) I2C_TXDR;
    volatile uint32_t *const pI2C_ISR  = (uint32_t*) I2C_ISR;
    volatile uint32_t *const pI2C_ICR  = (uint32_t*) I2C_ICR;

    // Clearing any pending error flags from previous aborted runs
    *pI2C_ICR |= (1U << 5) | (1U << 4) | (1U << 8) | (1U << 9); // Clear STOPCF, NACKCF, BERRCF, ARLOCF

    // Clearing previous transfer bits in CR2 (SADD, NBYTES, AUTOEND, RD_WRN, START, STOP)
    *pI2C1_CR2 &= ~((0x3FF << 0) | (0xFF << 16) | (1U << 25) | (1U << 10));

    // Configuring new transfer settings
    *pI2C1_CR2 |= ((uint32_t)slave_adr << 1) & (0x7F << 1); // Shift 7-bit addr to bits 7:1
    *pI2C1_CR2 |= ((uint32_t)byte_length << 16); // Set NBYTES
    *pI2C1_CR2 |= (1U << 25); // Enable AUTOEND
    *pI2C1_CR2 &= ~(1U << 10); // RD_WRN = 0 (Master Write)

    // Generating START condition
    *pI2C1_CR2 |= (1U << 13);

    // Streaming data bytes
    for (uint32_t i = 0; i < byte_length; i++) {

        // Waiting until TXIS (TX buffer empty) or NACK is received
        while (!(*pI2C_ISR & (1U << 1))) {

            // Checking if slave (Arduino) did not acknowledge (NACK)
            if (*pI2C_ISR & (1U << 4)) {
                *pI2C_ICR |= (1U << 4); // Clear NACK flag
                return; // Exit transmission
            }
        }

        // Write byte into TXDR (clears TXIS automatically)
        *pI2C_TXDR = pData[i];
    }

    // Waiting for STOP condition (AUTOEND handles generation)
    while (!(*pI2C_ISR & (1U << 5)));

    // Clearing STOP flag
    *pI2C_ICR |= (1U << 5);
}

int main(void)
{
    // Addressing and Enabling Clocks
    volatile RCC_AHBENR_t *const pRCC_AHBENR = (RCC_AHBENR_t*) RCC_AHBENR;
    volatile uint32_t *const pRCC_APB1ENR = (uint32_t*) RCC_APB1ENR;

    pRCC_AHBENR->gpiob_en = 1; // Enable GPIOB clock
    *pRCC_APB1ENR |= (1U << 21); // Enable I2C1 clock

    // Configuring PB8 and PB9 GPIOs
    volatile uint32_t *const pGPIOB_MODER = (uint32_t*) GPIOB_MODER;
    volatile uint32_t *const pGPIOB_OTYPER = (uint32_t*) GPIOB_OTYPER;
    volatile GPIOx_PUPDR_t *const PUPDR = (GPIOx_PUPDR_t*) GPIOB_PUPDR;
    volatile uint32_t *const pGPIOB_AFRH = (uint32_t*) GPIOB_AFRH;

    // Alternate Function mode (10) for PB8 & PB9
    *pGPIOB_MODER &= ~((3U << (8 * 2)) | (3U << (9 * 2)));
    *pGPIOB_MODER |= ((2U << (8 * 2)) | (2U << (9 * 2)));

    // Map PB8 & PB9 to AF4 (I2C1) in AFRH
    *pGPIOB_AFRH &= ~((0xFU << 0) | (0xFU << 4));
    *pGPIOB_AFRH |= ((4U << 0) | (4U << 4));

    // Open-Drain output type (1)
    *pGPIOB_OTYPER |= (1U << 8) | (1U << 9);

    // Pull-up enabled (01)
    PUPDR->pupdr8 = 1;
    PUPDR->pupdr9 = 1;

    // Configure I2C Peripheral
    volatile uint32_t *const pI2C1_CR1  = (uint32_t*) I2C1_CR1;
    volatile uint32_t *const pI2C_TIMINGR = (uint32_t*) I2C_TIMINGR;

    // Standard 100 kHz timing value
    *pI2C_TIMINGR = 0x00201D2B;

    // Enable I2C peripheral (PE = 1)
    *pI2C1_CR1 |= 1;

    // Example transmission loop
    uint8_t message[] = "Hello Arduino!\r\n";

    while (1) {
        I2C1_Master_Transmit(0x55, message, sizeof(message) - 1);
        delay_ms(500);
    }
}
