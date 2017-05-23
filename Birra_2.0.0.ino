
/*
 * Simone Volpara
 * 18/03/2017
 * See http://www.volpara-hb.it/
 */
#if defined(__AVR__)
  #define imagedatatype  unsigned int
#elif defined(__PIC32MX__)
  #define imagedatatype  unsigned short
#elif defined(__arm__)
  #define imagedatatype  unsigned short
#endif
//#include <avr/io.h>
//#include <wdt.h>




//Gestione Display e Pulsanti touch
#include <UTFT.h>									//Libreria gestione display
#include <URTouch.h>								//Libreria gestione touch
#include <UTFT_Buttons.h>							//Libreria gestion pulsanti touch
#include <stdio.h>									/* printf, fgets */
#include <stdlib.h>									/* atoi */
//Gestione SD_CARD
#include <OneWire.h>
#include <SdFat.h>									//Libreria gestione SD card
SdFat sd;
//SdFat_h sd;
SdFile myFile;
SdFile myFileC;
const int chipSelect = 53;
//
String stringa_Root;
int lap = 0;
int indiceMax = 1;
String File_Root[2];
String file;
int numero_file = 0;
bool first = false;
bool firstloop = false;
int indice_stringa = 0;
//

UTFT myGLCD(CTE50CPLD,25,26,27,28);					//Settaggi per il display e shield    //Set the pins for display and shield
//UTFT myGLCD(EHOUSE50,38,39,40,ms41);				//IF USE SSD1963 ELETROHOUSE
URTouch        myTouch(6,5,4,3,2);					//Settaggi per il touch screen e shield    //Set the pins for touch screen and shield
UTFT_Buttons   myButtons(&myGLCD, &myTouch);
//Aggiungo i font 
extern uint8_t Grotesk16x32[];						//Impostiamo i caratteri che useremo  //Declare which fonts we will be using
extern uint8_t Grotesk24x48[];						//Impostiamo i caratteri che useremo  //Declare which fonts we will be using
//Aggiungo le immagini
//extern unsigned short etichetta[0x7E90];		    //nome  e dimensione dell'array per il file da visualizzare
extern unsigned short Etichetta_102_97[0x26A6];
extern unsigned short StartGreyp[0x26AC];
extern unsigned short Tino_89_85[0x1D8D];
extern unsigned short Cronometro_168_185[0x7968];
extern unsigned short AllarmGrey121_121[0x3931];
extern unsigned short StartedFillPot[0x1104];
extern unsigned short start_dis75_33[0x9AB];
//extern unsigned short Pulsante_plus[0x1104];
extern unsigned short FrecciaPiatta[0x1104];
extern unsigned short Pulsante_minus_piccolo[0x441];
//Aggiungo le immagini per i pulsanti
extern imagedatatype StartGrey[];					//immagine per pulsante Start
extern imagedatatype NextStepGrey[];				//immagine per pulsante Next Step
extern imagedatatype MenuGrey[];					//immagine per pulsante Menu
//extern imagedatatype LitriStart[];					//immagine per pulsante Start Contalitri
//extern imagedatatype LitriStop[];					//immagine per pulsante Stop Contalitri
extern imagedatatype LitriReset[];					//immagine per pulsante Reset Contalitri
extern imagedatatype AllarmGrey[];					//immagine per pulsante Allarme, funge anche da icona per allarme attivo
extern imagedatatype minus5_53_51[];
extern imagedatatype plus5_53_51[];
//extern imagedatatype Pulsante_plus[];
//extern imagedatatype Pulsante_minus_piccolo[];
//elenco pulsanti
int iG_primo, iG_Menu, iG_Start, iG_nextStep, iG_StatoAllarme, iG_AllLuppolo, iG_Pulstante_1, iG_Pulstante_2, iG_Pulstante_3, iG_Pulstante_4, iG_Pulstante_5, iG_Back, iG_plus5, iG_minus5,iG_StopUP,iG_Stop/*, iG_plus, iG_minus*/, iG_Pressed_button; // iG_ResetFillPot//iG_StartFillPotSparg
//iG_StartBoil , iG_StopFillPot , iG_StartFillPot ,

//Tastierino numerico
//extern uint8_t BigFont[];
//unsigned long valore = 0;
unsigned long ul_Tmush = 0;
bool TmushSetted = false;
bool setTmush = false;
int x, y;
char stCurrent[20]=""; //numero di caratteri massimo 20, posso scrivere al massimo 20 caratteri
int stCurrentLen=0;    //contattore del numero di caratteri
unsigned long count;
bool coutfinish = false;
char stLast[20]="";    //
String NOME_RICETTA = "SNOME_RICETTA";
char charbuf[50];
String file1;
String file2;


//INGRESSI ANALOGICI=================================================================================================================
// LETTURE ANALOGICHE PER ARRAY
#define tmush_NUMREADINGS 256						//dimensione array 20 valori da leggere
#define tsparge_NUMREADINGS 256						//dimensione array 20 valori da leggere
//array tmush========================
int readingsMush[tmush_NUMREADINGS];				//readingMush[] è l'array per A0 (mush) tmush_NUMREADINGS la dimensione dell'array
int indice_mush        = 0;							//Indice dell'array per il mush
float total_mush       = 0;							//Il valore totale delle letture dell'array
float average_mush     = 0;							//La media delle letture dell'array
float Pt1000_Mush_real = 0;							//Valore analogico reale (non filtrato)
//array sparge=======================
int readingsSparge[tsparge_NUMREADINGS];			//readingSparge[] è l'array per A2 (sparge) tsparge_NUMREADINGS la dimensione dell'array
int indice_sparge       = 0;						//Indice dell'array per lo sparge
float total_sparge       = 0;						//Il valore totale delle letture dell'array
float average_sparge     = 0;						//La media delle letture dell'array
float Pt1000_Sparge_real = 0;						//Valore analogico reale (non filtrato)
//====================================================================================================================================
//DICHIARAZIONE VARIABILI GLOBALI====
  long Pt1000_Mush           = 0;
  long Pt1000_Sparge         = 0;
  float tmush                 = 0;
  float tmush_old             = 0;
  float tsparge               = 0;
  float tsparge_old           = 0;
//======================================
  bool G_btaratura         = false;				//mi serve per fare la taratura
  bool G_btaraturaREALE    = false;
//taratura PT1000 Mush===============
  float AMushMin=2568.0;	//2544.0;				//temperatura minima
  float AMushMax=2844.0;	//2720.0;				//temperatura massima
  float AMushMinOld=0.0;	//2544.0;				//temperatura minima
  float AMushMaxOld=0.0;	//2720.0;				//temperatura massima
  float tMushMin=46.0;		//50.0;					//valore analogico minimo
  float tMushMax=80.0;		//70.0;					//valore analogico massimo  
//taratura PT1000 Sparge=============
  float ASpargeMin=2555.0;	//2549.0;				//temperatura minima   2551
  float ASpargeMax=2838.0;	//2720.0;				//temperatura massima
  float ASpargeMinOld=0.0;	//2549.0;				//temperatura minima   2551
  float ASpargeMaxOld=0.0;
  float tSpargeMin=46.0;	//50.0;					//valore analogico minimo
  float tSpargeMax=80.0;	//70.0;					//valore analogico massimo
//================================================================
//temperature degli steps in °C======
  float tMush_Pre      =  45.00;
  float tMush_IN       =  68.00;				//impasto omogeneo a 40°C temperatura di mushIN
  float tAcid_Rest     =  48.00;				//Acid rest a 40°
  float tProtein_Rest  =  52.00;
  float tB_amilasi     =  60.00;
  float tA_amilasi     =  70.00;
  float tS_unica_AB    =  68.00;				//la tempertura varia in base al fatto se si vuole preferire la fase a o b amilasi se si fa questa non si fanno le 2 precedenti
  float tMush_OUT      =  78.00;				//si porta a 78°C per rendere l'impasto meno denso
  float tSpargeIN      =  68.00;
  float offset_t       =   2.00;				//isteresi per la temperatura
  //float f_tSparge      =  60.00; 
//PARAMETRI STEPS====================
  int conf_par_B_amilasi     = 0;					//se a 0 non fa lo step se a 1 fa lo step
  int conf_par_A_Aminasi     = 0;					//se a 0 non fa lo step se a 1 fa lo step
  int conf_par_S_unica_AB    = 1;					//se a 0 non fa lo step se a 1 fa lo step se a 1 allora conf_par_B_amilasi a 0 e conf_par_A_Aminasi a 0
//TEMPI STEPS========================
  unsigned long TCorrezioneSosta= 0;
  unsigned long TMush_IN        = 0;// 
  unsigned long TAcid_Rest      = 0;//
  unsigned long TProtein_Rest   = 0;//
  unsigned long TB_amilasi      = 0;//
  unsigned long TA_amilasi      = 0;//
  unsigned long TS_unica_AB     = 0;//   
  unsigned long TMush_OUT       = 0;//
  unsigned long TBoil           = 0;//
  unsigned long Tluppoli1       = 0;
  unsigned long Tluppoli2       = 0;
  unsigned long Tluppoli3       = 0;
  unsigned long tempo_trascorso = 0;//
  bool bConvers_millisec_min = false;
  bool pot_full = true;
  
  unsigned long mTCorrezioneSosta=  5;
  unsigned long mTMush_IN        =  1; //durata del mush in minuti prima era in millisecondi TMush_IN orava viene convertita ad inizio ciclo
  unsigned long mTAcid_Rest      =  6;
  unsigned long mTProtein_Rest   =  3;
  unsigned long mTB_amilasi      =  4;
  unsigned long mTA_amilasi      =  5;
  unsigned long mTS_unica_AB     =  2;
  unsigned long mTMush_OUT       =  3;
  unsigned long mTBoil           =  7;
  unsigned long mTluppoli1       =  2;
  unsigned long mTluppoli2       =  2;
  unsigned long mTluppoli3       =  2;
  unsigned long lG_TempoRampaAcidRest  =   0;
  unsigned long lG_TempoRampaMush_IN   =   0;
  unsigned long lG_TempoRampaS_unica_AB = 0;
  unsigned long lG_TempoRampaMushOUT = 0;
  long lG_TcorrezioneMushout           =   0;
//==================================================
//DICHIARAZIONE VARIABILI GLOBALI====
int let_analogici                     = 0;
int stato_pulsante_reset              = 0;
int G_pos_puls_start                  = 0;
//bool firstlap							= false;
bool Serial_Tempo_ciclo				  = true;
bool bG_ContalitriPot				  = false;
bool luppolo1inserito                 = false;
bool luppolo3inserito                 = false;
bool luppolo2inserito                 = false;
bool allarmeluppolo1                  = false;
bool allarmeluppolo2                  = false;
bool allarmeluppolo3                  = false;
bool bG_Started                    = false;  //Serve per vedere se il sistema è avviato, la pagina iniziale è stata stampata
bool Gb_pulsante_next_ready        = false;
bool tempo_trascorso_scaduto       = false;
bool G_pos_puls_next               = false;
bool G_pos_puls_freccia            = false;
bool G_puls_next_premuto           = false;
bool bStato_SpargeOK               = false;
bool bStatoAcceso                  = false;  
bool bG_StatoAllarme               = false;  // stato allarme suona o no
bool bStato_puls                   = false;
bool btMush_raggiunta    = false;  // t° Mush_IN raggiunta
bool bstato_puls_next    = false;  // stato pulsante next step
bool G_bDebug            = false;
bool G_bDebug_touch      = false;
bool G_bDebug_SD         = false; 
bool G_puls_premuto      = false;
bool G_puls_start_premuto= false;  // stato pulsante di start
bool Gb_puls_next_premuto = false;
bool G_start_rilasciato  = true ;
bool G_next_rilasciato   = true ;
bool G_bStampato         = false;
bool bS_main             = false;
bool G_puls_start_gia_premuto = false;
bool G_puls_next_gia_premuto =  false;
bool bG_no220vac = false;
bool bG_ComeBackMenuold = false;
bool bG_recipeLoaded = false;
bool bG_prima_volta = false;
bool bG_ritornoMenu = false;
bool bL_AvvioLoaded				 = false;
bool bL_AvviotLoaded			 = false;
bool bL_MainLoaded			     = false;
bool bL_MaintLoaded				 = false;
bool bL_MenuLoaded				 = false;
bool bL_Menut_Loaded			 = false;
bool bL_TestIOtLoaded			 = false;
bool bL_TestIOLoaded			 = false;
bool bL_TaratureLoaded			 = false;
bool bL_TaraturetLoaded			 = false;
bool bG_RicetteLoaded			 = false;
bool bG_RicettetLoaded			 = false;
//int iG_IndexRighe = 0;
//======================
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
//timer per ritardi==================
long int millisecondi;
unsigned long		 ulG_timeBoil			 =	   0;		//prendo il tempo per il boil
unsigned long		 ulG_timerBoil			 =	   0;		//salvo
unsigned long        timer                   =     0;
static unsigned long lG_cycle_time           =     0;       //Prendo il tempo del ciclo   //Get time for cycle
static unsigned long timerStart              =  5000;       //Tempo di attesa nella schermata iniziale
static unsigned long Tmush                   =     0;
static unsigned long durata_ciclo            =     0;
static unsigned long durata                  =     0;
//static unsigned long attesa                =     0;
//static unsigned long tciclo                =   100;
//======================================================
    int Ore      = 0;
    int Minuti   = 0;
    int Secondi  = 0;
    int Secondi2 = 0;

bool bG_Parametri_Steps = true;
//GESTIONE PAGINE
bool bG_pgMainSeted = false;
//========================================================

static bool bFirstRound = true;
bool bG_StartFillPotSpargePrinted = false;
bool bStatoCambiato;
bool bG_StepEnd = false;
bool bG_Buttons_drawed = false;

//Variabili per la gestione dei contalitri e degli stati per riempire le pentole

float cont                      = 0;     //Variabile per il conteggio degli impulsi del contalitri
long contatoreglobale          = 0;     //Variabile per il conteggio degli impulsi del contalitri
float sulG_Litri_impulso        = 0.002139963;//0.002039394;//1;  //Variabile per il rapporto degli impulsi a litro
float sulG_Litri                = 0;     //Variabile conteggio per i litri che stanno passando nel contalitri
float fG_Litri_in_Mush          = 0;     //Salva il valore dei litri caricati alla fine dentro la pentola del Mush
float fG_Litri_in_Sparge        = 0;     //Salva il valore dei litri caricati alla fine dentro la pentola dello Sparge
float fG_LitriOffset            = 2;     //Serve per avvisare quanti litri prima del target fare suonare l'allarme per il raggiungimento dei litri desiderati
float fG_LitriMush              = 56;    //Serve per impostare quanti litri si devono mettere dentro alla pentola del Mush in futuro saranno calcolati automaticamente dalla ricetta
float fG_LitriSparge            = 46;    //Serve per impostare quanti litri si devono mettere dentro alla pentola dello Sparge in futuro saranno calcolati automaticamente dalla ricetta
float fG_Litri_in_Ferment       = 0;
float fG_Litri_in_Boil          = 0;

static unsigned long attesa     = 0;
static unsigned long tciclo     = 100;
unsigned long lG_During_cycle_time = 0;

bool ulL_timer_NoNscaduto = true;
unsigned long ulL_timeCampioni = 0;
unsigned long ulL_tempoCampionatura = 60000; //un minuto

//static bool bL_nextStepPrinted  = false;//variabile locale per stampare solo una volta
bool bG_inserireluppolo1		= false;
bool bG_inserireluppolo2		= false;
bool bG_inserireluppolo3		= false;
bool Luppolo1terminato			= false;
bool Luppolo2terminato			= false;
bool Luppolo3terminato			= false;
bool bG_Boil_terminato			= false;
bool bG_AllarmLuppolo1Reset		= false;
bool bG_AllarmLuppolo2Reset		= false;
bool bG_AllarmLuppolo3Reset		= false;
bool bG_StartBoil               = false;
bool bG_InizioRiempire          = false;  //
bool bG_InizioRiempireSparge    = false;
bool bG_GoNextStep              = false;
bool bG_pgSeted                 = false;  //
bool bG_FillingPotMush          = false;  //
bool bG_FillPotMush             = false;
bool bG_FillingPotSparge        = false;  //
bool bG_ComeBackMenu            = false;  //
bool bL_PulsantiLitriDisegnati  = true;
bool bG_LitriRaggiuntiMush      = false;
bool bG_LitriRaggiuntiSparge    = false;
bool iG_Pressed_iG_StartFirst   = false;
bool iG_StatoAllarmePressed     = false;
bool bG_PulsNextEnable          = false;
bool bG_terminato               = false;
bool bG_bypassCicalinOn         = false;
bool bG_CicalinoOff             = false;
bool sendToSD                   = true;
bool bVal_iStato_220            = false;
bool iG_AllLuppoloPressed       = false;
bool bG_AllLuppolo              = false;
bool bG_NextStep				= false;
bool bG_potMushFull             = false;
bool bG_potSpargeFull           = false;
bool bG_TaratureMashtLoaded     = false;
bool bG_TaratureMashLoaded	    = false;
bool bG_TaratureSpargetLoaded	= false;
bool bG_TaratureSpargeLoaded	= false;
//DEBUG
bool bG_ButtonDebug		        = false;
bool bG_pagetDebug				= false;
bool bG_pageDebug				= false;
bool bG_StartOK					= false;
bool iG_mixerGO					= false;
bool Stato_K1 = 0;
bool Stato_K2 = 0;
bool bG_stopUP = false;
char name[13];
String fileName;
char result[13];
unsigned long resetmillis =  0;
int contare = 0;
//Allarme

bool bG_Allarm = false;
//enum per motore
  typedef enum{
	Motore=0,
    Motore_fermo,
    Motore_avanti,
    Motore_inversione_da_avanti,
    Motore_indietro,
    Motore_inversione_da_indietro,
    Motore_errore,
  }Stati_Motore; 
  Stati_Motore mixer;

//Switch case pagine page)
typedef enum{
    Avvio=0,
    Main,
    Menu,
    TestIO,
    Tarature,
	TaratureMash,
	TaratureSparge,
    Ricette,
	pagineUltimo
  }pagine;
  pagine page;
  
typedef enum{
	Avviot=0,
	Maint,
	Menut,
	TestIOt,
	Taraturet,
	TaratureMasht,
	TaratureSparget,
	Ricettet,
	Miscelatoret,
	Whirlpoolt,
	}paginet;
	paginet pgt;
////Switch case fillpot (pot)//ancora da inserire
typedef enum{
    potAvvio=0,
    FillPotMush,
    FillPotSparge,
    FullPots,
    potAttesa,
    BoilPot,
    FermentationPot,
    Fine,
  }fillpot;
  
  fillpot pot;
  
//enumerazione steps======
  typedef enum{
    sComincio=0,
    sAVVIO,
    sMush_Pre,
    sMush_IN,
    sAcid_Rest,
    sProtein_Rest,
    sB_amilasi,
    sA_amilasi,
    sS_unica_AB,
    sMush_OUT,
    sBoil,
    sGotoFermentation,
    sRiavvio,
    sfinito,
  }steps;
  steps Steps;
  const char *const NomiSteps[sfinito] = {"PORTARE LA TEMPERATURA AL VALORE DESIDERATO","FILL POTS","PRE MASH","MASH IN","ACID REST","PROTEIN REST","B AMINASI","A AMINASI", "SOSTA UNICA AB","MASH OUT","BOIL","OUT TO FERMENTATION","CI VEDIAMO ALLA PROSSIMA COTTA"};
  typedef enum{
	  M_in=0,
	  a_rest,
	  p_rest,
	  ab_unica,
	  m_out,
	  ultimo
	  }stamp;
	  stamp Stamp;
	  /*
		const char *const dastamp[ultimo] = {"Mu. in:","So. AB:","M. out:"};//,"Acid r:","Prot r:","So. AB:","M. out:"};//NomiSteps[Steps]
		int stampo;
	 
		unsigned long Tempo []={mTMush_IN,mTS_unica_AB,mTMush_OUT}; //mTAcid_Rest,mTProtein_Rest,mTS_unica_AB,mTMush_OUT};
		unsigned long indiceTempo;
		unsigned long T = 0;
		float gradi []={tMush_IN,tS_unica_AB,tMush_OUT}; //tAcid_Rest,tProtein_Rest,tS_unica_AB,tMush_OUT};
		int indiceTemperature;
		float t = 0;
	 */
	 //static stamp stamp_old = M_in;
//===========================
//#define Righe 0;
  //readingMush[] è l'array per A0 (mush) tmush_NUMREADINGS la dimensione dell'array
	
//Stamp[i] = Pt1000_Mush_real;

//___________________________________________________
ArduinoOutStream cout(Serial);
String stringa = "";
String miastringa;
String tagRiga;
String valore;

String prova_Strigna [] = { 
	"Temperatura_Pre_Mush"		,
	"Temperatura_Mush_IN"		,
	"Temperatura_Sosta_Unica"	,
	"Temperatura_Mush_Out"		,
	"Temperatura_Sparge"		,
	"Temperatura_Offset"		,
	"Tempo_Sosta_Mush_IN"		,
	"Tempo_Sosta_Unica"			,
	"Tempo_Mush_Out"			,
	"Tempo_Boil"				,
	"Tempo_Luppolo1"			,
	"Tempo_Luppolo2"			,
	"Tempo_Luppolo3"
};

char nomeTarature[13];

typedef enum {
	PARAM_TYPE_FLOAT = 0,
	PARAM_TYPE_ULONG = 1,
	PARAM_TYPE_LONG  = 2,
	PARAM_TYPE_INT   = 3,
	PARAM_TYPE_BOOL  = 4,
	PARAM_TYPE_LAST_ITEM
} eParamTypes;

typedef struct {
	String sTag;
	eParamTypes eParamType;
	void *pParam;
} ParamTable_str;

//array di strutture {stringa,tipo parametro, & "indirizzo" della variabile  };
const ParamTable_str ParamTable[] = {
	{ "Temperatura_Pre_Mush"	, PARAM_TYPE_FLOAT,		& tMush_Pre			},
	{ "Temperatura_Mush_IN"		, PARAM_TYPE_FLOAT,		& tMush_IN			},
	{ "Temperatura_Sosta_Unica" , PARAM_TYPE_FLOAT,		& tS_unica_AB		},
	{ "Temperatura_Mush_Out"    , PARAM_TYPE_FLOAT,     & tMush_OUT			},
	{ "Temperatura_Sparge"      , PARAM_TYPE_FLOAT,     & tSpargeIN			},
	{ "Temperatura_Offset"      , PARAM_TYPE_FLOAT,     & offset_t			},
	{ "Tempo_Sosta_Mush_IN"     , PARAM_TYPE_ULONG,     & mTMush_IN			},
	{ "Tempo_Sosta_Unica"		, PARAM_TYPE_ULONG,     & mTS_unica_AB		},
	{ "Tempo_Mush_Out"          , PARAM_TYPE_ULONG,     & mTMush_OUT		},
	{ "Tempo_Boil"				, PARAM_TYPE_ULONG,     & mTBoil			},
	{ "Tempo_Luppolo1"			, PARAM_TYPE_ULONG,     & mTluppoli1		},
	{ "Tempo_Luppolo2"			, PARAM_TYPE_ULONG,     & mTluppoli2		},
	{ "Tempo_Luppolo3"			, PARAM_TYPE_ULONG,     & mTluppoli3		},
	
};
//=============================0
ArduinoOutStream coutTarature(Serial);
String stringaTarature = "";
String miastringaTarature;
String tagRigaTarature;
String valoreTarature;

String prova_StrignaTarature [] = { "AMushMin"		,
	"AMushMax"										,
	"tMushMin"										,
	"tMushMax"										,
	"ASpargeMin"									,
	"ASpargeMax"									,
	"tSpargeMin"									,
	"tSpargeMax"
};

char nome[13];

typedef enum {
	TARATURE_TYPE_FLOAT = 0,
	TARATURE_TYPE_ULONG = 1,
	TARATURE_TYPE_LONG  = 2,
	TARATURE_TYPE_INT   = 3,
	TARATURE_TYPE_BOOL  = 4,
	TARATURE_TYPE_LAST_ITEM
} eTaratureTypes;

typedef struct {
	String sTagTarature;
	eParamTypes eTaratureType;
	void *pTarature;
} TaratureTable_str;

const TaratureTable_str TaratureTable[] = {
	{"AMushMin"					, PARAM_TYPE_FLOAT,		& AMushMin			},
	{"AMushMax"					, PARAM_TYPE_FLOAT,		& AMushMax			},
	{"tMushMin"					, PARAM_TYPE_FLOAT,		& tMushMin			},
	{"tMushMax"					, PARAM_TYPE_FLOAT,		& tMushMax			},
	{"ASpargeMin"				, PARAM_TYPE_FLOAT,		& ASpargeMin		},
	{"ASpargeMax"				, PARAM_TYPE_FLOAT,		& ASpargeMax		},
	{"tSpargeMin"				, PARAM_TYPE_FLOAT,		& tSpargeMin		},
	{"tSpargeMax"				, PARAM_TYPE_FLOAT,		& tSpargeMax		},
};
//___________________________________________________

static steps Steps_old = sAVVIO;

//Pinout
//Uscite
int Oallarme   =   9; //uscita per commandare il cicalino
int Omixer_K1  =  10;
int Omixer_K2  =  11;
int iO_Travaso_Mash = 12;


//======ingressi======//
/*
* A0 pt1000 mush
* A2 pt1000 sparge
* 8 contalitri
*/
int Istato220vac = 12;
OneWire  ds(5);

 volatile byte RPMcontatoreglobale;
 float rpm;
 float litri_min;
 unsigned long timeold;
 unsigned long timerpm;
 bool bG_PimogiroPerPagine = true;
 bool firstlaps = true;
 float offset = 0; 
 //=============================
	 
void setup() 
{
  pinMode(Omixer_K1, OUTPUT);
  pinMode(Omixer_K2, OUTPUT);
  
  //______________________________________________________
/*
NOME_RICETTA = "tarature.txt";
NOME_RICETTA.toCharArray(charbuf,50);
testGetline();
*/
  //______________________________________________________
  //Serial.begin(9600);
  //while (!Serial) {}  // wait for Leonardo
//#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {}
  // pstr stores strings in flash to save RAM
  //cout << pstr("Type any character to start\n");
  //while (Serial.read() <= 0) {}
  //delay(400);  // catch Due reset problem

  //if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();
  // run the example
  //watchdogEnable(2000);
  //watchdogSetup();
  if(bG_ContalitriPot)
  {
	attachInterrupt(8,ContaLitri,RISING); //ogni volta che il segnale passa da basso a alto 
  }
  analogReadResolution(12); //setto gli ingressi analigici a 12 bit (se si usa un arduino diverso dal due commentare questa riga
	
	iG_Pressed_button = -1; //serve per ...
	
	iG_Menu               = myButtons.addButton( 325,  414, 150,  66, MenuGrey,BUTTON_NO_BORDER);
	iG_Start              = myButtons.addButton( 0,  414, 150,  66, StartGrey, BUTTON_NO_BORDER);
	iG_nextStep           = myButtons.addButton( 650,  414, 150,  66, NextStepGrey, BUTTON_NO_BORDER);
	iG_StatoAllarme       = myButtons.addButton( 664,  50, 121, 121, AllarmGrey, BUTTON_NO_BORDER);
	//iG_StatoAllarme       = myButtons.addButton( 664,  254, 121, 121, AllarmGrey, BUTTON_NO_BORDER);//
	iG_AllLuppolo         = myButtons.addButton( 650,  414, 150,  66, NextStepGrey, BUTTON_NO_BORDER);
	iG_Pulstante_1        = myButtons.addButton( 0,  44, 66,  66, LitriReset, BUTTON_NO_BORDER);//74
	iG_Pulstante_2        = myButtons.addButton( 0, 112, 66,  66, LitriReset, BUTTON_NO_BORDER);//142
	iG_Pulstante_3        = myButtons.addButton( 0, 180, 66,  66, LitriReset, BUTTON_NO_BORDER);//210
	iG_Pulstante_4        = myButtons.addButton( 0, 248, 66,  66, LitriReset, BUTTON_NO_BORDER);//210
	iG_Pulstante_5        = myButtons.addButton( 0, 316, 66,  66, LitriReset, BUTTON_NO_BORDER);//210
	iG_Back               = myButtons.addButton( 0, 414, 66,  66, LitriReset, BUTTON_NO_BORDER);
	iG_plus5			  = myButtons.addButton( 101+57, 47+ 27, 53,  51, plus5_53_51, BUTTON_NO_BORDER);
	iG_minus5		      = myButtons.addButton( 101+57, 47+123, 53,  51, minus5_53_51, BUTTON_NO_BORDER);
	//iG_plus				  = myButtons.addButton(400, 44, 66, 66, Pulsante_plus, BUTTON_NO_BORDER);
	//iG_minus			  = myButtons.addButton(400, 44, 66, 66, Pulsante_minus_piccolo, BUTTON_NO_BORDER);
	iG_StopUP            = myButtons.addButton( 151, 414, 66,  66, LitriReset);
	iG_Stop              = myButtons.addButton( 218, 414, 66,  66, LitriReset);
	myButtons.drawButtons();

  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setFont(Grotesk16x32);
  myGLCD.clrScr();
  myGLCD.fillScr(0,0,0);
  myGLCD.setBrightness(16);
  /*
  tastierino
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButtons();
  */
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);
  myButtons.setTextFont(Grotesk16x32);
  Serial.begin(115200); 
  delay(400);
if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();
  
if (!myFile.open("Dati/birra.txt",  O_CREAT | O_READ))//O_APPEND | O_CREAT | O_AT_END)) 
{
	sd.errorHalt("opening birra.txt for write failed");
	myGLCD.print("____ERROR____",CENTER,CENTER);
}


	myFile.println("birra cotta zizua");
	myFile.close();

		if (!myFileC.open("Dati/Campioni.txt", O_RDWR | O_CREAT | O_AT_END))//O_APPEND | O_CREAT | O_READ))//O_RDWR | O_CREAT | O_APPEND))//O_APPEND | O_CREAT | | O_CREAT))//O_APPEND | O_CREAT | O_READ))//O_RDWR | O_CREAT | O_APPEND))//O_APPEND | O_CREAT | O_AT_END))
		{
			sd.errorHalt("opening Campioni.txt for create failed");
			myGLCD.print("____ERROR____",CENTER,CENTER);
		}
			myFileC.close();
   RPMcontatoreglobale = 0;
   rpm = 0;
   litri_min = 0;
   timeold = 0;
   //Read_Param();
   
   digitalWrite (Omixer_K1, LOW);
   digitalWrite (Omixer_K2, LOW);
   listLfn(sd.vwd());  //chiamo la funzione che legge i file presenti dentro la sd
   Pages ();//chiamo la funzione che imposta le parti che non cambiano per ogni pagnia
   GetTarature();
}

void loop() 
{
	lG_cycle_time = millis();
	Readinputs ();
	Visu ();
	BirraSteps ();
	Allarms ();
	Out ();
			
		//	Serial.print("lG_During_cycle_time ");
		//	Serial.println(lG_During_cycle_time);
			
//===

//===
	//save_sd();
/*
	lG_During_cycle_time = millis()-lG_cycle_time;

	if(lG_During_cycle_time<tciclo)
	{
		attesa=tciclo-lG_During_cycle_time;	
		lG_During_cycle_time =	tciclo+attesa;
		delay(attesa); 
	}
		//if(Serial_Tempo_ciclo)
		//{
		//Serial.print("tempo di ciclo____");
		Serial.println(lG_During_cycle_time);
		//}
*/		
	/*
	if(bG_ContalitriPot)
	{
		//RPMcontatoreglobale
		timerpm = millis() - timeold;
		RPMcontatoreglobale = contatoreglobale;
		if(timerpm >= 1000)//viene aggiornato ogni ...
		{
			//Update RPM every 20 counts, increase this for better RPM resolution,
			//decrease for faster update
			rpm = (30*1000)/((millis() - timerpm)*RPMcontatoreglobale);//rpm impulsi al minuto
			litri_min=rpm*0.002139963;
			timeold = millis();
			timerpm = 0;
		}
	}
	*/
}