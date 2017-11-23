#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Wire.h>
#include <GraphicsLib.h>
#include <MI0283QT9.h>
#include <ArduinoNunchuk.h>
#include <EEPROM.h>


//Declare display !
MI0283QT9 lcd;  //MI0283QT9 Adapter v1
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void init_adc_single_sample()
{
	ADMUX |= (1<<MUX0);		// input analog A1 Arduino
	ADMUX |= (1<<REFS0);	// 5 volt
	ADCSRA |= (1<<ADEN);	// ADC enable
}
void init_pwm_fast()
{
	TCCR2A |= (1<<COM0A1);					// Non-inverting mode A
	TCCR2A |= (1 << WGM01) | (1 << WGM00);	// set fast PWM Mode
	TCCR2B |= (1 << CS01);					// set prescaler to 8 and start the timer
}

void single_sample()
{
	uint8_t bricht;
	uint16_t result;
	ADCSRA |= (1<<ADSC);		// Start conversion
	while(ADCSRA & (1<<ADSC)) ;	// Wait
	result = ADC;
	//remap
	bricht = map((result >> 2), 0, 255, 0, 10);
	bricht = bricht * 10;
	lcd.led(bricht);
}

void mlevel1() {
	lcd.fillRect(60,15,200,50,0xFFFFFF);
	lcd.drawText(82,30, "Level 1", 0x111111, 0xFFFFFF, 3.5);
}
void mlevel2() {
	lcd.fillRect(60,70,200,50,0xFFFFFF);
	lcd.drawText(82,85, "Level 2", 0x111111, 0xFFFFFF, 3.5);
}
void mlevelRandom() {
	lcd.fillRect(60,125,200,50,0xFFFFFF);
	lcd.drawText(89,140, "Random", 0x111111, 0xFFFFFF, 3.5);
}
void mhighScore() {
	lcd.fillRect(60,180,200,50,0xFFFFFF);
	lcd.drawText(82,195, "High score", 0x111111, 0xFFFFFF, 2);
}
void characterA(int X, int Y) {
	int i,j;
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X + (i+3)),(Y+0),RGB(2,13,199));
	}
	
	lcd.drawPixel((X+2),(Y+1),RGB(2,13,199));
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+1),RGB(49,127,236));
	}
	lcd.drawPixel((X+13),(Y+1),RGB(2,13,199));
	
	lcd.drawPixel((X+ 1),(Y+2),RGB(2,13,199));
	for(i = 0; i < 12; i++){
		lcd.drawPixel((X+(i+2)),(Y+2),RGB(49,127,236));
	}
	lcd.drawPixel((X+14),(Y+2),RGB(2,13,199));
	
	lcd.drawPixel((X+1),(Y+3),RGB(2,13,199));
	for(i = 0; i < 12; i++){
		lcd.drawPixel((X+(i+2)),(Y+3),RGB(49,127,236));
	}
	lcd.drawPixel((X+14),(Y+3),RGB(2,13,199));
	
	lcd.drawPixel((X+1),(Y+4),RGB(2,13,199));
	lcd.drawPixel((X+2),(Y+4),RGB(49,127,236));
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+4),RGB(2,13,199));
	}
	lcd.drawPixel((X+13),(Y+4),RGB(49,127,236));
	lcd.drawPixel((X+14),(Y+4),RGB(2,13,199));
	
	lcd.drawPixel((X+2),(Y+5),RGB(2,13,199));
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+5),RGB(49,127,236));
	}
	lcd.drawPixel((X+13),(Y+5),RGB(2,13,199));
	
	for(i = 0; i < 12; i++){
		lcd.drawPixel((X+(i+2)),(Y+6),RGB(2,13,199));
	}
	
	lcd.drawPixel((X+3),(Y+7),RGB(254,204,154));
	lcd.drawPixel((X+4),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+5),(Y+7),RGB(0,0,0));
	lcd.drawPixel((X+6),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+7),(Y+7),RGB(254,204,154));
	lcd.drawPixel((X+8),(Y+7),RGB(254,204,154));
	lcd.drawPixel((X+9),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+10),(Y+7),RGB(0,0,0));
	lcd.drawPixel((X+11),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+12),(Y+7),RGB(254,204,154));
	
	lcd.drawPixel((X+0),(Y+8),RGB(254,204,154));
	lcd.drawPixel((X+1),(Y+8),RGB(254,204,154));
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+3)),(Y+8),RGB(254,204,154));
	}
	lcd.drawPixel((X+7),(Y+8),RGB(253,154,102));
	lcd.drawPixel((X+8),(Y+8),RGB(253,154,102));
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+9)),(Y+8),RGB(254,204,154));
	}

	lcd.drawPixel((X+14),(Y+8),RGB(254,204,154));
	lcd.drawPixel((X+15),(Y+8),RGB(254,204,154));
	
	lcd.drawPixel((X+0),(Y+9),RGB(254,204,154));
	lcd.drawPixel((X+1),(Y+9),RGB(254,204,154));
	lcd.drawPixel((X+2),(Y+9),RGB(2,13,199));
	lcd.drawPixel((X+4),(Y+9),RGB(2,13,199));
	for(i = 0; i < 6; i++){
		lcd.drawPixel((X+(i+5)),(Y+9),RGB(49,127,236));
	}
	lcd.drawPixel((X+11),(Y+9),RGB(2,13,199));
	lcd.drawPixel((X+13),(Y+9),RGB(2,13,199));
	lcd.drawPixel((X+14),(Y+9),RGB(254,204,154));
	lcd.drawPixel((X+15),(Y+9),RGB(254,204,154));
	
	lcd.drawPixel((X+1),(Y+10),RGB(2,13,199));
	lcd.drawPixel((X+2),(Y+10),RGB(49,127,236));
	lcd.drawPixel((X+3),(Y+10),RGB(2,13,199));
	for(i = 0; i < 8; i++){
		lcd.drawPixel((X+(i+4)),(Y+10),RGB(49,127,236));
	}
	lcd.drawPixel((X+12),(Y+10),RGB(2,13,199));
	lcd.drawPixel((X+12),(Y+10),RGB(49,127,236));
	lcd.drawPixel((X+12),(Y+10),RGB(2,13,199));

	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+2)),(Y+11),RGB(2,13,199));
	}
	for(i = 0; i < 6; i++){
		lcd.drawPixel((X+(i+5)),(Y+11),RGB(49,127,236));
	}
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+11)),(Y+11),RGB(2,13,199));
	}
	
	for(i = 0; i < 8; i++){
		lcd.drawPixel((X+(i+4)),(Y+12),RGB(2,13,199));
	}
	
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+3)),(Y+13),RGB(2,13,199));
	}
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+9)),(Y+13),RGB(2,13,199));
	}
	
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+2)),(Y+14),RGB(0,0,0));
	}
	lcd.drawPixel((X+5),(Y+14),RGB(2,13,199));
	lcd.drawPixel((X+10),(Y+14),RGB(2,13,199));
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+11)),(Y+14),RGB(0,0,0));
	}
	
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+2)),(Y+15),RGB(0,0,0));
	}
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+10)),(Y+15),RGB(0,0,0));
	}
	
}

void characterB(int X, int Y) {
	int i,j;
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+0),RGB(194,0,9));
	}
	
	lcd.drawPixel((X+2),(Y+1),RGB(194,0,9));
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+1),RGB(255,1,12));
	}
	lcd.drawPixel((X+13),(Y+1),RGB(194,0,9));
	
	lcd.drawPixel((X+1),(Y+2),RGB(194,0,9));
	for(i = 0; i < 12; i++){
		lcd.drawPixel((X+(i+2)),(Y+2),RGB(255,1,12));
	}
	lcd.drawPixel((X+14),(Y+2),RGB(194,0,9));
	
	lcd.drawPixel((X+1),(Y+3),RGB(194,0,9));
	for(i = 0; i < 12; i++){
		lcd.drawPixel((X+(i+2)),(Y+3),RGB(255,1,12));
	}
	lcd.drawPixel((X+14),(Y+3),RGB(194,0,9));
	
	lcd.drawPixel((X+1),(Y+4),RGB(194,0,9));
	lcd.drawPixel((X+2),(Y+4),RGB(255,1,12));
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+4),RGB(194,0,9));
	}
	lcd.drawPixel((X+13),(Y+4),RGB(255,1,12));
	lcd.drawPixel((X+14),(Y+4),RGB(194,0,9));
	
	lcd.drawPixel((X+2),(Y+5),RGB(194,0,9));
	for(i = 0; i < 10; i++){
		lcd.drawPixel((X+(i+3)),(Y+5),RGB(255,1,12));
	}
	lcd.drawPixel((X+13),(Y+5),RGB(194,0,9));
	
	for(i = 0; i < 12; i++){
		lcd.drawPixel((X+(i+2)),(Y+6),RGB(194,0,9));
	}
	
	lcd.drawPixel((X+3),(Y+7),RGB(254,204,154));
	lcd.drawPixel((X+4),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+5),(Y+7),RGB(0,0,0));
	lcd.drawPixel((X+6),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+7),(Y+7),RGB(254,204,154));
	lcd.drawPixel((X+8),(Y+7),RGB(254,204,154));
	lcd.drawPixel((X+9),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+10),(Y+7),RGB(0,0,0));
	lcd.drawPixel((X+11),(Y+7),RGB(255,255,255));
	lcd.drawPixel((X+12),(Y+7),RGB(254,204,154));
	
	lcd.drawPixel((X+0),(Y+8),RGB(254,204,154));
	lcd.drawPixel((X+1),(Y+8),RGB(254,204,154));
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+3)),(Y+8),RGB(254,204,154));
	}
	lcd.drawPixel((X+7),(Y+8),RGB(253,154,102));
	lcd.drawPixel((X+8),(Y+8),RGB(253,154,102));
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+9)),(Y+8),RGB(254,204,154));
	}
	lcd.drawPixel((X+14),(Y+8),RGB(254,204,154));
	lcd.drawPixel((X+15),(Y+8),RGB(254,204,154));
	
	lcd.drawPixel((X+0),(Y+9),RGB(254,204,154));
	lcd.drawPixel((X+1),(Y+9),RGB(254,204,154));
	lcd.drawPixel((X+2),(Y+9),RGB(194,0,9));
	lcd.drawPixel((X+4),(Y+9),RGB(194,0,9));
	for(i = 0; i < 6; i++){
		lcd.drawPixel((X+(i+5)),(Y+9),RGB(255,1,12));
	}
	lcd.drawPixel((X+11),(Y+9),RGB(194,0,9));
	lcd.drawPixel((X+13),(Y+9),RGB(194,0,9));
	lcd.drawPixel((X+14),(Y+9),RGB(254,204,154));
	lcd.drawPixel((X+15),(Y+9),RGB(254,204,154));
	
	lcd.drawPixel((X+1),(Y+10),RGB(194,0,9));
	lcd.drawPixel((X+2),(Y+10),RGB(255,1,12));
	lcd.drawPixel((X+3),(Y+10),RGB(194,0,9));
	for(i = 0; i < 8; i++){
		lcd.drawPixel((X+(i+4)),(Y+10),RGB(255,1,12));
	}
	lcd.drawPixel((X+12),(Y+10),RGB(194,0,9));
	lcd.drawPixel((X+13),(Y+10),RGB(255,1,12));
	lcd.drawPixel((X+14),(Y+10),RGB(194,0,9));
	
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+2)),(Y+11),RGB(194,0,9));
	}
	for(i = 0; i < 6; i++){
		lcd.drawPixel((X+(i+5)),(Y+11),RGB(255,1,12));
	}
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+11)),(Y+11),RGB(194,0,9));
	}
	
	for(i = 0; i < 8; i++){
		lcd.drawPixel((X+(i+4)),(Y+12),RGB(194,0,9));
	}
	
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+3)),(Y+13),RGB(194,0,9));
	}
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+9)),(Y+13),RGB(194,0,9));
	}
	
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+2)),(Y+14),RGB(0,0,0));
	}
	lcd.drawPixel((X+5),(Y+14),RGB(194,0,9));
	lcd.drawPixel((X+10),(Y+14),RGB(194,0,9));
	for(i = 0; i < 3; i++){
		lcd.drawPixel((X+(i+11)),(Y+14),RGB(0,0,0));
	}
	
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+2)),(Y+15),RGB(0,0,0));
	}
	for(i = 0; i < 4; i++){
		lcd.drawPixel((X+(i+10)),(Y+15),RGB(0,0,0));
	}
}
int navigate() {
	int nunchukY = 1;
	int counter = 5;
	int i = 0;
	int q = 0;
	
	while(1) {
		//single_sample();
		nunchuk.update();
		if(nunchuk.analogY < 60) {
			if(i>counter) {
				i=0;
			}
			if(i == 0) {
				nunchukY++;
				i++;
			}
			i++;
		}
		
		if(nunchuk.analogY > 200) {
			if(i>counter) {
				i=0;
			}
			if(i == 0) {
				nunchukY--;
				i++;
			}
			i++;
		}
		
		Serial.print(nunchuk.analogY, DEC);
		Serial.print(' ');
		Serial.println(nunchukY, DEC);
		
		if(nunchukY == 1){
			lcd.drawRect(60, 180, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 181, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 182, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 70, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 71, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 72, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 15, 200, 50, RGB(255,0,0));
			lcd.drawRect(61, 16, 198, 48, RGB(255,0,0));
			lcd.drawRect(62, 17, 196, 46, RGB(255,0,0));
			if (nunchuk.zButton) {
				return 1;
			}
		}
		if(nunchukY == 2){
			lcd.drawRect(60, 15, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 16, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 17, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 125, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 126, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 127, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 70, 200, 50, RGB(255,0,0));
			lcd.drawRect(61, 71, 198, 48, RGB(255,0,0));
			lcd.drawRect(62, 72, 196, 46, RGB(255,0,0));
			if (nunchuk.zButton) {
				return 2;
			}
		}
		if(nunchukY == 3){
			lcd.drawRect(60, 70, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 71, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 72, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 180, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 181, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 182, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 125, 200, 50, RGB(255,0,0));
			lcd.drawRect(61, 126, 198, 48, RGB(255,0,0));
			lcd.drawRect(62, 127, 196, 46, RGB(255,0,0));
			
			if (nunchuk.zButton) {
				return 3;
			}
		}
		if(nunchukY == 4){
			lcd.drawRect(60, 125, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 126, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 127, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 15, 200, 50, RGB(255,255,255));
			lcd.drawRect(61, 16, 198, 48, RGB(255,255,255));
			lcd.drawRect(62, 17, 196, 46, RGB(255,255,255));
			
			lcd.drawRect(60, 180, 200, 50, RGB(255,0,0));
			lcd.drawRect(61, 181, 198, 48, RGB(255,0,0));
			lcd.drawRect(62, 182, 196, 46, RGB(255,0,0));
			
			if (nunchuk.zButton) {
				return 4;
			}
		}
		if(nunchukY == 5){
			nunchukY = 1;
		}
		if(nunchukY == 0){
			nunchukY = 4;
		}
	}
}

int Startscherm(){
	int level;
	lcd.fillScreen(RGB(0,0,0));
	mlevel1();
	mlevel2();
	mlevelRandom();
	mhighScore();
	lcd.fillRect(0,0,16,16,RGB(255,255,255));
	characterA(0,0);
	lcd.fillRect(304,0,16,16,RGB(255,255,255));
	characterB(304,0);
	level = navigate();
	return level;
}

int level1() {
	lcd.fillScreen(RGB(255,0,0));
	_delay_ms(1000);
	return;
}
int level2() {
	lcd.fillScreen(RGB(0,255,0));
	_delay_ms(1000);
	return;
}
int levelRandom() {
	lcd.fillScreen(RGB(0,0,255));
	_delay_ms(1000);
	return;
}
int highScore() {
	lcd.fillScreen(RGB(255,255,0));
	_delay_ms(1000);
	return;
}


int main(void)
{
	int level;
	init();
	Serial.begin(9600);
	//	MI0283QT9 lcd;  //MI0283QT9 Adapter v1
	uint8_t clear_bg=0x00; //0x80 = dont clear background for fonts (only for DisplayXXX)

	//init display
	lcd.begin();
	nunchuk.init();
	init_adc_single_sample();
//	init_pwm_fast();
	
	
	while (1)
	{
		level = Startscherm();
		Serial.println(level, DEC);

	if (level == 1)	{
		level1();
	}
	if (level == 2)	{
		level2();
	}
	if (level == 3)	{
		levelRandom();
	}
	if (level == 4)	{
		highScore();
	}
	}
}