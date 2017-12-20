#include <Arduino.h>
#include <avr/interrupt.h>
#include "lib/IRcom/IRcom.h"

IRcom ir;

ISR(TIMER2_COMPB_vect){
}

ISR(TIMER1_OVF_vect) {    //macro met interrupt vector
	ir.setTellerVerzender(ir.getTellerVerzender() + 1);
	ir.setTellerOntvanger(ir.getTellerOntvanger() + 1);
}

ISR(INT0_vect){

	ir.verschil = ir.getTellerOntvanger() - ir.tempteller;
	
	if(ir.startbit == 0){
		if(ir.verschil >= 40){
			ir.startbit = 1;
			ir.ontvangeraantal++;
		}
		} else if (ir.startbit == 1){
		if(ir.verschil >= 40){
			ir.startbit = 0;
			ir.setTellerOntvanger(0);
			ir.tempteller = 0;
			ir.ontvangeraantal++;
			} else if(ir.verschil >= 30 && ir.verschil <40){
			ir.ontvangenbericht |=(1<<ir.bitteller);
			ir.bitteller--;
			ir.ontvangeraantal++;
			} else if(ir.verschil >= 20 && ir.verschil <30){
			ir.ontvangenbericht &=~(1<<ir.bitteller);
			ir.bitteller--;
			ir.ontvangeraantal++;
		}
	}
	
	if(ir.ontvangeraantal % 10 == 0){
		if(ir.bitteller == -1){
			ir.bitteller = 7;
			ir.letter = ir. ontvangenbericht;
			Serial.println(ir.letter);
			ir.ontvangenbericht = 0x00;
			}else{
			ir.bitteller =7;
			ir.ontvangenbericht = 0x00;
		}
	}
	ir.tempteller = ir.getTellerOntvanger();
}

int main(void){
	Serial.begin(9600);
	
	ir.setIR();
	
	while(1){
		if(Serial.available()){
			char letter = Serial.read();
			ir.sendByte(letter);
		}
	}
	
	return;
	
}