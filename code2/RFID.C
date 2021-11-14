char flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0,count = 0;
sbit SWR = P1^2;
sbit SWT = P1^3;
sbit Speaker = P2^6;
sbit Motor1=P2^4;
sbit Motor2=P2^3;
unsigned char result[1];
int counter1,counter2,counter3;
//****************************************
void init_UART()
{
    TMOD = 0x22;
    SCON = 0x50;
    TH1  = 0xFD;
    TL1  = 0xFD;
    TR1  = 1;
}
//****************************************
void tx_UART(char v)
{	
	//IE = 0x00;	 // disable interrupt
	TI=0;
	SBUF = v;
	while(TI!=1);
	TI=0;
	//IE = 0x90;   // enable interrupt
}
//****************************************
void motor_routine()
{
	Motor1=1;            Motor2=0;
	delay(300);
	Motor1=0;            Motor2=0;
	delay(200);
	Motor1=0;            Motor2=1;
	delay(300);
	Motor1=0;            Motor2=0;
}
//****************************************
int read_card()
{
	int lv,flg1,lv2;
	char arrt[15];
	char code darr[3][10]	=	{{'3','A','0','0','1','7','4','A','C','8'}, //Change as per your card 3A00174AC8AF
    					 		 {'3','A','0','0','1','8','0','D','6','B'}, //Change as per your card 3A00180D6B44
					 			 {'3','A','0','0','1','7','4','6','2','A'}};	//Change as per your card 

	
	lcd_cmd(0x01);	lcd_cmd(0x80);
	lcd_string("Scan Your Card:");
	RI=0;
	for(lv=0;lv<12;lv++)
	{
		while(!RI){}			
		arrt[lv] = SBUF;	
		RI = 0;
	}
	lcd_cmd(0xC3);
	for(lv=0;lv<10;lv++)
	{
		lcd_data(arrt[lv]);	
	}
	delay(200);  
	
	for(lv2=0;lv2<5;lv2++)
	{
		flg1=0;
		for(lv=0;lv<10;lv++)
		{
			if(arrt[lv]==darr[lv2][lv])
			{
				flg1++;
			}	
		}
		lcd_cmd(0x01);			lcd_cmd(0x80);
		if(flg1==10)
		{
			//lcd_data('C');lcd_data('A');lcd_data('R');lcd_data('D');lcd_data(' ');lcd_data('A');lcd_data('C');lcd_data('C');lcd_data('E');lcd_data('P');lcd_data('T');lcd_data('E');lcd_data('D');
			//delay_lcd(2000);  
			return lv2+1;
		}
	}
		lcd_cmd(1);
		lcd_string("Invalid Card");
		lcd_cmd(0xc0);
		lcd_string("Try Another Card");
		Speaker=0;							 delay(300);							 Speaker=1;
		delay(300);
		return 0;
}
//**************************************
void while_rfid_loop()
{
	int ret=0;
	//tx_UART('O');tx_UART('K');
	while(1)
	{	
			ret = read_card();
			if(ret<=0 || ret>3)
			{
				
			}
			else
			{
				lcd_cmd(0x01);				lcd_cmd(0x80);
				if(ret==1)
				{
						counter1++;
            lcd_cmd(1);             
            lcd_string(" Attended");
            delay(200);
            lcd_cmd(1);
            lcd_string(" SATHWIK ");
						//lcd_string("     USER 1     ");
            lcd_cmd(0xc0);
            lcd_string("ENTRIES: ");
            sprintf(result, "%d", counter1);
            lcd_string(result);
            motor_routine();            
				}
				else if(ret==2)
				{
						counter2++;
						lcd_cmd(1);
						lcd_string(" Attended");
						delay(200);
						lcd_cmd(1);
						lcd_string(" PRASANTH ");
						//lcd_string("     USER 2     ");           
						lcd_cmd(0xc0);
						lcd_string("ENTRIES: ");
						sprintf(result, "%d", counter2);
						lcd_string(result);
						motor_routine();
				}
				else if(ret==3)
				{
						counter3++;
						lcd_cmd(1);
						lcd_string(" Attended");
						delay(200);
						lcd_cmd(1);
						lcd_string(" KARTHIK ");
						//lcd_string("     USER 3     ");
						lcd_cmd(0xc0);
						lcd_string("ENTRIES : ");
						sprintf(result, "%d", counter3);
						lcd_string(result);	
						motor_routine();
				}				
				else
				{
					//lcd_cmd(0x01);	lcd_cmd(0x80);
					//lcd_string("MARKED ALREADY! ");
					//tx_UART('<');tx_UART('X');tx_UART('>');
				}
			delay(200);
		}
	}
}
