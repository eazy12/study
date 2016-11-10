//---------------------------------------------------------------------------
//         МАССИВ ХЕШ-ТАБЛИЦ С ДИНАМИЧЕСКИ ИЗМЕНЯЮЩИМСЯ РАЗМЕРОМ
//                          НАЗНАЧЕНИЕ ПРОГРАММЫ
// Программа предназначена для поддержки табличного метода хранения и поиска
// слов. Пользователь может создать произвольное количество таблиц слов, имеющих
// номера 1, ... , N.
//                         СВЕДЕНИЯ О РЕАЛИЗАЦИИ
//  1. Используется единый массив (класс) THeap (куча), в который помещаются
//     слова в порядке поступления. По мере заполнении массив автоматически
//     увеличивается.
//  2. С массивом "куча" связан массив THashTableList, включающий  любое число
//     тематических массивов (объектов) класса THashTable, содержащих номера
//     строк в массиве куча. Каждый тематический массив имеет оригинальный номер.
//     Место слова в тематическом массиве вычисляется методом хеширования,
//     но физически слово располагается в куче.
//  3. Алгоритм поступления слова:
//       а) вычисляется место слова в тематическом массиве методом хеширо-
//          вания;
//       б) слово записывается в первую свободную ячейку в массив куча;
//       в) в вычисленную ячейку тематического массива записывается номер
//          ячейки со словом в массиве куча;
//       г) вместе со словом в массив куча записывается номер таблицы и
//          хеш -индекс слова.
//  4. Традиционно значение каждого помещаемого в таблицу слова кодируется
//     в виде пары-токена (Nтаблицы, Nячейки_таблицы). В этой программе токен
//     моделируетсяс помощью понятия лексический код cardALexicalCode, который
//     представляет собой место слова в массиве куча. Лексический код несет в
//     себе всю информацию о хранимом в таблицах слове.
//   5. Главным классом является класс THashTableList, в котором сосредоточены
//      все доступные пользователю программы свойства и методы
//                        ИСПОЛЬЗОВАНИЕ ПРОГРАММЫ
//    1.  Конструкторы и деструктор
//      Первоначально система хеш - таблиц создается конструктором:
//   		      THashTableList(Byte byteATableCount);
//      где byteATableCount - количество создаваемых хеш - таблиц.
//      Имеется еще один конструктор, который позволяется создать систему таблиц
//      по предварительно сохранненной в файле:
//		THashTableList(const Byte byteAFileType, const AnsiString strAFileName);
//      где byteAFileType - тип файла (см.далее), strAFileName - имя файла.
//
//      Удаляются ранее созданные таблицы с помощью деструктора:
//          ~THashTableList();
//      В процессе работы можно к существующей системе таблиц добавить
//          еще одну с помощью метода:  void Expantion();
//     2. После того, как таблицы созданы, можно узнать их количество
//        c помощью свойства:     __property Byte bytePTableCount;
//     3. Созданную во время работы программы систему таблиц можно
//         сохранить в файле с помощью метода:
//        void Save(const Byte byteAFileType, const AnsiString strAFileName);
//      Ранее сохраненную в файле систему таблиц можно восстановить:
//        void Load(const Byte byteAFileType, const AnsiString strAFileName);
//            Параметры byteAFileType - TEXT_FILE - текстовый файл в стиле С
//                                      STREAM_FILE - поток в стиле С++
//                      strAFileName - имя физического файла с путями, по умол-
//         чанию файл создается в одной папке с exe-файлом
//      Для контроля сохранения и воостановления таблиц используются:
//          __property bool boolPIsSaved;
//                     Сохранение таблиц в файле прошло успешно
//  		__property bool boolPIsLoaded;
//                     Восстановление таблиц из файла прошло успешно
//
//     4. Традиционно значение каждого помещаемого в таблицу слова кодируется
//   в виде токена (Nтаблицы, Nячейки). В этой программе токен моделируется
//   с помощью понятия Cardinal LexicalCode. LexicalCode несет в себе всю
//   информацию (Nтаблицы, Nячейки). Для этого нужно использовать свойства:
//     __property Byte Tables[Cardinal cardILexicalCode]
//             Возвращает номер таблицы
//     __property AnsiString LexicalUnits[Cardinal cardILexicalCode]
//             Возвращает значение strLexicalUnit слова
// Максксимальное значение лексического кода можно узнать с помощью свойства
//     __property Cardinal cardPMaxLexicalCode
//   5. Для работы с таблицами используются методы:
//   bool SearchLexicalUnit(const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
//   bool AddLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
//   void DeleteLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable);
//   void DeleteLexicalCode(const Cardinal cardALexicalCode);
//            Параметры strALexicalUnit - значение слова,
//                      byteATable - номер таблицы,
//                      cardALexicalCode - лексический код слова.
//    6. С каждой хеш - таблицей можно связать массив указателей типа void *
//          Первоначально массив указателей создается методом:
//          void  SetUserTable(const Byte byteATable);
//              Параметр byteATable - номер таблицы, при которой создается
//                                массив указателей
//    Для каждого слова работа с указателем осуществляется с помощью свойства:
//      __property void* UserTables[Cardinal cardILexicalCode]
//              Параметр cardILexicalCode - лексический код слова
//      Пример записи значения в пользовательскую таблицу хеш-таблицы htl при известном
//			   лексическом коде  LexCode
//                       TPoint * p = new TPoint();
//                       p->X = 1; p->Y = 2;
//                       TPoint **q1 = &p1;
//                       htl->UserTables[LexCode] = (void*)(*q1);
//      Пример извлечения записи из пользовательской таблицы
//          	TPoint * p2 = (TPoint *)(htl->UserTables[LexCode]);
//     Из каждой таблицы ATable можно прочитать коллекцию записанных в нее
//        слов. Коллекция возвращается в slstALexicalUnits
//      void GetLexicalUnitsList(const Byte ATable, TStringList *slstALexicalUnits);

//---------------------------------------------------------------------------
#ifndef uHashTablesH
#define uHashTablesH

#include <vector.h>
#include <vcl.h>
#define STREAM_FILE 0x00001000
#define TEXT_FILE   0x00001001
struct THeapItem
{
	AnsiString	 strFLexicalUnit;
	Byte byteFHashTable;
	Cardinal cardFHashIndex;
};

class THeap: public TObject
{
	private:
		vector<THeapItem>	  arrFHeapTable;
		vector<Cardinal>	  arrDeleted;
		Cardinal			  cardFFreeItem;
		bool				  boolIsSaved;
		bool 				  boolIsLoaded;
		void				  Expansion(void);
		bool				  IsSaved(void);
		bool				  IsLoaded(void);
		THeapItem GetItem(Cardinal i);
		void SetItem(Cardinal i,THeapItem New);
	public:
		__fastcall THeap();
		__fastcall ~THeap();
		__property bool boolPIsSaved  = {read = IsSaved};
		__property bool boolPIsLoaded = {read = IsLoaded};
		__property THeapItem arrPItems[Cardinal i]={read=GetItem,write=SetItem};
		__property Cardinal cardPFreeItem={read=cardFFreeItem};
		void AddLexicalUnit(const AnsiString strALexicalUnit, const Byte byteAHashTable, const Cardinal cardAHashIndex, Cardinal *cardALexicalCode);
		void DeleteLexicalUnit(const Cardinal cardALexicalCode);
		void Save(const Byte byteAFileType);
		void Load(const Byte byteAFileType);

// отладка
		void HeapTableView(TStringList * sList)
		{
			for(int i=0;i<this->arrFHeapTable.size();i++)
				 sList->Add(this->arrFHeapTable[i].strFLexicalUnit);
//			ShowMessage(IntToStr((int)this->cardPFreePosition));
        }

};

class THashTable: public TObject
{
	private:
		vector <Cardinal> arrFHashTable;
		Cardinal	 	 cardFCurrentPrimeNumber;
		Cardinal	 	 cardFItemReserve;
		Cardinal	 	 cardFHashIndex;
		vector <void*>	 arrFUserTable;
		THeap			 *objFHeap;
		bool			 boolFIsSaved;
		bool			 boolFIsLoaded;
		void			 HashIndex(const AnsiString strALexicalUnit);
		void			 ReHashing();
		void			 Expansion();
		bool			 IsSaved(void);
		bool			 IsLoaded(void);
		void*			 GetUserPointer(Cardinal cardILexicalCode);
		void			 SetUserPointer(Cardinal cardILexicalCode, void * ptrANewPoint);
		Cardinal GetTableSize() {return arrFHashTable.size();};
		Cardinal NextPrimeNumber(const Cardinal cardAOldPrimeNumber);
		Cardinal ReHashFunction_Line(Cardinal h, const AnsiString strALexicalUnit);
//		Cardinal crc32(const AnsiString strALexicalUnit);
	public:
		THashTable(THeap *objAHeap);
		__fastcall ~THashTable();
		__property void * arrPUserTable[Cardinal cardILexicalCode] = { read = GetUserPointer, write = SetUserPointer };
		__property Cardinal cardPTableSize = {read = GetTableSize};
		void  SetUserTable();
		bool  SearchLexicalUnit(const AnsiString strALexicalUnit, Cardinal *cardALexicalCode);
		bool  AddLexicalUnit(const AnsiString strAlexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
		void  DeleteLexicalUnit(const AnsiString strALexicalUnit);
		void  DeleteLexicalCode(const Cardinal cardALexicalCode);
		void  Save(const Byte byteAFileType);
		void  Load(const Byte byteAFileType);
		void  GetLexicalUnitList(TStringList *slstALexicalUnits);

// отладка
		void TableToStringList(TStringList * sList)
		{
			int k = this->arrFHashTable.size();
			for(int i=0;i<this->arrFHashTable.size();i++)
				{
					k = this->arrFHashTable[i];
					if ( k == 0) { sList->Add(""); }
					else
					   {
						  sList->Add(IntToStr(k) + "    " + objFHeap->arrPItems[k].strFLexicalUnit);
					   };
				};
		 }
};

class THashTableList : public TObject
{
	private:
		vector <THashTable*> arrFHashTableList;
		bool		 		   boolFIsSaved;
		bool		 		   boolFIsLoaded;
		THeap	   	 	      *objFHeap;
//		Byte        		   byteFTableCount;
		bool		 	       IsSaved(void);
		bool		 		   IsLoaded(void);
		Cardinal     	       GetMaxLexicalCode(void);
		Byte        		   GetTable(Cardinal cardALexicalCode);
		void*	 	 		   GetUserData(Cardinal cardILexicalCode);
		void		 		   SetUserData(Cardinal cardILexicalCode, void* ptrAUserData);
//		void                   SetUserDataSubsidiary(Cardinal cardALexicalCode, void** ptrAUserData);
		AnsiString	  		   GetLexicalUnit(Cardinal cardALexicalCode);
		Byte        		   GetTableSize(void);
		Byte	   InputTableCount(const AnsiString strAFileName);
	public:
		THashTableList(Byte byteATableCount);
		THashTableList(const Byte byteAFileType, const AnsiString strAFileName);
		__fastcall ~THashTableList();
		__property Byte bytePTableSize = { read = GetTableSize, default = false };
		__property bool boolPIsSaved = { read = IsSaved, default = false };
		__property bool boolPIsLoaded = { read = IsLoaded, default = false };
		__property Cardinal cardPMaxLexicalCode = { read = GetMaxLexicalCode };
		__property Byte Tables[Cardinal cardILexicalCode] = { read = GetTable };
		__property void* UserTables[Cardinal cardILexicalCode] = { read = GetUserData, write = SetUserData };
		__property AnsiString LexicalUnits[Cardinal cardILexicalCode] = { read = GetLexicalUnit };
		bool	   SearchLexicalUnit(const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
		bool	   AddLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
		void       DeleteLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable);
		void  	   DeleteLexicalCode(const Cardinal cardALexicalCode);
		void	   SetUserTable(const Byte byteATable);
		void 	   GetLexicalUnitsList(const Byte ATable, TStringList *slstALexicalUnits);
		void	   Expantion();
		void       Save(const Byte byteAFileType, const AnsiString strAFileName);
		void	   Load(const Byte byteAFileType, const AnsiString strAFileName);
// отладка
		void HeapTableView(TStringList * sList)
		{
			objFHeap->HeapTableView(sList);
		}

		 void TableToStringList(Byte Table, TStringList * sList )
		 {
				arrFHashTableList[Table]->TableToStringList(sList);
//				ShowMessage(IntToStr((int)(this->objFHeap->cardPFreePosition)));
		 }
};

#endif
