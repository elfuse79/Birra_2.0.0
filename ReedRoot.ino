/*
 * Simone Volpara
 * 08/04/2017
 * See http://www.volpara-hb.it/
 * gestire meglio la lettura dell'elenco dei file, non devo leggere il nome della sotto cartella, al momento funziona solo se la sottocartella è aggiunta dopo i file delle ricette
 */
void listLfn(SdBaseFile* dirFile)
{
  uint8_t offset[] = {1, 3, 5, 7, 9, 14, 16, 18, 20, 22, 24, 28, 30};
  char name[13];
  char lfn[131];
  bool haveLong = false;
  dir_t dir;
  uint8_t i;
  uint8_t lfnIn = 130;
  uint8_t ndir;
  uint8_t sum;
  uint8_t test;

  dirFile->rewind();
  while (dirFile->read(&dir, 32) == 32)
  {
	if (DIR_IS_LONG_NAME(&dir))
    {
      if (!haveLong)
      {
		if ((dir.name[0] & 0XE0) != 0X40) continue;
        ndir = dir.name[0] & 0X1F;
        test = dir.creationTimeTenths;
        haveLong = true;
        lfnIn = 130;
        lfn[lfnIn] = 0;
      }
      else if (dir.name[0] != --ndir || test != dir.creationTimeTenths)
      {
		haveLong = false;
        continue;
      }
      char *p = (char*)&dir;
      if (lfnIn > 0)
      {
		lfnIn -= 13;
        for (i = 0; i < 13; i++)
        {
          lfn[lfnIn + i] = p[offset[i]];
        }
      }
    }
    else if (DIR_IS_FILE_OR_SUBDIR(&dir)
    && dir.name[0] != DIR_NAME_DELETED
    && dir.name[0] != DIR_NAME_FREE)
    {
      SdFile::dirName(dir, name);
       String str(name);
       stringa_Root = str;
       File_Root[indice_stringa] = stringa_Root;
       indice_stringa++;
       numero_file++;
	   Serial.print("numero_file ");
	   Serial.println(numero_file);
    }
    else     
    {
	  if (dir.name[0] == DIR_NAME_FREE) return;
      haveLong = false;
    }
  }
  //numero_file da usare per sapere quanti file sono presenti dentro alla sd ed utilizzaro per abbianre i pulsanti all'inteno della schermata
}
