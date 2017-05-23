  /*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
  void Pages()
  {
	//gestione pagine
		for	(int i=0; i<pagineUltimo; i++)
		{
			page = (pagine)i;
			myGLCD.setWritePage(page);
			switch (page)
			{
				case Avvio:
					//Disablebuttons ();
					//myGLCD.setWritePage(Avvio);//imposto la pagina
					myGLCD.fillScr(255,255,255);  //Pulisco lo schermo prima di passare alla pagina successiva
					myGLCD.setBackColor(255,255,255);
					myGLCD.setColor(0,0,0);//255,255,255 "bianco"
					myGLCD.print("sw: birra2.0.0",CENTER,14);
					//myGLCD.drawBitmap (220, 60, 180, 180, etichetta, 2);//(orignie-x,origine-y, dimensione x, dimensione-y, nome file, scala)
					myGLCD.drawBitmap (247, 95, 102, 97, Etichetta_102_97, 3);
					myGLCD.print("www.volpara-hb.it",CENTER,434);
					//myGLCD.setDisplayPage(Avvio);
					break;

				case Main:
					//Disablebuttons ();
					//myGLCD.setWritePage(Main);//imposto la pagina
					//myGLCD.clrScr();
					myGLCD.fillScr(160,160,160);  //Pulisco lo schermo prima di passare alla pagina successiva
					myGLCD.setBackColor(160,160,160);
					//cronometro
					myGLCD.drawBitmap(101,  47, 168, 185, Cronometro_168_185,1);//x=168/2=84+101->185-84=101,y=101+47
					myGLCD.setColor(0,0,0);     //set color black
					myGLCD.print(":",180,132);
					//settaggio colori
					myGLCD.setColor(255,255,255);     //set color (rgb white for draw rectangle)
					myGLCD.fillRect(0,38,800,42);     //riga bianca in alto 0,68,800,72
					//myGLCD.fillRect(0,30,800,34);     //riga bianca in alto altezza 4px
					myGLCD.fillRect(0,408,800,412);   //riga bianca in basso 412??
					myGLCD.setFont(Grotesk16x32);
					//myGLCD.print(NomiSteps[Steps], CENTER, 4); //stampa a video il nome dello steps attuale  da spostare //
					//mush + sparge
					myGLCD.drawBitmap(  3, 234, 89, 85, Tino_89_85, 2);	
					myGLCD.print("MASH", 60, 272);//x=(89+3=92-16-16)=60 ;y=234+32+2=268
					myGLCD.drawBitmap(187, 234, 89, 85, Tino_89_85, 2);//x=(3+89+89+3+3)=187
					myGLCD.print("SPARGE", 187+89-32-16, 272);//x=(187+89)=60 ;y=234+32+2=268
					//righe (/*tMush_Pre,24,*/477,220,16);  //da spostare in maint
					break;
				case Menu:
					myGLCD.clrScr();                                    //Pulisco lo schermo prima per entrare nella pagina pulita
					myGLCD.fillScr(160,160,160);                        //Disegno lo sfondo del display (rgb grigio)
					myGLCD.setBackColor(160,160,160); //Imposto lo sfondo per le scritte del display (rgb grigio
					myGLCD.setColor(255,255,255);// set color (rgb white for draw rectangle)
					myGLCD.fillRect(0,38,800,42);     //riga bianca in alto 0,68,800,72
					myGLCD.print("MENU",CENTER,4);
					myGLCD.print("Test I/O",70, 77-16);//94
					myGLCD.print("Tarature",70,145-16);//159
					myGLCD.print("Ricette" ,70,213-16);//227
					myGLCD.print("Back"    ,70,431);
					//myGLCD.setDisplayPage(Menu);
					break;
				case TestIO:
					//myGLCD.fillScr(160,160,160); 
					myGLCD.clrScr();
					//char *Valori[] = {"PIN","DESCRIZIONE","VALORE"};
					//static int stampo;
					static int f = 16;
					static int x =  0;
					static int y =  76;		//partenza seconda riga 16*2+10=42 -> 44+16+2=62-32=>78
					static int off = 4;//72
					myGLCD.fillScr(160,160,160);					//Disegno lo sfondo del display (rgb grigio)
					myGLCD.setBackColor(160,160,160);				//Imposto lo sfondo per le scritte del display (rgb grigio
					myGLCD.setColor(255,255,255);					//set color (rgb white for draw rectangle)
					myGLCD.fillRect(0,38,800,42);					//riga bianca in alto 0,68,800,72
					for (byte i=0; i<7; i++)
					{
						myGLCD.fillRect(x,y,800,y+off);     //riga bianca in alto (0,42,800,42+4) da gestire con y1 e y2
						y = y + f*2 + 8;
						//
						//myGLCD.print(Valori[stampo], x+f, y+off);
					}
					myGLCD.print("TEST I/O",CENTER,4);
					myGLCD.print("PIN",4,44);
					myGLCD.print("DESCRIZIONE", CENTER,44);
					myGLCD.print("VALORE", 670,44);//660
					//righe verticali
					myGLCD.fillRect(62,38,66,408);    //
					myGLCD.fillRect(652,38,656,408);    //
					//myButtons.enableButton(iG_Back, true);
					//myButtons.enableButton(iG_Menu, true);//attivo il tasto menu
					myGLCD.setColor(255,255,255);                                   //Imposto il colore (rgb bianco)                                         //Set color (rgb white)
					myGLCD.fillRect(0,408,800,412);  //riga bianca in basso
					//myGLCD.setDisplayPage(TestIO);
					break;
				case Tarature:
					myGLCD.clrScr();
					myGLCD.fillScr(160,160,160);  //Pulisco lo schermo prima di passare alla pagina successiva
					myGLCD.setBackColor(160,160,160);
					myGLCD.setColor(255,255,255);     //
					myGLCD.fillRect(0,38,800,42);     //riga bianca in alto 0,68,800,72
					myGLCD.print("TARATURE",CENTER,4);
					break;
				case TaratureMash:
					myGLCD.clrScr();
					myGLCD.fillScr(160,160,160);  //Pulisco lo schermo prima di passare alla pagina successiva
					myGLCD.setBackColor(160,160,160);
					myGLCD.setColor(255,255,255);     //
					myGLCD.fillRect(0,38,800,42);     //riga bianca in alto 0,68,800,72
					myGLCD.print("TARATURE MASH",CENTER,4);
					break;
				case TaratureSparge:
					myGLCD.clrScr();
					myGLCD.fillScr(160,160,160);  //Pulisco lo schermo prima di passare alla pagina successiva
					myGLCD.setBackColor(160,160,160);
					myGLCD.setColor(255,255,255);     //
					myGLCD.fillRect(0,38,800,42);     //riga bianca in alto 0,68,800,72
					myGLCD.print("TARATURE SPARGE",CENTER,4);
					break;
				case Ricette:
					myGLCD.clrScr();
					myGLCD.fillScr(160,160,160);  //Pulisco lo schermo prima di passare alla pagina successiva
					myGLCD.setBackColor(160,160,160);
					myGLCD.setColor(255,255,255);     //set color black
					myGLCD.fillRect(0,38,800,42);     //riga bianca in alto 0,68,800,72
					myGLCD.print("RICETTE",CENTER,4);
					break;
			}//chiude lo switch case
		}//ciclo for
  }//chiude il void
