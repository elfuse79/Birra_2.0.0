/*
//Timer 
int G_iTempo_mixer_avanti = 180000; //tempo per il quale il motore gira avanti 180000 = 3 minuri
int G_iTempo_mixer_per_inversione_avanti = 2500; // tempo per il quale il motore stà fermo per l'inversione
int G_iTempo_mixer_indietro = 180000;// tempo per il quale il motore gira indietro 180000 = 3 minuri
int G_iTempo_mixer_per_inversione_indietro = 2500;// tempo per il quale il motore stà fermo per l'inversione
//Variabli
int G_iTimer_K2H_avanti = 0;
int G_iTimer_inv_avanti = 0;
int G_iTempo_attesa_passaggio_stato_avanti = 0;
int G_iTimer_K2H_indietro = 0;
int G_iTimer_inv_indietro = 0;
int G_iTempo_attesa_passaggio_stato_indietro = 0;
int G_iTimer_start_mixer_avanti = 0; //non è un tempo ma lo stato per lo start di un tempo deve valere  0 allo start
int G_iTempo_mixer_on = 0; //deve valere  0 allo start
int G_iTimer_inversione_mixer_avanti = 0;//deve rimanere a 0 valoree per fare inversione no tempo
int G_iTempo_mixer_inversione_avanti_on = 0;//deve partire a 0 allo start
int G_iTimer_start_mixer_indietro = 0;
int G_iTimer_inversione_mixer_indietro = 0;//tempo per il quale il motore gira indietro
int G_iTempo_mixer_inversione_indietro_on = 0;
int G_iTimer_avanti = 0;
int G_iTimer_indietro = 0;
int G_iTimer_da_avanti =0;
int G_iTimer_da_indietro = 0;
*/
/*
bool ulL_timer_NoNscaduto = true;
unsigned long ulL_timeCampioni = 0;
unsigned long ulL_tempoCampionatura = 60000; //un minuto
*/
static int iL_Minuti = 0;
static bool bL_start = false;
static bool bL_finish = false;
void Out()
{			
						
//CAMPIONATURA TEMPERATURA
if( (bG_StartOK == true) && (bL_start == false) && (bL_finish == false))//(iG_Pressed_button == iG_Start)
{
	bL_start = true;
	myGLCD.print("GO",CENTER,CENTER);
}
if(bL_start == true)
{
	Serial.print("ulL_timeCampioni ");
	Serial.println(ulL_timeCampioni);

	if(ulL_timer_NoNscaduto == true)
	{
		ulL_timeCampioni = millis(); //prendo il tempo
		ulL_timer_NoNscaduto = false;
	}
	if((millis() - ulL_timeCampioni) >= ulL_tempoCampionatura)
	{
		if (!myFileC.open("Dati/Campioni.txt", O_RDWR | O_AT_END))//O_APPEND | O_CREAT | O_READ))//O_RDWR | O_CREAT | O_APPEND))//O_APPEND | O_CREAT | | O_CREAT))//O_APPEND | O_CREAT | O_READ))//O_RDWR | O_CREAT | O_APPEND))//O_APPEND | O_CREAT | O_AT_END))
		{
			sd.errorHalt("opening Campioni.txt for write failed");
			myGLCD.print("____ERROR____",CENTER,CENTER);
		}
		if(bG_stopUP == true)
		{
			myFileC.println("Stop_fornellone,");
			myGLCD.print("STOPED",CENTER,CENTER);
			Serial.println("Stop_fornellone####################################");
			bG_stopUP = false;
		}
		Serial.println("scrivo nel file________________________________________");
		//prendo la temperatura e la salvo
		iL_Minuti ++;
		myFileC.print("Minuti,");
		myFileC.println(iL_Minuti);
		myFileC.print("Temperatura Mash,");
		myFileC.println(tmush);
		myFileC.print("Temperatura Sparge,");
		myFileC.println(tsparge);
		myFileC.close();
		ulL_timer_NoNscaduto = true;
	}
}
if(iG_Pressed_button == iG_StopUP)
{
	bG_stopUP = true;
	myGLCD.print("STOP",CENTER,CENTER);
	Serial.println("iG_StopUP________");
	iG_Pressed_button = -1;
}
if(iG_Pressed_button == iG_Stop)
{
	bL_start = false;
	bL_finish = true;
	Serial.println("iG_Stop++++++++++++++++++");
	myGLCD.print("  FINISH  ",CENTER,CENTER);
	iG_Pressed_button = -1;
}
//=============================
	if (   
		   //( (bG_Started == true) &&  
				(Steps == sMush_IN ) || (Steps == sS_unica_AB    ) 	|| 
				( iG_mixerGO == true  &&	bG_Started == true )//&& Steps != sMush_Pre)//|| //8
		   //(bVal_iStato_220 == false)
	   )

    {
        switch(mixer)
        {
              	case Motore:
			  {
				digitalWrite (Omixer_K1, LOW);
				digitalWrite (Omixer_K2, LOW);
				if (  (Steps == sMush_IN )			|| //3
				(Steps == sS_unica_AB    )
				)
				{
					mixer=Motore_fermo;
				}
				break;  
			  }
			  case Motore_fermo:
              {
                  digitalWrite (Omixer_K1, LOW);
                  digitalWrite (Omixer_K2, LOW);
                  //digitalWrite (Oallarme, HIGH);//Solo per debug
                  	if (  (Steps != sComincio )			|| //0
                  	(Steps != sAVVIO    )			|| //1
                  	(Steps != sMush_Pre )			|| //2
                  	(Steps != sMush_OUT )			|| //9
                  	(Steps != sBoil     )			|| //10
                  	(Steps != sGotoFermentation)  || //11
                  	(Steps != sRiavvio)			|| //12
                  	(Steps != sfinito)
                  	)
					{
					mixer=Motore_avanti;
					}
					else
					{
						mixer=Motore_fermo;
					} 
                  break;
              }              
              case Motore_avanti:
              {
                  digitalWrite (Omixer_K1, HIGH);
                  digitalWrite (Omixer_K2, LOW);
				  Stato_K1 = true;
				  Stato_K2 = false;                 
                  if(G_iTimer_start_mixer_avanti == 0)
                  {
                      G_iTempo_mixer_on = millis();
                      G_iTimer_start_mixer_avanti = 1;
                  }
                  G_iTimer_avanti=(millis() - G_iTempo_mixer_on);
                  if ( G_iTimer_avanti >= G_iTempo_mixer_avanti )
                  {
                      G_iTimer_start_mixer_avanti = 0;
                      digitalWrite (Omixer_K1, LOW);
                      mixer=Motore_inversione_da_avanti;
                  }
                  break;
              }
              case Motore_inversione_da_avanti:
              {
                      //digitalWrite (Omixer_K2, HIGH);
                      digitalWrite (Omixer_K1, LOW);//NON SAREBBE NECESSARIO PERCè GIA SPENTO PRIMA DEL CAMBIO DI STATO
					  				  Stato_K1 = false;
					  				  Stato_K2 = false;
                      if(G_iTimer_inversione_mixer_avanti == 0)
                      {
                          G_iTempo_mixer_inversione_avanti_on = millis();
                          G_iTimer_inversione_mixer_avanti = 1;
                      }
                      G_iTimer_da_avanti= (millis() - G_iTempo_mixer_inversione_avanti_on);
                      if (  G_iTimer_da_avanti >= G_iTempo_mixer_per_inversione_avanti )
                      {
                          digitalWrite (Omixer_K2, HIGH);
                          if (G_iTimer_K2H_avanti == 0)
                          {
                              G_iTimer_inv_avanti = millis();
                              G_iTimer_K2H_avanti = 1;
                          }
                          G_iTempo_attesa_passaggio_stato_avanti = (millis() - G_iTimer_inv_avanti);
                          if(G_iTempo_attesa_passaggio_stato_avanti >= G_iTempo_mixer_per_inversione_avanti)
                          {
                                G_iTimer_inversione_mixer_avanti = 0;
                                mixer=Motore_indietro;
                          }
                      } 
                  break;
              }
              case Motore_indietro:
              {
                  digitalWrite (Omixer_K2, HIGH); //non sarebbe necessario
                  digitalWrite (Omixer_K1, HIGH);
				  Stato_K1 = true;
				  Stato_K2 = true;
                  if(G_iTimer_start_mixer_indietro == 0)
                  {
                      G_iTempo_mixer_on = millis();
                      G_iTimer_start_mixer_indietro = 1;
                  }
                  G_iTimer_indietro = (millis() - G_iTempo_mixer_on);
                  if (G_iTimer_indietro >= G_iTempo_mixer_indietro) 
                  {
                      G_iTimer_start_mixer_indietro = 0;
                      mixer=Motore_inversione_da_indietro;
                      digitalWrite (Omixer_K1, LOW);
                  }
                  break;
              }
              case Motore_inversione_da_indietro:
              {
                    //digitalWrite (Omixer_K2, LOW);
                    digitalWrite (Omixer_K1, LOW);
									  Stato_K1 = false;
									  Stato_K2 = false;
                    if(G_iTimer_inversione_mixer_indietro == 0)
                    {
                        G_iTempo_mixer_inversione_indietro_on = millis();
                        G_iTimer_inversione_mixer_indietro = 1;
                    }
                    G_iTimer_da_indietro = (millis() - G_iTempo_mixer_inversione_indietro_on);
                    if (G_iTimer_da_indietro >= G_iTempo_mixer_per_inversione_indietro)
                    {
                        G_iTimer_inversione_mixer_indietro = 0;
                        digitalWrite (Omixer_K2, LOW);
                        if (G_iTimer_K2H_indietro == 0)
                          {
                              G_iTimer_inv_indietro = millis();
                              G_iTimer_K2H_indietro = 1;
                          }
                          G_iTempo_attesa_passaggio_stato_indietro = ( millis() - G_iTimer_inv_indietro);
                          if(G_iTempo_attesa_passaggio_stato_indietro >= G_iTempo_mixer_per_inversione_indietro)
                          {
                              mixer=Motore_avanti;
                          }     
                    }       
                  break;
              }//chiude il case Motore_inversione_da_indietro
         }//chiude lo schift case
    }
	else
	{
		digitalWrite (Omixer_K1, LOW);
		digitalWrite (Omixer_K2, LOW);	
	}
}

