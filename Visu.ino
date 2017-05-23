/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
bool bL_MiscelatoretLoaded = false;
void Visu()
{
	switch (pgt)
	{	
        case Avviot:
			static unsigned long lL_Avvio_time = 0;
			//Variabile locale  per prendere il tempo quando parte il programma, la variabile viene inizializzata a 0 solo la prima volta che il programma passa di qui, questo perchè è dichiarata come static
			if(bL_AvviotLoaded == false)
			{
				//myGLCD.setDisplayPage(Avvio);//scrivo la pagina
				myGLCD.setDisplayPage(Avvio);//scrivo la pagina
				lL_Avvio_time = millis();
				bL_AvviotLoaded = true;   
			}
			if( (millis() - lL_Avvio_time) >= timerStart)//se il tempo che è trascorso da quando ho finito di stampare la pagina è maggiore o uguale al tempo impostato per l'attesa allora
			{
				Steps = sAVVIO;
				pgt = Maint;//Passo alla schermata sucessiva //go to next page
				lL_Avvio_time = 0;
			}  
			break;
//Pagina principale  
        case Maint: 
			//Serial.println("VISU");
			//iG_Pressed_button = 0;
			
			if(bL_MainLoaded == false )
			{
				//Pages();
				myGLCD.setDisplayPage(Main);//impostare quali pagina di memoria da visualizzare
				Disablebuttons();
				bL_MainLoaded  = true;
				//bL_MaintLoaded = !bL_MainLoaded;
			}
			//myGLCD.setWritePage(Maint);	
			if(bL_MaintLoaded  == false)
			{
				myGLCD.setWritePage(Maint);//impostare quale pagina di memoria da utilizzare per le successive operazioni di scrittura di visualizzazione
				myButtons.enableButton(iG_Menu,true);
				myButtons.enableButton(iG_StopUP,true);
				myButtons.enableButton(iG_Stop,true);
				if(bG_recipeLoaded == true) //serve solo per non farle scrivere all'avvio
				{
					//LoadRecipe();
					righe (477,220,16);  //da provare
					//bG_recipeLoaded = false;
				}
				
				if(bG_Started)  //stato pulsante start
				{
					myGLCD.drawBitmap (0, 414, 150, 66, StartGreyp);	
					//forse serve myButtons.disableButton(iG_Menu);
				}
				else
				{
					myButtons.enableButton(iG_Start,true);	
				}
				myGLCD.setBackColor(160,160,160); //Imposto lo sfondo per timer
				myGLCD.setColor(0,0,0);//Imposto colore del caratter per timer
				//righe (/*tMush_Pre,24,*/477,220,16); 
				myGLCD.printNumI(tSpargeIN,(187+89+32+16),260-22);//(560+8),45); //187+89-32-16, 272
				myGLCD.print("C",  (187+89+32+16+32+4+4),260-22);//X=(800-32-8)=213
				myGLCD.drawCircle((187+89+32+16+32+4),(260-22),4);
				
				bL_MaintLoaded = true;
				//myButtons.enableButton(iG_Start,true);
			}
			bStatoCambiato = (Steps_old != Steps) || bFirstRound;
			Steps_old = Steps;
			if (bStatoCambiato)
			{
				myGLCD.setColor(160,160,160);// set color (rgb white for draw rectangle)
				myGLCD.fillRect(0,0,800,32+4);// riga verticale sparge
				myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
				myGLCD.setFont(Grotesk16x32);
				myGLCD.print(NomiSteps[Steps], CENTER, 4); //stampa a video il nome dello steps attuale
			}
			bFirstRound = false;
			if (iG_Pressed_button == iG_Menu)
			{
				bL_MainLoaded  = false;
				bL_MaintLoaded = false;
				iG_Pressed_button = -1;
				pgt = Menut;
			}
			myGLCD.setColor(0,0,0);//Imposto colore del caratter per timer
			myGLCD.setBackColor(249,181,91);
			myGLCD.setFont(Grotesk24x48);
			myGLCD.printNumF(tmush, 1, 60, 330);
            myGLCD.printNumF(tsparge, 1, 187+89-32-16, 330);
			myGLCD.setFont(Grotesk16x32);
			myGLCD.setBackColor(160,160,160);
			myGLCD.printNumI(Minuti, (180-32),132,2);
			myGLCD.printNumI(Secondi, (180+16),132,2);
			//myGLCD.print((&Serial), CENTER, CENTER);
			//Serial.print("minuti_");
			//Serial.println(Minuti);
			//Serial.print("Secondi_");
			//Serial.println(Secondi);
			if( Steps == sAVVIO)
			{
				if( (iG_Pressed_button == iG_Start))//iG_Start) )//&& (btMush_raggiunta == true) )
				{
					bG_Started = true;
					bG_StartOK = true;
					iG_Pressed_button = -1; //Disabilito il
					myGLCD.drawBitmap (0, 414, 150, 66, StartGreyp);//, 1); solo la prima volta
				}
			}
			if ( Steps == sMush_Pre)//2
			{                        
                static bool bL_nextStepPrinted = false;//variabile locale per stampare solo una volta
				static bool firstlaps = true;
				if(firstlaps == true)
				{
					myGLCD.setColor(255,255,255);
					myGLCD.printNumI(tMush_Pre,(187+89+32+16+32+4+4-178-48-48+24+12+6),260-22);//89
					myGLCD.print("C",  (187+89+32+16+32+4+4-178-48+24+12),260-22);//X=(800-32-8)=213
					myGLCD.drawCircle((187+89+32+16+32+4-178-48+24+12),(260-22),4);
					//myGLCD.fillRect(187+89+32+16+32+4+4-178-48-48+24+12+6),260-22);
					//myGLCD.print("Temp rif pre Mush",477,220-16);
					firstlaps = false;					
				}

				//myGLCD.print("STEPS", 597, y+72-f*2);
				//myGLCD.print("Temp Sparge:",400,120);
				//myGLCD.printNumF(tMush_IN,0,400+(16*12),120);
				
				if(iG_Pressed_iG_StartFirst)
				{
					//myGLCD.drawBitmap (0, 414, 150, 66, StartGreyp, 1);
					iG_Pressed_iG_StartFirst = false;//!iG_Pressed_iG_StartFirst;
				}
				//bG_GoNextStep
				if( (btMush_raggiunta == true)  &&  (bL_nextStepPrinted == false) || ( (btMush_raggiunta == true) && (bG_ComeBackMenu == true)))
                {
                    bL_nextStepPrinted = true;
                    myButtons.enableButton(iG_nextStep, true);//da provare                
                    myGLCD.print("INSERIRE IL MALTO",CENTER,4);
                }
                /*
				if( (iG_Pressed_button == iG_Start))//iG_Start) )//&& (btMush_raggiunta == true) )
                {
                    bG_Started = true;
                    iG_Pressed_button = -1; //Disabilito il 
                    myGLCD.drawBitmap (0, 414, 150, 66, StartGreyp);//, 1); solo la prima volta
					//iG_Pressed_iG_StartFirst  =  true; // mi serve per entrare qui solo la prima volta
                    //myButtons.disableButton(iG_Start);
                } 
				*/ 
                if( (iG_Pressed_button == iG_nextStep) && (bG_Started)  ) 
                {
                    bG_GoNextStep = true;
					iG_Pressed_button = -1;
                    myButtons.disableButton(iG_nextStep);
                    myGLCD.setColor(160,160,160);     
                }     
            }  
            if( Steps == sMush_IN)
			{
                  /*non dovrebbero servire
				  myGLCD.setBackColor(160,160,160);
                  myGLCD.setFont(Grotesk16x32);
				  */
                  static bool firstlap = false;
				  if(firstlap == false)
				  {  
					//myGLCD.fillRect((187+89+32+16+32+4+4-178-48-48+24+12+6),260-22);
					myGLCD.setColor(160,160,160);
					myGLCD.fillRect((132),(234),(174+16),(238+32));
					myGLCD.setColor(255,128,0);
                    myGLCD.fillCircle(477,220+80+8,10);//36
                    myGLCD.setColor(0,0,0);
					firstlap == true;//firstlap;
				  }
                  if(bG_PulsNextEnable == true)
                  {
                      myButtons.enableButton(iG_nextStep, true);
                  }
                  else
                  {
                      myButtons.disableButton(iG_nextStep);
                      myGLCD.setColor(160,160,160);
                      //myGLCD.fillRect( 325,  412, 475,  480);  //forse menu
                  }
					  /*
					  if(iG_Pressed_button == iG_plus5)
					  {
						  mTMush_IN = mTMush_IN + 5;  
						  iG_Pressed_button = -1;  				
					  }
					  */
					  if( (iG_Pressed_button == iG_nextStep) )
                      {
                          iG_Pressed_button = -1; //Display non premuto
						  myGLCD.setColor(0,255,0);
					 	  myGLCD.fillCircle(477,220+80+8,10);//36
						  myGLCD.setColor(0,0,0);
                          bG_GoNextStep = true;  
                      }
            }
			
            //=======
			/*
            if( Steps == sAcid_Rest)
            {
                  myGLCD.setBackColor(160,160,160);
                  myGLCD.setFont(Grotesk16x32);
                  //myGLCD.printNumI(tAcid_Rest, 102, 195); //mush tMush_Pre 
                  if(bG_PulsNextEnable == true)
                  {
                        myButtons.enableButton(iG_nextStep,true);
                  }
                  else
                  {
                        myButtons.disableButton(iG_nextStep);
                         myGLCD.setColor(160,160,160);
                        myGLCD.fillRect( 325,  410, 475,  476); 
                  }
				static bool firstlap = false;
				if(!firstlap)
				{
					myGLCD.setColor(255,128,0);
					//477,220,16
					myGLCD.fillCircle(477,220+16+36,10);//36
					myGLCD.setColor(0,0,0);
					//myGLCD.printNumI(tMush_IN, 102, 195); //mush tMush_Pre
					firstlap = !firstlap;
				}
                  if (myTouch.dataAvailable() == true)
                  {
                      iG_Pressed_button = myButtons.checkButtons();
                      if( (iG_Pressed_button == iG_nextStep)  )// && (tempo_trascorso_scaduto) )
                      {
                          iG_Pressed_button = -1; //Disabilito 
                          bG_GoNextStep = true;  
                      }
                      if( (iG_Pressed_button  ==  iG_StatoAllarme)  &&  (bG_Allarm == true) )
                      {
                          iG_StatoAllarmePressed = true;
                          iG_Pressed_button = -1;
                      }
                  }
            }
            //========
            else if( Steps == sProtein_Rest)
            {
                  myGLCD.setBackColor(160,160,160);
                  myGLCD.setFont(Grotesk16x32);
                  //myGLCD.printNumI(tProtein_Rest, 102, 195); //mush tMush_Pre 
                  if(bG_PulsNextEnable == true)
                  {
                       myButtons.enableButton(iG_nextStep,true);
                  }
                  else
                  {
                       myButtons.disableButton(iG_nextStep);
                       myGLCD.setColor(160,160,160);
                       myGLCD.fillRect( 325,  410, 475,  476);
                  }
                  if (myTouch.dataAvailable() == true)
                  {
                      iG_Pressed_button = myButtons.checkButtons();
                      if( (iG_Pressed_button == iG_nextStep) )
                      {
                          bG_Started = true;
                          iG_Pressed_button = -1; //Disabilito il
                          bG_GoNextStep = true;
                      }
                      if( (iG_Pressed_button  ==  iG_StatoAllarme)  &&  (bG_Allarm == true) )
                      {
                          iG_StatoAllarmePressed = true;
                      }
                  }
            }
			*/
            //===========
            if( Steps == sS_unica_AB)
            {
                static bool firstlap = false;
                if( (firstlap == false) || (bG_ComeBackMenu == true) )
                {
	                myButtons.enableButton(iG_plus5,true);
					myButtons.enableButton(iG_minus5,true);
					myGLCD.setColor(255,128,0);
	                //477,220,16
	                myGLCD.fillCircle(477,220+80+8+32+4,10);//36
	                myGLCD.setColor(0,0,0);
	                firstlap = !firstlap;
					bG_ComeBackMenu = false;
                }
				myGLCD.setBackColor(160,160,160);
                myGLCD.setFont(Grotesk16x32);
                if(bG_PulsNextEnable == true)
                {
                    myButtons.enableButton(iG_nextStep,true);
                }
                else
                {
                    myButtons.disableButton(iG_nextStep); 
                    myGLCD.setColor(160,160,160);
                    //myGLCD.fillRect( 325,  410, 475,  476); Menu???
                }
                    if(iG_Pressed_button == iG_plus5)
					{
						TS_unica_AB = (TS_unica_AB + TCorrezioneSosta);
						//Serial.println("PLUS++++++++++++5");
						iG_Pressed_button = -1;
					}
					if(iG_Pressed_button == iG_minus5)
					{
						if(TS_unica_AB > TCorrezioneSosta)
						{
							TS_unica_AB = (TS_unica_AB - TCorrezioneSosta);
							//Serial.println("MINUS__________5");
							iG_Pressed_button = -1;
						}
						else
						{
							myGLCD.print("NON FACCIO NULLA OVERFLOW",CENTER,CENTER);							
						}

					}
					if( (iG_Pressed_button == iG_nextStep) )
                    {
                        bG_Started = true;
                        iG_Pressed_button = -1; //Disabilito il 
						myGLCD.setColor(0,255,0);
						//477,220,16
						myGLCD.fillCircle(477,220+80+8+32+4,10);//36
						myGLCD.setColor(0,0,0);
                        bG_GoNextStep = true;  
                    }
            }//chiude sosta unica
            //===============================
            if( Steps == sMush_OUT)
            {
                static bool firstlap = false;
                if(firstlap == false)
                {
	                myGLCD.setColor(255,128,0);
	                //477,220,16
	                myGLCD.fillCircle(477,220+80+8+64+8,10);//36
	                myGLCD.setColor(0,0,0);
	                //myGLCD.printNumI(tMush_IN, 102, 195); //mush tMush_Pre
	                firstlap = !firstlap;
                }
				myGLCD.setBackColor(160,160,160);
                myGLCD.setFont(Grotesk16x32);
                //myGLCD.printNumI(tMush_OUT, 102, 195); //mush tMush_Pre       
                if(bG_PulsNextEnable == true)
                {
                    myButtons.enableButton(iG_nextStep,true);
                }
                else
                {
                    myButtons.disableButton(iG_nextStep); 
                    //iG_Pressed_button = -1;  //non ha senso 10/04/17
                    myGLCD.setColor(160,160,160);
                    //myGLCD.fillRect( 325,  410, 475,  476); menu??
                }                    
                    if( (iG_Pressed_button == iG_nextStep) )
                    {
                        bG_Started = true;
                        iG_Pressed_button = -1; //Disabilito il probabilmente facci odel casino è maglio lasciare la gestione originale, no -1
						myGLCD.setColor(0,255,0);
						//477,220,16
						myGLCD.fillCircle(477,220+80+8+64+8,10);//36
						myGLCD.setColor(0,0,0);
                        bG_GoNextStep = true; 
                    }
					/*
                    if( (iG_Pressed_button == iG_plus5min) )
                    {
                    lG_TcorrezioneMushout = (lG_TcorrezioneMushout + 300000);// + 5 minuti
                    }
                    if( (iG_Pressed_button == iG_minus5min) )
                    {
                    lG_TcorrezioneMushout = (lG_TcorrezioneMushout - 300000);// - 5 minuti
                    }
					*/
                  //gestione pulsanti aumento o diminuisce il tempo mush out
                  //lG_TcorrezioneMushout
		    }//chiude mush_out
			
			if( Steps == sBoil)
			{
				//static bool bL_nextStepPrinted = false;//variabile locale per stampare solo una volta
				static bool iG_Pressed_iG_StartFirst = true;  //controllare se si può usare quella globale
				/*
				if(bG_StartBoil)
				{
					myGLCD.print("Premere start quando incomincia a bollire")
				}
				*/
				if( (iG_Pressed_iG_StartFirst) || (bG_ComeBackMenu == true) )
				{
					myButtons.enableButton(iG_Start,true);
					//Serial.println("enable_start_button");
					myButtons.disableButton(iG_nextStep);
					myGLCD.setColor(160,160,160);
					myGLCD.fillRect(650,  414, 650+150,  414+66);//inserire coordinate pulsante nextspep)
					//myButtons.enableButton(iG_Start, true);
					bG_ComeBackMenu = false;
					iG_Pressed_iG_StartFirst = false;//
				}
				else
				{
					
				}
				if( (iG_Pressed_button == iG_Start) )
				{
					bG_StartBoil = true;
					//Serial.println("bG_StartBoil_true");
					myButtons.disableButton(iG_Start);
					myGLCD.drawBitmap (0, 414, 150, 66, StartGreyp);
					bG_NextStep = true;
					iG_Pressed_button = -1;
				}
				if(bG_NextStep == true)  //gestire meglio l'ingresso nei lupoli forse switch case?
				{
					myButtons.enableButton(iG_nextStep,true);
					myGLCD.print("Inserire luppolo",CENTER,47 + 27);
					//Serial.println("nextsteptrue");
					bG_NextStep = false; //vedere se serve solo qui					
				}
				if( (iG_Pressed_button == iG_nextStep) && (Luppolo1terminato == false) )
				{
						//myGLCD.print("bG_inserireluppolo1",CENTER,CENTER);
						myGLCD.setColor(160,160,160);
						myGLCD.fillRect(360,47+27,440,47+27+36);
						myGLCD.setColor(255,255,255);
						luppolo1inserito = true;
						//Serial.println("luppolo1inserito++++++++++++++++");
						myButtons.disableButton(iG_nextStep);
						myGLCD.setColor(160,160,160);
						myGLCD.fillRect(650,  414, 650+150,  414+66);//inserire coordinate pulsante nextspep)
						iG_Pressed_button = -1;
				}
				if( (iG_Pressed_button == iG_nextStep) && (Luppolo2terminato == false) )
				{
						myGLCD.print("bG_inserireluppolo 2",CENTER,CENTER);
						luppolo2inserito = true;
						//Serial.println("luppolo2inserito-----------------");
						myButtons.disableButton(iG_nextStep);
						myGLCD.setColor(160,160,160);
						myGLCD.fillRect(650,  414, 650+150,  414+66);//inserire coordinate pulsante nextspep)
						iG_Pressed_button = -1;
				}
				if( (iG_Pressed_button == iG_nextStep) && (Luppolo3terminato == false) )
				{
					myGLCD.print("bG_inserireluppolo3",CENTER,CENTER);
					luppolo3inserito = true;
					//Serial.println("luppolo3inserito-----------------");
					myButtons.disableButton(iG_nextStep);
					myGLCD.setColor(160,160,160);
					myGLCD.fillRect(650,  414, 650+150,  414+66);//inserire coordinate pulsante nextspep)
					//save_sd();
					iG_Pressed_button = -1;
				}
				if( (bG_Boil_terminato == true) && (Steps!=sRiavvio) )
				{
					bG_StepEnd = true;
					myGLCD.print("TERMINATO",CENTER,CENTER);
					iG_Pressed_button = -1;
				}
				if( (iG_Pressed_button == iG_nextStep) && (bG_Boil_terminato == true) )
				{
					bG_StepEnd = false;
					//myGLCD.print("TERMINATO",CENTER,CENTER);
					Steps=sRiavvio;
					iG_Pressed_button = -1;
				}
			}//chiude Boil
            //gestione allarme===========================
            if(bG_Allarm == true)
            {
                    myButtons.enableButton(iG_StatoAllarme, true);
                        if( (iG_Pressed_button == iG_StatoAllarme) )
                        {
                            iG_StatoAllarmePressed = true;
                            iG_Pressed_button = -1; //Disabilito il             
                        }
            }
            else
            {
                myGLCD.drawBitmap (664,  50, 121, 121,AllarmGrey121_121, 1);//y=50+121=171
            }
			
            /*
			if(bG_AllLuppolo)
            {
                //static bool firstloop = true;
                // if(firstloop)
                // {
                myButtons.enableButton(iG_AllLuppolo, true);
                //  firstloop = false;
                //}                      
                if (myTouch.dataAvailable() == true)
                {
                    iG_Pressed_button = myButtons.checkButtons();
                    if( (iG_Pressed_button == 7))//iG_AllLuppolo) )
                    {
                        //luppolo1inserito = true;
                        //iG_AllLuppoloPressed = true;
                        if(allarmeluppolo1)
                        {
                            luppolo1inserito = true;
                            iG_AllLuppoloPressed = true;
                            iG_StatoAllarmePressed = false;
                            iG_Pressed_button = -1;
                        }
                        if(allarmeluppolo2)
                        {
                            luppolo2inserito = true;
                            iG_AllLuppoloPressed = true;
                            iG_StatoAllarmePressed = false;
                            iG_Pressed_button = -1;
                        }
                        if(allarmeluppolo3)
                        {
                            luppolo3inserito = true;
                            iG_AllLuppoloPressed = true;
                            iG_StatoAllarmePressed = false;
                            iG_Pressed_button = -1;
                        }
                        //iG_Pressed_button = -1; //Disabilito il             
                    }
                }
				*/
				//controllo se ho premuto i pulsanti
				//se premo next step
				/*
				if( (iG_Pressed_button == iG_Start)  &&  (bG_StepEnd = true) )
				{
					//myGLCD.drawBitmap (0, 414, 150, 66, StartGreyp, 1);//??
					//myGLCD.drawBitmap (0, 410, 150, 66, StartGreyp, 1);
					//myButtons.drawButton(iG_nextStep);
					myButtons.enableButton(iG_nextStep, true);//????
					//Mi serve per comunicare al case che è stato premuto il tasto di Start
				}
				
            }
            else
            {
                 myButtons.disableButton(iG_AllLuppolo);
            }
            */    
            /*
			//controllo se ho premuto i pulsanti
            //se premo next step
            if( (iG_Pressed_button == iG_Start)  &&  (bG_StepEnd = true) )
            {   
            myGLCD.drawBitmap (0, 410, 150, 66, StartGreyp, 1);
            myButtons.drawButton(iG_nextStep);
            myButtons.enableButton(iG_nextStep);
            //Mi serve per comunicare al case che è stato premuto il tasto di Start
            }
			*/
            //?????????????????
			/*
			if(iG_Pressed_button == iG_nextStep)
            {
                Steps = sMush_IN;
            }
            */
            //Se arrivo dalla pagina menu allora
              
	        //Se premo il tasto Menu vado nella pagina sucessiva=====================================================

			break;//chiude il case main
// Menu Page
		case Menut:	
			if(bL_MenuLoaded == false)
			{
			 
			   myGLCD.setDisplayPage(Menu);//scrivo la pagina;
			   myButtons.disableButton(iG_Start);
			   myButtons.disableButton(iG_Menu);
			   bL_MenuLoaded  = true;
			}
			if(bL_Menut_Loaded == false)
			{
				myGLCD.setWritePage(Menut);
				myButtons.enableButton(iG_Pulstante_1, true);
				myButtons.enableButton(iG_Pulstante_2, true);
				myButtons.enableButton(iG_Pulstante_3, true);
				myButtons.enableButton(iG_Back, true);
				bG_ComeBackMenu = false;
				bL_Menut_Loaded = true;
			}
			if (iG_Pressed_button == iG_Back)
			{
				bG_ComeBackMenu = true;
				bL_MenuLoaded    = false;
				bL_Menut_Loaded   = false;
				pgt = Maint;
				iG_Pressed_button = -1;
			}
			else if (iG_Pressed_button == iG_Pulstante_1)
			{
				bG_pgSeted = false;
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				pgt = TestIOt;
				iG_Pressed_button = -1;
			}
			else if (iG_Pressed_button == iG_Pulstante_2)
			{
				bG_pgSeted = false;
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				pgt = Taraturet;
				iG_Pressed_button = -1;
			}
			else if (iG_Pressed_button == iG_Pulstante_3)
			{
				bG_pgSeted = false;
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				pgt = Ricettet;
				iG_Pressed_button = -1;
			}
			else if (iG_Pressed_button == iG_Pulstante_4)
			{
				bG_pgSeted = false;
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				pgt = Miscelatoret;
				iG_Pressed_button = -1;
			}
			else if (iG_Pressed_button == iG_Pulstante_5)
			{
				bG_pgSeted = false;
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				pgt = Whirlpoolt;
				iG_Pressed_button = -1;
			}
			break;//chiude il case menu		
        case TestIOt:
             static int yTestIO = 83;//120
			 if(bL_TestIOLoaded == false)
             {
				 myGLCD.setDisplayPage(TestIO);//scrivo la pagina;
	             //Disablebuttons();
	             //myButtons.disableButton(iG_Start);
	             bL_TestIOLoaded  = true;
	             //bL_MaintLoaded = !bL_MainLoaded;
             }
             if(bL_TestIOtLoaded == false)
             {
				myGLCD.setWritePage(TestIOt);
				Disablebuttons();
				myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
                myGLCD.print("A0", 4,yTestIO);
                myGLCD.print("PT1000 Mush", 70,yTestIO);
                myGLCD.print("A2", 4,yTestIO + 40);
                myGLCD.print("PT1000 Sparge", 70,yTestIO + 40);
                myGLCD.print("08", 4,yTestIO + 80);
                myGLCD.print("Contalitri", 70,yTestIO + 80);
                myGLCD.print("08", 4,yTestIO + 120);
                myGLCD.print("litri_min", 70,yTestIO + 120);
				myGLCD.print("10", 4,yTestIO + 160);
				myGLCD.print("Rele K1", 70,yTestIO + 160);
				myGLCD.print("11", 4,yTestIO + 200);
				myGLCD.print("Rele K2", 70,yTestIO + 200);
				myButtons.enableButton(iG_Back, true);
				myGLCD.print("Back"    ,70,431);
				bL_TestIOtLoaded = true;
			 }
 			 //myGLCD.printNumI(Pt1000_Mush, 0, 674, yTestIO);
 			 //myGLCD.printNumI(Pt1000_Sparge, 0, 674, yTestIO + 40);
			 myGLCD.printNumI(Pt1000_Mush, 674, yTestIO);
			 myGLCD.printNumI(Pt1000_Sparge, 674, yTestIO + 40); 
			 myGLCD.printNumI(contatoreglobale, 674, yTestIO + 80);
			 myGLCD.printNumF( litri_min, 0 , 674, yTestIO + 120);
  			 myGLCD.printNumI(Stato_K1, 674, yTestIO + 160);
			 myGLCD.printNumI(Stato_K2, 674, yTestIO + 200);
			 //myGLCD.printNumF(Stato_K2, 0, 674, CENTER);
   			 if (iG_Pressed_button == iG_Back)
 			 {
			 	bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				bL_TestIOLoaded = false;
				bL_TestIOtLoaded = false;
				pgt = Menut;           
				iG_Pressed_button = -1;
			 }
			 break;//chiude il case test I/O
        case Taraturet:
          if(bL_TaratureLoaded == false)
		  {
			  myGLCD.setDisplayPage(Tarature);//scrivo la pagina;
			  bL_TaratureLoaded = true;
		  }
          if(bL_TaraturetLoaded == false)
            {
                myGLCD.setWritePage(Taraturet);
				Disablebuttons();
                myGLCD.setBackColor(160,160,160); //Imposto lo sfondo per le scritte del display (rgb grigio
                myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
                myGLCD.print("Mush temperature",70, 77-16);
                myGLCD.print("Sparge temperature",70,145-16);
                myGLCD.print("Contalitri" ,70,213-16);
                myButtons.enableButton(iG_Pulstante_1, true);
                myButtons.enableButton(iG_Pulstante_2, true);
                myButtons.enableButton(iG_Pulstante_3, true);
                myButtons.enableButton(iG_Back, true);
				myGLCD.print("Back"    ,70,431);
                bG_ComeBackMenu = false;
                bL_TaraturetLoaded = true;                                
            }
			if(iG_Pressed_button == iG_Pulstante_1)
			{
				pgt = TaratureMasht;
				iG_Pressed_button = -1;
				/*
				myGLCD.setColor(160,160,160);
				myGLCD.fillRect(0,43,800,413);
				*/
			}
			if(iG_Pressed_button == iG_Pulstante_2)
			{
				pgt = TaratureSparget;
				iG_Pressed_button = -1;
			}
            if (iG_Pressed_button == iG_Back)
            {
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				bL_TaratureLoaded = false;
				bL_TaraturetLoaded = false;
				pgt = Menut;
				iG_Pressed_button = -1;            
            }
        break;//chiude il case Tarature
		case TaratureMasht:
		{
			if(bG_TaratureMashLoaded == false)
			{
				myGLCD.setDisplayPage(TaratureMash);//scrivo la pagina;
				bG_TaratureMashLoaded = true;
			}
			if(bG_TaratureMashtLoaded == false)
			{
				myGLCD.setWritePage(TaratureMasht);
				Disablebuttons();
				myGLCD.setBackColor(160,160,160); //Imposto lo sfondo per le scritte del display (rgb grigio
				myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
				//myButtons.enableButton(iG_Pulstante_1, true);
				myButtons.enableButton(iG_Pulstante_2, true);
				myButtons.enableButton(iG_Pulstante_3, true);
				myGLCD.print("Valore attuale PT1000 = ",0, 77-16);
				myGLCD.print("Set Temperature Min",70,145-16);
				myGLCD.print("T Min = ",608, 145-16);//77-16);
				myGLCD.printNumF(tMushMin,0,736, 145-16);//77-16);
				//myButtons.enableButton(iG_Pulstante_4, true);
				myGLCD.print("T Max = ",608, 180+16);//77-16);
				myGLCD.printNumF(tMushMax,0,736, 180+16);//77-16);
				myGLCD.print("Set Temperature Max",70,180+16);
				myButtons.enableButton(iG_Pulstante_5, true);
				myGLCD.print("Save values",70,316+16);
				myButtons.enableButton(iG_Back, true);
				myGLCD.print("Back"    ,70,431);
				AMushMinOld = AMushMin;//così quando rientro ritrovo sempre quelle attualmente in uso
				AMushMaxOld = AMushMax;
				bG_TaratureMashtLoaded = true;
			}
			myGLCD.printNumF(Pt1000_Mush, 0,384, 77-16);
			myGLCD.printNumF(AMushMinOld, 0,384, 145-16);
			myGLCD.printNumF(AMushMaxOld, 0,384, 180+16);
			if(iG_Pressed_button == iG_Pulstante_2)
			{
				myGLCD.setColor(160,160,160);
				myGLCD.fillRect(384,145-16, 600,145-16+32);
				myGLCD.setColor(255,255,255);
				AMushMinOld = Pt1000_Mush;
				iG_Pressed_button = -1;
			}
			if(iG_Pressed_button == iG_Pulstante_3)
			{
				myGLCD.setColor(160,160,160);
				myGLCD.fillRect(384,180+16, 600,180+16+32);
				myGLCD.setColor(255,255,255);
				AMushMaxOld = Pt1000_Mush;
				iG_Pressed_button = -1;
			}
			//if(iG_Pressed_button == iG_Pulstante_4)
			//{

			//}
			if(iG_Pressed_button == iG_Pulstante_5)
			{
				AMushMin = AMushMinOld;
				AMushMax = AMushMaxOld;
				save_TARATURE();
				GetTarature();
				myGLCD.setColor(255,255,255);
				myGLCD.print("Values saved",CENTER,316+16);
				myButtons.disableButton(iG_Pulstante_5);
				delay(1000);
				iG_Pressed_button = iG_Back;
			}
			if (iG_Pressed_button == iG_Back)
			{
				bL_TaratureLoaded = false;
				bL_TaraturetLoaded = false;
				bG_TaratureMashLoaded = false;
				bG_TaratureMashtLoaded = false;
				myGLCD.setColor(160,160,160);
				myGLCD.fillRect(400-(16*7),316+16,400+(16*7),316+16+32);
				pgt = Taraturet;
				iG_Pressed_button = -1;
			}
			break;
		}
		
			case TaratureSparget:
				{
				if(bG_TaratureSpargeLoaded == false)
				{
					myGLCD.setDisplayPage(TaratureSparge);//scrivo la pagina;
					bG_TaratureSpargeLoaded = true;
				}
				if(bG_TaratureSpargetLoaded == false)
				{
					myGLCD.setWritePage(TaratureSparget);
					Disablebuttons();
					myGLCD.setBackColor(160,160,160); //Imposto lo sfondo per le scritte del display (rgb grigio
					myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
					myButtons.enableButton(iG_Pulstante_2, true);
					myButtons.enableButton(iG_Pulstante_3, true);
					myGLCD.print("Valore attuale PT1000 = ",0, 77-16);
					myGLCD.print("Set Temperature Min",70,145-16);
					myGLCD.print("T Min = ",608, 145-16);//77-16);
					myGLCD.printNumF(tSpargeMin,0,736, 145-16);//77-16);
					//myButtons.enableButton(iG_Pulstante_4, true);
					myGLCD.print("T Max = ",608, 180+16);//77-16);
					myGLCD.printNumF(tSpargeMax,0,736, 180+16);//77-16);
					myGLCD.print("Set Temperature Max",70,180+16);
					myButtons.enableButton(iG_Pulstante_5, true);
					myGLCD.print("Save values",70,316+16);
					myButtons.enableButton(iG_Back, true);
					myGLCD.print("Back"    ,70,431);
					ASpargeMinOld = ASpargeMin;//così quando rientro ritrovo sempre quelle attualmente in uso
					ASpargeMaxOld = ASpargeMax;
					bG_TaratureSpargetLoaded = true;
				}
				myGLCD.printNumI(Pt1000_Sparge, 384, 77-16);
				myGLCD.printNumF(ASpargeMinOld, 0,384, 145-16);
				myGLCD.printNumF(ASpargeMaxOld, 0,384, 180+16);
				if(iG_Pressed_button == iG_Pulstante_2)
				{
					myGLCD.setColor(160,160,160);
					myGLCD.fillRect(384,145-16, 600,145-16+32);
					myGLCD.setColor(255,255,255);
					ASpargeMinOld = Pt1000_Sparge;
					iG_Pressed_button = -1;
				}
				if(iG_Pressed_button == iG_Pulstante_3)
				{
					myGLCD.setColor(160,160,160);
					myGLCD.fillRect(384,180+16, 600,180+16+32);
					myGLCD.setColor(255,255,255);
					ASpargeMaxOld = Pt1000_Sparge;
					iG_Pressed_button = -1;
				}

				if(iG_Pressed_button == iG_Pulstante_5)
				{

					ASpargeMin = ASpargeMinOld;
					ASpargeMax = ASpargeMaxOld;
					save_TARATURE();
					GetTarature();
					myGLCD.setColor(255,255,255);
					myGLCD.print("Values saved",CENTER,316+16);
					myButtons.disableButton(iG_Pulstante_5);
					delay(1000);
					iG_Pressed_button = iG_Back;
				}
				if (iG_Pressed_button == iG_Back)
				{
					bL_TaratureLoaded = false;
					bL_TaraturetLoaded = false;
					bG_TaratureSpargeLoaded = false;
					bG_TaratureSpargetLoaded = false;
					myGLCD.setColor(160,160,160);
					myGLCD.fillRect(400-(16*7),316+16,400+(16*7),316+16+32);
					
					pgt = Taraturet;
					iG_Pressed_button = -1;
				}
				break;
			}
        case Ricettet:
		{
			if(bG_RicetteLoaded == false)
			{
				myGLCD.setDisplayPage(Ricette);									//scrivo la pagina;
				bG_RicetteLoaded = true;
			}
			if(bG_RicettetLoaded == false)
			{
				myGLCD.setWritePage(Ricettet);
				Disablebuttons();
				myGLCD.setBackColor(160,160,160);								//Imposto lo sfondo per le scritte del display (rgb grigio
				myGLCD.setColor(255,255,255);									// set color (rgb white for draw rectangle)
				myButtons.enableButton(iG_Back, true);
				myGLCD.print("Back"    ,70,431);
				int y2 = 68;
				int y1 = 0;
				//listLfn(sd.vwd());  //chiamo la funzione che legge i file present dentro la sd
				//
				//Serial.println("ricettet_loaded-");
				for(int index_stringa = 0; index_stringa < numero_file; index_stringa++)
				{
					file = File_Root[index_stringa];
					y1=y2+y1;
					myGLCD.print(file,70, 9+y1-16);//77 145 213
					if(index_stringa == 0)
					{
						//myButtons.enableButton(iG_Pulstante_1, true);
						file1 = file;
					}
					else if(index_stringa == 1)
					{
						//myButtons.enableButton(iG_Pulstante_2, true);
						file2 =file;
					}
					//Serial.print("file ");
					//Serial.println(file);
					if (Steps != sAVVIO)
					{
						myButtons.disableButton(iG_Pulstante_1);
						myButtons.disableButton(iG_Pulstante_2);
						myGLCD.setColor(192,192,192);
						myGLCD.fillRoundRect( 0,  44, 64,  44+64);
						myGLCD.fillRoundRect( 0,  112, 64,112+64);
						myGLCD.setColor(160,160,160);
					}
					else
					{
						myButtons.enableButton(iG_Pulstante_1, true);
						myButtons.enableButton(iG_Pulstante_2, true);
					}
				}
				//
				bG_RicettetLoaded = true;
			}
			if(iG_Pressed_button == iG_Pulstante_1)
			{
				//iG_IndexRighe = 0;
				//Serial.print("new_ricetta ");
				//Serial.println(NOME_RICETTA);
				NOME_RICETTA = file1;
				//Serial.print("new_ricetta ");
				//Serial.println(NOME_RICETTA);
				NOME_RICETTA.toCharArray(charbuf,50);
				//Serial.print("charbuf ");
				//Serial.println(charbuf);
				LoadRecipe(); //test io
				myGLCD.print("loaded",CENTER,61);  //bisogna cancellarla una volta che si esce dalla pagina
				//color = myGLCD.getColor(VGA_SILVER);
				//myGLCD.getColor(oldColor)
				myGLCD.setColor(160,160,160);
				myGLCD.fillRect(300,61+68,500,91+68);
				myGLCD.setColor(255,255,255);
				bG_recipeLoaded = true;
				iG_Pressed_button = -1;
			}
			if(iG_Pressed_button == iG_Pulstante_2)
			{
				//iG_IndexRighe = 0;
				//Serial.print("new_ricetta ");
				//Serial.println(NOME_RICETTA);
				NOME_RICETTA = file2;
				Serial.print("new_ricetta ");
				Serial.println(NOME_RICETTA);
				NOME_RICETTA.toCharArray(charbuf,50);
				Serial.print("charbuf ");
				Serial.println(charbuf);
				//LoadRecipe(); //taraTURE
				myGLCD.print("loaded",CENTER,61+68);  //bisogna cancellarla una volta che si esce dalla pagina
				myGLCD.setColor(160,160,160);
				myGLCD.fillRect(300,61,500,91);
				myGLCD.setColor(255,255,255);
				LoadRecipe(); //taraTURE
				bG_recipeLoaded = true;
				iG_Pressed_button = -1;
			}
			if (iG_Pressed_button == iG_Back)
			{
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				bG_RicetteLoaded = false;
				bG_RicettetLoaded = false;
				//myGLCD.fillRect(300,200,500,300); da vedere come gestire la cancellazione della scritta loaded
				pgt = Menut;
				iG_Pressed_button = -1;
			}
        }break;//chiude il case Ricette
		case Miscelatoret:
          /*
		  if(bL_TaratureLoaded == false)
		  {
			  myGLCD.setDisplayPage(Miscelatore);//scrivo la pagina;
			  bL_TaratureLoaded = true;
		  }
		  */
          if(bL_TaraturetLoaded == false)
            {
                myGLCD.setWritePage(Miscelatoret);
				Disablebuttons();
                myGLCD.setBackColor(160,160,160); //Imposto lo sfondo per le scritte del display (rgb grigio
                myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
                myGLCD.print("Mixer Start",70, 77-16);
                myGLCD.print("Mixer Stop",70,145-16);
                myButtons.enableButton(iG_Pulstante_1, true);
                myButtons.enableButton(iG_Pulstante_2, true);
                myButtons.enableButton(iG_Pulstante_3, true);
                myButtons.enableButton(iG_Back, true);
				myGLCD.print("Back"    ,70,431);
                bG_ComeBackMenu = false;
                bL_MiscelatoretLoaded = true;                                
            }
			if(iG_Pressed_button == iG_Pulstante_1)
			{
				
				iG_Pressed_button = -1;
			}
			if(iG_Pressed_button == iG_Pulstante_2)
			{
				
				iG_Pressed_button = -1;
			}
            if (iG_Pressed_button == iG_Back)
            {
				bL_MenuLoaded = false;
				bL_Menut_Loaded = false;
				//bL_TaratureLoaded = false;
				bL_MiscelatoretLoaded = false;
				pgt = Menut;
				iG_Pressed_button = -1;            
            }
			break;
		//iG_mixerGO
    }//chiude lo switch case pg
}//chiude il loop
