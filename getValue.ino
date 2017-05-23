/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 * divide una stringa in 3 prima e dopo il separatore, inserendo le 3 semistringhe in 3 nuove stringhe
 */
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) 
    {
        if (data.charAt(i) == separator || i == maxIndex) 
        {
            found++;
            strIndex[0] = strIndex[1] + 1;  //parte dall'inizio strIndex[0] = [-1] + 1 = 0
			strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
