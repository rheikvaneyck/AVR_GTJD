#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#include "pins_arduino.h"

#include "i2c_iaw.h"

void i2c_init(void) {
	cbi(DDRC, DDC4); // SDA, Clear the PC4 pin, PC4 is now an input
	cbi(DDRC, DDC5); // SCL, Clear the PC5 pin, PC5 is now an input
	sbi(PORTC, PORTC4); // SDA, turn On the Pull-up PC4 is now an input with pull-up enabled
	sbi(PORTC, PORTC5); // SCL, turn On the Pull-up PC5 is now an input with pull-up enabled

  // initialize twi prescaler and bit rate
  cbi(TWSR, TWPS0);
  cbi(TWSR, TWPS1);

  /* twi bit rate formula from atmega128 manual pg 204
  SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
  note: TWBR should be 10 or higher for master mode
  It is 72 for a 16mhz Wiring board with 100kHz TWI 
  and 32 for a 8 MHz Wiring board with 100kHz TWI */
	TWBR = (CPU_FREQ / I2C_SPEED - 16) / 2;
	// enable twi module, acks, and twi interrupt
	TWCR = (_BV(TWEN) | _BV(TWEA));
};

void i2c_wait_for_twint(void) {
	loop_until_bit_is_set(TWCR, TWINT);
};

uint8_t i2c_status(void) {
	return TWSR;
}

void i2c_start(void) {
	TWCR = (_BV(TWINT)|_BV(TWEN)|_BV(TWSTA));
	i2c_wait_for_twint();
};

void i2c_stop(void) {
	TWCR = (_BV(TWINT)|_BV(TWEN)|_BV(TWSTO));
};

void i2c_write_addr(uint8_t dev_addr, uint8_t rw) {
	TWDR = (dev_addr << 1);
	if(rw)	TWDR += 1;
	TWCR = (_BV(TWINT)|_BV(TWEN));
	i2c_wait_for_twint();
};

void i2c_write(uint8_t data) {
	TWDR = data;
	TWCR = (_BV(TWINT)|_BV(TWEN));
	i2c_wait_for_twint();
};

uint8_t i2c_read(uint8_t ack) {
	if(ack) { 
		TWCR = (_BV(TWINT)| _BV(TWEN) | _BV(TWEA));
	} else {
		TWCR = (_BV(TWINT)| _BV(TWEN) );
	}
	i2c_wait_for_twint();
	return (TWDR);
};
