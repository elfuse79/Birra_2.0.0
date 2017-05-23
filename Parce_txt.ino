/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
//------------------------------------------------------------------------------
void testGetline() 
{
  Serial.println("testGetline");
  const int line_buffer_size = 30;				  //dimensione array ogni stringa può contenera al massimo 30 caratteri
  char buffer[line_buffer_size];				  //array dove vengono salvati i dati 
  ifstream sdin(charbuf);						  //legge la riga sino a trovare un a capo "GETLINE.TXT" è il nome del file
  int line_number = 0;							  //contattore linee
  while (sdin.getline(buffer, line_buffer_size, '\n') || sdin.gcount())   //dentro il ciclo while riempe il buffer
  {
	  int count = sdin.gcount();
      if (sdin.fail()) 
      {
        cout << "Partial long line";
        sdin.clear(sdin.rdstate() & ~ios_base::failbit);
      }
      else
      { 
		count--;  // Don’t include newline in count
        miastringa = String(buffer);
		tagRiga = getValue(miastringa, '=', 0);  //tagRiga
		valore = getValue(miastringa, '=', 1);  //valore
		
		for (unsigned int k=0; k<(sizeof(ParamTable)/sizeof(ParamTable[0])); k++)
		{
			if (ParamTable[k].sTag == tagRiga) //trovato parametro?
			{
				switch (ParamTable[k].eParamType)
				{
				case PARAM_TYPE_FLOAT:
					*((float *)ParamTable[k].pParam) = atof(valore.c_str()); //coverte in float il valore e lo assegna alla variabile puntata
					break;
					
				case PARAM_TYPE_LONG:
				*((long *)ParamTable[k].pParam) = atol(valore.c_str()); //coverte in float il valore e lo assegna alla variabile puntata
				break;			
					
				case PARAM_TYPE_ULONG:
				    *((unsigned long *)ParamTable[k].pParam) = strtoul(valore.c_str(), NULL, 10);
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

}