///////////////////////// Variablendeklarationen (Global)	

//#include <ClickEncoder.h>		// Routinen für den Drehimpulsgeber

const int ledPin =  13;      // the number of the LED pin
bool ledState = LOW;             // ledState used to set the LED

bool g_condetion_test_allowed = false;
bool menue_E1 = true;
bool menue_E2 = false;
bool menue_E3 = false;


char tx_reg[50];

bool start_lasercutter =  false;
bool page_useranzeige = false;			// Anzeige auf Grafikdisplay --> Useranwahl
bool page_login = false;				// Anzeige auf Grafikdisplay --> Login mit PIN
bool page_change_pw = false;			// Anzeige auf Grafisdisplay --> Passwortwechsel
bool page_add_user = false;
bool menue_inc = false;
bool menue_dec = false;
bool piezzo_state;


//ClickEncoder::Button button_pressed;
bool me_button = false;
bool touch_button = false;


unsigned long currentMillis;
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long dauer = 0;

byte laser_sekunden = 0;
byte laser_minuten = 59;
byte laser_stunden = 9;

byte standby_sekunden = 0;
byte standby_minuten = 59;
byte standby_stunden = 9;

// byte minuten_previous = 0;
int betriebstimer;
int standbytimer;
unsigned int user_pin;
unsigned int calc_pin = 0;
byte pin_index = 0;						// Index für die Eingabe des PIN
signed int pineingabe = 0;			// Wert vom Drehimpulsgeber für die Eingabe des PIN
signed int previous_pin = 0;
int changed_pin_1 = 0;
int changed_pin_2 = 0;
bool logged_in = false;
bool pin1_ready = false;
bool me_pin1_ready = false;
bool pin2_ready = false;
bool me_pin2_ready = false;

byte user_nr = 0;
byte current_user = 0;
int anzeige_index = 0;
int anzeige_previous = 0;
int userindex = 0;
int max_user;
byte sound = 0;								// Dauer für den Piepston
//char user_string[7][15];
String inString = "";    // string to hold input
byte zeichen_nr = 0;

int startadress_user = 50;
byte offset_timer = 20;
byte offset_standby = 25;
byte offset_PIN = 30;

#define BEEPER_PIN      37				
#define BTN_EN1         31
#define BTN_EN2         33
#define BTN_ENC         35
#define SD_DETECT_PIN   49
#define KILL_PIN        41
#define blinkled		68
#define FG_laser		13
#define laser_activ		12	


String MySaveString = "";

String serialData = "";

int interval = 1000;           				// Blinkinterval (milliseconds)

//////////////////////////////////////////////////////////////////////////
////////////////////  Subroutinen  ///////////////////////////////////////

// void lcd_buzz(long duration, uint16_t freq);
void init_grafic_128x64();					// Initialisierung des Grafikdisplays 128x64
void init_T1_interrupt();					// Initialisierung für den Timer1 Interrupt
// void read_encoder();						// Einlesen des Drehimpulsgebers
void menueanzeige();						// Ausgabe eines kleinen "Menüs" über UART auf einem Terminalprogramm
void update_betriebstimer();				// Ausgabe einer der laufenden Betrieszeit des Users auf dem Grafikdisplay 128x64
void save_betriebstimer(byte sek, byte  min, byte std);		// Speichern der laufenden Betrieszeit des Users im EEPROM
void startseite();							// Ausgabe einer "Startseite" auf dem Grafikdisplay 128x64
void read_seriell();						// Einlesen der Zeichen von einem Terminalprogramm
void userverwaltung();						// Userverwaltung über Terminalprogramm (Add User)
void useranzeige_128x64();					// Useranzeige auf Grafikdisplay 128x64
void piezzo();								// Ansteuerung des Piezzo-Piepsers
void user_select();							// im Menü über Tasten des Encoders "blättern"
void login();								// Login mittel persönlichen PIN (4-stellig)
void change_pw();							// Passwortwechsel
	
