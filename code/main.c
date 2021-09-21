#include <REGX51.H>	   
#include "LCD.C"
#include "RFID.C"
void main()
{
	init_LCD();
	init_UART();
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_string("   RFID BASED   ");
	lcd_cmd(0xC0);
	lcd_string("ATENDANCE SYSTEM");	
	delay_lcd(2000);
	while_rfid_loop();
}
//****************************************