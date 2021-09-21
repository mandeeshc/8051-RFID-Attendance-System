char flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0,count = 0;
sbit SWR = P1^2;
sbit SWT = P1^3;
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
int read_card()
{
	int lv,flg1,lv2;
	char arrt[15];
	char code darr[5][10]	=	{{'3','A','0','0','1','7','4','C','4','7'}, //Change as per your card 
    					 		 {'3','A','0','0','1','7','F','1','3','A'}, //Change as per your card 
					 			 {'1','6','0','0','6','5','D','1','3','0'}, //Change as per your card 
								 {'1','9','0','0','4','A','B','2','3','3'}, //Change as per your card 
								 {'1','9','0','0','4','A','C','8','9','5'}};	//Change as per your card 

	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_data(' ');lcd_data(' ');lcd_data(' ');lcd_data('P');lcd_data('L');lcd_data('A');lcd_data('C');lcd_data('E');lcd_data(' ');lcd_data('C');lcd_data('A');lcd_data('R');lcd_data('D');lcd_data(' ');lcd_data(' ');lcd_data(' ');
	RI=0;
	for(lv=0;lv<12;lv++)
	{
		while(!RI)
		{
			 if(SWR == 0)
				{
					flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
					lcd_cmd(0x01);	lcd_cmd(0x80);
					tx_UART('<');tx_UART('C');tx_UART('>');
					lcd_string("ATNDANCE CLEARED");
					count = 0;
					while(SWR == 0);
					delay_lcd(2000);
					return 20;
					
				}
				else if(SWT == 0)
				{
					lcd_cmd(0x01);	lcd_cmd(0x80);
					lcd_string("TOTAL ATTENDANCE");
					disp_val(0xC0, count, 6);
					lcd_cmd(0xC4);
					lcd_data('P');lcd_data(':');
					if(flag1 == 1) {lcd_data('1');lcd_data(' ');}
					if(flag2 == 1) {lcd_data('2');lcd_data(' ');}
					if(flag3 == 1) {lcd_data('3');lcd_data(' ');}
					if(flag4 == 1) {lcd_data('4');lcd_data(' ');}
					if(flag5 == 1) {lcd_data('5');lcd_data(' ');}
							
				  while(SWT == 0);
					delay_lcd(2000);
					//count = 0;
					return 20;
				}
		}			
		arrt[lv] = SBUF;	
		RI = 0;
	}
	lcd_cmd(0xC3);
	for(lv=0;lv<10;lv++)
	{
		lcd_data(arrt[lv]);	
	}
	delay_lcd(2000);  
	
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
		lcd_cmd(0x01);	
		lcd_cmd(0x80);
		if(flg1==10)
		{
			//lcd_data('C');lcd_data('A');lcd_data('R');lcd_data('D');lcd_data(' ');lcd_data('A');lcd_data('C');lcd_data('C');lcd_data('E');lcd_data('P');lcd_data('T');lcd_data('E');lcd_data('D');
			//delay_lcd(2000);  
			return lv2+1;
	
		}
	}
//		buz=1;
		lcd_data('I');lcd_data('N');lcd_data('V');lcd_data('A');lcd_data('L');lcd_data('I');lcd_data('D');lcd_data(' ');lcd_data('C');lcd_data('A');lcd_data('R');lcd_data('D');
		delay_lcd(2000);  
//		buz=0;

		return 0;
}
//**************************************
void while_rfid_loop()
{
	int ret=0;
	tx_UART('O');tx_UART('K');
	while(1)
	{	
			ret = read_card();
			if(ret<=0 || ret>5)
			{
				
			}
			else
			{
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				if(ret==1 && flag1 == 0)
				{
						flag1 = 1;
						//lcd_cmd(0x01);
						//lcd_cmd(0x80);
						lcd_data('W');lcd_data('E');lcd_data('L');lcd_data('C');lcd_data('O');lcd_data('M');lcd_data('E');lcd_data(' ');lcd_data('U');lcd_data('S');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('1');lcd_data(' ');lcd_data(' ');
						tx_UART('<');tx_UART('1');tx_UART('>');
						count++;
				}
				else if(ret==2 && flag2 == 0)
				{
						flag2 = 1;
						//lcd_cmd(0x01);
						//lcd_cmd(0x80);
						lcd_data('W');lcd_data('E');lcd_data('L');lcd_data('C');lcd_data('O');lcd_data('M');lcd_data('E');lcd_data(' ');lcd_data('U');lcd_data('S');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('2');lcd_data(' ');lcd_data(' ');
						tx_UART('<');tx_UART('2');tx_UART('>');
						count++;
				}
				else if(ret==3 && flag3 == 0)
				{
						flag3 = 1;
					  //lcd_cmd(0x01);
						//lcd_cmd(0x80);
						lcd_data('W');lcd_data('E');lcd_data('L');lcd_data('C');lcd_data('O');lcd_data('M');lcd_data('E');lcd_data(' ');lcd_data('U');lcd_data('S');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('3');lcd_data(' ');lcd_data(' ');
						tx_UART('<');tx_UART('3');tx_UART('>');
						count++;
				}
				else if(ret==4 && flag4 == 0)
				{
						flag4 = 1;
					  //lcd_cmd(0x01);
						//lcd_cmd(0x80);
						lcd_data('W');lcd_data('E');lcd_data('L');lcd_data('C');lcd_data('O');lcd_data('M');lcd_data('E');lcd_data(' ');lcd_data('U');lcd_data('S');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('4');lcd_data(' ');lcd_data(' ');
						tx_UART('<');tx_UART('4');tx_UART('>');
						count++;
				}
				else if(ret==5 && flag5 == 0)
				{
						flag5 = 1;
					  //lcd_cmd(0x01);
						//lcd_cmd(0x80);
						lcd_data('W');lcd_data('E');lcd_data('L');lcd_data('C');lcd_data('O');lcd_data('M');lcd_data('E');lcd_data(' ');lcd_data('U');lcd_data('S');lcd_data('E');lcd_data('R');lcd_data(' ');lcd_data('5');lcd_data(' ');lcd_data(' ');
						tx_UART('<');tx_UART('5');tx_UART('>');
						count++;	
				}
				
				else if(ret == 20)
				{
					
				}
				
				else
				{
					lcd_cmd(0x01);	lcd_cmd(0x80);
					lcd_string("MARKED ALREADY! ");
					tx_UART('<');tx_UART('X');tx_UART('>');
				}
			delay_lcd(2000);
		}
	}
}
