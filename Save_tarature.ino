///*
// * Simone Volpara
// * 18/03/2017
// * See http://www.volpara-hb.it/
// */
void save_TARATURE()
{

			if (!myFile.open("Dati/TARATURE.TXT", O_RDWR | O_CREAT))//| O_APPEND))//O_RDWR | O_CREAT| O_APPEND))//O_APPEND | O_CREAT | O_READ))///*O_WRITE*/O_APPEND | O_CREAT | O_AT_END))
			{
				sd.errorHalt("opening tarature.txt for write failed");
				myGLCD.print("____ERROR____",CENTER,CENTER);
			}
			myFile.print("AMushMin=");//1
			myFile.println(AMushMin); //1
			myFile.print("AMushMax=");//2
			myFile.println(AMushMax); //2
			myFile.print("tMushMin=");//3
			myFile.println(tMushMin); //3
			myFile.print("tMushMax=");//4
			myFile.println(tMushMax); //4
			myFile.print("ASpargeMin=");//5
			myFile.println(ASpargeMin); //5
			myFile.print("ASpargeMax=");//6
			myFile.println(ASpargeMax); //6
			myFile.print("tSpargeMin=");//7
			myFile.println(tSpargeMin); //7
			myFile.print("tSpargeMax=");//8
			myFile.println(tSpargeMax); //8
			myFile.close();
}