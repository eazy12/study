//---------------------------------------------------------------------------


#pragma hdrstop

#include "uLexicalAnalyzer.h"

//---------------------------------------------------------------------------
  //                 ����������� ����������                   //
  // ����� ������ ���������� ����������:
  //   �) ��������� stgsPIncomingText: TStrings ��������� �������� �����
  //   �) enumPState: TState ��������� �������� Start
  // ����� ����������� ���������� ����������:
  //   �) enumPState: TState ��������� �������� Continue

  // ��� ������ ��������� ����������:
  //   �) enumPForecastToken: TToken ��������� ��� ���������� �����
  //      ��� Unknown, ���� ������� �����������
  //   �) ������� procedure RecognizeNextToken, ������� ���������
  //        - � enumPCurrentRecognizedToken ���� �� ��������
  //          (��. �������� TToken) ��� Unknown - ����������� �����,
  //        - � strPLexicalUnit: AnsiString ����� ���������� �����
  //          ������������� ����� (��� ������)
  //        - � enumPState ���� �� ��������
  //            Continue - �������� ����� ��������� �� ����,
  //            Finish - �������� ����� ��������� ����.

  // ��������� ������ �����:
  //   �) ��� ������ ��������� ��������� ���������� � ��������
  //      �������� � ����� �����
  //   �) ����������� ���������� ������ ���������
  //      ����������� ��������� �� ������������ ������ ������
  //   �) ��� ������ ����������� ���������� ������ ���������
  //      ��������� � ����������� ����� ������������ ����� �����.
//---------------------------------------------------------------------------

void TLexicalAnalyzer::GetSymbol()
{
  cardFSourceCodeColSelection++;
  if ((int)cardFSourceCodeColSelection >
		stgsFSourceCode->Strings[cardFSourceCodeRowSelection].Length())
	 {
	   cardFSourceCodeRowSelection++;
	   if( (int)cardFSourceCodeRowSelection <= stgsFSourceCode->Count - 1)
		  {
			cardFSourceCodeColSelection = 0;
			wchrFSelection = '\0';
			enumFCharType = EndRow;
			enumFState = Continue;
		  }
	   else
		  {
			wchrFSelection = '\0';
			enumFCharType = EndText;
			enumFState = Finish;
	      }
	 }
  else
	 {
		wchrFSelection = stgsFSourceCode->Strings[
				  cardFSourceCodeRowSelection][cardFSourceCodeColSelection];

		  //switch(chrFSelection)
		  WideChar c = (WideChar)wchrFSelection;
//		  WideString s = L":;,.(){}[]=><-+*/&\'";
//		  s = s + (WideString)chrCUnQuantor + (WideString)chrCExQuan;
//		  int k = (unsigned WideChar) c;
		  {
			if(c ==' ') { enumFCharType = Space; }
			else if ( (c >= 'A' && c <= 'Z') ||
					 (c >= '�' && c <= '�') )
					{ enumFCharType = UpperLetter; }
			else if ( (c >= 'a' && c <= 'z') ||
					 (c >= '�' && c <= '�') ||
					 (c >= '�' && c <= '�') )
					{ enumFCharType = LowerLetter; }
			else if (c >= '0' && c <= '9')
					{ enumFCharType = Digit; }
			  //wchar_t *wcschr(const wchar_t *s, int c);
			else if(
			  wcschr((L":;,.(){}[]=><-+*/&\'" + (WideString)wchrCUnQuantor + (WideString)wchrCExQuantor).w_str(), c)
				!= NULL )
			{  enumFCharType = ReservedSymbol; }
			else { enumFCharType = Another; }
		  }

		  enumFState = Continue;
  }
}
//---------------------------------------------------------------------------
void TLexicalAnalyzer::NextToken()
{
  strFLexicalUnit = "";
  enumFToken = lxmUnknown;

  if(enumFState == Start)
  {
	cardFSourceCodeRowSelection = 0;
	cardFSourceCodeColSelection = 0;
	GetSymbol();

  }

  cardFLastTokenRow = cardFSourceCodeRowSelection;
  cardFLastTokenCol = cardFSourceCodeColSelection;

  while(enumFCharType == Space || enumFCharType == EndRow)
  { GetSymbol(); }

  switch(enumFForecast)
  {
	 case lxmUpperIdentifier:
	 {
	   if(enumFCharType == UpperLetter)
	   {
		 enumFToken = lxmUpperIdentifier;
		 RecognizeIdentifier();
	   } else { enumFToken = lxmUnknown; }
	   break;
	 }

	 case lxmLowerIdentifier:
	 {
	   if(enumFCharType == LowerLetter)
	   {
		 enumFToken = lxmLowerIdentifier;
		 RecognizeIdentifier();
	   } else { enumFToken = lxmUnknown; }
	   break;
	 }

	 case lxmUnknown :
	 {
	   switch(enumFCharType)
	   {
		 case UpperLetter:
		 {
		   enumFToken = lxmUpperIdentifier;
		   RecognizeIdentifier();
		   break;
		 }
		 case LowerLetter:
		 {
		   enumFToken = lxmLowerIdentifier;
		   RecognizeIdentifier();
		   break;
		 }
		 case Digit:
		 {
		   RecognizeNumber();
		   break;
		 }
		 case ReservedSymbol:
		 {
		   RecognizeReservedSymbol();
		   break;
		 }
		 case Another:
		 {
		   enumFToken = lxmUnknown;
		   strFLexicalUnit = wchrFSelection;
		   GetSymbol();
		   break;
		 }
		 case EndText:
		 {
		   enumFToken = lxmEmpty;
		   break;
		 }
		 default: {throw  EAbort(L"����������� ��� �������"); }
	   }
	   break;
	 }
	 default: { throw  EAbort(L"����������� ������� �����"); }
  }
}
//---------------------------------------------------------------------------
void TLexicalAnalyzer::RecognizeIdentifier()
{
  while ( (enumFCharType == UpperLetter || enumFCharType == LowerLetter ||
		   enumFCharType == Digit)
		 || wchrFSelection == '_' )
  {
	strFLexicalUnit = strFLexicalUnit + wchrFSelection;
	GetSymbol();
  }
}
//---------------------------------------------------------------------------
void TLexicalAnalyzer::RecognizeNumber()
{
  if(enumFCharType == Digit)
  {
	strFLexicalUnit = strFLexicalUnit + wchrFSelection;
	GetSymbol();

	while(enumFCharType == Digit)
	{
	  strFLexicalUnit = strFLexicalUnit + wchrFSelection;
	  GetSymbol();
	}
	if(wchrFSelection == '.')
	{
	  strFLexicalUnit = strFLexicalUnit + wchrFSelection;
	  GetSymbol();
	  if(enumFCharType == Digit)
	  {
		strFLexicalUnit = strFLexicalUnit + wchrFSelection;
		GetSymbol();
		while(enumFCharType == Digit)
		{
		  strFLexicalUnit = strFLexicalUnit + wchrFSelection;
		  GetSymbol();
		}
		enumFToken = lxmReal;
	  }
	  else { throw   EAbort("L������ � ������ ������������� �����"); }
	}
	else enumFToken = lxmInteger;
  }
}
//---------------------------------------------------------------------------
void TLexicalAnalyzer::RecognizeString()
{
  if(wchrFSelection == '\'')
  {
	A:
	  GetSymbol();
	  while(wchrFSelection != '\'' &&
			!(enumFCharType == EndRow || enumFCharType == EndText) )
	  {
		strFLexicalUnit = strFLexicalUnit + wchrFSelection;
		GetSymbol();
	  }

	  if(wchrFSelection == '\'')
	  {
		GetSymbol(); // ���������� '

		if(wchrFSelection == '\'')
		{
		  strFLexicalUnit = strFLexicalUnit + wchrFSelection;
		  goto A;
		}
		else { enumFToken = lxmString; }
	  }
	  else { throw  EAbort("L������������� ������"); }
  }
}
//---------------------------------------------------------------------------
void TLexicalAnalyzer::RecognizeReservedSymbol()
{
//   WideChar cc = (WideChar)chrCUnQuantor;
//   int c1 = (unsigned char)chrCUnQuantor;
//   int c2 =  (unsigned char) wchrFSelection;
//   int c3 =  (unsigned char)cc;
//   bool b = (cc == wchrFSelection);
  switch(wchrFSelection)
  {
	 case '&':
			  {
				enumFToken = lxmAmpersand;
				strFLexicalUnit = '&';
				GetSymbol();
				break;
			  }
	 case ':':
			  {
				enumFToken = lxmColon;
				strFLexicalUnit = ':';
				GetSymbol();
				break;
	          }
	 case ';':
			  {
				enumFToken = lxmSemicolon;
				strFLexicalUnit = ';';
				GetSymbol();
				break;
			  }
	 case ',':
			  {
				enumFToken = lxmComma;
				strFLexicalUnit = ',';
				GetSymbol();
				break;
			  }
	 case '.':
			  {
				enumFToken = lxmDot;
				strFLexicalUnit = '.';
				GetSymbol();
				break;
			  }
	 case '=':
			  {
				enumFToken = lxmEqual;
				strFLexicalUnit = '=';
				GetSymbol();
				break;
			  }
	 case '<':
			  {
				GetSymbol();
				if (wchrFSelection == '>')
				   {
					 enumFToken = lxmLessGreater;
					 strFLexicalUnit = "<>";
					 GetSymbol();
				   }
				else if (wchrFSelection == '=')
						{
						  GetSymbol();
						  if (wchrFSelection == '>')
							 {
							   enumFToken = lxmEquivalence;
							   strFLexicalUnit = "<=>";
							   GetSymbol();
							 }
						  else
							 {
							   enumFToken = lxmLessEqual;
							   strFLexicalUnit = "<=";
							 }
						}
					 else
						 {
						   enumFToken = lxmLess;
						   strFLexicalUnit = '<';
						 };
				break;
			  }
	 case '>':
			  {
				GetSymbol();
				if (wchrFSelection == '=')
				   {
					 enumFToken = lxmGreaterEqual;
					 strFLexicalUnit = ">=";
					 GetSymbol();
				   }
				else
				   {
					 enumFToken = lxmGreater;
					 strFLexicalUnit = '>';
				   }
				break;
			  }
	 case '{':
			  {
				enumFToken = lxmLeftBrance;
				strFLexicalUnit = '{';
				GetSymbol();
				break;
			  }
	 case '}':
			  {
				enumFToken = lxmRightBrance;
				strFLexicalUnit = '}';
				GetSymbol();
				break;
			  }
	 case '[':
			  {
				enumFToken = lxmLeftBracket;
				strFLexicalUnit = '[';
				GetSymbol();
				break;
			  }
	 case ']':
			  {
				enumFToken = lxmRightBracket;
				strFLexicalUnit = ']';
				GetSymbol();
				break;
			  }
	 case '(':
			  {
				enumFToken = lxmLeftParenth;
				strFLexicalUnit = '(';
				GetSymbol();
				break;
			  }
	 case ')':
			  {
				enumFToken = lxmRightParenth;
				strFLexicalUnit = ')';
				GetSymbol();
				break;
			  }
	 case '-':
			  {
				GetSymbol();
				if (wchrFSelection == '>')
				   {
					 enumFToken = lxmImplication;
					 strFLexicalUnit = "->";
					 GetSymbol();
				   }
				else
				   {
					 enumFToken = lxmSubstraction;
					 strFLexicalUnit = '-';
				   };
				break;
			  }
	 case '+':
			  {
				enumFToken = lxmAddition;
				strFLexicalUnit = '+';
				GetSymbol();
				break;
			  }
	 case '*':
			  {
				enumFToken = lxmMultiplication;
				strFLexicalUnit = '*';
				GetSymbol();
				break;
			  }
	 case '/':
			  {
				enumFToken = lxmRealDivision;
				strFLexicalUnit = '/';
				GetSymbol();
				break;
			  }
	 case (WideChar)wchrCUnQuantor:
			  {
				enumFToken = lxmUnQuan;
				strFLexicalUnit = wchrCUnQuantor;
				GetSymbol();
				break;
			  }
	 case (WideChar)wchrCExQuantor:
			  {
				enumFToken = lxmExQuan;
				strFLexicalUnit = wchrCExQuantor;
				GetSymbol();
				break;
			  }
	 case '\'':
			  {
				RecognizeString();
	            break;
			  }
	 default: { throw  EAbort(L"����������� �����������"); }
  }
}
//---------------------------------------------------------------------------
TToken TLexicalAnalyzer::NextInTurn()
{
  TToken Result;

  TToken enumVOldToken;
  Cardinal cardVOldRow, cardVOldCol;
  TCharType enumVOldCharType;
  AnsiChar chrVOldSelection;
  TState enumVOldState;

  enumVOldToken = enumFToken;
  cardVOldRow = cardFSourceCodeRowSelection;
  cardVOldCol = cardFSourceCodeColSelection;
  enumVOldCharType = enumFCharType;
  chrVOldSelection = wchrFSelection;
  enumVOldState = enumFState;

  NextToken();
  Result = enumFToken;

  enumFToken = enumVOldToken;
  cardFSourceCodeRowSelection = cardVOldRow;
  cardFSourceCodeColSelection = cardVOldCol;
  enumFCharType = enumVOldCharType;
  wchrFSelection = chrVOldSelection;
  enumFState = enumVOldState;
  return Result;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
