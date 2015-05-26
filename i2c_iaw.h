#include <inttypes.h>

#define CPU_FREQ 8000000UL
#define I2C_SPEED 400000UL

#define TW_START		0x08
#define TW_REP_START		0x10
#define TW_MT_SLA_ACK		0x18
#define TW_MT_SLA_NACK		0x20
#define TW_MT_DATA_NACK		0x30
#define TW_MT_ARB_LOST		0x38
#define TW_MR_ARB_LOST		0x38
#define TW_MR_SLA_ACK		0x40
#define TW_MR_SLA_NACK		0x48
#define TW_MR_DATA_ACK		0x50
#define TW_MR_DATA_NACK		0x58
#define TW_ST_SLA_ACK		0xA8
#define TW_ST_ARB_LOST_SLA_ACK	0xB0
#define TW_ST_DATA_ACK		0xB8
#define TW_ST_DATA_NACK		0xC0
#define TW_ST_LAST_DATA		0xC8
#define TW_SR_SLA_ACK		0x60
#define TW_SR_ARB_LOST_SLA_ACK	0x68
#define TW_SR_GCALL_ACK		0x70
#define TW_SR_ARB_LOST_GCALL_ACK 0x78
#define TW_SR_DATA_ACK		0x80
#define TW_SR_DATA_NACK		0x88
#define TW_SR_GCALL_DATA_ACK	0x90
#define TW_SR_GCALL_DATA_NACK	0x98
#define TW_SR_STOP		0xA0
#define TW_NO_INFO		0xF
#define TW_BUS_ERROR		0x00

#define TW_STATUS_MASK		(_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|_BV(TWS3))
#define TW_STATUS		(TWSR & TW_STATUS_MASK)
#define TW_READ		1
#define TW_WRITE	0

#define ACK 1
#define NOACK 0


#ifdef __cplusplus
extern "C" {
#endif

void i2c_init(void);
void i2c_wait_for_twint(void);
uint8_t i2c_status(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write_addr(uint8_t dev_addr, uint8_t rw);
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ack);

#ifdef __cplusplus
}
#endif