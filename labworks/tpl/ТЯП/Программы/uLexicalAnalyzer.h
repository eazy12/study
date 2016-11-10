//---------------------------------------------------------------------------

#ifndef uLexicalAnalyzerH
#define uLexicalAnalyzerH
//---------------------------------------------------------------------------
#include "uTranslatorDeclarations.h"
#include <Classes.hpp>
//---------------------------------------------------------------------------
enum TState { Start, Continue, Finish };

enum TCharType { UpperLetter, LowerLetter, Digit, ReservedSymbol,
				  Space, Another, EndRow, EndText };

class TLexicalAnalyzer
  {
	private:
	  TStrings * stgsFSourceCode;  // ��������� �� ������ �����
	  TToken enumFToken;
	  TToken enumFForecast; // ������� �����
	  AnsiString strFLexicalUnit; // ������������ �����/������ (�������)
	  TState enumFState;
	  WideChar wchrFSelection;
	  TCharType enumFCharType;
	  Cardinal cardFSourceCodeRowSelection;
	  Cardinal cardFSourceCodeColSelection;

	  Cardinal cardFLastTokenRow,
	           cardFLastTokenCol;

	  void GetSymbol();
	  void RecognizeIdentifier();
	  void RecognizeNumber();
	  void RecognizeReservedSymbol();
	  void RecognizeString();
	public:
	__property TStrings *stgsPSourceCode={write = stgsFSourceCode};
	__property TToken enumPCurrentRecognizedToken={read=enumFToken};
	__property TToken enumPForecastToken={write=enumFForecast};
	__property AnsiString strPLexicalUnit={read=strFLexicalUnit};
	__property TState enumPState={read=enumFState, write=enumFState};
	__property Cardinal cardPSourceCodeRowSelection = {read=cardFSourceCodeRowSelection,
														 write=cardFSourceCodeRowSelection};
	__property Cardinal cardPSourceCodeColSelection= {read=cardFSourceCodeColSelection,
														write=cardFSourceCodeColSelection};

	__property Cardinal cardPLastTokenRow={read=cardFLastTokenRow};
	__property Cardinal cardPLastTokenCol={read=cardFLastTokenCol};

	  void  NextToken();    // ��������� ����� � ������������� �� ������
	  TToken NextInTurn(); // ��������� ����� ��� ������������ �� ������
};
//---------------------------------------------------------------------------
#endif
