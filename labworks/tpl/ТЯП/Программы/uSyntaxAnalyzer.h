//---------------------------------------------------------------------------
#ifndef uSyntaxAnalyzerH
#define uSyntaxAnalyzerH
//---------------------------------------------------------------------------
//#include "uTranslatorDeclarations.h"
#include "uLexicalAnalyzer.h"
#include "uProver.h"
#include "uHashTables.h"
//#include "uTermAndFormulaStructures.h"
#include <Classes.hpp>

struct TVariablesStackNode
{
    Cardinal cardFLexCode;
	TVariablesStackNode * FNext;
};
typedef  TVariablesStackNode * TVariablesStack;

class  TSyntaxAnalyzer
{
   private:
	   TLexicalAnalyzer * objFLexicalAnalyzer;
	   TStrings * stgsFMessages;
	   THashTableList * htaFTermsPredicates;
	   bool boolFWriteMessages;

	   TVariablesStack FVariablesStack;
	   THashTableList * htaFVariables;

	   Cardinal cardFErrorRow;
	   Cardinal cardFErrorCol;

	   void SetMessagesField(TStrings * Value);
	   void WriteMessage(const AnsiString strAMessage);
	   void RaiseExpected(const AnsiString strAWhatExpected);
	   void Match(const TToken enumAToken);
	   void NT_POFormula(TQuantifier ** addrAFormulaRoot);
	   void NT_ListOfExSubFormulas(TQuantifier ** addrAExQuantifier);
	   void NT_ExSubFormula(TQuantifier ** addrAExQuantifier);
	   void NT_ListOfUnSubFormulas(TQuantifier ** addrAUnQuantifier);
	   void NT_UnSubFormula(TQuantifier ** addrAUnQuantifier);
	   void NT_UnQuan(TQuantifier ** addrAUnQuantifier);
	   void NT_ExQuan(TQuantifier ** addrAExQuantifier);
	   void NT_QuantifierContents(TQuantifier ** addrAQuantifier);
	   void NT_ListOfQuanVariables(TQuantifier ** addrAUnQuantifier);
	   void NT_TypeCondition(TQuantifier ** addrAUnQuantifier);
	   void NT_ListOfAtoms(TQuantifier ** addrAUnQuantifier);
	   void NT_Atom(TQuantifier ** addrAUnQuantifier);
	   void NT_BinaryRelation(TQuantifier ** addrAUnQuantifier);
	   void NT_ListOfTerms(TArrayOfTerm * arATerms);
	   void NT_Term(TArrayOfTerm * arATerms);
	   void NT_QuanVariable(TQuantifier ** addrAUnQuantifier);
	   void NT_AtomVariable(TArrayOfTerm * arATerms);
	   void NT_Constant(TArrayOfTerm * arATerms);
	   bool Push(const AnsiString strAVariable);
	   void RestoreStack(const TVariablesStack AOldStack);
	   void LoadReservedPredicates();
	   TadrAtom CreateAndFillAtom(Byte ATag, Cardinal cardAName);
	   void IntegerConstant(const AnsiString  strALexicalUnit,TArrayOfTerm * arATerms);
	   void RealConstant(const AnsiString strAlexicalUnit,TArrayOfTerm * arATerms);
	   void  StringConstant(const AnsiString strALexicalUnit,TArrayOfTerm * arATerms);
  public:
	   TSyntaxAnalyzer();
	   ~TSyntaxAnalyzer();
	   bool AnalyseAndTranslate(TStrings * stgsAIncomingText, TQuantifier ** addrAFormulaRoot);
	   __property TStrings* stgsPMessages={write=SetMessagesField};
	   __property THashTableList * htaPTermsPredicates={write=htaFTermsPredicates};
	   __property Cardinal cardPErrorRow={read=cardFErrorRow};
	   __property Cardinal cardPErrorCol={read=cardFErrorCol};
  };
#endif
