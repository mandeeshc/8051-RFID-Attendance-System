#include <REGX51.H>	   
#include "LCD.C"
#include "RFID.C"
void main()
{
	lcd_init();	
	init_UART();
	lcd_cmd(0x01);	lcd_cmd(0x80);
	lcd_string("---RFID Based---");
  lcd_cmd(0xc0);
  lcd_string("Attendance systm"); 
  delay(200);
	lcd_cmd(0x01);
	lcd_string("---Using 8051---");
  delay(200);
	lcd_cmd(0x01);
  while_rfid_loop();
}
//****************************************