#pragma hdrstop
#include "uTranslatorDeclarations.h"
//---------------------------------------------------------------------------
AnsiString TokenAsString(TToken enumAToken)
{
  switch (enumAToken)
	{
	  case lxmUpperIdentifier : return "идентификатор с прописной буквы";
	  case lxmLowerIdentifier : return "идентификатор со строчной буквы";
	  case lxmInteger : return "целое число";
	  case lxmString : return "строка";
	  case lxmColon : return ":";
	  case lxmComma : return ",";
	  case lxmDot : return ".";
	  case lxmLeftParenth : return "(";
	  case lxmRightParenth : return ")";
	  case lxmUnQuan : return wchrCUnQuantor;
	  case lxmExQuan : return wchrCExQuantor;
	  case lxmQuotationMark : return "''";
	  default : return "";
	}
};
#pragma package(smart_init)
