// Login für die Benutzung des LaserCutters
// Steuerung über 128x64 Grafikdisplay und Drehimpulstaster
// Autor: Astner A.
// Erstellt: 13.01.2018 --> Basisversion, Entwicklung der Menüpunkte
// Geändert: 19.01.2018 --> Piezzo in Interruptroutine einbinden
// Geändert: 22.01.2018 --> Umbau auf LCDMenuLib2 (neue Menüstruktur)
// Geändert: 30.01.2018 --> Versuche mit neuer Menüstruktur (show/hide)
// Geändert: 03.02.2018 --> Umbau der Menüstruktur (show/hide), Menüpunkte erweitern

#include <Arduino.h>
#include <U8g2lib.h>
#include "Library_LaserCutter_V3.h"
#include "Library_EEprom_V3.h"
#include <EEPROM.h>
#include <String.h>
#include "watchdog.h"					// WatchdogTimer
#include <LCDMenuLib2.h>				// Bibliothek für die Menüanzeige
#include <TimerOne.h>					// Timer1 Interrupt für Encoder und Piezzo
#include <SPI.h>						// Ansteuerung des Grafikdisplays
#include "menue_LaserCutter_V3.h"		// Definition der Menüstruktur für die Bedienung des Lasercutters

// #include "fastio.h"
// #include "buzzer.h"
// #include <ClickEncoder.h>		// Routinen für den Drehimpulsgeber
 

// ClickEncoder *encoder;
// int16_t last, value;

void timerIsr(void) {
	// encoder->service();		// Abwicklung des Drehimpulsgebers
	piezzo();  							// Ansteuerung des Piezzo
}

 
void setup(void) {
	
	pinMode(ledPin, OUTPUT); 			// BlinkLed
	pinMode(BEEPER_PIN, OUTPUT); 		// Piezzo auf der Grafikanzeige 128x64
	pinMode(FG_laser, OUTPUT); 			// Freigaberelais für den Lasercutter (bei erfolgreichem Login)
	pinMode(laser_activ, INPUT_PULLUP);	// Rückmeldung von Steuerplatine des Lasercutters --> Laser aktiv
	
	init_T1_interrupt();				// Initialisierung Timer1 Interrupt
	init_grafic_128x64();				// Initialisierung des Grafikdisplays 128x64
	
	u8g2.begin();  

	Serial.begin(115200);
	Serial.println(F(_LCDML_VERSION)); // only for examples
	Serial.print('\n');
	Serial.print('\n');
   
    LCDML_setup(_LCDML_DISP_cnt);		// LCDMenuLib Setup
    LCDML.MENU_enRollover();			// Enable Menü Rollover

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 20000); // set to 20 secounds 
    //LCDML.SCREEN_disable();

    // Some needfull methods 
    
    // You can jump to a menu function from anywhere with 
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name 

	
	sprintf(tx_reg, "Login / Userverwaltung fuer LaserCutter V1.10");
	Serial.println(tx_reg);
	Serial.print('\n');
	
	menueanzeige();						// Anzeige einer Hilfe auf einem Terminalprogramm
	startseite();						// Ausgabe der Startseite auf 128x64 Grafikdisplay
	
	max_user = EEPROM.read(0);
	// max_user = 222;
	if(max_user > 200){
		EEPROM.update(0, 10);			// Speichere "max_user" an Speicherstelle 0 in EEPROM		
		
		max_user = EEPROM.read(0);		// Zurücklesen "max_user" aus EEPROM
		
		for(int i = 1; i <= max_user; i++){
			int adress = (startadress_user * i) + offset_timer;
			int timer = 10 * i;
			eepromWriteInt(true, adress, timer);
		}
	}
	
	
	
	max_user = EEPROM.read(0);			// Value aus Speicherstelle 0 (max_user) in Variable abspeichern
	
	sprintf(tx_reg, "max user aus EEPROM ausgelesen: %d", max_user);    			
	Serial.println(tx_reg);

	MySaveString = "Gastkonto";
	StringToEEPROM(true, startadress_user, MySaveString);
	
	MySaveString = "Gaun Richy";
	StringToEEPROM(true, startadress_user*2, MySaveString);

	MySaveString = "Gruber Manuel";
	StringToEEPROM(true, startadress_user*3, MySaveString);

	MySaveString = "Prada Tom";
	StringToEEPROM(true, startadress_user*4, MySaveString);

	MySaveString = "Astner Andrae";
	StringToEEPROM(true, startadress_user*5, MySaveString);

	MySaveString = "W. Alexander";
	StringToEEPROM(true, startadress_user*6, MySaveString);
	
	MySaveString = "Breitenl. Georg";
	StringToEEPROM(true, startadress_user*7, MySaveString);

	MySaveString = "Brugger Michael";
	StringToEEPROM(true, startadress_user*8, MySaveString);

	MySaveString = "Tischler Julius";
	StringToEEPROM(true, startadress_user*9, MySaveString);

	MySaveString = "Muster Max";
	StringToEEPROM(true, startadress_user*10, MySaveString);
	
	serialData = StringFromEEPROM(startadress_user);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*2);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*3);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*4);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*5);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*6);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*7);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*8);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*9);
	Serial.print(serialData);
	serialData = StringFromEEPROM(startadress_user*10);
	Serial.print(serialData);
	

	sprintf(tx_reg, "Betriebszeiten der User anzeigen:");
	Serial.println(tx_reg);
	for(int i = 1; i <= max_user; i++){
		int adress = (startadress_user * i) + offset_timer;
		Serial.println(eepromReadInt(adress));
	}

	sprintf(tx_reg, "Standbyzeiten der User anzeigen:");
	Serial.println(tx_reg);	
	for(int i = 1; i <= max_user; i++){
		int adress = (startadress_user * i) + offset_standby;
		Serial.println(eepromReadInt(adress));
	}
	
	sprintf(tx_reg, "PIN der User anzeigen:");
	Serial.println(tx_reg);
	for(int i = 1; i <= max_user; i++){
		int adress = (startadress_user * i) + offset_PIN;
		Serial.println(eepromReadInt(adress));
	}
 
	watchdog_init();
	

	
}

void loop(void) {

    LCDML.loop(); 						// Menüabarbeitung --> muss zyklisch aufgerufen werden

	read_seriell();						// Einlesen der Zeichen über UART und Reaktion auf die Eingabe									

	if(page_useranzeige){
	  start_lasercutter = false;
	  useranzeige_128x64();				// Useranzeige auf dem Grafikdisplay 128x64-
	}
	else if(page_login){
	  start_lasercutter = false;	
	  page_useranzeige = false;
	  login();							// Useranzeige auf dem Grafikdisplay 128x64-
	}
	else if(page_change_pw){
		start_lasercutter = false;	
		page_useranzeige = false;
		change_pw();
	}


	currentMillis = millis();			
	if (currentMillis - previousMillis >= interval) {		// Intervall = 1 Sekunde
		previousMillis = currentMillis;
		
		ledState = ledState^1;
		digitalWrite(ledPin, ledState);
		
	
		if(start_lasercutter){
		  page_useranzeige = false;
			update_betriebstimer();			
		}

	}  

	watchdog_reset();
	
}	// END loop(void)

// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib2.h
# endif

# if(_LCDML_glcd_tft_box_x1 > _LCDML_glcd_tft_w)
# error _LCDML_glcd_tft_box_x1 is to big
# endif

# if(_LCDML_glcd_tft_box_y1 > _LCDML_glcd_tft_h)
# error _LCDML_glcd_tft_box_y1 is to big
# endif

