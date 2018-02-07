///////////////////////////////////////////////////////////////////////
/// Festlegung der Menüstruktur für die Bedienung des Lasercutters  ///
///////////////////////////////////////////////////////////////////////
  
  
 #include "LCDML_DISP.h"
// #include "Library_LaserCutter_V3.h"
#include "LCDML_Stat_function.h"  

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
// LCDML_0        => layer 0 
// LCDML_0_X      => layer 1 
// LCDML_0_X_X    => layer 2 
// LCDML_0_X_X_X  => layer 3 
// LCDML_0_...      => layer ...   

// LCDMenuLib_add	(id, prev_layer,  new_num, condition, lang_char_array		, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced	(0  , LCDML_0      	, 1  , COND_e1 	, "Useranzeige/Anwahl" 	, mFUNC_useranzeige	, 0	, 	_LCDML_TYPE_default);       
LCDML_addAdvanced   (1  , LCDML_0		, 2  , COND_e1 	, "Anzeige Laufzeiten"  , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (2  , LCDML_0		, 3  , COND_e1 	, "Ausgaenge testen"    , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (3  , LCDML_0		, 4  , COND_e1 	, "Eingaenge anzeigen"  , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (4  , LCDML_0		, 5  , COND_e2 	, "Login akt. User"     , NULL  			, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (5 	, LCDML_0		, 6  , COND_e3 	, "Freigabe Laser"		, mFUNC_FG_Cutter	, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (6  , LCDML_0_5		, 1  , COND_e2 	, "Login mit PIN" 	    , mFUNC_login 		, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (7  , LCDML_0_5		, 2  , COND_e2 	, "Passwortwechsel"     , mFUNC_change_pw	, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (8  , LCDML_0_5		, 3  , COND_e2 	, "Anzeige Userdaten"   , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (9  , LCDML_0_3		, 1  , COND_e1 	, "Absaugung HAND ein"  , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (10 , LCDML_0_3		, 2  , COND_e1 	, "Absaugung HAND aus"  , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (11 , LCDML_0_3		, 3  , COND_e1 	, "Wasserp. HAND ein"   , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (12 , LCDML_0_3		, 4  , COND_e1 	, "Wasserp. HAND aus"   , NULL 				, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (13 , LCDML_0_3		, 5  , COND_e1 	, "Ruecksprung Hauptm." , mFunc_goToRootMenu, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (14 , LCDML_0		, 7  , COND_e3 	, "Standby Lasercutter" , mFunc_back 		, 0	, 	_LCDML_TYPE_default);        		  
LCDML_addAdvanced   (15 , LCDML_0		, 8  , COND_e3 	, "Logout akt. User"    , mFUNC_logout		, 0	, 	_LCDML_TYPE_default);        		    
LCDML_addAdvanced 	(16 , LCDML_0       , 9  , COND_hide, "screensaver"        	, mFunc_screensaver	, 0	,	_LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab 
  

#define _LCDML_DISP_cnt    16  		// menu element count - last element id --> this value must be the same as the last menu element
LCDML_createMenu(_LCDML_DISP_cnt);	// create menu

