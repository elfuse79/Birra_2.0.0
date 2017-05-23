/*
 * Simone Volpara
 * 27/04/2017
 * See http://www.volpara-hb.it/
 */
//------------------------------------------------------------------------------
void GetTarature() 
{
	if (!myFile.open("Dati/TARATURE.TXT", O_RDWR | O_CREAT))//| O_APPEND))| O_AT_END))
	{
		sd.errorHalt("opening tarature.txt for write failed");
		myGLCD.print("____ERROR____",CENTER,CENTER);
	}
	const int line_buffer_size = 30;  //dimensione array ogni stringa può contenera al massimo 30 caratteri
	char buffer[line_buffer_size];    //array dove vengono salvati i dati 
	ifstream sdin("Dati/TARATURE.TXT");
	int line_number = 0;              //contattore linee
	while (sdin.getline(buffer, line_buffer_size, '\n') || sdin.gcount())
	{
	  int count = sdin.gcount();      
      if (sdin.fail()) 
      {
        //coutTarature() << "Partial long line";
        sdin.clear(sdin.rdstate() & ~ios_base::failbit);
      }
      else
      { 
		count--;  // Don’t include newline in count
        miastringaTarature = String(buffer);
		tagRigaTarature = getValue(miastringaTarature, '=', 0);  //tagRiga
		valoreTarature = getValue(miastringaTarature, '=', 1);  //valore
		for (unsigned int g=0; g<(sizeof(TaratureTable)/sizeof(TaratureTable[0])); g++)
		{
			if (TaratureTable[g].sTagTarature == tagRigaTarature) //trovato parametro?
			{
				switch (TaratureTable[g].eTaratureType)
				{
				case TARATURE_TYPE_FLOAT:
					*((float *)TaratureTable[g].pTarature) = atof(valoreTarature.c_str()); //coverte in float il valore e lo assegna alla variabile puntata
					break;
					
				case TARATURE_TYPE_LONG:
				*((long *)TaratureTable[g].pTarature) = atol(valoreTarature.c_str()); //coverte in float il valore e lo assegna alla variabile puntata
				break;
					
				case TARATURE_TYPE_ULONG:
				    *((unsigned long *)TaratureTable[g].pTarature) = strtoul(valoreTarature.c_str(), NULL, 10);
					break;
					
				default: //tipo di dato non gestito
				    myGLCD.print("dato no previsto",CENTER ,CENTER);
					break;
				}
			}
		}

        ++line_number;
    }
  }
  myFile.close();
}