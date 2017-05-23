/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
void save_sd()
{
		if(sendToSD == true)
		{
			if (!myFile.open("Dati/birra.txt", O_RDWR | O_CREAT))//| O_APPEND))//O_APPEND | O_CREAT | O_READ))//O_RDWR | O_CREAT | O_APPEND))//O_APPEND | O_CREAT | O_AT_END))
			{
				sd.errorHalt("opening birra.txt for write failed");
				myGLCD.print("____ERROR____",CENTER,CENTER);
			}
			//Serial.print("Writing to test.txt...");
			myFile.println("Save_toSD");
			//myFile.open("birra.txt", O_RDWR | O_AT_END);// myFile.open("birra.txt", O_RDWR | O_CREAT | O_AT_END);
			/*myFile.print(fG_Litri_in_Mush);
			myFile.println(", (56) litri mush");
			myFile.print(lG_TempoRampaAcidRest);
			myFile.println(", tempo rampa Acid Rest");
			*/
			myFile.print(lG_TempoRampaMush_IN);
			myFile.println(", tempo rampa Mush_IN");
			myFile.print(mTMush_IN);
			myFile.println(", tempo Mush_IN");
	
			myFile.print(lG_TempoRampaS_unica_AB);
			myFile.println(", tempo rampa Sosta UNICA");
			myFile.print(mTS_unica_AB);
			myFile.println(", tempo Sosta UNICA");
			
			myFile.print(lG_TempoRampaMushOUT);
			myFile.println(", tempo rampa Mush OUT");
			myFile.print(mTMush_OUT);
			myFile.println(", tempo Mush_OUT");
			
			// close the file:
			myFile.close();
			//Serial.println("done.");
			sendToSD = false;
		}
}