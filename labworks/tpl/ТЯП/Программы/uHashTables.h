//---------------------------------------------------------------------------
//         ������ ���-������ � ����������� ������������ ��������
//                          ���������� ���������
// ��������� ������������� ��� ��������� ���������� ������ �������� � ������
// ����. ������������ ����� ������� ������������ ���������� ������ ����, �������
// ������ 1, ... , N.
//                         �������� � ����������
//  1. ������������ ������ ������ (�����) THeap (����), � ������� ����������
//     ����� � ������� �����������. �� ���� ���������� ������ �������������
//     �������������.
//  2. � �������� "����" ������ ������ THashTableList, ����������  ����� �����
//     ������������ �������� (��������) ������ THashTable, ���������� ������
//     ����� � ������� ����. ������ ������������ ������ ����� ������������ �����.
//     ����� ����� � ������������ ������� ����������� ������� �����������,
//     �� ��������� ����� ������������� � ����.
//  3. �������� ����������� �����:
//       �) ����������� ����� ����� � ������������ ������� ������� ������-
//          �����;
//       �) ����� ������������ � ������ ��������� ������ � ������ ����;
//       �) � ����������� ������ ������������� ������� ������������ �����
//          ������ �� ������ � ������� ����;
//       �) ������ �� ������ � ������ ���� ������������ ����� ������� �
//          ��� -������ �����.
//  4. ����������� �������� ������� ����������� � ������� ����� ����������
//     � ���� ����-������ (N�������, N������_�������). � ���� ��������� �����
//     ������������� ������� ������� ����������� ��� cardALexicalCode, �������
//     ������������ ����� ����� ����� � ������� ����. ����������� ��� ����� �
//     ���� ��� ���������� � �������� � �������� �����.
//   5. ������� ������� �������� ����� THashTableList, � ������� �������������
//      ��� ��������� ������������ ��������� �������� � ������
//                        ������������� ���������
//    1.  ������������ � ����������
//      ������������� ������� ��� - ������ ��������� �������������:
//   		      THashTableList(Byte byteATableCount);
//      ��� byteATableCount - ���������� ����������� ��� - ������.
//      ������� ��� ���� �����������, ������� ����������� ������� ������� ������
//      �� �������������� ������������ � �����:
//		THashTableList(const Byte byteAFileType, const AnsiString strAFileName);
//      ��� byteAFileType - ��� ����� (��.�����), strAFileName - ��� �����.
//
//      ��������� ����� ��������� ������� � ������� �����������:
//          ~THashTableList();
//      � �������� ������ ����� � ������������ ������� ������ ��������
//          ��� ���� � ������� ������:  void Expantion();
//     2. ����� ����, ��� ������� �������, ����� ������ �� ����������
//        c ������� ��������:     __property Byte bytePTableCount;
//     3. ��������� �� ����� ������ ��������� ������� ������ �����
//         ��������� � ����� � ������� ������:
//        void Save(const Byte byteAFileType, const AnsiString strAFileName);
//      ����� ����������� � ����� ������� ������ ����� ������������:
//        void Load(const Byte byteAFileType, const AnsiString strAFileName);
//            ��������� byteAFileType - TEXT_FILE - ��������� ���� � ����� �
//                                      STREAM_FILE - ����� � ����� �++
//                      strAFileName - ��� ����������� ����� � ������, �� ����-
//         ����� ���� ��������� � ����� ����� � exe-������
//      ��� �������� ���������� � �������������� ������ ������������:
//          __property bool boolPIsSaved;
//                     ���������� ������ � ����� ������ �������
//  		__property bool boolPIsLoaded;
//                     �������������� ������ �� ����� ������ �������
//
//     4. ����������� �������� ������� ����������� � ������� ����� ����������
//   � ���� ������ (N�������, N������). � ���� ��������� ����� ������������
//   � ������� ������� Cardinal LexicalCode. LexicalCode ����� � ���� ���
//   ���������� (N�������, N������). ��� ����� ����� ������������ ��������:
//     __property Byte Tables[Cardinal cardILexicalCode]
//             ���������� ����� �������
//     __property AnsiString LexicalUnits[Cardinal cardILexicalCode]
//             ���������� �������� strLexicalUnit �����
// �������������� �������� ������������ ���� ����� ������ � ������� ��������
//     __property Cardinal cardPMaxLexicalCode
//   5. ��� ������ � ��������� ������������ ������:
//   bool SearchLexicalUnit(const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
//   bool AddLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable, Cardinal *cardALexicalCode);
//   void DeleteLexicalUnit (const AnsiString strALexicalUnit, const Byte byteATable);
//   void DeleteLexicalCode(const Cardinal cardALexicalCode);
//            ��������� strALexicalUnit - �������� �����,
//                      byteATable - ����� �������,
//                      cardALexicalCode - ����������� ��� �����.
//    6. � ������ ��� - �������� ����� ������� ������ ���������� ���� void *
//          ������������� ������ ���������� ��������� �������:
//          void  SetUserTable(const Byte byteATable);
//              �������� byteATable - ����� �������, ��� ������� ���������
//                                ������ ����������
//    ��� ������� ����� ������ � ���������� �������������� � ������� ��������:
//      __property void* UserTables[Cardinal cardILexicalCode]
//              �������� cardILexicalCode - ����������� ��� �����
//      ������ ������ �������� � ���������������� ������� ���-������� htl ��� ���������
//			   ����������� ����  LexCode
//                       TPoint * p = new TPoint();
//                       p->X = 1; p->Y = 2;
//                       TPoint **q1 = &p1;
//                       htl->UserTables[LexCode] = (void*)(*q1);
//      ������ ���������� ������ �� ���������������� �������
//          	TPoint * p2 = (TPoint *)(htl->UserTables[LexCode]);
//     �� ������ ������� ATable ����� ��������� ��������� ���������� � ���
//        ����. ��������� ������������ � slstALexicalUnits
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

// �������
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

// �������
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
// �������
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
