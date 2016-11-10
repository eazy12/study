//---------------------------------------------------------------------------
#pragma hdrstop
#include "uSyntaxAnalyzer.h"
//#include "uLexicalAnalyzer.h"
//#include "uHashTables.h"
//#include "uProver.h"
//---------------------------------------------------------------------------
TSyntaxAnalyzer::TSyntaxAnalyzer()
{
	objFLexicalAnalyzer = new TLexicalAnalyzer();
	boolFWriteMessages = False;
	FVariablesStack = NULL;
	htaFVariables = new THashTableList(1);
	cardFErrorRow = -1;
	cardFErrorCol = -1;
}
//---------------------------------------------------------------------------
TSyntaxAnalyzer::~TSyntaxAnalyzer()
{
	TVariablesStack	VWrk;
	objFLexicalAnalyzer->~TLexicalAnalyzer();
	while (FVariablesStack!=NULL)
		{
		   VWrk = FVariablesStack->FNext;
		   free(FVariablesStack);
		   FVariablesStack = VWrk;
		};
	 htaFVariables->~THashTableList();
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::SetMessagesField(TStrings * Value)
{
   stgsFMessages = Value;
   stgsFMessages->Clear();
   boolFWriteMessages = True;
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::WriteMessage(const AnsiString  strAMessage)
{
  if (boolFWriteMessages) stgsFMessages->Append(strAMessage);
}
//---------------------------------------------------------------------------
bool TSyntaxAnalyzer::AnalyseAndTranslate(TStrings * stgsAIncomingText,
										TQuantifier ** addrAFormulaRoot)
{
	 bool Result = true;
	 htaFTermsPredicates->SetUserTable(byCVariablesTable);
	 htaFTermsPredicates->SetUserTable(byCIntegersTable);
	 htaFTermsPredicates->SetUserTable(byCRealsTable);
	 htaFTermsPredicates->SetUserTable(byCStringsTable);
	 htaFTermsPredicates->SetUserTable(byCPredicatesTable);
	 LoadReservedPredicates();

	                                Cardinal cardVLexicalCode = 1;
									TadrAtom A = (TadrAtom) htaFTermsPredicates->UserTables[cardVLexicalCode];
	 objFLexicalAnalyzer->stgsPSourceCode = stgsAIncomingText;
	 objFLexicalAnalyzer->enumPState = Start;
	 objFLexicalAnalyzer->enumPForecastToken = lxmUnknown;

	 try
	   {
		 objFLexicalAnalyzer->NextToken();
		 NT_POFormula(addrAFormulaRoot);
	   }
	 catch(EAbort& Err)
		  { if (Err.Message.SubString(0,1)=="S")
		  {
			WriteMessage("Синтаксис: " + Err.Message.SubString(1,strlen((char *)Err.Message.c_str())-1));
			if (cardFErrorRow == -1 )
			   {
				 cardFErrorRow = objFLexicalAnalyzer->cardPSourceCodeRowSelection;
				 cardFErrorCol = objFLexicalAnalyzer->cardPSourceCodeColSelection;
			   };
			Result = false;
		  }
  /*	catch(EAbort& ELexAn)    */
		else
		  {
			WriteMessage("Лексика: " + Err.Message.SubString(1,strlen((char *)Err.Message.c_str())-1));

			if (cardFErrorRow == -1)
			   {
				  cardFErrorRow = objFLexicalAnalyzer->cardPSourceCodeRowSelection;
				  cardFErrorCol = objFLexicalAnalyzer->cardPSourceCodeColSelection;
			   };
			Result = false;
		  }};
	return Result;
}
//---------------------------------------------------------------------------
 void TSyntaxAnalyzer::RaiseExpected(const AnsiString strAWhatExpected)
{
	cardFErrorRow = objFLexicalAnalyzer->cardPLastTokenRow;
	cardFErrorCol = objFLexicalAnalyzer->cardPLastTokenCol;
	AnsiString s = "Sожидалось \"" + strAWhatExpected + "\"";
	throw EAbort(s);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::Match(const TToken enumAToken)
{
	 if(objFLexicalAnalyzer->enumPCurrentRecognizedToken == enumAToken)
		 objFLexicalAnalyzer->NextToken();
	 else RaiseExpected(TokenAsString(enumAToken));
}
//---------------------------------------------------------------------------
 void TSyntaxAnalyzer::NT_POFormula(TQuantifier ** addrAFormulaRoot)
{
	  *addrAFormulaRoot = new TQuantifier();
	  (*addrAFormulaRoot)->boolFUnQuan = True;
	  (*addrAFormulaRoot)->adrFSon = NULL;
	  (*addrAFormulaRoot)->adrFBrother = NULL;

	  Match(lxmUnQuan);
	  Match(lxmColon);
	  if(objFLexicalAnalyzer->strPLexicalUnit == strCTrue)
		 { objFLexicalAnalyzer->NextToken();}
	  else {RaiseExpected(strCTrue);};

	  TQuantifier ** addrVSon=&((*addrAFormulaRoot)->adrFSon);

	  if(objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLeftParenth)
		 {
		   objFLexicalAnalyzer->NextToken();
		   NT_ListOfExSubFormulas(addrVSon);
		   Match(lxmRightParenth);
		 }
	  else{ NT_ExSubFormula(addrVSon);};
	  if(objFLexicalAnalyzer->enumPCurrentRecognizedToken != lxmEmpty)
		 {
		   if(objFLexicalAnalyzer->strPLexicalUnit.Length() == 1)
			  { throw EAbort("лишний символ"); }
		   else { throw EAbort("лишние символы");}
		 }
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ExSubFormula(TQuantifier ** addrAExQuantifier)
{
	TVariablesStack VOldStack = FVariablesStack;
	NT_ExQuan(addrAExQuantifier);

	TQuantifier ** addrVSon=&((*addrAExQuantifier)->adrFSon);

	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLeftParenth)
	{
		 objFLexicalAnalyzer->NextToken();
		 NT_ListOfUnSubFormulas(addrVSon);
		 Match(lxmRightParenth);
	}
	else if(objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmUnQuan)
			NT_UnSubFormula(addrVSon);
	RestoreStack(VOldStack);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ListOfExSubFormulas(TQuantifier ** addrAExQuantifier)
{

	NT_ExSubFormula(addrAExQuantifier);

	TQuantifier ** addrFBrother=&((*addrAExQuantifier)->adrFBrother);

	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmComma)
	{
		objFLexicalAnalyzer->NextToken();
		NT_ListOfExSubFormulas(addrFBrother);
	}
}
void ShowQuan(TQuantifier * AQuan)
{
	 String s;
	 if (AQuan->boolFUnQuan) s= "Un  "; else s = "Ex  ";
	 int N = AQuan->arFVariables.size();
	 TadrVariable V;
	 for (int i = 0; i<N; i++)
		 {
			V = AQuan->arFVariables[i];
			Cardinal C = V->cardFLexicalCode;

			s = s + IntToStr((int)C) + "  ";
		 }
	 ShowMessage(s);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ExQuan(TQuantifier ** addrAExQuantifier)
{
	Match(lxmExQuan);
	*addrAExQuantifier = new TQuantifier();
	(*addrAExQuantifier)->boolFUnQuan = False;
	(*addrAExQuantifier)->adrFSon = NULL;
	(*addrAExQuantifier)->adrFBrother = NULL;
	NT_QuantifierContents(addrAExQuantifier);
			   ShowQuan(*addrAExQuantifier);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ListOfUnSubFormulas(TQuantifier ** addrAUnQuantifier)
{
	NT_UnSubFormula(addrAUnQuantifier);

	TQuantifier ** addrFBrother=&((*addrAUnQuantifier)->adrFBrother);

	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmComma)
	  {
		objFLexicalAnalyzer->NextToken();
		NT_ListOfUnSubFormulas(addrFBrother);
	  }
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_UnSubFormula(TQuantifier ** addrAUnQuantifier)
{
	TVariablesStack VOldStack = FVariablesStack;
	NT_UnQuan(addrAUnQuantifier);

	TQuantifier ** addrFSon=&((*addrAUnQuantifier)->adrFSon);

	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLeftParenth)
	{
		objFLexicalAnalyzer->NextToken();
		NT_ListOfExSubFormulas(addrFSon);
		Match(lxmRightParenth);
	}
	else NT_ExSubFormula(addrFSon);
	RestoreStack(VOldStack);
}
//---------------------------------------------------------------------------
void  TSyntaxAnalyzer::NT_UnQuan(TQuantifier ** addrAUnQuantifier)
{
	Match(lxmUnQuan);
	*addrAUnQuantifier = new  TQuantifier();

	//TQuantifier ** addrFSon=&((*adrAUnQuantifier)->adrFSon);
	//TQuantifier ** addrFBrother=&((*adrAUnQuantifier)->adrFBrother);


	(*addrAUnQuantifier)->boolFUnQuan = True;
	(*addrAUnQuantifier)->adrFSon = NULL;
	(*addrAUnQuantifier)->adrFBrother = NULL;
	NT_QuantifierContents(addrAUnQuantifier);
               ShowQuan(*addrAUnQuantifier);

}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_QuantifierContents(TQuantifier ** adrAQuantifier)
{
	if(objFLexicalAnalyzer->enumPCurrentRecognizedToken != lxmColon)
		NT_ListOfQuanVariables(adrAQuantifier);
	Match(lxmColon);

	NT_TypeCondition(adrAQuantifier);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ListOfQuanVariables(TQuantifier ** addrAQuantifier)
{
	NT_QuanVariable(addrAQuantifier);
	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmComma)
	{
		objFLexicalAnalyzer->NextToken();
		NT_ListOfQuanVariables(addrAQuantifier);
	};
	(*addrAQuantifier)->SortVariables(addrAQuantifier);
}
//---------------------------------------------------------------------------         l
void TSyntaxAnalyzer::NT_QuanVariable(TQuantifier ** addrAUnQuantifier)
{
	int intVTemp;
	Cardinal cardVLexicalCode;
	TVariable * adrVVariable;
	//with objFLexicalAnalyzer, htaFTermsPredicates do
	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLowerIdentifier)
	{
		AnsiString x = objFLexicalAnalyzer->strPLexicalUnit;
		if (!Push(x))
			throw EAbort("Sпеременная  " + objFLexicalAnalyzer->strPLexicalUnit + " уже связана квантором");
		htaFTermsPredicates->AddLexicalUnit(objFLexicalAnalyzer->strPLexicalUnit, byCVariablesTable, &cardVLexicalCode);
		adrVVariable = new TVariable();
		adrVVariable->cardFLexicalCode = cardVLexicalCode;
		htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)adrVVariable;
		intVTemp = (*addrAUnQuantifier)->arFVariables.size();
		(*addrAUnQuantifier)->arFVariables.resize(intVTemp + 1);
		(*addrAUnQuantifier)->arFVariables[intVTemp] = adrVVariable;
		objFLexicalAnalyzer->NextToken();
	}
	else RaiseExpected(TokenAsString(lxmLowerIdentifier));
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_TypeCondition(TQuantifier ** addrAUnQuantifier)
{
	Cardinal cardVLexicalCode;
	//with objFLexicalAnalyzer-> do
	if (objFLexicalAnalyzer->strPLexicalUnit == strCFalse)
	   {
		  htaFTermsPredicates->SearchLexicalUnit(strCFalse,byCPredicatesTable,&cardVLexicalCode);
		  (*addrAUnQuantifier)->arFTypeCondition.resize(1);
						void * V = htaFTermsPredicates->UserTables[cardVLexicalCode];
						TadrAtom A = (TadrAtom) V;
		  (*addrAUnQuantifier)->arFTypeCondition[0] = CopyReferenceToAtom(A); // TadrAtom(htaFTermsPredicates->UserTables[cardVLexicalCode]));
		  objFLexicalAnalyzer->NextToken();
	   }
	else NT_ListOfAtoms(addrAUnQuantifier);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ListOfAtoms(TQuantifier ** addrAUnQuantifier)
{
	TToken enumVTempToken;
	if (objFLexicalAnalyzer->strPLexicalUnit == strCTrue)
		objFLexicalAnalyzer->NextToken(); // strCTrue - пустой атом
	else NT_Atom(addrAUnQuantifier);
	//with objFLexicalAnalyzer-> do
	if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmComma)
	{
		enumVTempToken = objFLexicalAnalyzer->NextInTurn();
		if ((enumVTempToken != lxmUnQuan) && (enumVTempToken != lxmExQuan))
		{
			objFLexicalAnalyzer->NextToken();
			NT_ListOfAtoms(addrAUnQuantifier);
		}
	}
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_Atom(TQuantifier ** addrAUnQuantifier)
{
  int  intVTemp;
  Cardinal  cardVLexicalCode;
  bool  boolVInTable;
  TArrayOfTerm  arVTerms;

  switch (objFLexicalAnalyzer->enumPCurrentRecognizedToken)
	  {
		case lxmUpperIdentifier:
		   {
			  boolVInTable = htaFTermsPredicates->AddLexicalUnit(objFLexicalAnalyzer->strPLexicalUnit,byCPredicatesTable,&cardVLexicalCode);
			  objFLexicalAnalyzer->NextToken();
			  if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLeftParenth)
				 if  (!((objFLexicalAnalyzer->NextInTurn() == lxmUnQuan) || (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmExQuan)))
					 {
					   objFLexicalAnalyzer->NextToken();
					   NT_ListOfTerms(&arVTerms);
					   Match(lxmRightParenth);
					 };
			  intVTemp = (*addrAUnQuantifier)->arFTypeCondition.size();
			  (*addrAUnQuantifier)->arFTypeCondition.resize(intVTemp + 1);

			  if (arVTerms.size() == 0)
				 {
					if (boolVInTable)
					   (*addrAUnQuantifier)->arFTypeCondition[intVTemp] = CopyReferenceToAtom(TadrAtom(htaFTermsPredicates->UserTables[cardVLexicalCode]));
					else
					   {
						 (*addrAUnQuantifier)->arFTypeCondition[intVTemp] = CreateAndFillAtom(byCSimplePredicateTag, cardVLexicalCode);
						 htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)(CopyReferenceToAtom((*addrAUnQuantifier)->arFTypeCondition[intVTemp]));
					   };
				 }
			  else
				  {
					  (*addrAUnQuantifier)->arFTypeCondition[intVTemp] = CreateAndFillAtom(byCSimplePredicateTag, cardVLexicalCode);
					  (*addrAUnQuantifier)->arFTypeCondition[intVTemp]->arFTerms.resize(arVTerms.size());
					  for (unsigned int i = 0; i < arVTerms.size() ; i++)
					  {
						 (*addrAUnQuantifier)->arFTypeCondition[intVTemp]->arFTerms[i] = arVTerms[i];
					  };
// 					  (*arATypeCondition)[intVTemp]->arFTerms = Copy(arVTerms);
					  htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;
				  };
		   break;
		   };
		case lxmLowerIdentifier: {NT_BinaryRelation(addrAUnQuantifier); break;};
		case lxmInteger: {NT_BinaryRelation(addrAUnQuantifier);break;};
		case lxmReal: {NT_BinaryRelation(addrAUnQuantifier);break;};
		case lxmString: {NT_BinaryRelation(addrAUnQuantifier);break;};
		case lxmAddition: {NT_BinaryRelation(addrAUnQuantifier);break;};
		case lxmSubstraction: {NT_BinaryRelation(addrAUnQuantifier);break;};
		default : RaiseExpected("1)имя атома - " + TokenAsString(lxmUpperIdentifier) +
					  " или 2)бинарное отношение");
	  }
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_ListOfTerms(TArrayOfTerm * arATerms)
{
  NT_Term(arATerms);
  if (objFLexicalAnalyzer->enumPCurrentRecognizedToken== lxmComma )
  {
		  objFLexicalAnalyzer->NextToken();
		  NT_ListOfTerms(arATerms);
	 }
}

void TSyntaxAnalyzer::NT_Term(TArrayOfTerm * arATerms)
{

	 if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLowerIdentifier)
	   {	NT_AtomVariable(arATerms) ;}
	 else
	  {	if ((objFLexicalAnalyzer->enumPCurrentRecognizedToken==lxmInteger)||
			(objFLexicalAnalyzer->enumPCurrentRecognizedToken==lxmReal)||
			 (objFLexicalAnalyzer->enumPCurrentRecognizedToken==lxmString)||
			(objFLexicalAnalyzer->enumPCurrentRecognizedToken==lxmAddition)||
			(objFLexicalAnalyzer->enumPCurrentRecognizedToken==lxmSubstraction))

		{
		   NT_Constant(arATerms);
		   }
		else
		   RaiseExpected("терм");
}       }

 void TSyntaxAnalyzer::NT_AtomVariable(TArrayOfTerm * arATerms )
{

   int intVTemp;
   Cardinal cardVLexicalCode;
	 if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmLowerIdentifier)
	 {
			 if ( !(htaFVariables->SearchLexicalUnit(objFLexicalAnalyzer->strPLexicalUnit, 1,
													&cardVLexicalCode) ))
					throw EAbort(L"несвязанная переменная " +
										 objFLexicalAnalyzer->strPLexicalUnit);

			 htaFTermsPredicates->SearchLexicalUnit(objFLexicalAnalyzer->strPLexicalUnit, byCVariablesTable,
							   &cardVLexicalCode);
			 intVTemp = (* arATerms).size();
			 (* arATerms).resize( intVTemp + 1);

			 (* arATerms)[intVTemp].Tag = byCVariableTag;
			 (* arATerms)[intVTemp].ptrFReference = htaFTermsPredicates->UserTables[cardVLexicalCode];

			 objFLexicalAnalyzer->NextToken();
	 }
	 else
		RaiseExpected(TokenAsString(lxmLowerIdentifier));
}

void TSyntaxAnalyzer::IntegerConstant(const AnsiString  strALexicalUnit,TArrayOfTerm * arATerms)
{
	   TIntegerConstant * adrVIntegerConstant;
	   int intVTemp;
	   Cardinal cardVLexicalCode;

  //	  with htaFTermsPredicates do
	   if (!htaFTermsPredicates->AddLexicalUnit(strALexicalUnit, byCIntegersTable, &cardVLexicalCode))
		  {
				adrVIntegerConstant = new TIntegerConstant();
				adrVIntegerConstant->cardFLexicalCode = cardVLexicalCode;
				adrVIntegerConstant->intFValue = StrToInt(strALexicalUnit);
				 htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)(adrVIntegerConstant);
		  }
	   else adrVIntegerConstant = (TIntegerConstant *)( htaFTermsPredicates->UserTables[cardVLexicalCode]);


	  intVTemp = (* arATerms).size();
	  (* arATerms).resize(intVTemp + 1);

	  (* arATerms) [intVTemp].Tag = byCIntegerConstantTag;
	  (* arATerms) [intVTemp].ptrFReference = (void *)(adrVIntegerConstant);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::RealConstant(const AnsiString strAlexicalUnit,TArrayOfTerm * arATerms)
{
	  TRealConstant * adrVRealConstant;
	  AnsiString strVTemp;
	  int intVTemp;
	  Cardinal cardVLexicalCode;
	  if(!htaFTermsPredicates->AddLexicalUnit(strAlexicalUnit, byCRealsTable, &cardVLexicalCode))
		 {
		   adrVRealConstant = new TRealConstant();
		   adrVRealConstant->cardFLexicalCode = cardVLexicalCode;
		   strVTemp = strAlexicalUnit;
		   intVTemp = strVTemp.Pos(".");
		   strVTemp[intVTemp] = ',';
		   adrVRealConstant->dubFValue = StrToFloat(strVTemp);
		   htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)(adrVRealConstant);
		 }
	  else adrVRealConstant = (TRealConstant *)(htaFTermsPredicates->UserTables[cardVLexicalCode]);
	  intVTemp =  (*arATerms).size();
	  (*arATerms).resize(intVTemp + 1);
	  (*arATerms)[intVTemp].Tag = byCRealConstantTag;
	  (*arATerms)[intVTemp].ptrFReference = (void *)(adrVRealConstant);
}
//---------------------------------------------------------------------------
void  TSyntaxAnalyzer::StringConstant(const AnsiString strALexicalUnit,TArrayOfTerm * arATerms)
{
	TStringConstant * adrVStringConstant;
	int intVTemp;
	Cardinal cardVLexicalCode;
	if (!htaFTermsPredicates->AddLexicalUnit(strALexicalUnit, byCStringsTable, &cardVLexicalCode))
		 {
			 adrVStringConstant= new TStringConstant();
			 adrVStringConstant->cardFLexicalCode = cardVLexicalCode;
			 htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)(adrVStringConstant);
		 }
		 else { adrVStringConstant = (TStringConstant *)(htaFTermsPredicates->UserTables[cardVLexicalCode]);}
		 intVTemp =  (*arATerms).size();
		 (*arATerms).resize(intVTemp + 1);

		 (*arATerms)[intVTemp].Tag = byCStringConstantTag;
		 (*arATerms)[intVTemp].ptrFReference = (void *)(adrVStringConstant);
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_Constant(TArrayOfTerm * arATerms)
{
   AnsiString strVOperation;
   Cardinal cardVLexicalCode;
   switch (objFLexicalAnalyzer->enumPCurrentRecognizedToken)
		  {
			case  lxmInteger: {IntegerConstant(objFLexicalAnalyzer->strPLexicalUnit,arATerms);break; };
			case  lxmAddition:
					{
					   if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmSubstraction)
							 strVOperation = objFLexicalAnalyzer->strPLexicalUnit;
					   else  strVOperation = "";
					   objFLexicalAnalyzer->NextToken();
					   switch (objFLexicalAnalyzer->enumPCurrentRecognizedToken)
							  {
								  case lxmInteger: {IntegerConstant(strVOperation + objFLexicalAnalyzer->strPLexicalUnit,arATerms);break; };
								  case lxmReal: {RealConstant(strVOperation + objFLexicalAnalyzer->strPLexicalUnit,arATerms); break; };
								  default: RaiseExpected("целое или вещественное число");
							  };
					   break;
					};
			case  lxmSubstraction:
					{
					   if (objFLexicalAnalyzer->enumPCurrentRecognizedToken == lxmSubstraction)
							 strVOperation = objFLexicalAnalyzer->strPLexicalUnit;
					   else  strVOperation = "";
					   objFLexicalAnalyzer->NextToken();
					   switch (objFLexicalAnalyzer->enumPCurrentRecognizedToken)
							  {
								  case lxmInteger: {IntegerConstant(strVOperation + objFLexicalAnalyzer->strPLexicalUnit,arATerms);break; };
								  case lxmReal: {RealConstant(strVOperation + objFLexicalAnalyzer->strPLexicalUnit,arATerms); break; };
								  default: RaiseExpected("целое или вещественное число");
							  };
					   break;
					};
			case lxmString: {StringConstant(objFLexicalAnalyzer->strPLexicalUnit,arATerms); break; };
			case lxmReal: {RealConstant(objFLexicalAnalyzer->strPLexicalUnit,arATerms);  break; };
			default : RaiseExpected("константа");
		  }
   objFLexicalAnalyzer->NextToken();
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::NT_BinaryRelation(TQuantifier ** addrAUnQuantifier)
{
  int intVTemp;
  Cardinal cardVLexicalCode;
  Byte byVTag;
  TArrayOfTerm arVTerms;
  NT_Term(&arVTerms);

  switch (objFLexicalAnalyzer->enumPCurrentRecognizedToken)
		{
		   case lxmEqual: {byVTag = byCEqualTag; break;};
		   case lxmLessGreater:  { byVTag = byCLessGreaterTag; break;};
		   case lxmLess:  { byVTag = byCLessTag; break;};
		   case lxmLessEqual: { byVTag = byCLessEqualTag; break;};
		   case lxmGreater: { byVTag = byCGreaterTag; break;};
		   case lxmGreaterEqual: { byVTag = byCGreaterEqualTag; break;};
		   default : RaiseExpected("знак бинарного отношения");
		}
  htaFTermsPredicates->SearchLexicalUnit(objFLexicalAnalyzer->strPLexicalUnit,
										byCPredicatesTable,
										&cardVLexicalCode);
  objFLexicalAnalyzer->NextToken();
  NT_Term(&arVTerms);
  intVTemp = (*addrAUnQuantifier)->arFTypeCondition.size();
  (*addrAUnQuantifier)->arFTypeCondition.resize(intVTemp + 1);
  (*addrAUnQuantifier)->arFTypeCondition[intVTemp] = CreateAndFillAtom(byVTag, cardVLexicalCode);
  for (unsigned int i = 0; i < arVTerms.size(); i++)
  {
	(*addrAUnQuantifier)->arFTypeCondition[intVTemp]->arFTerms[i] = arVTerms[i];
  }

}
//---------------------------------------------------------------------------
bool TSyntaxAnalyzer::Push(const AnsiString strAVariable)
{
  TVariablesStackNode * VWrk;
  Cardinal cardVLexCode;
  bool Result;
  if (htaFVariables->AddLexicalUnit(strAVariable, 1, &cardVLexCode))
	 Result = False;
  else
	  {
		  Result = True;
		  VWrk = new TVariablesStackNode();
		  VWrk->cardFLexCode = cardVLexCode;
		  if (FVariablesStack == NULL)
				VWrk->FNext = NULL;
		  else  VWrk->FNext = FVariablesStack;

		  FVariablesStack = VWrk;
	  }
  return Result;
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::RestoreStack(const TVariablesStack AOldStack)
{
  TVariablesStack VWrk;
  while ((AOldStack != FVariablesStack) && (FVariablesStack != NULL))
	 {
	   VWrk = FVariablesStack->FNext;
	   htaFVariables->DeleteLexicalCode(FVariablesStack->cardFLexCode);
//	   FVariablesStack-> ~TVariablesStack();
	   FVariablesStack = VWrk;
	 };
}
//---------------------------------------------------------------------------
TadrAtom TSyntaxAnalyzer::CreateAndFillAtom(Byte ATag, Cardinal cardAName)
{
  TadrAtom Result = NewAtom();
  Result->Tag = ATag;
  Result->cardFName = cardAName;
  return Result;
}
//---------------------------------------------------------------------------
void TSyntaxAnalyzer::LoadReservedPredicates()
{
	 Cardinal  cardVLexicalCode;

	 htaFTermsPredicates->AddLexicalUnit(strCFalse, byCPredicatesTable, &cardVLexicalCode);

	 htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)(CreateAndFillAtom(byCFalseTag, cardVLexicalCode));
		   TadrAtom A = (TadrAtom) htaFTermsPredicates->UserTables[cardVLexicalCode];
	 htaFTermsPredicates->AddLexicalUnit(strCTrue, byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = (void *)(CreateAndFillAtom(byCTrueTag, cardVLexicalCode));


	 htaFTermsPredicates->AddLexicalUnit("=", byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;

	 htaFTermsPredicates->AddLexicalUnit("<>", byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;

	 htaFTermsPredicates->AddLexicalUnit("<", byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;

	 htaFTermsPredicates->AddLexicalUnit("<=", byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;

	 htaFTermsPredicates->AddLexicalUnit(">", byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;

	 htaFTermsPredicates->AddLexicalUnit(">=", byCPredicatesTable, &cardVLexicalCode);
	 htaFTermsPredicates->UserTables[cardVLexicalCode] = NULL;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
