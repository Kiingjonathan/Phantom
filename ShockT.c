#include <stdio.h>
#include <bcm2835.h>
// Register addresses
#define CONVERSION_REG 0x0
#define CONFIG_REG     0x1
#define LO_THRESH_REG  0x2
#define HI_THRESH_REG  0x3
// ADC Slave Address
#define ADC_ADDR 0x48
// Write to a register (16 bits)
void writeReg16(uint8_t reg, uint16_t value) {
  bcm2835_i2c_setSlaveAddress(ADC_ADDR);
  char buf[] = {reg, value >> 8, value & 0xFF};
  bcm2835_i2c_write(buf,3);
}
// Read from a register (16 bits)
// Note this function returns an unsigned value
uint16_t readReg16(uint8_t reg) {
  char buf[1];
  bcm2835_i2c_setSlaveAddress(ADC_ADDR); //sets address for the ADC 
  bcm2835_i2c_write(&reg,1); //tells the adc tbe selected address "reg"
  bcm2835_i2c_read(buf,2);
  return buf[0] << 8 | buf[1]; // assemble 16 bit value
}

int main() {
  //printf("hello ethan main1\n");
  if (!bcm2835_init()) {// Initialise the BCM2835 library
  // printf("first if statement (true)\n");
    
  } else {
   // printf("first if statement (false)\n");
    // return 0;
  }
  if(!bcm2835_i2c_begin()){// open I2C
  //    printf("second if statement (true)\n");
  }else {
  //  printf("second if statement (false)\n");
    // return 0;
  }
  // WRITE YOUR CODE HERE
  //the 16 bit for writing to chose: 1 000 010 0 100 0 0 0 11

  // 1   Operational status or single-shot conversion start: PICK THIS ONEE IDK WHAT THIS MEANS
  // 000 Input multiplexer configuration:   000: AINp = AIN0 and AINn = AIN1 (default)
  // 001 Programmalbe gain amplifier configuration:   FSR = +-4.096V
  // 100 Data rate:     128 SPS (default)
  // 0   comparator mode:     traditional comparator 
  // 0   comparator polartiy:   active low
  // 0   nonlatching comparator:    The ALERT/RDY pin does not latch when asserted (default)
  // 11  Comparator queue and disable:    disable comparator and set ALERT/RDY pin to high impedance (default)
  uint16_t ay0 = 0b1000010010000011; 
  writeReg16(CONFIG_REG, ay0);
 // Read and print the registers. No idea if this works cuz i cant test it
  uint16_t config = readReg16(CONFIG_REG);
  // uint16_t lower_threshold = readReg16(LO_THRESH_REG);
  // uint16_t upper_threshold = readReg16(HI_THRESH_REG);

  for (int i = 0; i < 10; i++){
  uint16_t adc_reg = readReg16(CONVERSION_REG);
  // printf("CONFIG_REG     0x%X\n", config);
  // printf("LO_THRESH_REG  %d\n", lower_threshold, (int16_t)lower_threshold); // default: 0x8000
  // printf("HI_THRESH_REG  %d\n", upper_threshold, (int16_t)upper_threshold); // default: 0x7FFF
  printf(" %d, ", (int16_t)adc_reg);
 
  }
  printf("\n");
  bcm2835_i2c_end(); // close I2C
  bcm2835_close(); // Close the BCM2835 libraryd
  return 1;
  //can i get a hooyah
}