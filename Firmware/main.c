#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000UL

#define LCD_RS RB0
#define LCD_EN RB1

#define LCD_D4 RB2
#define LCD_D5 RB3
#define LCD_D6 RB4
#define LCD_D7 RB5



#define FRONT_SENSOR RC4
#define LEFT_SENSOR  RC5
#define REAR_SENSOR  RC6
#define RIGHT_SENSOR RA1



#define BUZZER    RC7

#define GREEN_LED RD4
#define RED_LED   RD5




void LCD_Pulse(void)
{
    LCD_EN = 1;
    __delay_us(2);
    LCD_EN = 0;
    __delay_us(100);
}


void LCD_Send4Bit(unsigned char data)
{
    LCD_D4 = (data >> 0) & 1;
    LCD_D5 = (data >> 1) & 1;
    LCD_D6 = (data >> 2) & 1;
    LCD_D7 = (data >> 3) & 1;

    LCD_Pulse();
}


void LCD_Command(unsigned char cmd)
{
    LCD_RS = 0;

    LCD_Send4Bit(cmd >> 4);
    LCD_Send4Bit(cmd & 0x0F);

    __delay_ms(2);
}


void LCD_Char(char data)
{
    LCD_RS = 1;

    LCD_Send4Bit(data >> 4);
    LCD_Send4Bit(data & 0x0F);

    __delay_us(100);
}


void LCD_String(const char *str)
{
    while(*str)
    {
        LCD_Char(*str++);
    }
}


void LCD_Clear(void)
{
    LCD_Command(0x01);
    __delay_ms(2);
}


void LCD_SetCursor(unsigned char row, unsigned char column)
{
    if(row == 1)
        LCD_Command(0x80 + column - 1);
    else
        LCD_Command(0xC0 + column - 1);
}


void LCD_Init(void)
{
    __delay_ms(20);

    LCD_RS = 0;
    LCD_EN = 0;

    LCD_Send4Bit(0x03);
    __delay_ms(5);

    LCD_Send4Bit(0x03);
    __delay_us(150);

    LCD_Send4Bit(0x03);

    LCD_Send4Bit(0x02);

    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);

    __delay_ms(2);
}



void Motor_Stop(void)
{
    RD0 = 0;
    RD1 = 0;
    RD2 = 0;
    RD3 = 0;
}


void Motor_Forward(void)
{
    
    RD0 = 1;
    RD1 = 0;

    
    RD2 = 1;
    RD3 = 0;
}


void Motor_Reverse(void)
{
    
    RD0 = 0;
    RD1 = 1;

    
    RD2 = 0;
    RD3 = 1;
}


 
void Servo_Left_Pulse(void)
{
    RC2 = 1;
    __delay_us(1000);

    RC2 = 0;
    __delay_ms(19);
}



void Servo_Center_Pulse(void)
{
    RC2 = 1;
    __delay_us(1500);

    RC2 = 0;
    __delay_ms(18);
}

 
void Servo_Right_Pulse(void)
{
    RC2 = 1;
    __delay_ms(2);

    RC2 = 0;
    __delay_ms(18);
}

 

void Servo_Left(void)
{
    unsigned char i;

    for(i = 0; i < 30; i++)
    {
        Servo_Left_Pulse();
    }
}


void Servo_Center(void)
{
    unsigned char i;

    for(i = 0; i < 30; i++)
    {
        Servo_Center_Pulse();
    }
}


void Servo_Right(void)
{
    unsigned char i;

    for(i = 0; i < 30; i++)
    {
        Servo_Right_Pulse();
    }
}

 

void Display_Sensors(void)
{
    LCD_Clear();

    LCD_SetCursor(1,1);

    LCD_String("F:");

    if(FRONT_SENSOR)
        LCD_String("OBS");
    else
        LCD_String("CLR");

    LCD_String(" L:");

    if(LEFT_SENSOR)
        LCD_String("OBS");
    else
        LCD_String("CLR");


    LCD_SetCursor(2,1);

    LCD_String("R:");

    if(REAR_SENSOR)
        LCD_String("OBS");
    else
        LCD_String("CLR");

    LCD_String(" Rt:");

    if(RIGHT_SENSOR)
        LCD_String("OBS");
    else
        LCD_String("CLR");
}


 

void Emergency_Stop(void)
{
    Motor_Stop();

    Servo_Center();

    RED_LED = 1;
    GREEN_LED = 0;

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("OBSTACLE!");

    LCD_SetCursor(2,1);
    LCD_String("STOPPED");

    __delay_ms(1000);
}


 

void Search_Parking_Space(void)
{
    unsigned int clear_count = 0;

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("SEARCHING");

    LCD_SetCursor(2,1);
    LCD_String("FOR SPACE");

    GREEN_LED = 1;
    RED_LED = 0;

    Motor_Forward();


    while(1)
    {
         
        Servo_Center_Pulse();


         
        if(FRONT_SENSOR)
        {
            Motor_Stop();

            LCD_Clear();

            LCD_SetCursor(1,1);
            LCD_String("FRONT");

            LCD_SetCursor(2,1);
            LCD_String("OBSTACLE");

            RED_LED = 1;
            GREEN_LED = 0;

            
            while(FRONT_SENSOR)
            {
                Servo_Center_Pulse();
            }

            RED_LED = 0;

            Motor_Forward();
        }


         
        if(LEFT_SENSOR == 0)
        {
            clear_count++;

             
            if(clear_count >= 100)
            {
                Motor_Stop();

                LCD_Clear();

                LCD_SetCursor(1,1);
                LCD_String("SPACE FOUND");

                LCD_SetCursor(2,1);
                LCD_String("STOP");

                GREEN_LED = 0;

                __delay_ms(1000);

                break;
            }
        }
        else
        {
            clear_count = 0;
        }
    }
}


void Reverse_Left(void)
{
    unsigned int i;

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("PARKING");

    LCD_SetCursor(2,1);
    LCD_String("REVERSE LEFT");

    Motor_Reverse();

    GREEN_LED = 1;
    RED_LED = 0;


   
    for(i = 0; i < 125; i++)
    {
        Servo_Left_Pulse();


        
        if(REAR_SENSOR)
        {
            Motor_Stop();

            LCD_Clear();

            LCD_SetCursor(1,1);
            LCD_String("REAR");

            LCD_SetCursor(2,1);
            LCD_String("OBSTACLE");

            RED_LED = 1;
            GREEN_LED = 0;

            Servo_Center();

            return;
        }
    }

    Motor_Stop();

    __delay_ms(500);
}

 

void Reverse_Right(void)
{
    unsigned int i;

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("PARKING");

    LCD_SetCursor(2,1);
    LCD_String("REVERSE RIGHT");

    Motor_Reverse();

    GREEN_LED = 1;
    RED_LED = 0;

 
    for(i = 0; i < 100; i++)
    {
        Servo_Right_Pulse();

 
        if(REAR_SENSOR)
        {
            Motor_Stop();

            RED_LED = 1;
            GREEN_LED = 0;

            LCD_Clear();

            LCD_SetCursor(1,1);
            LCD_String("REAR");

            LCD_SetCursor(2,1);
            LCD_String("OBSTACLE");

            Servo_Center();

            return;
        }
    }

    Motor_Stop();

    __delay_ms(500);
}

 

void Straighten_Car(void)
{
    unsigned int i;

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("STRAIGHTENING");

    LCD_SetCursor(2,1);
    LCD_String("CAR");

    GREEN_LED = 1;
    RED_LED = 0;


    Motor_Reverse();

 
    for(i = 0; i < 50; i++)
    {
        Servo_Center_Pulse();

        if(REAR_SENSOR)
        {
            Motor_Stop();

            RED_LED = 1;
            GREEN_LED = 0;

            return;
        }
    }

    Motor_Stop();

    Servo_Center();

    GREEN_LED = 0;
}

 

void Parking_Complete(void)
{
    Motor_Stop();

    Servo_Center();

    GREEN_LED = 1;
    RED_LED = 0;

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("PARKING");

    LCD_SetCursor(2,1);
    LCD_String("COMPLETE");

    __delay_ms(5000);
}

 

void main(void)
{
   

    ADCON1 = 0x06;

 

    TRISA = 0xFF;

    
    TRISA1 = 1;

 
    TRISB = 0x00;

    PORTB = 0;
 

    
    TRISC2 = 0;

    
    TRISC4 = 1;
    TRISC5 = 1;
    TRISC6 = 1;

     
    TRISC7 = 0;


    
    TRISD0 = 0;
    TRISD1 = 0;
    TRISD2 = 0;
    TRISD3 = 0;

   
    TRISD4 = 0;
    TRISD5 = 0;

 

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;

    Motor_Stop();

    RC2 = 0;

    BUZZER = 0;

    GREEN_LED = 0;
    RED_LED = 0;

 

    LCD_Init();

 

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_String("CEREBRAL");

    LCD_SetCursor(2,1);
    LCD_String("AUTOPARK");

    GREEN_LED = 1;

    Servo_Center();

    __delay_ms(2000);

    GREEN_LED = 0;

 

    while(1)
    {
         
        Search_Parking_Space();

 
        Reverse_Left();

 
        Reverse_Right();


         
        Straighten_Car();

 
        Parking_Complete();

 
        Motor_Stop();

        Servo_Center();

        while(1)
        {
            GREEN_LED = 1;
            RED_LED = 0;

            LCD_Clear();

            LCD_SetCursor(1,1);
            LCD_String("PARKED");

            LCD_SetCursor(2,1);
            LCD_String("SYSTEM READY");

            __delay_ms(1000);
        }
    }
}
