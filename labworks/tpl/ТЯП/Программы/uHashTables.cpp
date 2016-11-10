//---------------------------------------------------------------------------
#pragma hdrstop
#define UNICODE
#include "uHashTables.h"
#include <stdio.h>
#include <fstream.h>
#include <iomanip.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
FILE * fileText;
ofstream outfile;
ifstream infile;
//---------------------------------------------------------------------------
__fastcall THeap::THeap()
{
	arrFHeapTable.resize(10);
	for (int i = 0; i < arrFHeapTable.size(); i++)
		{
		   arrFHeapTable[i].strFLexicalUnit = "";
		   arrFHeapTable[i].byteFHashTable = 0;
		   arrFHeapTable[i].cardFHashIndex = 0;
		}
	arrDeleted.resize(0);
	cardFFreeItem = 1;
}
//---------------------------------------------------------------------------
__fastcall THeap::~THeap()
{
   arrFHeapTable.resize(0);
   arrDeleted.resize(0);
}
//---------------------------------------------------------------------------
void THeap::Expansion(void)
{
	Cardinal cardVSize = arrFHeapTable.size();
	cardVSize = cardVSize + cardVSize % 10 + 1;
	arrFHeapTable.resize(cardVSize);
}
//---------------------------------------------------------------------------
bool THeap::IsSaved(void) { return boolIsSaved; }
bool THeap::IsLoaded(void) { return boolIsLoaded; }
//---------------------------------------------------------------------------
void THeap::AddLexicalUnit(const AnsiString strALexicalUnit, const Byte byteAHashTable, const Cardinal cardAHashIndex, Cardinal *cardALexicalCode)
{
	Cardinal cardVIndex;

	if(arrDeleted.empty())
	   {
		  cardVIndex = cardFFreeItem;
		  cardFFreeItem++;
		  if(cardFFreeItem > arrFHeapTable.size()*0.9) Expansion();
	   }
	else
	   {
		  cardVIndex = arrDeleted[arrDeleted.size()-1];
		  arrDeleted.resize(arrDeleted.size()-1);
	   }
	arrFHeapTable[cardVIndex].strFLexicalUnit = strALexicalUnit;
	arrFHeapTable[cardVIndex].byteFHashTable  = byteAHashTable;
	arrFHeapTable[cardVIndex].cardFHashIndex  = cardAHashIndex;
	*cardALexicalCode = cardVIndex;
}
//---------------------------------------------------------------------------
void THeap::DeleteLexicalUnit(const Cardinal cardALexicalCode)
{
	Cardinal i;
	if (arrDeleted.empty()) i = 0; else i = arrDeleted.size();
	arrDeleted.resize(i+1);
	arrDeleted[i] = cardALexicalCode;
	arrFHeapTable[cardALexicalCode].strFLexicalUnit = "";
	arrFHeapTable[cardALexicalCode].byteFHashTable = 0;
	arrFHeapTable[cardALexicalCode].cardFHashIndex = 0;
}
//---------------------------------------------------------------------------
void THeap::Save(const Byte byteAFileType)
{
	switch(byteAFileType)
	{
		case TEXT_FILE:
			try
			  {
				 if (arrDeleted.empty()) fprintf(fileText,"%8u\n",0);
				 else
					 {
						fprintf(fileText,"%8u\n",arrDeleted.size());
						for (unsigned int i = 0; i < arrDeleted.size();i++) fprintf(fileText,"%8u",arrDeleted[i]);
						fprintf(fileText,"%\n");
					 }
				 fprintf(fileText,"%8u\n",cardFFreeItem);
				 for (unsigned int i = 1; i < cardFFreeItem; i++)
					{
					   fprintf(fileText,"%s\n",arrPItems[i].strFLexicalUnit);
					   fprintf(fileText,"%4u",arrPItems[i].byteFHashTable);
					   fprintf(fileText,"%8u\n",arrPItems[i].cardFHashIndex);
					}
				 boolIsSaved = True;
			   } catch(...) { boolIsSaved = false; }
			break;

		case STREAM_FILE:
			try
			  {
				 if (arrDeleted.empty()) outfile << setw(8) << 0 << endl;
				 else
					 {
						outfile << setw(8) << arrDeleted.size() << endl;
						for (unsigned int i = 0; i < arrDeleted.size();i++)
							outfile << setw(8) << arrDeleted[i];
						outfile << endl;
					 }
				 outfile << setw(8) << cardFFreeItem << endl;
				 for (unsigned int i = 1; i < cardFFreeItem; i++)
					{
					   outfile << arrPItems[i].strFLexicalUnit.c_str() << endl;
					   outfile << setw(4) << (int)arrPItems[i].byteFHashTable;
					   outfile << setw(8) << (int)arrPItems[i].cardFHashIndex << endl;
					}
				 boolIsSaved = True;

			  } catch(...) { boolIsSaved = false; }
			break;
	}
}
//---------------------------------------------------------------------------
void THeap::Load(const Byte byteAFileType)
{
	Cardinal cardVarrDeletedsSize;  char * s;   char c;   char s1[100];  char * s2;
	Cardinal cardVAssistant;
	vector<char> strVAssistant;

//						  int v; AnsiString a;
	switch(byteAFileType)
	{
		case TEXT_FILE:
			try
			  {
				 fscanf(fileText,"%8u\n",&cardVarrDeletedsSize);
				 if (cardVarrDeletedsSize != 0)
					 {
						arrDeleted.resize(cardVarrDeletedsSize);
						for (unsigned int i = 0; i < cardVarrDeletedsSize;i++) fscanf(fileText,"%8u",arrDeleted[i]);
					 }
				 fscanf(fileText,"%8u",&cardFFreeItem);
				 arrFHeapTable.resize(cardFFreeItem + 1);
				 int k = arrFHeapTable.size();
				 for (unsigned int i = 1; i < cardFFreeItem; i++)
					{
					   c = getc(fileText);      // пропуск перевода строки, т.к. под форматом пропускаются сразу два /n
					   c = getc(fileText); strVAssistant.resize(0);
					   for (int j = 0; c != '\n'; j++)
						 {
						   strVAssistant.resize(j+1);
						   strVAssistant[j] = c;
						   c = getc(fileText);
						 }
					   int nn = strVAssistant.size();
					   s = (char *)(malloc(nn+1)); //strVAssistant.size()));
					   s[nn] = '\0';
					   for (int j = 0; j < nn; j++)
					   s[j] = strVAssistant[j];

//					   AnsiString ss = AnsiString(s);   v = strlen(s);
			//		   arrPItems[i].strFLexicalUnit = AnsiString(s);
					   arrFHeapTable[i].strFLexicalUnit = AnsiString(s);

					   fscanf(fileText,"%4u",&cardVAssistant); //arrPItems[i].byteFHashTable = cardVAssistant;
					   arrFHeapTable[i].byteFHashTable = cardVAssistant;
					   fscanf(fileText,"%8u",&cardVAssistant); //arrPItems[i].cardFHashIndex = cardVAssistant;
					   arrFHeapTable[i].cardFHashIndex = cardVAssistant;
					}
					fscanf(fileText,"%\n");
				 boolIsLoaded = True;
			   } catch(...) { boolIsLoaded = false; }
//			   ShowMessage(IntToStr((int)cardFFreeItem));
			break;

		case STREAM_FILE:
			try
			   {
				   char charWord[255];
				   infile >> setw(8) >> cardVarrDeletedsSize;
				   if (cardVarrDeletedsSize != 0)
					  {
						arrDeleted.resize(cardVarrDeletedsSize);
						for (unsigned int i = 0; i < cardVarrDeletedsSize;i++)
						   infile >> setw(8) >> arrDeleted[i]; // inline >> arrDeleted[i]; ???!
					  }
				   infile >> setw(8) >> cardFFreeItem;
				   arrFHeapTable.resize(cardFFreeItem + 1);
				   for (unsigned int i=1;i<cardFFreeItem;i++)
					  {
						 int t;
						 infile >> setw(255) >> charWord;
						 char* strWrite = (char*)(malloc(strlen(charWord)+1));
						 strWrite[strlen(charWord)+1] = '\0';
						 for(int j=0;j<strlen(charWord);j++)
							 strWrite[j] = charWord[j];
						 THeapItem hItm;
						 hItm.strFLexicalUnit = AnsiString(strWrite);
						 infile >> setw(4) >> t; hItm.byteFHashTable = t;
						 infile >> setw(8) >> t; hItm.cardFHashIndex = t;
						 arrPItems[i] = hItm;
					  }
				   boolIsLoaded = true;
			   } catch(...) { boolIsLoaded = false; }
			break;
	  }
}
//---------------------------------------------------------------------------
THeapItem THeap::GetItem(Cardinal i)
{
   AnsiString s = "GetИндекс кучи вышел за диапазон!"; // + "[" + IntToStr(i) + "," + IntToStr(k);
   if (i >= arrFHeapTable.size())
	  {ShowMessage(s);} //"GetИндекс кучи вышел за диапазон!"+"["+IntToStr(i)+","+IntToStr(arrFHeapTable.size()));}
   else return  arrFHeapTable[i];
}
//---------------------------------------------------------------------------
void THeap::SetItem(Cardinal i,THeapItem NewItem)
{
   if (i >= arrFHeapTable.size()) ShowMessage("SetИндекс кучи вышел за диапазон!");
   else arrFHeapTable[i] = NewItem;
}
//---------------------------------------------------------------------------
Cardinal THashTable::NextPrimeNumber(const Cardinal cardAOldPrimeNumber)
{
	// вычисляет следующее за cardAOldPrimeNumber простое число cardVNextPrimeNumber
	// отстоящее не менее, чем на 10 процентов от cardAOldPrimeNumber
	Cardinal cardVLowerBound, cardVUpperBound, cardVNextPrimeNumber;
	bool boolVIsDivisor;
	cardVNextPrimeNumber = cardAOldPrimeNumber + cardAOldPrimeNumber / 10 + 1;  // увеличиваем на 10 процентов
	if ((cardVNextPrimeNumber % 2) == 0) cardVNextPrimeNumber++;
	// рассматриваем только нечетные числа, т.к. простые среди них
	do {
		  boolVIsDivisor = true; cardVNextPrimeNumber = cardVNextPrimeNumber+2;
		  cardVLowerBound = 3; cardVUpperBound = cardVNextPrimeNumber / 3 + 1; // диапазон делителей
		  while(boolVIsDivisor && (cardVLowerBound < cardVUpperBound))
			{
			  if ((cardVNextPrimeNumber % cardVLowerBound) == 0) boolVIsDivisor = false;
			  else cardVLowerBound = cardVLowerBound + 2;
		    }
	   } while(!boolVIsDivisor);
	return cardVNextPrimeNumber;
}
//------------------------------------------------------------------------------
Cardinal HashFunction(const AnsiString strALexicalUnit)
//суммируем коды символов строки как послед-ть 3-хбайтных чисел
{
	unsigned int h = 0;
	for(int i=1; i<=strALexicalUnit.Length(); i++)
	   {
		   switch(i % 3)
			  {
				  case 1: h = h + strALexicalUnit[i]; break;
				  case 2: h = h + strALexicalUnit[i]*256; break;
				  case 0: h = h + strALexicalUnit[i]*65536; break;
			  }
	   }
	return h;
}
//------------------------------------------------------------------------------
Cardinal HashFunction_crc32(const AnsiString strALexicalUnit)
{
   typedef unsigned long udmcrc32_t;
   const udmcrc32_t crc32tab[256] =
									 {
									  0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,  0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
									  0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,  0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
									  0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,  0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
									  0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,  0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
									  0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,  0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
									  0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,  0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
									  0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,  0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
									  0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,  0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
									  0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,  0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
									  0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,  0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
									  0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,  0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
									  0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,  0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
									  0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,  0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
									  0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,  0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
									  0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,  0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
									  0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,  0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
									  0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,  0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
									  0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,  0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
									  0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,  0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
									  0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,  0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
									  0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,  0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
									  0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,  0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
									  0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,  0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
									  0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,  0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
									  0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,  0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
									  0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,  0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
									  0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,  0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
									  0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,  0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
									  0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,  0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
									  0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,  0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
									  0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,  0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
									  0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,  0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
									};
   #define UDM_CRC32_UPDATE(crc, ch) (crc = (crc >> 8) ^ crc32tab[(crc ^ (ch)) & 0xff])

   char *b = strALexicalUnit.c_str(); int size = strALexicalUnit.Length();
   udmcrc32_t crc= (udmcrc32_t)~0L;
   const char *e;
   for (e= b + size; b < e; ++b)
	  UDM_CRC32_UPDATE(crc, *b) ;
   return (~crc);
}
//------------------------------------------------------------------------------
Cardinal HashFunction_Wainberger(const AnsiString strALexicalUnit)
{
	char *s = strALexicalUnit.c_str(), *p;
	Cardinal h = 0, g;
	for (p = s; *p != '\0'; p++)
		 if (g = (h = (h << 4) + *p) && 0xF0000000)
			 h ^= g >> 24 ^ g;
	return h;
}
//------------------------------------------------------------------------------
Cardinal HashFunction_Wainberger1(const AnsiString strALexicalUnit)
{
   #define BITS_IN_int     ( sizeof(int) * CHAR_BIT )
   #define THREE_QUARTERS  ((int) ((BITS_IN_int * 3) / 4))
   #define ONE_EIGHTH      ((int) (BITS_IN_int / 8))
   #define HIGH_BITS       ( ~((unsigned int)(~0) >> ONE_EIGHTH ))
   char *s = strALexicalUnit.c_str();
   Cardinal h = 0, i;
   for ( h = 0; *s; ++s )
	   {
		 h = ( h << ONE_EIGHTH ) + *s;
		 if (( i = h & HIGH_BITS ) != 0 )
			h = ( h ^ ( i >> THREE_QUARTERS )) & ~HIGH_BITS;
	   }
   return h;
}
//------------------------------------------------------------------------------
Cardinal HashFunction_Elf(const AnsiString strALexicalUnit)
{
	char *s = strALexicalUnit.c_str(), *p;
	Cardinal h = 0, g;
	while (*s)
	{
		h = (h<<4) + *s++;
		if (g = h & 0xF0000000)
			 h ^= g >> 24;
		h &= ~g;
	}
	return h;
}
//------------------------------------------------------------------------------
Cardinal THashTable::ReHashFunction_Line(Cardinal h, const AnsiString strALexicalUnit)
// линейное рехеширование   hi = h (i+1) mod <текущий размер таблицы> , i=1,2,...
{
	if (h == 0) h = arrFHashTable.size() / 3;
	else if (h == 1) h = arrFHashTable.size() * 3 / 4;
	Cardinal i = 1, hi = h;
	bool boolVFinish = false;
	do {
		 if(arrFHashTable[hi] == 0) boolVFinish = true;
		 else
			if(objFHeap->arrPItems[arrFHashTable[hi]].strFLexicalUnit == strALexicalUnit)
			   boolVFinish = true;
			else
				{
				 i++;
				 hi = (h - 1) * i % (arrFHashTable.size() - 1) + 1;
				}
	   } while(!boolVFinish);
//	ShowMessage(IntToStr((int)i) + "   " + IntToStr((int)hi));
	return hi;
}
//------------------------------------------------------------------------------
void THashTable::HashIndex(const AnsiString strALexicalUnit) {
	// вычисление Hash - индекса строки strALexicalUnit
	// результат заносится в cardFHashIndex
	unsigned int h;
	bool boolVFinish;
//	h = HashFunction(strALexicalUnit) % (arrFHashTable.size() - 1) + 1; // от 1 до <текущий размер таблицы>
//	h = HashFunction_crc32(strALexicalUnit) % (arrFHashTable.size() - 1);
//	h = HashFunction_Wainberger(strALexicalUnit) % (arrFHashTable.size() - 1);
	h = HashFunction_Wainberger1(strALexicalUnit) % (arrFHashTable.size() - 1);
//	h = HashFunction_Elf(strALexicalUnit) % (arrFHashTable.size() - 1);
	cardFHashIndex = ReHashFunction_Line(h, strALexicalUnit);
//	ShowMessage(IntToStr((int)i));
}
//------------------------------------------------------------------------------
void THashTable::ReHashing()
{
	bool IsUserData;
	Cardinal i, j;
	Cardinal OldSize = arrFHashTable.size();
	vector <Cardinal> cardarrVHashTableImage;
	vector <void*>  arrVUserTableImage;
	IsUserData = !arrFUserTable.empty();
	cardarrVHashTableImage.resize(OldSize);
	if(IsUserData) arrVUserTableImage.resize(OldSize);
	for(i=1; i < OldSize; i++)
	  {
 		cardarrVHashTableImage[i] = arrFHashTable[i];
		if(IsUserData)
		   {
			  void * V = arrFUserTable[i];
			  arrVUserTableImage[i] = V;
		   }
	  }
/*
	for(i=1; i<OldSize; i++)
	{
		Cardinal C = cardarrVHashTableImage[i];
		void * V;
		if(IsUserData)
		   {
			 V =  arrVUserTableImage[i];
		   }
	}
*/
	arrFHashTable.resize(0);
	if(IsUserData) arrFUserTable.resize(0);
//  cardFCurrentPrimeNumber содержит новый размер таблицы
	arrFHashTable.resize(cardFCurrentPrimeNumber+1);
	if(IsUserData) arrFUserTable.resize(cardFCurrentPrimeNumber+1);
	for(i=1; i < OldSize; i++)
	   {
		  if(cardarrVHashTableImage[i])
			{
			  j = cardarrVHashTableImage[i];    // место в куче
			  HashIndex(objFHeap->arrPItems[j].strFLexicalUnit);
			  arrFHashTable[cardFHashIndex] = j;
			  if(IsUserData)
				 {
				   void * V = arrVUserTableImage[i];
				   arrFUserTable[cardFHashIndex] = V;
				 }
			  THeapItem H; H.strFLexicalUnit = objFHeap->arrPItems[j].strFLexicalUnit;
						   H.byteFHashTable = objFHeap->arrPItems[j].byteFHashTable;
						   H.cardFHashIndex = cardFHashIndex;
              objFHeap->arrPItems[j] = H;
			  Cardinal C = objFHeap->arrPItems[j].cardFHashIndex;
			}
	   }
/*
	   for(i=1; i<cardFCurrentPrimeNumber+1; i++)
		 {
			Cardinal C = arrFHashTable[i];
			String S = objFHeap->arrPItems[C].strFLexicalUnit;
			Cardinal C1 = objFHeap->arrPItems[C].cardFHashIndex;
			void * V;
			if(IsUserData)
			  {
				V =  arrFUserTable[i];
			  }
			 V=V;
		  }
*/
   cardarrVHashTableImage.resize(0);
   if(IsUserData) arrVUserTableImage.resize(0);
}
//------------------------------------------------------------------------------
void THashTable::Expansion()
{
   cardFCurrentPrimeNumber = NextPrimeNumber(cardFCurrentPrimeNumber);
   ReHashing();
}
//------------------------------------------------------------------------------
bool THashTable::IsSaved(void) { return boolFIsSaved; }
bool THashTable::IsLoaded(void) { return boolFIsLoaded; }
//------------------------------------------------------------------------------
void* THashTable::GetUserPointer(Cardinal cardILexicalCode)
{
   if (objFHeap->arrPItems[cardILexicalCode].cardFHashIndex >= cardPTableSize)
	  {ShowMessage("Индекс пользовательского массива вышел за диапазон!");return NULL;}
   else
	  {
/*		  for (Cardinal i = 1; i < arrFUserTable.size(); i++)
		  {
				 Byte B = objFHeap->arrPItems[i].byteFHashTable;
				 String S = objFHeap->arrPItems[i].strFLexicalUnit;
				 Cardinal C = objFHeap->arrPItems[i].cardFHashIndex;
				 void * V = arrFUserTable[objFHeap->arrPItems[i].cardFHashIndex];
				 V=V;
		  }
*/		 return arrFUserTable[objFHeap->arrPItems[cardILexicalCode].cardFHashIndex];
      }
}
//------------------------------------------------------------------------------
void THashTable::SetUserPointer(Cardinal cardILexicalCode, void * ptrANewPoint)
{
   if (objFHeap->arrPItems[cardILexicalCode].cardFHashIndex >= cardPTableSize)
	  ShowMessage("Индекс пользовательского массива вышел за диапазон!");
   else
	  arrFUserTable[objFHeap->arrPItems[cardILexicalCode].cardFHashIndex] = ptrANewPoint;
}
//------------------------------------------------------------------------------
void  THashTable::SetUserTable()
{
   arrFUserTable.resize(cardPTableSize);
}
//------------------------------------------------------------------------------
bool THashTable::SearchLexicalUnit(const AnsiString strAlexicalUnit, Cardinal * cardALexicalCode)
{
	HashIndex(strAlexicalUnit);
	if(arrFHashTable[cardFHashIndex] == 0) return false;
	else
	   {
		   *cardALexicalCode = arrFHashTable[cardFHashIndex];
		   return true;
	   }
}
//------------------------------------------------------------------------------
bool THashTable::AddLexicalUnit(const AnsiString strAlexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode)
{
	HashIndex(strAlexicalUnit);
	if(arrFHashTable[cardFHashIndex])
	  {
		 *cardALexicalCode = arrFHashTable[cardFHashIndex];
		 return true;
	  }
	else
	  {
		 if((cardFItemReserve + 2) > (cardPTableSize * 0.9))
		   {
			 Expansion();
/*	bool IsUserData = !arrFUserTable.empty();
	for(Cardinal i=1; i<cardFCurrentPrimeNumber+1; i++)
	{
		Cardinal C = arrFHashTable[i];
		void * V;
		if(IsUserData)
		   {
			 V =  arrFUserTable[i];
		   }
		 V=V;
	}
*/
			 HashIndex(strAlexicalUnit);
		   }
		 objFHeap->AddLexicalUnit(strAlexicalUnit, byteATable, cardFHashIndex, &arrFHashTable[cardFHashIndex]);
		 *cardALexicalCode = arrFHashTable[cardFHashIndex];
		 cardFItemReserve++;
		 return false;
	  }
}
//------------------------------------------------------------------------------
void THashTable::DeleteLexicalUnit(const AnsiString strAlexicalUnit)
{
	HashIndex(strAlexicalUnit);
	if(arrFHashTable[cardFHashIndex] != 0)
	{
		if(!arrFUserTable.empty())
		{
			if(arrFUserTable[cardFHashIndex] != NULL) ShowMessage("Удаление из таблицы связанного данного");
			else
			{
				objFHeap->DeleteLexicalUnit(arrFHashTable[cardFHashIndex]);
				arrFHashTable[cardFHashIndex] = 0;
				cardFItemReserve--;
				ReHashing();
			}
		}
		else
		{
			objFHeap->DeleteLexicalUnit(arrFHashTable[cardFHashIndex]);
			arrFHashTable[cardFHashIndex] = 0;
			cardFItemReserve--;
			ReHashing();
		}
	}
}
//------------------------------------------------------------------------------
void THashTable::DeleteLexicalCode(const unsigned int cardALexicalCode) {
	unsigned int VHashIndex;

	VHashIndex = objFHeap->arrPItems[cardALexicalCode].cardFHashIndex;
	if(arrFHashTable[VHashIndex])
		if(arrFUserTable.size())
			if(arrFUserTable[VHashIndex]) ShowMessage("Удаление из таблицы связанного данного");
			else {
				objFHeap->DeleteLexicalUnit(cardALexicalCode);
				arrFHashTable[VHashIndex] = 0;
				cardFItemReserve--;
				ReHashing();
			}
		else {
			objFHeap->DeleteLexicalUnit(cardALexicalCode);
			arrFHashTable[VHashIndex] = 0;
			cardFItemReserve--;
			ReHashing();
		}
}
//------------------------------------------------------------------------------
void THashTable::Save(const Byte byteAFileType)
{
	switch(byteAFileType)
	{
		case TEXT_FILE:
			try
			  {
				fprintf(fileText,"%8u\n",cardPTableSize);
				fprintf(fileText,"%8u\n",cardFItemReserve);
				for(Cardinal i = 1; i < cardPTableSize; i++)
					 fprintf(fileText,"%8u",arrFHashTable[i]);
				fprintf(fileText,"\n");
				boolFIsSaved = true;
			  } catch(...) { boolFIsSaved = false; }
			break;

		case STREAM_FILE:
			try {
				outfile << setw(8) << cardPTableSize << endl;
				outfile << setw(8) << cardFItemReserve << endl;
				for(Cardinal i = 1; i < cardPTableSize; i++)
					outfile << setw(8) << arrFHashTable[i];
				outfile << endl;
				boolFIsSaved = true;
			} catch(...) { boolFIsSaved = false; }
			break;
	}
}
//------------------------------------------------------------------------------
void THashTable::Load(const Byte byteAFileType)
{
	switch(byteAFileType)
	{
		case TEXT_FILE:
			try
			  {
				Cardinal cardFHashTableSize;
				fscanf(fileText,"%8u\n",&cardFHashTableSize);
				arrFHashTable.resize(cardFHashTableSize);
				fscanf(fileText,"%8u\n",&cardFItemReserve);
				for(Cardinal i = 1; i < cardPTableSize; i++)
//				{
				   fscanf(fileText,"%8u",&arrFHashTable[i]);
//				#ifdef _DEBUG
//				   Cardinal k =  arrFHashTable[i];
//				#endif
//				}
				fscanf(fileText,"\n");
				boolFIsLoaded = true;
			  } catch(...) { boolFIsLoaded = false; }
			break;

		case STREAM_FILE:
			try
			   {
				  Cardinal cardFHashTableSize;
				  infile >> setw(8) >> cardFHashTableSize;
				  arrFHashTable.resize(cardFHashTableSize);
				  infile >> setw(8) >> cardFItemReserve;
				  for(unsigned int i = 1;i<cardPTableSize;i++)
//					 {
					   infile >> setw(8) >> arrFHashTable[i];
//					#ifdef _DEBUG
//						Cardinal k =  arrFHashTable[i];
//					#endif
//					 }
				  boolFIsLoaded = true;
			   }
			catch(...) { boolFIsLoaded = false; }
			break;
	}
}
//------------------------------------------------------------------------------
void THashTable::GetLexicalUnitList(TStringList *slstALexicalUnits)
{
	bool boolVSortedOld;
	unsigned int i;

	slstALexicalUnits->BeginUpdate();
	boolVSortedOld = slstALexicalUnits->Sorted;
	slstALexicalUnits->Sorted = false;
	try
	   {
		 for(i=1;i<cardPTableSize;i++)
		 if(arrFHashTable[i])
		 slstALexicalUnits->Add(objFHeap->arrPItems[arrFHashTable[i]].strFLexicalUnit);
	   }
	catch (...) {  	}
	slstALexicalUnits->EndUpdate();
	slstALexicalUnits->Sorted = boolVSortedOld;
}
//------------------------------------------------------------------------------
THashTable::THashTable(THeap *objAHeap)
{
	arrFHashTable.resize(8);
	objFHeap = (THeap*)objAHeap;
	cardFCurrentPrimeNumber = 7;
	cardFItemReserve = 0;
}
__fastcall THashTable::~THashTable()
{
   arrFHashTable.resize(0);
}
//------------------------------------------------------------------------------
bool THashTableList::IsSaved(void) { return boolFIsSaved; }
//------------------------------------------------------------------------------
bool THashTableList::IsLoaded(void) { return boolFIsLoaded; }
//------------------------------------------------------------------------------
Byte THashTableList::GetTable(Cardinal cardALexicalCode) { return objFHeap->arrPItems[cardALexicalCode].byteFHashTable; }
//------------------------------------------------------------------------------
void * THashTableList::GetUserData(Cardinal cardILexicalCode)
{
	if((0 < cardILexicalCode) && (cardILexicalCode < this->objFHeap->cardPFreeItem))
	   {
		 Byte T = Tables[cardILexicalCode];
		 THashTable * H = arrFHashTableList[Tables[cardILexicalCode]];
		 void * V = H->arrPUserTable[cardILexicalCode];
		 void * U = arrFHashTableList[Tables[cardILexicalCode]]->arrPUserTable[cardILexicalCode];
		 return arrFHashTableList[Tables[cardILexicalCode]]->arrPUserTable[cardILexicalCode];
	   }
	else
	   {
		 ShowMessage("Неверно задан лексический код");
		 return NULL;
	   }
}
//------------------------------------------------------------------------------
void  THashTableList::SetUserData(Cardinal cardILexicalCode, void * ptrAUserData)
{
   if ((0 < cardILexicalCode) && (cardILexicalCode < objFHeap->cardPFreeItem))
	  {
		 THashTable * hT = arrFHashTableList[Tables[cardILexicalCode]];
 //		 int size = hT->cardPTableSize;
		 if (hT->cardPTableSize > 0)
			arrFHashTableList[Tables[cardILexicalCode]]->arrPUserTable[cardILexicalCode] = ptrAUserData;
		 else ShowMessage(L"Попытка записи адреса в несозданный массив указателей!");
	  }
   else ShowMessage(L"Неверно задан лексический код!");
}
//------------------------------------------------------------------------------
AnsiString THashTableList::GetLexicalUnit(Cardinal cardALexicalCode)
{
	if((0 < cardALexicalCode) && (cardALexicalCode < objFHeap->cardPFreeItem)) return objFHeap->arrPItems[cardALexicalCode].strFLexicalUnit;
	else
		 {
		   ShowMessage("Неверно задан лексический код");
		   return "";
	     }
}
//------------------------------------------------------------------------------
bool THashTableList::SearchLexicalUnit(const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode)
		{ return arrFHashTableList[byteATable]->SearchLexicalUnit(strALexicalUnit, cardALexicalCode); }
//------------------------------------------------------------------------------
bool THashTableList::AddLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable, Cardinal * cardALexicalCode)
{
	bool B = arrFHashTableList[byteATable]->AddLexicalUnit(strALexicalUnit, byteATable, cardALexicalCode);
/*
	if (strALexicalUnit == ">")
{
	for (Cardinal i = 1; i < 8; i++)
	 {
		String S = LexicalUnits[i];
		void * V = UserTables[i];
		V=V;
	 }
}
*/	return B; //arrFHashTableList[byteATable]->AddLexicalUnit(strALexicalUnit, byteATable, cardALexicalCode);
}
//------------------------------------------------------------------------------
void THashTableList::DeleteLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable)
{
  arrFHashTableList[byteATable]->DeleteLexicalUnit(strALexicalUnit);
}
//------------------------------------------------------------------------------
void THashTableList::DeleteLexicalCode(const unsigned int cardALexicalCode) {
	unsigned short T = objFHeap->arrPItems[cardALexicalCode].byteFHashTable;
	arrFHashTableList[T]->DeleteLexicalCode(cardALexicalCode);
}
//------------------------------------------------------------------------------
void THashTableList::SetUserTable(const Byte byteATable)
	  { arrFHashTableList[byteATable]->SetUserTable(); }
//------------------------------------------------------------------------------
void THashTableList::GetLexicalUnitsList(const Byte ATable, TStringList *slstALexicalUnits)
{
	arrFHashTableList[ATable]->GetLexicalUnitList(slstALexicalUnits);
}
//------------------------------------------------------------------------------
void THashTableList::Expantion()
{
	arrFHashTableList.resize(bytePTableSize + 1);
	arrFHashTableList[bytePTableSize - 1] = new THashTable(objFHeap);
}
//------------------------------------------------------------------------------
void THashTableList::Save(const Byte byteAFileType, const AnsiString strAFileName)
{
//				ShowMessage(IntToStr((int)this->objFHeap->cardPFreeItem));
	switch(byteAFileType)
	{
		case TEXT_FILE:
			try
			  {
				fileText = fopen(strAFileName.c_str(), "wt");     // wt - запись в текстовый файл
				fprintf(fileText,"%4u\n",bytePTableSize);
				objFHeap->Save(TEXT_FILE);
				for(Byte i = 1; i < bytePTableSize; i++) arrFHashTableList[i]->Save(TEXT_FILE);
				boolFIsSaved = true;
				fclose(fileText);
			  } catch(...) { boolFIsSaved = false; }
			break;

		case STREAM_FILE:
			try
			  {
				outfile.open(strAFileName.c_str());
				if(!outfile)
				   {
					 ShowMessage("Файл не удается создать");
					 return;
				   }
				 outfile << setw(4) << bytePTableSize << endl;
				 objFHeap->Save(STREAM_FILE);
				 for(Byte i = 1; i < bytePTableSize; i++)
					 arrFHashTableList[i]->Save(STREAM_FILE);
				 boolFIsSaved = true;
				 outfile.close();
			  } catch(...) { boolFIsSaved = false; }
			break;
	}
}
//------------------------------------------------------------------------------
void THashTableList::Load(const Byte byteAFileType, const AnsiString strAFileName)
{

	switch(byteAFileType)
	 {
		case TEXT_FILE:
			try
			  {
				Byte byteFTableCount;
				fileText = fopen(strAFileName.c_str(), "rt");     // rt - только для чтения из текстового файла
				fscanf(fileText,"%4u\n",&byteFTableCount);
				objFHeap->Load(TEXT_FILE);
				for(Byte i = 1; i < bytePTableSize; i++)
					arrFHashTableList[i]->Load(TEXT_FILE);
				fclose(fileText);
				boolFIsLoaded = true;
			  } catch(...) { ShowMessage("Ошибка при восстановлении из файла хеш-таблиц!"); boolFIsLoaded = false; }
			break;
		case STREAM_FILE:
			try {
				Byte byteFTableCount;
				infile.open(strAFileName.c_str());
				infile >> byteFTableCount;
				objFHeap->Load(STREAM_FILE);
				for(int i=1;i< bytePTableSize;i++) arrFHashTableList[i]->Load(STREAM_FILE);
				infile.close();
				boolFIsLoaded = true;
			} catch (...) {	boolFIsLoaded = false; }
		break;
	 }
}
//------------------------------------------------------------------------------
Byte THashTableList::GetTableSize(void) { return arrFHashTableList.size(); }
//------------------------------------------------------------------------------
THashTableList::THashTableList(Byte byteATableCount)
{
	arrFHashTableList.resize(byteATableCount+1);
	objFHeap = new THeap();
	for(int i=1;i<=byteATableCount;i++) arrFHashTableList[i] = new THashTable(objFHeap);
}
//------------------------------------------------------------------------------
THashTableList::THashTableList(const Byte byteAFileType, const AnsiString strAFileName)
{
	Byte byteVTableSize;
	switch (byteAFileType)
	{
		case TEXT_FILE:
			   try
				   {
					 fileText = fopen(strAFileName.c_str(), "rt");     // rt - Єюы№ъю фы  ўЄхэш  шч ЄхъёЄютюую Їрщыр
					 fscanf(fileText,"%4u\n",&byteVTableSize);
					 fclose(fileText);
					 arrFHashTableList.resize(byteVTableSize);
					 objFHeap = new THeap();
					 for(int i = 1;i < bytePTableSize;i++)
						arrFHashTableList[i] = new THashTable(objFHeap);
					 Load(byteAFileType, strAFileName);
					 boolFIsLoaded = true;
				   }
			   catch(...)
				   {
					  ShowMessage("Ошибка при восстановлении из файла хеш-таблиц!");
					  boolFIsLoaded = false;
				   }
			   break;

		case STREAM_FILE:
			try
			   {
				  infile.open(strAFileName.c_str());
				  infile >> setw(4) >> byteVTableSize;
				  infile.close();
				  arrFHashTableList.resize(byteVTableSize);
				  objFHeap = new THeap();
				  for(int i = 1;i < bytePTableSize;i++)
					arrFHashTableList[i] = new THashTable(objFHeap);
				  Load(byteAFileType, strAFileName);
				  boolFIsLoaded = true;
			   }
			catch(...) { ShowMessage("Ошибка при восстановлении из потока хеш-таблиц!"); boolFIsLoaded = false; }
			break;
	}
}
//------------------------------------------------------------------------------
__fastcall THashTableList::~THashTableList()
{
	for (Byte i= 1; i < bytePTableSize; i++) arrFHashTableList[i]->~THashTable();
	arrFHashTableList.resize(0);
	objFHeap->~THeap();
}
//------------------------------------------------------------------------------
#pragma package(smart_init)
