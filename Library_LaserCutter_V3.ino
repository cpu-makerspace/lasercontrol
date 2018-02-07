///////////////////////////////////////////////////////////////////////
//////////// Funktion zur Ansteuerung des Piezzo-Piepsers  ////////////
///////////////////////////////////////////////////////////////////////
	void piezzo(){
		piezzo_state = piezzo_state^1;
		if(sound){
			sound --;
			digitalWrite(BEEPER_PIN, piezzo_state);
		}
		else {
			sound = 0;
			digitalWrite(BEEPER_PIN, LOW);
		}
	}	// END void piezzo()

	
///////////////////////////////////////////////////////////////////////
///// Funktion zur Anzeige einer Hilfe auf einem Terminalprogramm  ////
///////////////////////////////////////////////////////////////////////
	void menueanzeige(){
		sprintf(tx_reg, "Menueanzeige LaserCutter V1.1");     
		Serial.println(tx_reg);
		sprintf(tx_reg, "============================"); 
		Serial.println(tx_reg);   
		Serial.print('\n'); 
		sprintf(tx_reg, "m .... Aufruf der (M)enueanzeige");     
		Serial.println(tx_reg);
		sprintf(tx_reg, "r .... Anzeigen der (r)egistrierten Users");     
		Serial.println(tx_reg);
		sprintf(tx_reg, "a .... Anlegen eines neuen Users --> (a)dd User");     
		Serial.println(tx_reg);
		sprintf(tx_reg, "w .... An(w)ahl des zu bearbeitenden Users");     
		Serial.println(tx_reg);
		sprintf(tx_reg, "s .... (s)tart Lasercutter");     
		Serial.println(tx_reg);		
		sprintf(tx_reg, "q .... (q)uitt und zurueck zum Menue");     
		Serial.println(tx_reg);		
		Serial.print('\n'); 	
		
		
		
	}	// END void menueanzeige()

	
///////////////////////////////////////////////////////////////////////
///////// Funktion Anzeige der Betriebsdauer des LaserCutter  /////////
///////////////////////////////////////////////////////////////////////
	void update_betriebstimer(){

		LCDML.SCREEN_resetTimer();				// reset Timer für screensaver
		
		if(!digitalRead(laser_activ)){			// Eingang "Laser aktiv" = aktiv_low
			laser_sekunden ++;					// Timer für Betrieb des Lasercutters
			if(laser_sekunden > 59){
				laser_sekunden = 0;
				laser_minuten ++;
				save_betriebstimer(laser_sekunden, laser_minuten, laser_stunden);
			}
			if(laser_minuten > 59){
				laser_minuten = 0;
				laser_stunden ++;
			}
		}
		else{
			standby_sekunden ++;				// Timer für Standby des Lasercutters
			if(standby_sekunden > 59){
				standby_sekunden = 0;
				standby_minuten ++;
				save_betriebstimer(standby_sekunden, standby_minuten, standby_stunden);
			}
			if(standby_minuten > 59){
				standby_minuten = 0;
				standby_stunden ++;
			}
			
		}
		
		u8g2.firstPage();
		do {
			String user = "";
			u8g2.setFont(u8g2_font_ncenB10_tr);
			u8g2.setCursor(2, 12);
			u8g2.print("LaserCutter V1.1");     

			u8g2.setFont(u8g2_font_helvR08_tf); 
			u8g2.drawStr(0,24,"User: ");    

			user = StringFromEEPROM(current_user * startadress_user);
			sprintf(tx_reg, user.c_str());    
			u8g2.drawStr(30,24,tx_reg);
			
			u8g2.setFont(u8g2_font_helvR08_tf); 
			u8g2.drawStr(0,36,"Betriebszeit: ");   
			sprintf(tx_reg, "%02d:%02d:%02d",laser_stunden, laser_minuten, laser_sekunden);     
			u8g2.drawStr(75,36,tx_reg);   
			
			u8g2.setFont(u8g2_font_helvR08_tf); 
			u8g2.drawStr(0,48,"Standbyzeit: ");   
			sprintf(tx_reg, "%02d:%02d:%02d",standby_stunden, standby_minuten, standby_sekunden);     
			u8g2.drawStr(75,48,tx_reg);			

			u8g2.setFont(u8g2_font_helvB08_tf); 
			u8g2.drawStr(0,62,"Verrechnung: 1Euro / Min."); 
			// u8g2.drawStr(0,62,"Beenden mit Taste *"); 
		} while ( u8g2.nextPage() );      
	} // END void update_betriebstimer()
		
///////////////////////////////////////////////////////////////////////
//////// Funktion speichern der Betriebsdauer des LaserCutter  ////////
///////////////////////////////////////////////////////////////////////
	void save_betriebstimer(byte sek, byte  min, byte std){

		int betriebszeit = std * 3600 + min*60 + sek;	  
		eepromWriteInt(true, (startadress_user * current_user) + offset_timer, betriebszeit);	
	} // END void save_betriebstimer(byte sek, byte  min, byte std)	

///////////////////////////////////////////////////////////////////////
//////// Funktion speichern der Betriebsdauer des LaserCutter  ////////
///////////////////////////////////////////////////////////////////////
	void save_standbytimer(byte sek, byte  min, byte std){

		int standbyzeit = std * 3600 + min*60 + sek;	  
		eepromWriteInt(true, (startadress_user * current_user) + offset_standby, standbyzeit);	
	} // END void save_standbytimer(byte sek, byte  min, byte std)	
	
///////////////////////////////////////////////////////////////////////
/////// Funktion Ausgabe der Startseite auf dem Grafikdisplay  ////////
///////////////////////////////////////////////////////////////////////
	void startseite(){
		u8g2.firstPage();
		do {
			u8g2.setFont(u8g2_font_ncenB10_tr);
			u8g2.setCursor(2, 12);
			u8g2.print("LaserCutter V1.1");     

			u8g2.setFont(u8g2_font_helvR08_tf); 
			u8g2.drawStr(5,24,"Userauswahl ueber");    
			u8g2.drawStr(5,34,"Tastenfeld durch Eingabe");    
			u8g2.drawStr(5,44,"des persoenlichen Pin");    
			u8g2.drawStr(5,54,"---------------------------");    
			u8g2.drawStr(5,64,"danach Start mit Taster #");    
		} while ( u8g2.nextPage() );      
  
  } // END void startseite()

///////////////////////////////////////////////////////////////////////
//////// Funktion zur Anzeige der User auf dem Grafikdisplay  /////////
///////////////////////////////////////////////////////////////////////
	void useranzeige_128x64(){
		
		byte usernummer;
		String user = "";
		
		if(anzeige_previous != anzeige_index){		// Displayupdate nur bei einer Änderung
			anzeige_previous = anzeige_index;	
			
			current_user = anzeige_index;			// Current User für weitere Verwendung
			
			u8g2.firstPage();
			do {
				
				if(anzeige_index >= max_user){
					usernummer = max_user-2;
					u8g2.drawStr( 1, 59,  _LCDML_DISP_cursor_char);	// set cursor in Zeile 3					
				}			
				else if(anzeige_index+1 >= max_user){
					usernummer = max_user-2;
					u8g2.drawStr( 1, 46,  _LCDML_DISP_cursor_char);	// set cursor in Zeile 2
				}			
				else{
					usernummer = anzeige_index;
					u8g2.drawStr( 1, 33,  _LCDML_DISP_cursor_char);	// set cursor in Zeile 1
				}
				
				// drow a box around the menu
				u8g2.drawFrame(_LCDML_DISP_box_x0, _LCDML_DISP_box_y0, (_LCDML_DISP_box_x1-_LCDML_DISP_box_x0), (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0));
					
				u8g2.setFont(u8g2_font_ncenB10_tr);
				u8g2.setCursor(5, 13);
				u8g2.print("Userwahl:");  

				u8g2.setFont(u8g2_font_helvR08_tf);
				sprintf(tx_reg, "%d User",max_user);
				u8g2.drawStr(86,13,tx_reg);
				
				u8g2.drawStr(0,22,"--------------------------------"); 

				// Ausgabe des Users in der 1. Zeile
				sprintf(tx_reg, "User %02d:",usernummer);
				u8g2.drawStr(7,33,tx_reg); 
				user = StringFromEEPROM(startadress_user * usernummer);
				sprintf(tx_reg, user.c_str());    
				u8g2.drawStr(50,33,tx_reg);

				// Ausgabe des Users in der 2. Zeile
				sprintf(tx_reg, "User %02d:",usernummer+1);
				u8g2.drawStr(7,46,tx_reg);  
				user = StringFromEEPROM(startadress_user * (usernummer + 1));
				sprintf(tx_reg, user.c_str());    			
				u8g2.drawStr(50,46,tx_reg);

				// Ausgabe des Users in der 3. Zeile
				sprintf(tx_reg, "User %02d:",usernummer+2);
				u8g2.drawStr(7,59,tx_reg);    
				user = StringFromEEPROM(startadress_user * (usernummer + 2));
				sprintf(tx_reg, user.c_str());    						
				u8g2.drawStr(50,59,tx_reg);
		
			} while ( u8g2.nextPage() );    	
		}
	}	// END void useranzeige()

///////////////////////////////////////////////////////////////////////
//////// Funktion zur Userverwaltung ueber ein Terminalprogramm  //////
///////////////////////////////////////////////////////////////////////
	void userverwaltung(){
		Serial.print('\n');
		sprintf(tx_reg, "Hinzufügen eines Users Ueber das Terminalprogramm");     
		Serial.print(tx_reg);
		Serial.print('\n');
		sprintf(tx_reg, "==============="); 	
	}	
		
///////////////////////////////////////////////////////////////////////
//////////////// Funktion zum Einlesen der Zeichen über UART  /////////
///////////////////////////////////////////////////////////////////////
	void read_seriell(){
		
		while ((Serial.available() > 0) || menue_inc || menue_dec){
		// while ((Serial.available() > 0)){
			int inChar = Serial.read();
			max_user = EEPROM.read(0);					// Value aus Speicherstelle 0 (max_user) in Variable abspeichern

			if(!page_add_user){
				
				if(inChar == 's'){
					start_lasercutter = true;
					page_useranzeige = false;	
					interval = 1000;
				}
				else if(inChar == 'a'){						// ADD User
					page_useranzeige = false;
					start_lasercutter = false;
					serialData = "";
					userindex = 0;
					interval = 500;		
					add_user();
					anzeige_index = 1;							
				}
				else if(inChar == 'r'){						// Anzeigen der (r)egistrierten Users
					page_useranzeige = true;
					start_lasercutter = false;
					page_add_user = false;
					interval = 500;		
					anzeige_index = 1;							
				}
				else if(inChar == 'q'){						// Quitt und Rücksprung zum Menü
					page_useranzeige = false;
					start_lasercutter = false;
					page_add_user = false;							
				}

				else if(inChar == 'm'){
					menueanzeige();
				}
				else if((inChar == '+') || menue_inc){
					menue_inc = false;
					if(user_nr < max_user){
						user_nr ++;
					}
					anzeige_index ++;
					if(anzeige_index-1 >= max_user){
						anzeige_index = 1;
					}
					
					Serial.println("Taste + gedrueckt");
				}
				else if((inChar == '-') || menue_dec){
					menue_dec = false;
					if(user_nr > 0){
						user_nr --;  
					}
					anzeige_index --;
					if(anzeige_index < 1){
						anzeige_index = max_user;
					}
					Serial.println("Taste - gedrueckt");					
				}
			}
			else if(page_add_user){
				
				menue_inc = false;
				menue_dec = false;
				
				
				
				
				serialData += (char)inChar;
				userindex ++;
				if(userindex > 15){
					sprintf(tx_reg, "Achtung: max. 15 Stellen eingeben");
					Serial.print(tx_reg);
					serialData = "";
					userindex = 0;
				}
				else if ((userindex > 3) && (inChar == '\n')){
					sprintf(tx_reg, "Ein Neuer User: ");
					Serial.print(tx_reg);
					Serial.println(serialData);
					Serial.print('\n');
					max_user ++;
					userindex = 0;
					EEPROM.update(0, max_user);					// Speichere "max_user" an Speicherstelle 0 in EEPROM
					StringToEEPROM(true, startadress_user * max_user, serialData);
					page_add_user = false;
					menueanzeige();
				}		
			}
		}    
	} // END void read_seriell()

///////////////////////////////////////////////////////////////////////
// Funktion zum Hinzufügen eines neuen Users über das Terminalprogramm 
///////////////////////////////////////////////////////////////////////
	void add_user(){
		sprintf(tx_reg, "Hinzufuegen eines neuen Users");     
		Serial.println(tx_reg);
		// sprintf(tx_reg, "============================"); 
		// Serial.println(tx_reg);   
		 Serial.print('\n'); 
		 sprintf(tx_reg, "Eingabe des Usernamen: mindesten 3 Zeichen und max 15 Zeichen");     
		 Serial.println(tx_reg);
		 Serial.print('\n'); 	
		// sprintf(tx_reg, "Neuer User: ");     
		// Serial.println(tx_reg);
		// Serial.print('\n'); 
		 page_add_user = true;		
		
	}	// END void add_user()
			
///////////////////////////////////////////////////////////////////////
////////// Funktion zur Initialisierung des Grafikdisplays 128x64  ////
///////////////////////////////////////////////////////////////////////
	void init_grafic_128x64(){									

	/*
	Arduino Nano			Grafikdisplay
		+5V						2 (+5V)
		Gnd						1 (Gnd)
		D10						4 (RS --> Data/Instruction)	
		D11	(MOSI)				5 (R/W --> Read/Write)
		D13	(SCK)				6 (E --> Enable)
								15(PSB --> H = parallel Mode, L = seriell Mode) --> auf Gnd
								19 --> +5V (Backlight)
								20 --> Gnd (Backlight)
								

	*/

	// U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);	// original

	//	U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, /* CS=*/ 16, /* reset=*/ 8); // Mega 2560

	//  U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);  // von Astner A. am 30.07.2017 eingefügt
		U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 23, /* data=*/ 17, /* CS=*/ 16, /* reset=*/ 8);	
	}

///////////////////////////////////////////////////////////////////////
///////// Funktion zur Initialisierung für den Drehimpulsgeber  ///////
///////////////////////////////////////////////////////////////////////	
	void init_T1_interrupt(){										
		Timer1.initialize(1000);
		Timer1.attachInterrupt(timerIsr); 
		// last = -1;	
	}							
	
///////////////////////////////////////////////////////////////////////
////////// Funktion zur USER-Auswahl über die Encodertasten ///////////
///////////////////////////////////////////////////////////////////////
	void user_select(){
		if(menue_inc){
			menue_inc = false;
			anzeige_index ++;
			if(anzeige_index-1 >= max_user){
				anzeige_index = 1;
			}			
			Serial.println("Taste + gedrueckt");
		}
		else if(menue_dec){
			menue_dec = false;
			anzeige_index --;
			if(anzeige_index < 1){
				anzeige_index = max_user;
			}
			Serial.println("Taste - gedrueckt");					
		}
	}
	
///////////////////////////////////////////////////////////////////////
//////// Funktion Login mittel persönlichen PIN (4-stellig) ///////////
///////////////////////////////////////////////////////////////////////	
	void login(){
				
		String user = "";
		
		if(previous_pin != pineingabe){		// Displayupdate nur bei einer Änderung
			previous_pin = pineingabe;	
			
			u8g2.firstPage();
			do {
				// drow a box around the menu
				u8g2.drawFrame(_LCDML_DISP_box_x0, _LCDML_DISP_box_y0, (_LCDML_DISP_box_x1-_LCDML_DISP_box_x0), (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0));
					
				u8g2.setFont(u8g2_font_helvR08_tf);
				u8g2.setCursor(10, 13);
				u8g2.print("Eingabe 4-stelliger PIN");  

				sprintf(tx_reg, "User %02d:",current_user);
				u8g2.drawStr(10,26,tx_reg);  
				user = StringFromEEPROM(startadress_user * (current_user));
				sprintf(tx_reg, user.c_str());    			
				u8g2.drawStr(52,26,tx_reg);
				
				u8g2.drawStr(0,33,"--------------------------------"); 		
				
				switch(pin_index){
						case 0:										// PIN Stelle 1
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(40,50,tx_reg);					
						break;
						case 1:										// PIN Stelle 2
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(50,50,tx_reg);					
						break;
						case 2:										// PIN Stelle 3
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(60,50,tx_reg);					
						break;
						case 3:										// PIN Stelle 4
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(70,50,tx_reg);					
						break;
						case 4:										// Abschluss PIN-Eingabe
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							if(user_pin == calc_pin){
								u8g2.setFont(u8g2_font_helvR08_tf);						
								sprintf(tx_reg, "PIN korrekt!");
								u8g2.drawStr(35,59,tx_reg);	
								logged_in = true;
							}
							else{								
								u8g2.setFont(u8g2_font_helvR08_tf);						
								sprintf(tx_reg, "PIN nicht korrekt!");
								u8g2.drawStr(30,59,tx_reg);		
								logged_in = false;
							}
						break;
						case 5:
							if(!logged_in){
								pin_index = 0;						// --> erneute PIN-Eingabe starten
							}
							else{
								pin_index ++;						// --> PIN-Eingabe beenden
							}
						break;
					}
				
			} while ( u8g2.nextPage() );   

		//eepromWriteInt(true, (startadress_user * current_user) + offset_PIN, user_pin);								




			
		}
	}	// END void login()
									 	
	
///////////////////////////////////////////////////////////////////////
//////////// Funktion Passwortwechsel des PIN (4-stellig) /////////////
///////////////////////////////////////////////////////////////////////	
	void change_pw(){
				
		String user = "";
		
		if(previous_pin != pineingabe){		// Displayupdate nur bei einer Änderung
			previous_pin = pineingabe;	



			sprintf(tx_reg, "wert hat sich geaendert");    
			Serial.println(tx_reg);


			
			u8g2.firstPage();
			do {
				// drow a box around the menu
				u8g2.drawFrame(_LCDML_DISP_box_x0, _LCDML_DISP_box_y0, (_LCDML_DISP_box_x1-_LCDML_DISP_box_x0), (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0));
					
				u8g2.setFont(u8g2_font_helvR08_tf);
				u8g2.setCursor(10, 13);
				u8g2.print("Initiale Vergabe des PIN");  

				sprintf(tx_reg, "User %02d:",current_user);
				u8g2.drawStr(10,26,tx_reg);  
				user = StringFromEEPROM(startadress_user * (current_user));
				sprintf(tx_reg, user.c_str());    			
				u8g2.drawStr(52,26,tx_reg);
				
				u8g2.drawStr(0,33,"--------------------------------"); 		
				
				switch(pin_index){
						case 0:										// PIN Stelle 1
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(40,50,tx_reg);					
						break;
						case 1:										// PIN Stelle 2
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(50,50,tx_reg);					
						break;
						case 2:										// PIN Stelle 3
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(60,50,tx_reg);					
						break;
						case 3:										// PIN Stelle 4
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							
							u8g2.setFont(u8g2_font_ncenB10_tr);						
							sprintf(tx_reg, "%d",pineingabe);
							u8g2.drawStr(70,50,tx_reg);					
						break;
						case 4:										// Abschluss PIN-Eingabe
							u8g2.setCursor(40, 50);
							u8g2.print("*");
							u8g2.setCursor(50, 50);
							u8g2.print("*");
							u8g2.setCursor(60, 50);
							u8g2.print("*");
							u8g2.setCursor(70, 50);
							u8g2.print("*");
							
							if(pin1_ready && !me_pin1_ready){				// neuen PIN das 1. mal eingegeben
								me_pin1_ready = true;
								u8g2.setFont(u8g2_font_helvR08_tf);						
								sprintf(tx_reg, "PIN erneut eingeben!");
								u8g2.drawStr(15,59,tx_reg);	
								
								sprintf(tx_reg, "PIN1 Grafik: %d ",changed_pin_1);    
								Serial.println(tx_reg);
							}
							else if(pin2_ready && !me_pin2_ready){			// neuen PIN korrekt das 2. mal eingegeben	
								me_pin2_ready = true;
								pin_index ++;
								u8g2.setFont(u8g2_font_helvR08_tf);						
								sprintf(tx_reg, "PIN geaendert!");
								u8g2.drawStr(30,59,tx_reg);		
								sprintf(tx_reg, "PIN2 Grafik: %d ",changed_pin_2);    
								Serial.println(tx_reg);

								}
							else{
								u8g2.setFont(u8g2_font_helvR08_tf);						
								sprintf(tx_reg, "PIN-Eingaben NOK!");
								u8g2.drawStr(15,59,tx_reg);	
								sprintf(tx_reg, "PIN Grafik nicht korrekt, erneut eingeben");    
								Serial.println(tx_reg);
							}
						break;
						case 5:
							if(!me_pin2_ready){
								pin_index = 0;						// --> erneute PIN-Eingabe starten
							}
							else{
								pin_index ++;						// --> PIN-Eingabe beenden
							}
						break;
					}
				
			} while ( u8g2.nextPage() );   

										




			
		}
	}	// END void login()
									 	
