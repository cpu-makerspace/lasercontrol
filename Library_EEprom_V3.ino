///////////////////////////////////////////////////////////////////////
//////////// Funktion zum Schreiben von Strings in das EEPROM /////////
///////////////////////////////////////////////////////////////////////
void StringToEEPROM(bool update, int adress, String ToWrite){
    byte Stringlaenge = ToWrite.length();
	byte b = 0;
//    Serial.println(Stringlaenge);
	
    for (b = 0; b < Stringlaenge; b++){
		
		if(update){
			EEPROM.update(adress + b,ToWrite.charAt(b));
//			Serial.println("update EEPROM schreiben...");
		} 
		else{
			EEPROM.write(adress + b,ToWrite.charAt(b));
			// Serial.println("write EEPROM schreiben...");
		}		
    }
	EEPROM.update(adress + b,'\n');
    // Serial.println("EEPROM schreiben abgeschlossen...");
}

///////////////////////////////////////////////////////////////////////
////////////// Funktion zum Lesen von Strings aus dem EEPROM //////////
///////////////////////////////////////////////////////////////////////
String StringFromEEPROM(int readposition){
    // Serial.println("EINLESEN AB HIER!!!");
    String ToRead = "";
	char f = 0;
	int b = readposition;
	
	do{
		f = EEPROM.read(b);
        ToRead += (f);
		b++;
	 }while(f != '\n');
    // Serial.println("EEPROM einlesen abgeschlossen...");
    return ToRead;
}


///////////////////////////////////////////////////////////////////////
/////// Funktion zum Lesen eines Integerwertes aus dem EEPROM /////////
///////////////////////////////////////////////////////////////////////
int eepromReadInt(int readposition){
	
    byte high = EEPROM.read(readposition);
	byte low = EEPROM.read(readposition + 1);
	// int value = word(high,low);
	
	int value = low + ((high << 8)&0xFF00);

    return value;
}

///////////////////////////////////////////////////////////////////////
///// Funktion zum Schreiben eines Integerwertes in das EEPROM ////////
///////////////////////////////////////////////////////////////////////
void eepromWriteInt(bool update, int adress, int ToWrite){
	
	byte high = ToWrite >> 8; 
	byte low = ToWrite;
		
	if(update){
		EEPROM.update(adress,high);
		EEPROM.update(adress + 1,low);			
	} 
	else{
		EEPROM.write(adress,high);
		EEPROM.write(adress + 1,low);			
	}		
}
	
