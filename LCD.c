#include "reg51.h"
#define display_port P2

// LCD module connections

sbit RS = P3^0; // RXD pin
sbit RW = P3^1; // TXD pin
sbit EN = P3^2; // INT0 pin

// Function to create delay
void msdelay(unsigned int msTime)
	{
	int i, j;
	for(i =0; i<msTime; i++)
		{
			for(j=0; j<1275; j++)
			{
			}
		}
	}
	
	
// Function for lcd_command - this is to pass commands
void lcd_Cmd(unsigned char command)
{
	display_port = command; 		// Port 2 is passed with the hexadecimal command
	
	RS = 0;			 				        // If we make the RS pin HIGH and feed an input to the data lines (DB0 to DB7), 
															// this input will be treated as data to display on LCD screen. 
															// If we make the RS pin LOW and feed an input to the data lines, 
															// then this will be treated as a command 
															//( a command to be written to LCD controller – like positioning cursor orclear screen or scroll)
	
	RW = 0;										// Logic HIGH at this pin activates read mode and logic LOW at this pin activates write mode 						

	
	EN = 1;
	
	msdelay(10);
	EN = 0; 									//  This pin is meant for enabling the LCD module. 
															// A HIGH to LOW signal at this pin will enable the module
}
	
	
// Function for LCD Display
	void lcd_data(unsigned char text)
	{
		display_port = text;			// Port 2 is passed with the user defined text
		
		RS = 1;										// If we make the RS pin HIGH and feed an input to the data lines (DB0 to DB7), 
															// this input will be treated as data to display on LCD screen. 
															// If we make the RS pin LOW and feed an input to the data lines, 
															// then this will be treated as a command 
															//( a command to be written to LCD controller – like positioning cursor orclear screen or scroll)
	
		RW = 0;										// Logic HIGH at this pin activates read mode and logic LOW at this pin activates write mode 		 
	
		
		EN = 1;
		msdelay(10);
		EN = 0; 									//  This pin is meant for enabling the LCD module. 
															// A HIGH to LOW signal at this pin will enable the module
	
	}
	
// Function to initialize the LCD 
void lcd_init()
	{
	
	lcd_Cmd(0x38); // 2 lines and 5×7 matrix selection
	msdelay(10); // delaying for 10 milliseconds
	
	lcd_Cmd(0x0F); // LCD on, cursor on
	msdelay(10);
	
	lcd_Cmd(0x01); // Clear display screen
	msdelay(10);
	
	lcd_Cmd(0x81);	// Bring cursor to position 1 of line 1
	msdelay(10); 
}


void main(){
	
	unsigned char arr[] = "Welcome all!!";
	int k =0;
	lcd_init();
	
	while(arr[k] != '\0'){
	lcd_data(arr[k]);
	k++;
	msdelay(50);
	}
	
}