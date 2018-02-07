/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
    // loop
    // is called when it is triggert
    // - with LCDML_DISP_triggerMenu( millisecounds ) 
    // - with every button status change

    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // loop end
    // you can here reset some global vars or delete it 
  } 
}

 
 * ===================================================================== * 
 */

 
// *********************************************************************
// *********************************************************************
void mFunc_information(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    // setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "To close this");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "function press");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "any button or use");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 4), "back button");
    } while( u8g2.nextPage() );
  }

  if(LCDML.FUNC_loop()){           // ****** LOOP ********* 
   
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function   
    if(LCDML.BT_checkAny()) // check if any button is presed (enter, up, down, left, right)
    { 
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    } 
  }
  
  if(LCDML.FUNC_close()){      // ****** STABLE END ********* 
    // you can here reset some global vars or do nothing 
  } 
}  


// *********************************************************************
// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (globale variable)
void mFunc_timer_info(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP ********* 
     g_func_timer_info = 20;       // reset and set timer   
    
    char buf[20];
    sprintf (buf, "wait %d secounds", g_func_timer_info);
    
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "or press back button");
    } while( u8g2.nextPage() );
  
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds

    LCDML.TIMER_msReset(g_timer_1);  
  }

  if(LCDML.FUNC_loop()){           // ****** LOOP ********* 
   
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

     // this function is called every 100 millisecounds
    
    // this method checks every 1000 millisecounds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000)){ 
      g_timer_1 = millis();   
      g_func_timer_info--;                // increment the value every secound
      char buf[20];
      sprintf (buf, "wait %d secounds", g_func_timer_info);
      
      u8g2.setFont(_LCDML_DISP_font);
      u8g2.firstPage();  
      do {
        u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
        u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "or press back button");
      } while( u8g2.nextPage() );   
         
    }
        
    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normaly
    if (g_func_timer_info <= 0){
      // leave this function
      LCDML.FUNC_goBackToMenu();  
    } 
  } 

  if(LCDML.FUNC_close()){      // ****** STABLE END ********* 
    // you can here reset some global vars or do nothing
  }  
}


// *********************************************************************
// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
     
    // setup function
    // print lcd content
    char buf[17];
    sprintf (buf, "count: %d of 3", 0);
    
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press a or w button");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
    } while( u8g2.nextPage() );  
  
    // Reset Button Value
    g_button_value = 0; 

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();
  }
  
  if(LCDML.FUNC_loop()){           // ****** LOOP *********
  
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
    // the quit button works in every DISP function without any checks; it starts the loop_end function  
    if (LCDML.BT_checkAny()){ // check if any button is pressed (enter, up, down, left, right)
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()){ // check if button left is pressed
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;
      
        // update lcd content
        char buf[20];
        sprintf (buf, "count: %d of 3", g_button_value);
        
        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press a or w button");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
        } while( u8g2.nextPage() );        
      }    
    }
  
   // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function  
    }    
  }

  if(LCDML.FUNC_close()){     // ****** STABLE END *********
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
// *********************************************************************
void mFunc_screensaver(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
  
    // setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "screensaver");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "press any key");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "to leave it");
    } while( u8g2.nextPage() );
    
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds
  }

  if(LCDML.FUNC_loop()){           // ****** LOOP *********
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {      
      LCDML.FUNC_goBackToMenu();  // leave this function   
    }
  } 

  if(LCDML.FUNC_close()){          // ****** STABLE END *********
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}


// *********************************************************************
// *********************************************************************
void mFunc_back(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  } 
}


// *********************************************************************
// *********************************************************************
void mFunc_goToRootMenu(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    // go to root and display menu
    LCDML.MENU_goRoot();    
  } 
}


// *********************************************************************
// *********************************************************************
void mFunc_jumpTo_timer_info(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    // Jump to Initscreen
    if(!LCDML.OTHER_jumpToFunc(mFunc_timer_info)){
      // function not found or not callable
      LCDML.MENU_goRoot();           
    }
  }
}


// *********************************************************************
// *********************************************************************
void mFunc_para(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
  
    char buf[20];
    sprintf (buf, "parameter: %d", param);
    
    // setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "press any key");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "to leave it");
    } while( u8g2.nextPage() );
    
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds
  }

  if(LCDML.FUNC_loop()){               // ****** LOOP *********
  
    // For example
    switch(param){
      case 10:
        // do something
        break;

      case 20:
        // do something
        break;

      case 30:
        // do something
        break;

      default:
        // do nothing
        break;
    }

    
    if (LCDML.BT_checkAny()){ // check if any button is pressed (enter, up, down, left, right)  
      LCDML.FUNC_goBackToMenu();  // leave this function   
    }
  } 

  if(LCDML.FUNC_close()){      // ****** STABLE END *********
    // you can here reset some global vars or do nothing
  }
}



// *********************************************************************
// *********************************************************************
void mFUNC_useranzeige(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
	  anzeige_index = 1;
	  anzeige_previous = 0;
	  page_useranzeige = true;  
  }

  if(LCDML.FUNC_loop()){               // ****** LOOP *********
    LCDML.SCREEN_resetTimer();			// reset screensaver timer
	if(LCDML.BT_checkAny()){
		if(LCDML.BT_checkUp()){
			menue_inc = true;
		}
		else if(LCDML.BT_checkDown()){
			menue_dec = true;
		}
		else if(LCDML.BT_checkEnter()){
			page_useranzeige = false;
			LCDML.FUNC_goBackToMenu();
			// LCDML.FUNC_goBackToMenu();
		}
		LCDML.BT_resetAll();
	}
  } 

  if(LCDML.FUNC_close()){      // ****** STABLE END *********
    // you can here reset some global vars or do nothing
	menue_E1 = false;
	menue_E2 = true;
	menue_E3 = false;
  }
}



// *********************************************************************
// **************** Menüpunkt zum Starten des LaserCutters *************
// *********************************************************************
void mFUNC_FG_Cutter(uint8_t param){
	
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
	anzeige_index = 1;
	anzeige_previous = 0;
	page_useranzeige = false;
	start_lasercutter = true;
	betriebstimer = eepromReadInt((startadress_user * current_user) + offset_timer);
	laser_stunden = betriebstimer / 3600;
	betriebstimer = betriebstimer % 3600;	// Rest der Division durch 3600
	laser_minuten = betriebstimer / 60;
	betriebstimer = betriebstimer % 60;		// Rest der Division durch 60
	laser_sekunden = betriebstimer;
	
	standbytimer = eepromReadInt((startadress_user * current_user) + offset_standby);
	standby_stunden = standbytimer / 3600;
	standbytimer = standbytimer % 3600;		// Rest der Division durch 3600
	standby_minuten = standbytimer / 60;
	standbytimer = standbytimer % 60;		// Rest der Division durch 60
	standby_sekunden = standbytimer;
  }	
  // setup function

	if(LCDML.FUNC_loop()){               // ****** LOOP *********
		LCDML.SCREEN_resetTimer();			// reset screensaver timer		
		if(LCDML.BT_checkAny()){
			if(LCDML.BT_checkUp()){
				menue_inc = true;
			}
			else if(LCDML.BT_checkDown()){
				menue_dec = true;
			}
			else if(LCDML.BT_checkEnter()){
				page_useranzeige = false;
				LCDML.FUNC_goBackToMenu();
			}
			
			LCDML.BT_resetAll();
			user_select();
		}	
	}


	if(LCDML.FUNC_close()){      // ****** STABLE END *********
		start_lasercutter = false;
		save_betriebstimer(laser_sekunden, laser_minuten, laser_stunden);
		save_standbytimer(standby_sekunden, standby_minuten, standby_stunden);
		LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
	}
}


  
// *********************************************************************
// ******************* Menüpunkt Login aktueller User ******************
// *********************************************************************
void mFUNC_login(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
	  page_login = true;
	  pin_index = 0;
	  pineingabe = 0;
	  previous_pin = 1;
	  calc_pin = 0;
	  logged_in = false;
	  user_pin = eepromReadInt((startadress_user * current_user) + offset_PIN);
	  
	  if(user_pin > 65000){				// PIN noch nicht vergeben --> 0xFFFF in EEProm
		user_pin = 0;
	  }  
  }

  if(LCDML.FUNC_loop()){               // ****** LOOP *********
	if(LCDML.BT_checkAny()){
		if(LCDML.BT_checkUp()){
			pineingabe ++;
			if(pineingabe > 9){
				pineingabe = 0;
			}
		}
		else if(LCDML.BT_checkDown()){
			pineingabe --;
			if(pineingabe < 0){
				pineingabe = 9;
			}
		}
		else if(LCDML.BT_checkEnter()){
			pin_index ++;
			switch(pin_index){
				case 1:
					calc_pin = pineingabe * 1000;				// 1000-er Stelle des Pin
				break;
				case 2:
					calc_pin = calc_pin + (pineingabe * 100);	// 100-er Stelle des Pin
				break;
				case 3:
					calc_pin = calc_pin + (pineingabe * 10);	// 10-er Stelle des Pin
				break;
				case 4:
					calc_pin = calc_pin + pineingabe;			// 1-er Stelle des Pin
				break;
			}
			previous_pin = 10;
			if(pin_index > 4 && logged_in){						
				page_login = false;
				LCDML.FUNC_goBackToMenu(1);  					// bei erfolgreichen Login --> einen Layer im Menü zurück    				
			}
		}
		LCDML.BT_resetAll();
	}
  } 

  if(LCDML.FUNC_close()){      // ****** STABLE END *********
	menue_E1 = false;
	menue_E2 = false ;
	menue_E3 = true ;
  }
}

// *********************************************************************
// ******************* Menüpunkt Login aktueller User ******************
// *********************************************************************
void mFUNC_change_pw(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
	  page_change_pw = true;
	  pin_index = 0;
	  pineingabe = 0;
	  previous_pin = 1;
	  calc_pin = 0;
	  logged_in = false;
	  changed_pin_1 = 0;
	  changed_pin_2 = 0;
	  pin1_ready = false;
	  pin2_ready = false;
	  me_pin1_ready = false;
	  me_pin2_ready = false;
	  user_pin = eepromReadInt((startadress_user * current_user) + offset_PIN);
	  
	  if(user_pin > 65000){				// PIN noch nicht vergeben --> 0xFFFF in EEProm
		user_pin = 0;
	  }  
  }

  if(LCDML.FUNC_loop()){               // ****** LOOP *********
	if(LCDML.BT_checkAny()){
		if(LCDML.BT_checkUp()){
			pineingabe ++;
			if(pineingabe > 9){
				pineingabe = 0;
			}
		}
		else if(LCDML.BT_checkDown()){
			pineingabe --;
			if(pineingabe < 0){
				pineingabe = 9;
			}
		}
		else if(LCDML.BT_checkEnter()){
			pin_index ++;
			
			
			sprintf(tx_reg, "pin_index: %d ",pin_index);    
			Serial.println(tx_reg);
			
			
			switch(pin_index){
				case 1:
					calc_pin = pineingabe * 1000;				// 1000-er Stelle des Pin
				break;
				case 2:
					calc_pin = calc_pin + (pineingabe * 100);	// 100-er Stelle des Pin
				break;
				case 3:
					calc_pin = calc_pin + (pineingabe * 10);	// 10-er Stelle des Pin
				break;
				case 4:
					calc_pin = calc_pin + pineingabe;			// 1-er Stelle des Pin
					
					if(!pin1_ready){							// 1. Eingabe des neuen PIN noch nicht gespeichert
						pin1_ready = true;
						changed_pin_1 = calc_pin;
						sprintf(tx_reg, "PIN1: %d ",changed_pin_1);    
						Serial.println(tx_reg);
					}
					else{
						changed_pin_2 = calc_pin;
						sprintf(tx_reg, "PIN2: %d ",changed_pin_2);    
						Serial.println(tx_reg);
						if(changed_pin_1 == changed_pin_2){		// Vergleich der beiden Eingaben
							pin2_ready = true;	
							sprintf(tx_reg, "PIN geaendert");    
							Serial.println(tx_reg);
							//eepromWriteInt(true, (startadress_user * current_user) + offset_PIN, changed_pin_1);
						}
						else{
							sprintf(tx_reg, "PIN nicht korrekt, erneut eingeben");    
							Serial.println(tx_reg);
							changed_pin_1 = 0;
							changed_pin_2 = 0;
							pin1_ready = false;
							pin2_ready = false;
							me_pin1_ready = false;
							me_pin2_ready = false;
							pin_index = 0;
						}
					}
					
				break;
			}	// END switch(pin_index)
			
			previous_pin = 10;
			if(pin_index > 4 && me_pin1_ready){
				pin_index = 0;						// --> erneute PIN-Eingabe starten
			}
			if(pin_index > 4 && pin2_ready){						
				page_change_pw = false;
				LCDML.FUNC_goBackToMenu(1);  					// bei erfolgreichen Login --> einen Layer im Menü zurück    				
			}
		}
		LCDML.BT_resetAll();
	}
  } 

  if(LCDML.FUNC_close()){      // ****** STABLE END *********
	menue_E1 = false;
	menue_E2 = false ;
	menue_E3 = true ;
  }
}


// *********************************************************************
// ******************* Menüpunkt Logout aktueller User *****************
// *********************************************************************
void mFUNC_logout(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
  }

  if(LCDML.FUNC_loop()){               // ****** LOOP *********
	if(LCDML.BT_checkAny()){
		if(LCDML.BT_checkUp()){
			menue_inc = true;
		}
		else if(LCDML.BT_checkDown()){
			menue_dec = true;
		}
		else if(LCDML.BT_checkEnter()){
			page_useranzeige = false;
			LCDML.FUNC_goBackToMenu();
			// LCDML_DISP_funcend();      // LCDML_DISP_funcend calls the loop_end function
			sprintf(tx_reg, "Logout in loop");     
			Serial.println(tx_reg);
		}
		
		LCDML.BT_resetAll();
	}  
  } 

  if(LCDML.FUNC_close()){      // ****** STABLE END *********
	sprintf(tx_reg, "Logout in end");     
	Serial.println(tx_reg);
	menue_E1 = true;
	menue_E2 = false ;
	menue_E3 = false ;
	LCDML.MENU_goRoot();
  }	
}


// *********************************************************************
// *********************************************************************
void mFunc_goRoot(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    // go to root and display menu
    LCDML.MENU_goRoot();    
  } 
}

// *********************************************************************
// *********************************************************************
void mFunc_jumpToFunc(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    // Jump to Initscreen
    if(!LCDML.OTHER_jumpToFunc(mFunc_p2)){ // menu function allowed
    
      // function not found or not callable
      LCDML.MENU_goRoot();           
    }
  }
}


// *********************************************************************
// *********************************************************************
void mFunc_test_hidden(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
    Serial.println("hidden menu");
  }

  if(LCDML.FUNC_loop()){           // ****** LOOP ********* 
    //
  }

  if(LCDML.FUNC_close()){      // ****** STABLE END *********
  
  }
}


// *********************************************************************
// *********************************************************************
void mFunc_test_complex(uint8_t param){
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
  
    if(param == 10){
      g_condetion_test_allowed = false;
    }
    else{
      g_condetion_test_allowed = true;
    }
    LCDML.FUNC_goBackToMenu(); 
  } 
}










/* ===================================================================== *
 *                                                                       *
 * Conditions to show or hide a menu element on the display              *
 *                                                                       *
 * ===================================================================== *
 */



// *********************************************************************
// ***************** hide a menu element ******************************* 
boolean COND_hide(){ 
  return false;  // hidden
} 


// *********************************************************************
// ********************  hide a menu element  ************************** 
boolean COND_a1(){ 
  if(g_condetion_test_allowed == false){
    return true;
  }
  else{
    return false;  // hidden
  }
} 

// *********************************************************************
// ********************  hide a menu element  ************************** 
boolean COND_a2(){ 
  if(g_condetion_test_allowed == true){
    return true;
  }
  else{
    return false;  // hidden
  }
} 

// *********************************************************************
// ******************  show / hide Menüebene 1 ************************* 
// *********************************************************************
boolean COND_e1(){ 
  if(menue_E1 == true){
    return true;
  }
  else{
    return false;  // hidden
  }
} 

// *********************************************************************
// ******************  show / hide Menüebene 2 ************************* 
// *********************************************************************
boolean COND_e2(){ 
  if(menue_E2 == true){
    return true;
  }
  else{
    return false;  // hidden
  }
} 

// *********************************************************************
// ******************  show / hide Menüebene 3 ************************* 
// *********************************************************************
boolean COND_e3(){ 
  if(menue_E3 == true){
    return true;
  }
  else{
    return false;  // hidden
  }
} 

