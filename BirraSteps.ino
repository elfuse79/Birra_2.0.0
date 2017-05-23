/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
void  BirraSteps()
{

	  switch(Steps)
      {               
            case sComincio://0
				{
						Steps = sAVVIO;	
				}break;			
            case sAVVIO://1 //Riempo le pentole di acqua       //The pots have to be filled with water                        
				{
					if(bG_StartOK == true)
					{
						Steps = sMush_Pre; //passo allo steps sucessivo   //go to next steps 
					}                        
				}break;
            case sMush_Pre://2
				{
				//Serial.print("bG_Started___");
				//Serial.println(bG_Started);
				//Serial.println("una minchia_________________");
                if(bG_Started) //Se ho premuto il tasto Start
                {
                    //Serial.print("btMush_raggiunta___");
                    //Serial.println(btMush_raggiunta);
					if ( (tmush <= (tMush_Pre + offset_t)) && (tmush >= (tMush_Pre - offset_t)) ) //Se la temperatura è nell'intorno del target
                    {  
                        btMush_raggiunta = true;  //Non serve prendere il tempo, perchè mi serve solo per raggiungere la temperatura dell'acqua per poi procedere con il MushIN
						if (btMush_raggiunta == true)
						{
							bG_StepEnd = true;
						}
						else
						{
							bG_StepEnd = false;
						}
								
                        if((bG_GoNextStep == true) && (btMush_raggiunta == true )) //Ho premuto il tasto per il passaggio allo step sucessivo
                        {
	                        bG_StepEnd = false;
							//Serial.print("next step");
							Steps=sMush_IN;       //Vado nello step sucessivo
                        }
						/*
						if(bG_GoNextStep == true) //Ho premuto il tasto per il passaggio allo step sucessivo
                        {
	                        Steps=sMush_IN;       //Vado nello step sucessivo
                        }
						*/
								
						//bG_StepEnd = true;        //Lo uso per attivare l'allarme                 
                    }
					else
					{
						btMush_raggiunta = false;
						//bG_StepEnd = false;        //Lo uso per attivare l'allarme
					}
					/*
					if((bG_GoNextStep == true) && (btMush_raggiunta == true )) //Ho premuto il tasto per il passaggio allo step sucessivo
					{
						Steps=sMush_IN;       //Vado nello step sucessivo
					}
					*/
                    /*
					if(btMush_raggiunta == true)
                    {
                        if(bG_GoNextStep == true) //Ho premuto il tasto per il passaggio allo step sucessivo
                        {        
                            Steps=sMush_IN;       //Vado nello step sucessivo
                        }
                    }
					*/
                }  
				}break;            
            case sMush_IN://3
				{
                //logica step
                static bool lb_firstlaps = true;
                static long lL_T_InizioRampa   =    0;  //salvo il tempo quando entro nello step
                static long lL_T_FineRampa     =    0;  //salvo il tempo quando raggiungo la temperatura desiderata  
                if(lb_firstlaps == true)
                {
                    bG_GoNextStep = false;//preparo la variabile per lo step sucessivo  
                    btMush_raggiunta = false;
                    lL_T_InizioRampa = millis();
                    bG_StepEnd = false;
                    lb_firstlaps = false;
                }
                if( (tmush  >=  (tMush_IN - offset_t))) //se la temperatura è raggiunta, altrimenti...
                {
                    btMush_raggiunta = true;// mi salvo che è stata raggiunta almeno una volta
                    static bool bL_firstTraggiunta = true;
                    if(bL_firstTraggiunta  == true)
                    {
                        lL_T_FineRampa = millis();
						lG_TempoRampaMush_IN = (lL_T_FineRampa - lL_T_InizioRampa);  //salvo il tempo della durate della rampa
                        bL_firstTraggiunta = false;
                    }
                }
                //lG_TempoRampaMush_IN = (lL_T_FineRampa - lL_T_InizioRampa);
                if(btMush_raggiunta == true) //se la temperatura è stata raggiunta almeno una volta comincio a contare il tempo
                {
                    if(Tmush == 0)// mi serve per salvarmi il momento in cui la temperatura è stata raggiunta, da re-impostare a 0 prima di uscire dallo step
                    {
                        Tmush = millis();//mi salvo il momento in cui la temperatura è stata raggiunta
                    }
                    timer = (millis() - Tmush);//imposta la variabile timer con la sottrazzione del tempo trascorso dal momento in cui la temperatura è stata raggiunta
                    if(timer >= TMush_IN)//controllo se il tempo trascorso da quando la temperatura è stata raggiunta è minore o ugualo al tempo di durata dello step
                    {
                        bG_PulsNextEnable = true;
                    }
                    // mi serve per viusalizzare a display il tempo che manca========================
                    //stampo il valore di timer da sistemare over flow
                    if (tempo_trascorso < 0)
                    {
                        tempo_trascorso = 0;   
                    }
                    else
                    {
                        if(tempo_trascorso_scaduto == false)
                        {
                            tempo_trascorso = (( TMush_IN - timer)/1000);
                            if(tempo_trascorso == 0)
                            {
                                tempo_trascorso_scaduto = true;
                                //bG_StepEnd = true;
                                tempo_trascorso = 0;
                            }
                            // remain time=================
                            //Ore = (tempo_trascorso / 3600);
                            Minuti =  (tempo_trascorso / 60 );//% 60);
                            Secondi =  (tempo_trascorso % 60);
                            //Minuti =  (tempo_trascorso / 60);
                        }
                    }
                    if(bG_GoNextStep == true) //Ho premuto il tasto per il passaggio allo step sucessivo
                    {
                        Steps=sS_unica_AB;//Steps=sAcid_Rest;       //Vado nello step sucessivo
                    }                      
                }//chiudo la tempertura raggiunta almeno una volta
                        
				}break; //chiudo il case  
            case sAcid_Rest:
				{
                static bool bL_firstlap        = true;  //impostaioni di ingresso
                static long lL_T_InizioRampa   =    0;  //salvo il tempo quando entro nello step
                static long lL_T_FineRampa     =    0;  //salvo il tempo quando raggiungo la temperatura desiderata  
                if(bL_firstlap == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    lL_T_InizioRampa = millis(); //prendo il tempo da quando entro nello steps
                    bG_GoNextStep = false;//preparo la variabile per lo step sucessivo  
                    btMush_raggiunta = false;
                    iG_StatoAllarmePressed = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
                    bL_firstlap = false;
                }
                //logica step
                if((tmush  >=  (tAcid_Rest - offset_t))) //se la temperaturaè raggiunta, altrimenti...
                {
                    btMush_raggiunta = true;// mi salvo che è stata raggiunta almeno una volta
                    static bool bL_firstTraggiunta = true;
                    if(bL_firstTraggiunta == true)
                    {
                        lL_T_FineRampa = millis();
                        bL_firstTraggiunta = false;
                    }
                }
                lG_TempoRampaAcidRest = (lL_T_FineRampa - lL_T_InizioRampa);
                if(btMush_raggiunta == true) //se la temperatura è stata raggiunta almeno una volta comincio a contare il tempo
                {
                    if(Tmush == 0)// mi serve per salvarmi il momento in cui la temperatura è stata raggiunta, da re-impostare a 0 prima di uscire dallo step
                    {
                        Tmush = millis();//mi salvo il momento in cui la temperatura è stata raggiunta
                    }
                    timer = (millis() - Tmush);//imposta la variabile timer con la sottrazzione del tempo trascorso dal momento in cui la temperatura è stata raggiunta
                    if(timer >= TAcid_Rest)//controllo se il tempo trascorso da quando la temperatura è stata raggiunta è minore o ugualo al tempo di durata dello step
                    {
                        bG_PulsNextEnable = true;
                        //bG_StatoAllarme = true;//accendo l'allarme di fine step
                    }
                    // mi serve per viusalizzare a display il tempo che manca========================
                    //stampo il valore di timer da sistemare over flow
                    if (tempo_trascorso < 0)
                    {
                        tempo_trascorso = 0;   
                    }
                    //ho provato a gestire l'over flow
                    else
                    {
                        if(tempo_trascorso_scaduto == false)
                        {
                            tempo_trascorso = (( TAcid_Rest - timer)/1000);
                            if(tempo_trascorso == 0)
                            {
                                tempo_trascorso_scaduto = true;
                                tempo_trascorso = 0;
                            }
                            // remain time=================
                            //Ore = (tempo_trascorso / 3600);
                            Minuti =  (tempo_trascorso / 60 );//% 60);
                            Secondi =  (tempo_trascorso % 60);
                        }
                    }
                    if(bG_GoNextStep == true) //Ho premuto il tasto per il passaggio allo step sucessivo
                    {
                        Steps=sProtein_Rest;       //Vado nello step sucessivo
                    }       
                    //===================================================================================DOVREBBE FUNZIONA                          
                }//chiudo la tempertura raggiunta almeno una volta
				}break;
            case sProtein_Rest:
			{
                static bool lb_firstlaps = true;
                if(lb_firstlaps == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    bG_GoNextStep = false;//preparo la variabile per lo step sucessivo  
                    btMush_raggiunta = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
                    lb_firstlaps = false;
                }
                        
                //logica step
                if( (tmush  >=  (tProtein_Rest - offset_t))) //se la temperaturaè raggiunta, altrimenti...
                {
                    btMush_raggiunta = true;// mi salvo che è stata raggiunta almeno una volta
                }
                if(btMush_raggiunta == true) //se la temperatura è stata raggiunta almeno una volta comincio a contare il tempo
                {
                    if(Tmush == 0)// mi serve per salvarmi il momento in cui la temperatura è stata raggiunta, da re-impostare a 0 prima di uscire dallo step
                    {
                        Tmush = millis();//mi salvo il momento in cui la temperatura è stata raggiunta
                    }
                    timer = (millis() - Tmush);//imposta la variabile timer con la sottrazzione del tempo trascorso dal momento in cui la temperatura è stata raggiunta
                    if(timer >= TProtein_Rest)//controllo se il tempo trascorso da quando la temperatura è stata raggiunta è minore o ugualo al tempo di durata dello step
                    {   //non dovrebbe servire
                        bG_PulsNextEnable = true;
                        //bG_StatoAllarme = true;//accendo l'allarme di fine step
                    }
                    // mi serve per viusalizzare a display il tempo che manca========================
                    //stampo il valore di timer da sistemare over flow
                    if (tempo_trascorso < 0)
                    {
                        tempo_trascorso = 0;   
                    }
                    //ho provato a gestire l'over flow
                    else
                    {
                        if(tempo_trascorso_scaduto == false)
                        {
                            tempo_trascorso = (( TProtein_Rest - timer)/1000);
                            if(tempo_trascorso == 0)
                            {
                                tempo_trascorso_scaduto = true;
                                tempo_trascorso = 0;
                            }
                            // remain time=================
                            //Ore = (tempo_trascorso / 3600);
                            Minuti =  (tempo_trascorso / 60 );//% 60);
                            Secondi =  (tempo_trascorso % 60);
                        }
                    }
                    //===================================================================================DOVREBBE FUNZIONARE
                    if(bG_GoNextStep == true)
                    {
                        Steps=sS_unica_AB;
                    }
                }//chiudo la tempertura raggiunta almeno una volta    
				}break;
            case sB_amilasi:
			{
				//ATTENZIONE ANCORA DA PROVARE LA GESTIONA B e A AMILASI
                static bool lb_firstlaps = true;
                if(lb_firstlaps == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    bG_GoNextStep = false;
                    btMush_raggiunta = false;
                    iG_StatoAllarmePressed = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
                    lb_firstlaps = false;
                }
                    
                if(conf_par_S_unica_AB == 1)
                {
                    Steps=sS_unica_AB;
                }
                else
                {
                            
                    if(tmush>=tB_amilasi)
                    {
                        btMush_raggiunta = true;
                        if(Tmush == 0)
                        {
                            Tmush = millis(); 
                        } 
                        timer = (millis() - Tmush);                 
                        if(timer >= TB_amilasi)
                        {
                            bG_PulsNextEnable = true;
                            //bG_StatoAllarme = true;
                        }
                        if( (G_puls_premuto == true) && (bG_StatoAllarme == true)  )
                        {
                            bG_StatoAllarme = false;
                            btMush_raggiunta = false;
                            Tmush = 0; 
                            Steps=sS_unica_AB;
                        }
                    }
                }
				}break;
            case sA_amilasi:
			{
				//ATTENZIONE ANCORA DA PROVARE LA GESTIONA B e A AMILASI
                static bool lb_firstlaps = true;
                if(lb_firstlaps == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    bG_GoNextStep = false;
                    btMush_raggiunta = false;
                    iG_StatoAllarmePressed = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
                    lb_firstlaps = false;
                }
                        
                if(conf_par_S_unica_AB == 1)
                {
                    Steps=sS_unica_AB;
                }
                else
                {
                            
                    if(tmush>=tA_amilasi)
                    {
                        btMush_raggiunta = true;
                        if(Tmush == 0)
                        {
                            Tmush = millis(); 
                        } 
                        timer = (millis() - Tmush);                 
                        if(timer >= TA_amilasi)
                        {
                            bG_PulsNextEnable = true;
                            //bG_StatoAllarme = true;
                        }
                        if( (G_puls_premuto == true) && (bG_StatoAllarme == true)  )
                        {
                            bG_StatoAllarme = false;
                            btMush_raggiunta = false;
                            Tmush = 0; 
                            bG_StepEnd = false;
                            Steps=sMush_OUT;
                        }
                    }
                }    
				}break;
            case sS_unica_AB:
				{
                //
                static bool lb_firstlaps = true;
                static long lL_T_InizioRampa   =    0;  //salvo il tempo quando entro nello step
                static long lL_T_FineRampa     =    0;  //salvo il tempo quando raggiungo la temperatura desiderata
				if(lb_firstlaps == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    bG_GoNextStep = false;
                    btMush_raggiunta = false;
                    iG_StatoAllarmePressed = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
                    lL_T_InizioRampa = millis();
					lb_firstlaps = false;
                }
                        
                //logica step
                if( (tmush  >=  (tS_unica_AB - offset_t))) //se la temperaturaè raggiunta, altrimenti...
                {
                    btMush_raggiunta = true;// mi salvo che è stata raggiunta almeno una volta
					static bool bL_firstTraggiunta = true;
					if(bL_firstTraggiunta  == true)
					{
						lL_T_FineRampa = millis();
						lG_TempoRampaS_unica_AB = (lL_T_FineRampa - lL_T_InizioRampa);
						bL_firstTraggiunta = false;
					}
                }
                if(btMush_raggiunta == true) //se la temperatura è stata raggiunta almeno una volta comincio a contare il tempo
                {
                    if(Tmush == 0)// mi serve per salvarmi il momento in cui la temperatura è stata raggiunta, da re-impostare a 0 prima di uscire dallo step
                    {
                        Tmush = millis();//mi salvo il momento in cui la temperatura è stata raggiunta
                    }
                    timer = (millis() - Tmush);//imposta la variabile timer con la sottrazzione del tempo trascorso dal momento in cui la temperatura è stata raggiunta
                    if(timer >= TS_unica_AB)//controllo se il tempo trascorso da quando la temperatura è stata raggiunta è minore o ugualo al tempo di durata dello step
                    {
                        bG_PulsNextEnable = true;
                        //bG_StatoAllarme = true;//accendo l'allarme di fine step
                    }
                    // mi serve per viusalizzare a display il tempo che manca========================
                    //stampo il valore di timer da sistemare over flow
                    if (tempo_trascorso < 0)
                    {
                        tempo_trascorso = 0;   
                    }
                    //ho provato a gestire l'over flow
                    else
                    {
                        if(tempo_trascorso_scaduto == false)
                        {
                            if(TS_unica_AB < 0)
							{
								TS_unica_AB = 0;
							}
							tempo_trascorso = (( TS_unica_AB - timer)/1000);
							if(tempo_trascorso < 0)
							{
								tempo_trascorso = 0;
							}
							if(tempo_trascorso == 0)
                            {
                                tempo_trascorso_scaduto = true;
                                tempo_trascorso = 0;
                            }
                            // remain time=================
                            //Ore = (tempo_trascorso / 3600);
                            Minuti =  (tempo_trascorso / 60 );//% 60);
                            Secondi =  (tempo_trascorso % 60);
                        }
                    }
                    //===================================================================================DOVREBBE FUNZIONARE
                    if(bG_GoNextStep == true) //Ho premuto il tasto per il passaggio allo step sucessivo
                    {
                        /*tempo_trascorso_scaduto = false;
                        Tmush = 0;
                        bG_GoNextStep = false;//preparo la variabile per lo step sucessivo  
                        btMush_raggiunta = false;
                        iG_StatoAllarmePressed = false;//devo farlo altrimenti non visualizzo piu il timer
                        bG_StepEnd = false;
                        */
                        Steps=sMush_OUT;
                    }
                }//chiudo la tempertura raggiunta almeno una volta
				}break;    
            case sMush_OUT:
				{
                static bool lb_firstlaps = true;
				    static long lL_T_InizioRampa   =    0;  //salvo il tempo quando entro nello step
				    static long lL_T_FineRampa     =    0;  //salvo il tempo quando raggiungo la temperatura desiderata
                if(lb_firstlaps == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    bG_GoNextStep = false;
                    btMush_raggiunta = false;
                    iG_StatoAllarmePressed = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
					lL_T_InizioRampa = millis();
                    lb_firstlaps = false;
                }
                //logica step
                if( (tmush  >=  (tMush_OUT - offset_t))) //se la temperaturaè raggiunta, altrimenti...
                {
                    btMush_raggiunta = true;// mi salvo che è stata raggiunta almeno una volta
					static bool bL_firstTraggiunta = true;
					if(bL_firstTraggiunta  == true)
					{
						lL_T_FineRampa = millis();
						lG_TempoRampaMushOUT = (lL_T_FineRampa - lL_T_InizioRampa);
						bL_firstTraggiunta = false;
					}
                }
                if(btMush_raggiunta == true) //se la temperatura è stata raggiunta almeno una volta comincio a contare il tempo
                {
                    if(Tmush == 0)// mi serve per salvarmi il momento in cui la temperatura è stata raggiunta, da re-impostare a 0 prima di uscire dallo step
                    {
                        Tmush = millis();//mi salvo il momento in cui la temperatura è stata raggiunta
                    }
                    timer = ( (millis() - Tmush) + lG_TcorrezioneMushout);//imposta la variabile timer con la sottrazzione del tempo trascorso dal momento in cui la temperatura è stata raggiunta
                    if(timer >= TMush_OUT)//controllo se il tempo trascorso da quando la temperatura è stata raggiunta è minore o ugualo al tempo di durata dello step
                    {
                        bG_PulsNextEnable = true;
                        //bG_StatoAllarme = true;//accendo l'allarme di fine step
                    }
                    // mi serve per viusalizzare a display il tempo che manca========================
                    //stampo il valore di timer da sistemare over flow
                    if (tempo_trascorso < 0)
                    {
                        tempo_trascorso = 0;   
                    }
                    //ho provato a gestire l'over flow
                    else
                    {
                        if(tempo_trascorso_scaduto == false)
                        {
                            tempo_trascorso = (( TMush_OUT - timer)/1000);
                            if(tempo_trascorso == 0)
                            {
                                tempo_trascorso_scaduto = true;
                                tempo_trascorso = 0;
                            }
                            // remain time=================
                            //Ore = (tempo_trascorso / 3600);
                            Minuti =  (tempo_trascorso / 60 );//% 60);
                            Secondi =  (tempo_trascorso % 60);
                            //=============================
                        }
                    }
                    //===================================================================================DOVREBBE FUNZIONARE
                    if(bG_GoNextStep == true) //Ho premuto il tasto per il passaggio allo step sucessivo
                    {
                        tempo_trascorso_scaduto = false;
                        Tmush = 0;
                        bG_GoNextStep = false;//preparo la variabile per lo step sucessivo  
                        btMush_raggiunta = false;
                        iG_StatoAllarmePressed = false;
                        bG_StepEnd = false;
                        bG_PulsNextEnable = false;
						//save_sd();
                        Steps=sBoil;
                    }
                }//chiudo la tempertura raggiunta almeno una volta
				}break;
            case sBoil:
                {static bool lb_firstlaps = true;
                if(lb_firstlaps == true)
                {
                    tempo_trascorso_scaduto = false;
                    Tmush = 0;
                    bG_GoNextStep = false;
                    btMush_raggiunta = false;
                    iG_StatoAllarmePressed = false;
                    bG_StepEnd = false;
                    bG_PulsNextEnable = false;
                    //pot = potAttesa;//solo per le prove poi và rimossa
                    lb_firstlaps = false;
                }					          
                if(bG_StartBoil) //premo il pulsante per fare dire che la birra ha incominciato a bollire
                {
					//Prendo il tempo quando è incominciato a bollire
					if(ulG_timeBoil == 0)
					{
						ulG_timeBoil = millis();
					}
					//aggiorno la variabile del tempo passato
					ulG_timerBoil = (millis() - ulG_timeBoil);
					if( (ulG_timerBoil >= Tluppoli1) && (Luppolo1terminato == false) )
					{
						static bool lb_firstlaps = true;
						if(lb_firstlaps == true)
						{
							bG_NextStep = true;	
							lb_firstlaps = false;
						}
						else
						{
							bG_NextStep = false;
						}
						//Serial.println("timer1 scaduto");
						if(bG_AllarmLuppolo1Reset == false)
						{
							allarmeluppolo1 = true;
						}
						else
						{
									
						}
						if(luppolo1inserito == true)
						{
							allarmeluppolo1 = false;
							bG_inserireluppolo1 = true;
							//Serial.println("allarmeluppolo1_STEPS");
							bG_AllarmLuppolo1Reset = true;
							Luppolo1terminato = true;
						}
						else
						{
									
						}
					}
					//inserire la gestione del luppolo 1 rimane da disabilitare il pulsante nel luppolo 1
							
					else if((ulG_timerBoil >= (Tluppoli1 + Tluppoli2) ) && (Luppolo2terminato == false))
					{
						static bool lb_firstlaps = true;
						if(lb_firstlaps == true)
						{
							bG_NextStep = true;
							lb_firstlaps = false;
						}
						else
						{
							bG_NextStep = false;
						}
						allarmeluppolo2 = true;
						//Serial.println("timer2 scaduto");
						//Serial.print("timer2 bG_AllarmLuppolo2Reset");
						//Serial.println(bG_AllarmLuppolo2Reset);
						if(bG_AllarmLuppolo2Reset == false)
						{
							allarmeluppolo2 = true;
						}
						else
						{
									
						}
						if(luppolo2inserito == true)
						{
							allarmeluppolo2 = false;
							bG_inserireluppolo2 = true;
							//Serial.println("allarmeluppolo2_STEPS");
							bG_AllarmLuppolo2Reset = true;
							Luppolo2terminato = true;
						}
						else
						{
									
						}
					}
					else if( (ulG_timerBoil >= (Tluppoli1 + Tluppoli2 + Tluppoli3) ) && (Luppolo3terminato == false))
					{
						static bool lb_firstlaps = true;
						if(lb_firstlaps)
						{
							bG_NextStep = true;
							lb_firstlaps = false;
						}
						else
						{
							bG_NextStep = false;
						}
						//Serial.println("timer3 scaduto");
						if(bG_AllarmLuppolo3Reset == false)
						{
							allarmeluppolo3 = true;
						}
						else
						{
									
						}
						if(luppolo3inserito)
						{
							allarmeluppolo3 = false;
							bG_inserireluppolo3 = true;
							//Serial.println("allarmeluppolo3_STEPS");
							bG_AllarmLuppolo3Reset = true;
							Luppolo3terminato = true;
						}
						else
						{
									
						}
					}
					else if(ulG_timerBoil >= TBoil)//Controllo che il tempo trascorso sia maggiore o uguale al tempo impostato per la bollitura
                    {
                        static bool lb_firstlaps = true;
                        if(lb_firstlaps)
                        {
	                        bG_NextStep = true;
	                        lb_firstlaps = false;
                        }
                        else
                        {
	                        //bG_NextStep = false;
                        }
						//bG_PulsNextEnable = true;
						bG_Boil_terminato = true;
						//bG_StepEnd = true;
						//tempo_trascorso_scaduto = false; non mi fa gestire l'over flow
						//sendToSD = true;
						save_sd();
						//Serial.println("boil terminato______________________________________");
                    }
					if ((tempo_trascorso_scaduto == false) && (bG_Boil_terminato == false))
					{
						tempo_trascorso = (( TBoil - ulG_timerBoil)/1000);
						if (tempo_trascorso < 0)
						{
							tempo_trascorso = 0;
							tempo_trascorso_scaduto = false;
						}
						if( (tempo_trascorso == 0) && (bG_Boil_terminato == false) )
						{
							//bG_Boil_terminato = true;
							tempo_trascorso_scaduto = false;
							tempo_trascorso = 0; //non serve

						}
						// remain time=================
						//Ore = (tempo_trascorso / 3600);
						Minuti =  (tempo_trascorso / 60 );//% 60);
						Secondi =  (tempo_trascorso % 60);
						//=============================
						//ho provato a gestire l'over flow
					}
                    /*   
					else
                    {
                        if(tempo_trascorso_scaduto == false)
                        {
                            tempo_trascorso = (( TBoil - timer)/1000);
                            static bool allarmeluppolo1Resettato = false;
                                //Serial.print("allarmeluppolo1Resettato  ");
                                //Serial.println(allarmeluppolo1Resettato);
                            if( (timer >= Tluppoli1) && (allarmeluppolo1Resettato == false) )
                            {
                                allarmeluppolo1   =  true;
                                if(luppolo1inserito)//variabile che arriva dalla pressione del pulsante dell'allarme reset luppolo
                                {
                                    allarmeluppolo1   =  false;
                                    allarmeluppolo1Resettato = true;
                                    luppolo1inserito = true;
                                }
                            }
                            static bool allarmeluppolo2Resettato = false;
                            if( (timer >= (Tluppoli1+Tluppoli2)) && (allarmeluppolo2Resettato == false) )
                            {
                                allarmeluppolo2   =  true;
                                if(luppolo2inserito)//variabile che arriva dalla pressione del pulsante dellallarme reset luppolo
                                {
                                    allarmeluppolo2   =  false;
                                    allarmeluppolo2Resettato = true;
                                    luppolo2inserito = true;
                                }
                            }
                            static bool allarmeluppolo3Resettato = false;
                            if( (timer >= (Tluppoli1+Tluppoli2+Tluppoli3)) && (allarmeluppolo3Resettato == false) )
                            {
                                allarmeluppolo3   =  true;
                                if(luppolo3inserito)//variabile che arriva dalla pressione del pulsante dellallarme reset luppolo
                                {
                                    allarmeluppolo3   =  false;
                                    allarmeluppolo3Resettato = true;
                                    luppolo3inserito = true;
                                }
                            }
                                    
                            if(tempo_trascorso == 0)
                            {
                                tempo_trascorso_scaduto = true;
                                tempo_trascorso = 0;
                            }
                            // remain time=================
                            //Ore = (tempo_trascorso / 3600);
                            Minuti =  (tempo_trascorso / 60 );//% 60);
                            Secondi =  (tempo_trascorso % 60);
                            //=============================
                        }
					}
				*/	
				}
				else if (tempo_trascorso_scaduto)
				{                 
					static bool bL_firstBoil = true;
					if(bL_firstBoil)
					{
						pot = BoilPot;
					}
					if(pot == BoilPot)
					{
						if(bG_InizioRiempire)
						{
								sulG_Litri = 0;
								contatoreglobale = 0;
								cont = 0;
								//bG_LitriRaggiuntiMush = false;
								bG_InizioRiempire = false;
						}
						else//inserire variabile per tasto stop premuto
						{
								sulG_Litri = ( contatoreglobale * sulG_Litri_impulso);
								//fG_Litri_in_Ferment = sulG_Litri;// salvo il valore di acqua nella pentola del Mush
								//if( sulG_Litri >= (fG_LitriMush - fG_LitriOffset))
								//{
									//bG_LitriRaggiuntiMush = true;
								//}
						}              
					}
				}
				if(bG_terminato  ==  true)
					{
						Steps=sGotoFermentation;
					}
				}break;
			case sGotoFermentation:
					{
					if(pot == FermentationPot)
					{
						if(bG_InizioRiempire)
						{
							sulG_Litri = 0;
							contatoreglobale = 0;
							cont = 0;
							//bG_LitriRaggiuntiMush = false;
							bG_InizioRiempire = false;
							//Serial.println("inizioariempire");
						}
						else//inserire variabile per tasto stop premuto
						{
							sulG_Litri = ( contatoreglobale * sulG_Litri_impulso);
							//fG_Litri_in_Ferment = sulG_Litri;// salvo il valore di acqua nella pentola del Mush
							//if( sulG_Litri >= (fG_LitriMush - fG_LitriOffset))
							//{
								//bG_LitriRaggiuntiMush = true;
							//}
						}              
					}
					if((bG_terminato  ==  true) &&  (bG_InizioRiempire == false))
					{
						//save_sd();
						tempo_trascorso_scaduto = false;
						Steps=sRiavvio;
					}
				}break;
			case sRiavvio:
				{
					static unsigned long reset =0;
					static unsigned long prendotempo = 0;
					static unsigned long aspetto = 2000;
					static boolean primogiro = false;
					if  (primogiro == false)
					{
						reset = millis();
					}
					bG_StepEnd = false;
					if (aspetto <= ( millis() - reset) )
					{
						//Reset_AVR();
						mixer=Motore;
						pgt=Avviot;
						page=Avvio;
						Stamp=M_in;
						Steps=sComincio;	
					}
					
					
					
					
				}break;
			case sfinito:
				{
					//Serial.println("ERROR STEPS SFINITO");
					myGLCD.print("ERROR STEPS SFINITO",CENTER,CENTER);
				}break;
      }
}