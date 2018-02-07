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

 
void mFunc_information(uint8_t param);  
void mFunc_timer_info(uint8_t param);
void mFunc_p2(uint8_t param);
void mFunc_screensaver(uint8_t param);
void mFunc_back(uint8_t param);
void mFunc_goToRootMenu(uint8_t param);
void mFunc_jumpTo_timer_info(uint8_t param);
void mFunc_para(uint8_t param);
void mFUNC_useranzeige(uint8_t param);
void mFUNC_FG_Cutter(uint8_t param);
void mFUNC_login(uint8_t param);
void mFUNC_change_pw(uint8_t param);
void mFUNC_logout(uint8_t param);
void mFunc_goRoot(uint8_t param);
void mFunc_jumpToFunc(uint8_t param);
void mFunc_test_hidden(uint8_t param);
void mFunc_test_complex(uint8_t param);

boolean COND_hide();
boolean COND_a1();
boolean COND_a2();
boolean COND_e1();
boolean COND_e2();
boolean COND_e3();