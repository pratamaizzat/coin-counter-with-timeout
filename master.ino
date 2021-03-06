#include "Wire.h"
#include "EEPROM.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SH1106.h"

//oled define
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

//sistem define
#define pinIRd 17
#define pinIRa A0
#define pinLED 13
#define pbReset 13
#define pbOK 8
#define pbScroll 9
#define pbOUT 11
#define BUZZER A7
#define LED1 22
#define LED2 23
int IRvalueA = 0;
int IRvalueD = 0;
int jmlkoin = 0;
int koin = 0;
int jml = 0;
int jmltunai = 0;
int var1 = 0;
int var2 = 0;
int arr2 = 0;
int arr1 = 0;
int arrmin = 0;
int arrmax = 0;
int batas;
int adcValue=0;
int batasTersimpan;
int adc;
int adccoba=54;
int jmlArrS=0;
int jmlArrL=0;
int ratarata=0;
uint64_t time_loop=0;
uint64_t time_val=2000;
unsigned int sensor_L[10] = {};
unsigned int sensor_S[10] = {};
int dumb = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(pinIRd, INPUT);
  	pinMode(pinIRa, INPUT);
  	pinMode(pinLED, OUTPUT);
  	pinMode(pbOK, INPUT_PULLUP);
  	pinMode(pbScroll, INPUT_PULLUP);
  	pinMode(pbReset, INPUT_PULLUP);
  	pinMode(pbOUT, INPUT_PULLUP);
  	pinMode(BUZZER, OUTPUT);
  	pinMode(LED1, OUTPUT);
  	pinMode(LED2, OUTPUT);

  	digitalWrite(LED1, HIGH);
  	digitalWrite(LED2, HIGH);


	display.begin(SH1106_SWITCHCAPVCC, 60);
	display.clearDisplay();
	showBooting();
	showBnner();


	batasTersimpan=EEPROM.read(0);
}

void loop()
{

utama:
	showIDName();
	while(1){
	    // statement
	    if(digitalRead(pbOK)==LOW)
	    {
	    	delay(20);
	    	if(digitalRead(pbOK)==LOW)
	    	{
	    		while(digitalRead(pbOK)==LOW);
	    		goto MenuUtamaKalibrasi;
	    	}
	    }
	}

MenuUtamaKalibrasi:
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,0);
	display.println("KALIBRASI");
	display.setTextColor(WHITE);
	display.setCursor(0,20);
	display.println("COUNTER");
	display.setTextColor(WHITE);
	display.setCursor(0,40);
	display.println("SET ADC");
	display.display();
	delay(20);
	while(1){
		    // statement
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	delay(20);
		    	if(digitalRead(pbScroll)==LOW)
		    	{
		    		while(digitalRead(pbScroll)==LOW);
		    		goto MenuUtamaCounter;
		    	}
		    }

		    if(digitalRead(pbOK)==LOW)
		    {
		    	delay(20);
		    	if(digitalRead(pbOK)==LOW)
		    	{
		    		while(digitalRead(pbOK)==LOW);
		    		goto kalibrasi;
		    	}

		    }
		}

MenuUtamaCounter:
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("KALIBRASI");
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,20);
	display.println("COUNTER  ");
	display.setTextColor(WHITE);
	display.setCursor(0,40);
	display.println("SET ADC");
	display.display();
	delay(20);
	while(1){
	    // statement
	    if(digitalRead(pbScroll)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	while(digitalRead(pbScroll)==LOW);
		    	goto MenuUtamaADC;
		    }
		}

		if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				goto counterStart;
			}
		}
	}

MenuUtamaADC:
	adcValue=0;
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("KALIBRASI");
	display.setTextColor(WHITE);
	display.setCursor(0,20);
	display.println("COUNTER");
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,40);
	display.println("SET ADC  ");
	display.display();
	delay(20);
	while(1){
	    // statement
	    if(digitalRead(pbScroll)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	while(digitalRead(pbScroll)==LOW);
		    	goto MenuUtamaCredit;
		    }
		}

		if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				goto SetADC;
			}
		}
	}

MenuUtamaCredit:
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("COUNTER");
	display.setTextColor(WHITE);
	display.setCursor(0,20);
	display.println("SET ADC");
	display.setTextColor(BLACK,WHITE);
	display.setCursor(0,40);
	display.println("CREDIT   ");
	display.display();
	delay(20);
	while(1){
	    if(digitalRead(pbScroll)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbScroll)==LOW)
		    {
		    	while(digitalRead(pbScroll)==LOW);
		    	goto MenuUtamaKalibrasi;
		    }
		}
		if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				goto CreditShow;
			}
		}
	}

SetADC:
	display.clearDisplay();
	display.setCursor(0,25);
	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.println("Insert value =");
	display.display();
	while(1){
	    // statement
	    display.clearDisplay();
	    if(digitalRead(pbScroll)==LOW){
	    	adcValue++;
			display.setCursor(0,25);
			display.setTextColor(WHITE);
			display.setTextSize(1);
			display.println("Insert value =");
			display.setCursor(90,25);
			display.print(adcValue);
			display.display();
	    	delay(50);
	    }
	    if(digitalRead(pbOUT)==LOW){
	    	adcValue--;
			display.setCursor(0,25);
			display.setTextColor(WHITE);
			display.setTextSize(1);
			display.println("Insert value =");
			display.setCursor(90,25);
			display.print(adcValue);
			display.display();
	    	delay(50);
	    }
	    if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				batasTersimpan=EEPROM.read(0);
				digitalWrite(LED1, HIGH);
        		digitalWrite(LED2, HIGH);
				goto MenuUtamaADC;
			}
		}
		if (digitalRead(pbReset) == LOW)
    	{
      		delay(20);
      		if (digitalRead(pbReset) == LOW)
      		{
        		while (digitalRead(pbReset) == LOW);
        		EEPROM.write(0, adcValue);
        		digitalWrite(LED1, LOW);
        		digitalWrite(LED2, LOW);
        		digitalWrite(BUZZER, HIGH);
      			delay(100);
      			digitalWrite(BUZZER, LOW);
      			delay(100);
      			digitalWrite(BUZZER, HIGH);
      			delay(100);
      			digitalWrite(BUZZER, LOW);
      			delay(100);
      		}
    	}
	}

kalibrasi:
	display.clearDisplay();
	while(1){

  		display.clearDisplay();
  		display.setTextSize(3);
  		display.setTextColor(WHITE);
  		display.setCursor(20,20);
  		display.print(IRvalueA);
  		display.display();

    	if (IRvalueD == LOW) {
    		digitalWrite(LED_BUILTIN, HIGH);
    		digitalWrite(LED1, LOW);
    		digitalWrite(LED2, HIGH);

  		}
  		else {
   		 	digitalWrite(LED_BUILTIN, LOW);
   		 	digitalWrite(LED2, LOW);
   		 	digitalWrite(LED1, HIGH);

		}
  		delay(10);
  
  		IRvalueA = analogRead(pinIRa);
  		IRvalueD = digitalRead(pinIRd);


	    if(digitalRead(pbOK)==LOW)
		{
			delay(20);
			if(digitalRead(pbOK)==LOW)
			{
				while(digitalRead(pbOK)==LOW);
				digitalWrite(LED2, HIGH);
				digitalWrite(LED1, HIGH);
				goto MenuUtamaKalibrasi;
			}
		}
	}

counterStart:

	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(25,30);
	display.println("INSERT COIN!");
	display.display();
	while(1){
		// statement
		display.clearDisplay();
		time_loop=0;

		if(analogRead(pinIRa)<=batasTersimpan)
		{

			delay(10);
      		while (analogRead(pinIRa)<=batasTersimpan && time_loop++<=time_val);
      		if(time_loop>=time_val){
      			display.clearDisplay();
      			display.setCursor(25,30);
      			display.println("ERROR");
      			display.display();
      			digitalWrite(BUZZER, HIGH);
      			delay(200);
      			digitalWrite(BUZZER, LOW);
      			delay(200);
      			digitalWrite(BUZZER, HIGH);
      			delay(200);
      			digitalWrite(BUZZER, LOW);
      			delay(700);
  			}      			
      		else{
      			digitalWrite(LED_BUILTIN, HIGH);
      			jmlkoin++;
      			koin = 1000;
      			jmltunai += 10;

      			display.setTextSize(4);
				display.setTextColor(WHITE);
      			display.setCursor(40,0);
      			display.println(jmlkoin);
      			display.setTextSize(1);
      			display.setCursor(0,50);
      			display.println(koin);
      			display.setCursor(90,50);
      			display.print(jmltunai);
      			display.print("00");
      			display.display();
      		}		
		}
		else if(analogRead(pinIRa)<=100)
		{
			delay(10);
      		while (analogRead(pinIRa) <= 100 && time_loop++<=time_val);
      		if(time_loop>=time_val){
      			display.clearDisplay();
      			display.setTextSize(3);
      			display.setCursor(25,30);
      			display.println("ERROR");
      			display.display();
      			digitalWrite(BUZZER, HIGH);
      			delay(200);
      			digitalWrite(BUZZER, LOW);
      			delay(200);
      			digitalWrite(BUZZER, HIGH);
      			delay(200);
      			digitalWrite(BUZZER, LOW);
      			delay(700);
      			if(digitalRead(pbOK)==LOW)
	    		{
	    			delay(20);
	    			if(digitalRead(pbOK)==LOW)
	    			{
	    				while(digitalRead(pbOK)==LOW);
	    				break;
	    			}
	   			 }
  			}else{
  				digitalWrite(LED_BUILTIN, HIGH);
      			jmlkoin++;
      			koin = 500;
      			jmltunai += 5;

      			display.setTextSize(4);
				display.setTextColor(WHITE);
      			display.setCursor(40,0);
      			display.println(jmlkoin);
      			display.setTextSize(1);
				display.setTextColor(WHITE);
      			display.setCursor(0,50);
      			display.println(koin);
      			display.setCursor(90,50);
      			display.print(jmltunai);
      			display.print("00");
      			display.display();
  			}
      		
		}

		delay(50);

    	if (digitalRead(pbReset) == LOW)
    	{
      		delay(20);
      		if (digitalRead(pbReset) == LOW)
      		{
        		while (digitalRead(pbReset) == LOW);
        		display.clearDisplay();
        		goto ResetConter;
      		}
    	}

    	if(digitalRead(pbOUT)==LOW)
    	{
    		delay(20);
    		if(digitalRead(pbOUT)==LOW)
    		{
    			while(digitalRead(pbOUT)==LOW);
    			koin = 0;
	    		jmlkoin=0;
      			jmltunai=0;
    			display.clearDisplay();
    			goto MenuUtamaCounter;
    		}
    	}
	}

blankTest:
	blankShow();
	while(1){
	    // statement
	}

ResetConter:
	while(1){
	    // statement
	    koin = 0;
	    jmlkoin=0;
      	jmltunai=0;
	    goto counterStart;
	}

CreditShow:
	display.clearDisplay();
	showIDName();
	while(1){
		    // statement
		if(digitalRead(pbOK)==LOW)
		{
		    delay(20);
		    if(digitalRead(pbOK)==LOW)
		    {
		    	while(digitalRead(pbOK)==LOW);
		    	goto MenuUtamaCredit;
		    }
		}
	}	
}

void blankShow(void)
{
	display.println(" ");
	display.display();
	delay(3000);
	display.clearDisplay();
}

void showBnner(void)
{
	display.setTextSize(2);
	display.setTextColor(BLACK,WHITE);
	display.setCursor(10,20);
	display.println("PROJECT 2");
	display.setTextSize(1);
	display.setCursor(30,40);
	display.setTextColor(WHITE);
	display.println("TIMEOUT COIN");
	display.display();
	delay(1000);
	display.clearDisplay();

}

void showIDName(void)
{
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("ILFAT IZZAT P.");
	display.setCursor(0,15);
	display.println("1110171039");
	display.setCursor(0,30);
	display.println("FITROTUL IRDA A.");
	display.setCursor(0,45);
	display.println("1110171047");
	display.setCursor(100,50);
	display.setTextColor(BLACK,WHITE);
	display.println("MENU");
	display.display();
	delay(20);
	display.clearDisplay();
}

void showBooting(void)
{
	display.drawPixel(10,10,WHITE);
	display.display();
	delay(500);
	display.drawPixel(20,10,WHITE);
	display.display();
	delay(500);
	display.drawPixel(30,10,WHITE);
	display.display();
	delay(500);
	display.clearDisplay();
}