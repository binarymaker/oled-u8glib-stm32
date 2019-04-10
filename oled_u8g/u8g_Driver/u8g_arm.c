#include "u8g_arm.h"  
   
static uint8_t control = 0;  
void u8g_Delay(uint16_t val)  
{  
  
 HAL_Delay(val);  
}  

void u8g_xMicroDelay(uint16_t val) {
  static uint32_t i, j;
  static uint32_t freq;
  freq = HAL_RCC_GetSysClockFreq() / 1000000;

  for (i = 0; i < val;) {
    for (j = 0; j < freq; ++j) {
      ++j;
    }
    ++i;
  }
}

void u8g_MicroDelay(void)  
{  
  u8g_xMicroDelay(1); 
}  
  
void u8g_10MicroDelay(void)  
{  
  u8g_xMicroDelay(10);  
}  
  
  
uint8_t u8g_com_hw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)  
{  
 switch(msg)  
 {  
  case U8G_COM_MSG_STOP:  
   break;  
  
  case U8G_COM_MSG_INIT:  
   u8g_MicroDelay();  
   break;  
  
  case U8G_COM_MSG_ADDRESS:           /* define cmd (arg_val = 0) or data mode (arg_val = 1) */  
   u8g_10MicroDelay();  
   if (arg_val == 0)  
   {  
        control = 0;  
   }  
   else  
   {  
        control = 0x40;  
   }  
   break;  
  
  case U8G_COM_MSG_WRITE_BYTE:  
  {  
    HAL_I2C_Mem_Write(&I2C_HANDLER, DEVICE_ADDRESS, control, 1, &arg_val, 1, I2C_TIMEOUT);    
  }  
   break;  
  
  case U8G_COM_MSG_WRITE_SEQ:  
  case U8G_COM_MSG_WRITE_SEQ_P:  
  {  
    HAL_I2C_Mem_Write(&I2C_HANDLER, DEVICE_ADDRESS, control, 1, arg_ptr, arg_val, I2C_TIMEOUT); 
  }  
   break;  
 }  
 return 1;  
}  

