#include "main.h"

void write_lcd(unsigned char data , unsigned char mode)
{
   PORTD=data;
   RS = mode;
   RW=0;
   LCD_STROBE;
}

void is_busy(void)
{
  //config RD7 as an input port
  TRISDbits.RD7 = 1;
  
  RS = 0;
  RW = 1;
  
  do
  {
    LCD_STROBE;
  }while(BUSY);

  //config PORTD as an output
  TRISDbits.RD7 = 0;
}

void puts(unsigned char location,const char *ptr)
{
   write_lcd(location,CMD_MODE);

   //wait,if LCD is busy
//   is_busy();
//   delay(20);
 
   while(*ptr)
   {
      write_lcd(*ptr++,DATA_MODE);
  //     delay(1);
    //  is_busy();
   }
}

void putchar(unsigned char location,unsigned char ch)
{
   write_lcd(location,CMD_MODE);
   
   is_busy();

   write_lcd(ch,DATA_MODE);
}
