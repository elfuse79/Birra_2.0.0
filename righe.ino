/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
void righe(/*float T,float t,*/int x,int y, int f)
{
		myGLCD.setColor(255,255,255);
		//Serial.print("mTMush_IN_PRIMA ");
		//Serial.println(mTMush_IN);
	//if (bG_prima_volta == false)
	//{
		unsigned long indiceTempo = 0;
		int indiceTemperature = 0;
		int stampo = 0;
		//bG_prima_volta = true;
	//}

	//Serial.println("first");
	const char *const dastamp[ultimo] = {"Mu. in:","So. AB:","M. out:"};//,"Acidrighe r:","Prot r:","So. AB:","M. out:"};//NomiSteps[Steps]
	unsigned long Tempo []={mTMush_IN,mTS_unica_AB,mTMush_OUT}; //mTAcid_Rest,mTProtein_Rest,mTS_unica_AB,mTMush_OUT};
	//unsigned long indiceTempo = 0;
	unsigned long T = 0;
	float gradi []={tMush_IN,tS_unica_AB,tMush_OUT}; //tAcid_Rest,tProtein_Rest,tS_unica_AB,tMush_OUT};
	//static int indiceTemperature;
	float t = 0;
	int off = 72;
	myGLCD.print("STEPS", 597, y+72-f*2);//180);//X=(530+(89*3/2)=530+32*2+16=583; y=252-40=212
	//static int i = 0;// numero di righe
    // numero di righe
	//const char  *const Stamp[m_out] = {"MUSH IN","ACID REST","PROTEIN REST","SOSTA UNICA AB","MUSH OUT"};//NomiSteps[Steps]  -> myGLCD.print(NomiSteps[Steps], CENTER, 4);
	for	(int iG_IndexRighe = 0; iG_IndexRighe<3; iG_IndexRighe++)//(/*static int iG_IndexRighe = 0; */iG_IndexRighe<3; iG_IndexRighe++;)
	{
		//static int off = 72;
		T=Tempo[indiceTempo];
		t=gradi[indiceTemperature];
		myGLCD.drawCircle(x,y+f+off,12); 
		myGLCD.print(dastamp[stampo], x+f, y+off);
		myGLCD.printNumI(T, x+(f*9),  y+off);//x=645
		myGLCD.print("min", x+(f*12), y+off);//x=677 ->x=725-(16*2)-16-5=672  y=220
		myGLCD.printNumI(t, x+(f*16), y+off);
		myGLCD.print("C",  x+(f*19), y+off);//X=(800-32-8)=213
		myGLCD.drawCircle(x+(f*19)-4,y+off+2,4);
		off = off + f*2 + 4;				 //off= 0+32+4= 36 -> 36+32+4=72 -> 72+32+4=108 -> 108+32+4=144 -> 144+32+4=180
		stampo++;
		indiceTempo++;
		indiceTemperature++;
	}
	//Serial.print("mTMush_IN_dopo ");
	//Serial.println(mTMush_IN);
	//Serial.println("righe");
}