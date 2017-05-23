void Readinputs()
{
	//touch
	if (myTouch.dataAvailable() == true)
	{
		iG_Pressed_button = myButtons.checkButtons();
	}
//GESTIONE LETTURA INGRESSI ANALOGICI    
  //LETTURA TEMPERATURE    
    //temperatura del mush               
    Pt1000_Mush_real = analogRead(A0);                   //imposto la variabile all'ingresso analogico A0
	Pt1000_Sparge_real = analogRead(A2);
    total_mush -= readingsMush[indice_mush];             //Sottrae l'ultima lettura
    readingsMush[indice_mush] = Pt1000_Mush_real;        //analogRead(Pt1000_Mush_real); Legge i valori provenienti dal sensore e li salva nell'array
    total_mush += readingsMush[indice_mush];             //Aggiunge la lettura al totale
    indice_mush = (indice_mush + 1);                     //Incrementa l'indice   
	//Pt1000_Mush = total_mush / tmush_NUMREADINGS;		 //Calcola la media  così dovrei avere sempre la media sull'ultimo valore
    if (indice_mush >= tmush_NUMREADINGS)
    {
        indice_mush = 0;                                 //Alla fine dell'array resetta l'indice a 0         
        //Pt1000_Mush = total_mush / tmush_NUMREADINGS;    //Calcola la media
    }
	Pt1000_Mush = total_mush / tmush_NUMREADINGS;
	//Pt1000_Mush = total_mush >> tmush_NUMREADINGS;
    /*
	if(G_btaraturaREALE == true)
    {
        Serial.print("Pt1000_Mush_real ");
        Serial.println(Pt1000_Mush_real);
    }
    if(G_btaratura == true)
    {
        Serial.print("Pt1000_Mush ");
        Serial.println(Pt1000_Mush);                     //Stampa la media
    }
	*/
	
    //tmush=((tMushMax-tMushMin)/(AMushMax-AMushMin))*(Pt1000_Mush-AMushMax)+tMushMax;  //calcolo la retta con i valori della taratura
    /*
	if(tmush < 0)
	{
		tmush = 0;
	}
	else if(tmush>99)
	{
		tmush = 99;
	}
	*/
	//temperatura dello sparge
	/*
	Serial.print("Pt1000_Sparge ");
    Serial.println(Pt1000_Sparge_real);
		Serial.print("Pt1000_Mush ");
		Serial.println(Pt1000_Mush_real);
	*/
	//Pt1000_Sparge_real = analogRead(A2);                     //imposto la variabile all'ingresso analogico A2
    total_sparge -= readingsSparge[indice_sparge];           //Sottrae l'ultima lettura
    readingsSparge[indice_sparge] = Pt1000_Sparge_real;      //analogRead(Pt1000_Mush_real); Legge i valori provenienti dal sensore e li salva nell'array
    total_sparge += readingsSparge[indice_sparge];           //Aggiunge la lettura al totale
    indice_sparge = (indice_sparge + 1);                     //Incrementa l'indice   
    if (indice_sparge >= tsparge_NUMREADINGS)
    {
		indice_sparge = 0;                                   //Alla fine dell'array resetta l'indice a 0   
        //Pt1000_Sparge = total_sparge / tsparge_NUMREADINGS;  //Calcola la media
    }
	
	Pt1000_Sparge = total_sparge / tsparge_NUMREADINGS;  //Calcola la media
	//Pt1000_Sparge = total_sparge >> tsparge_NUMREADINGS;
    /*
	if(G_btaraturaREALE == true)
    {
        Serial.print("Pt1000_Sparge_real ");
        Serial.println(Pt1000_Sparge_real);
    }
    if(G_btaratura == true)
    {
        Serial.print("Pt1000_Sparge  ");
        Serial.println(Pt1000_Sparge); //Stampa la media
    }
	*/
	/*
	y - y1       x - x1
	------- = ---------
	y2 - y1      x2 - x1
	
	*/
	tmush=((tMushMax-tMushMin)/(AMushMax-AMushMin))*(Pt1000_Mush-AMushMax)+tMushMax;  //calcolo la retta con i valori della taratura
    tsparge=((tSpargeMax-tSpargeMin)/(ASpargeMax-ASpargeMin))*(Pt1000_Sparge-ASpargeMax)+tSpargeMax;
	if(tmush < 0)
	{
		tmush = 0;
	}
	else if(tmush>99)
	{
		tmush = 99;
	}
	if(tsparge < 0)
	{
		tsparge = 0;
	}
	else if(tsparge>99)
	{
		tsparge = 99;
	}
  //======================================================================================================
  //
  //DS18B20================
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius,celsiusCorr;
    if ( !ds.search(addr))
    {
	    Serial.println();
	    ds.reset_search();
	    delay(250);
	    return;
    }
    for( i = 0; i < 8; i++)
    {
	    Serial.write(' ');
    }
    if (OneWire::crc8(addr, 7) != addr[7]) {
	    return;
    }
    // the first ROM byte indicates which chip
    switch (addr[0]) {
	    case 0x10:
	    //Serial.println("  Chip = DS18S20");  // or old DS1820
	    type_s = 1;
	    break;
	    case 0x28:
	    //Serial.println("  Chip = DS18B20");
	    type_s = 0;
	    break;
	    case 0x22:
	    //Serial.println("  Chip = DS1822");
	    type_s = 0;
	    break;
	    default:
	    //Serial.println("Device is not a DS18x20 family device.");
	    return;
    }
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end
    present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);         // Read Scratchpad
    for ( i = 0; i < 9; i++)
    {           // we need 9 bytes
	    data[i] = ds.read();
    }

    int16_t raw = (data[1] << 8) | data[0];
    if (type_s)
    {
	    raw = raw << 3; // 9 bit resolution default
	    if (data[7] == 0x10)
	    {
		    // "count remain" gives full 12 bit resolution
		    raw = (raw & 0xFFF0) + 12 - data[6];
	    }
	    } else {
	    byte cfg = (data[4] & 0x60);
	    // at lower res, the low bits are undefined, so let's zero them
	    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
	    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
	    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
	    //// default is 12 bit resolution, 750 ms conversion time
    }
    celsius = (float)raw / 16.0;
    celsiusCorr = celsius + (offset);
    //Serial.print("  Temperature = ");
    //Serial.print(celsiusCorr);
    //Serial.println(" Celsius, ");
	if(lap == 0)
	{
		myGLCD.printNumF(celsiusCorr, 0,CENTER, 60);
		
	}
	else if (lap == 1)
	{
		myGLCD.printNumF(celsiusCorr, 0,CENTER, 100);
		
	}
	else if (lap == 2)
	{
		myGLCD.printNumF(celsiusCorr, 0,CENTER, 140);
	}
	lap++;
	if(lap > 2)
	{
		lap = 0;
	}
	
  //=======================
  
  bVal_iStato_220 = digitalRead(Istato220vac);
  
}
