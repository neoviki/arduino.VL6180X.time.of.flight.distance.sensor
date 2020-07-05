#include <Wire.h>

/* I2C Slave Address*/
#define ADDRESS_VL6180X                             0x29
#define ADDRESS_GPIO                                0x43

/* Register Address */
#define REG_ADDRESS_GPIO_DIRECTION                  0x14
#define REG_ADDRESS_GPIO_STATE                      0x12
#define REG_ADDRESS_SYS_RANGE_START                 0x018
#define REG_ADDRESS_RESULT_STATUS_INT_STATUS_GPIO   0x04f
#define REG_ADDRESS_RES_RANGE_VAL                   0x062  
#define REG_ADDRESS_INTERRUPT                       0x015


#define ENABLE      0x01
#define DISABLE     0x00

void i2c_init()
{
  Wire.begin();   
}

void set_pin_as_output()
{  
    Wire.beginTransmission(ADDRESS_GPIO); 
    Wire.write(REG_ADDRESS_GPIO_DIRECTION);   
    Wire.write(ENABLE);  
    Wire.endTransmission();

}

void enable_pin()
{
    Wire.beginTransmission(ADDRESS_GPIO); 
    Wire.write(REG_ADDRESS_GPIO_STATE);   
    Wire.write(ENABLE);  
    Wire.endTransmission();
}

void i2c_write16(uint16_t data)
{
    uint8_t msb = (data >> 8) & 0xFF;
    uint8_t lsb = data & 0xFF;
    Wire.write(msb);
    Wire.write(lsb);
}

void i2c_write8(uint8_t data)
{
    Wire.write(data);
}

uint8_t i2c_read8(uint8_t address)
{
    Wire.requestFrom(address, 1);
    return Wire.read();
}


void VL6180X_INIT_REGISTERS()
{

    if (VL6180X_READ_BYTE(ADDRESS_VL6180X, 0x016) == 0x01){
    //private registers
    
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0207, 0x01);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0208, 0x01);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0096, 0x00);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0097, 0xfd);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00e3, 0x01);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00e4, 0x03);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00e5, 0x02);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00e6, 0x01);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00e7, 0x03);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00f5, 0x02);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00d9, 0x05);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00db, 0xce);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00dc, 0x03);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00dd, 0xf8);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x009f, 0x00);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00a3, 0x3c);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00b7, 0x00);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00bb, 0x3c);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00b2, 0x09);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00ca, 0x09);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0198, 0x01);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x01b0, 0x17);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x01ad, 0x00);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x00ff, 0x05);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0100, 0x05);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0199, 0x05);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x01a6, 0x1b);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x01ac, 0x3e);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x01a7, 0x1f);
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0030, 0x00);
    
    //public registers
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0011, 0x10); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x010a, 0x30); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x003f, 0x46); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0031, 0xFF); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0041, 0x63); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x002e, 0x01); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x001b, 0x09); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x003e, 0x31); 
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, 0x0014, 0x24); 
  }  

}

void VL6180X_START_RANGE_MEASUREMENT()
{
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, REG_ADDRESS_SYS_RANGE_START, 0x01);   
}

void VL6180X_CLEAR_INTERRUPT()
{
    VL6180X_WRITE_BYTE(ADDRESS_VL6180X, REG_ADDRESS_INTERRUPT, 0x07);       
}

/* Return range value in mm */
int VL6180X_POLL_RANGE_MEASUREMENT()
{
    int range = 0;
    uint8_t reg_status = (VL6180X_READ_BYTE(ADDRESS_VL6180X, REG_ADDRESS_RESULT_STATUS_INT_STATUS_GPIO) & 0x07);

	Serial.println("Poll Loop"); 
    while (reg_status != 0x04 ){
        delay(1000);
        reg_status = VL6180X_READ_BYTE(ADDRESS_VL6180X, REG_ADDRESS_RESULT_STATUS_INT_STATUS_GPIO) & 0x07;
     	Serial.print(" reg_status : [ ");
    	Serial.print(reg_status);
    	Serial.println(" ] ");

    }
    
    range = VL6180X_READ_BYTE(ADDRESS_VL6180X, REG_ADDRESS_RES_RANGE_VAL); 
    
    VL6180X_CLEAR_INTERRUPT();

    return range;
}

void VL6180X_WRITE_BYTE(uint8_t i2c_slave_address, uint16_t register_address, uint8_t data) 
{
    Wire.beginTransmission(i2c_slave_address);
    i2c_write16(register_address);
    i2c_write8(data);
    Wire.endTransmission();
}

uint8_t VL6180X_READ_BYTE(uint8_t i2c_slave_address, uint16_t register_address) 
{
    Wire.beginTransmission(i2c_slave_address);
    i2c_write16(register_address);
    Wire.endTransmission(false);
    return i2c_read8(ADDRESS_VL6180X);
}

void setup() {
    i2c_init();
    Serial.begin(9600);   
    Serial.println("setup begin"); 
    set_pin_as_output(); 
    enable_pin();
    delay(100);
    VL6180X_INIT_REGISTERS();
    delay(2000);
	Serial.println("setup complete"); 
}


void loop() {
	Serial.println("Main Loop"); 
    int range = 0;
    VL6180X_START_RANGE_MEASUREMENT();
    range = VL6180X_POLL_RANGE_MEASUREMENT();
    Serial.print(" Range : [ ");
    Serial.print(range);
    Serial.println(" ] ");
    delay(100);
}


