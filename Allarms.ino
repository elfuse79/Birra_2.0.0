void Allarms ()
{
	if( 
         bG_StepEnd                 ==  true                                      ||
        //(bG_LitriRaggiuntiMush      ==  true  && bG_FillingPotMush     ==  true)  ||
        //(bG_LitriRaggiuntiSparge    ==  true  && bG_FillingPotSparge   ==  true)  ||
        tempo_trascorso_scaduto     ==  true                                      ||
        ( allarmeluppolo1 ||  allarmeluppolo2 ||  allarmeluppolo3 )                                  
      )
    { 
        Serial.println("ALLARM");
		bG_Allarm = true;
        if( allarmeluppolo1 ||  allarmeluppolo2 ||  allarmeluppolo3 )
        {
          bG_AllLuppolo = true;
		  Serial.println("ALLARM_LUPPOLO");
		  if(allarmeluppolo1)
		  {
			Serial.println("allarmeluppolo1");
		  }
		  if(allarmeluppolo2)
		  {
			  Serial.println("allarmeluppolo2");
		  }
		  if(allarmeluppolo3)
		  {
			  Serial.println("allarmeluppolo3");
		  }
        }
        else
		{
			bG_AllLuppolo = false;
			//Serial.println("ALLARM_LUPPOLO_OFF");
		}
        if( ((iG_StatoAllarmePressed)  &&  (bG_Allarm)) ||  ((iG_AllLuppoloPressed)  &&  (bG_AllLuppolo)) )
        {
            digitalWrite(Oallarme, LOW);
        }
        else
        {
            digitalWrite(Oallarme, HIGH);
        }
    }
	/*
	else if(bG_Boil_terminato == true)
	{
		bG_Allarm = false;
	}
	*/
    else
    {
        bG_Allarm = false;
        bG_AllLuppolo = false;
        iG_AllLuppoloPressed = false;
        iG_StatoAllarmePressed = false;
        digitalWrite(Oallarme, LOW);
    }
	/*
    //
    if (  (Steps != sMush_Pre) || (Steps != sMush_OUT ) || (bVal_iStato_220 == true) )
    {
      bG_no220vac = true;
    }
    else
    {
      bG_no220vac = false;
    }
	*/
} //chiude il loop
