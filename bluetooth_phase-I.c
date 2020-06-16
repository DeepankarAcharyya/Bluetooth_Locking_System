#include<reg51.h>

char str;
char Charin=0;

void delay(int time)
{
 unsigned int i,j;
 for(i=0;i<time;i++)
 for(j=0;j<1275;j++);
}

//TMOD = 0x20; // Set time Timer 1 in 8-bit auto-reload mode (mode 2) 
//TH1 = 0xFD; // FD = -3, to send/ receive the data at 9.6Kbps
//SCON = 0x50; // Serial Control is set in Mode 1, with REN = 1 (reception ON)
//TI = 0; // Initialize the Timer Flag
//RI = 0; // Initialize the Timer

void Serialbegin()
{
   TMOD=0x20;
   SCON=0x50;
   TH1=0xfd;
   TR1=1;
}

void main()
{
		unsigned int ch[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    char mychar; // Assign a variable for the character to be received
		P2=0xc0;
		
		Serialbegin();
		delay(50);

    while(1) // Runs forever until power supply is cutoff
    {
      while(!RI); // Wait till the data is recieved, as soon as the data is received completely, the RI flag is set
			
			Charin=SBUF;
			mychar=Charin;
			RI = 0; // Clear the RI flag to declare the availability for reception of another data

        if (mychar == 'A') // If the data received through the Bluetooth module is the character 'A'
        {
           P2=ch[1];
        } 
        else if (mychar == 'a') // If the data received through the Bluetooth module is the character 'a'
        {
           P2=ch[2];
        }

        if (mychar == 'B') // If the data received through the Bluetooth module is the character 'B'
        {
           P2=ch[3];
        }
        else if (mychar == 'b') // If the data received through the Bluetooth module is the character 'b'
        {
           P2=ch[4];
        } 
    } 
}