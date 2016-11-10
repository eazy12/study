#pragma hdrstop
#include "uTranslatorDeclarations.h"
//---------------------------------------------------------------------------
AnsiString TokenAsString(TToken enumAToken)
{
  switch (enumAToken)
	{
	  case lxmUpperIdentifier : return "������������� � ��������� �����";
	  case lxmLowerIdentifier : return "������������� �� �������� �����";
	  case lxmInteger : return "����� �����";
	  case lxmString : return "������";
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
