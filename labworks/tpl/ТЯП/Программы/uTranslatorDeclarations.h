//---------------------------------------------------------------------------

#ifndef uTranslatorDeclarationsH
#define uTranslatorDeclarationsH
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
const WideChar wchrCUnQuantor = L'А';
const WideChar wchrCExQuantor = L'Б';
//const char chrCUnQuantor = 128;
//const char chrCExQuan = 129;

const AnsiString strCTrue = "True";
const AnsiString strCFalse = "False";

enum TToken
  {
	 lxmUpperIdentifier,              lxmAddition,           /* + */
	 lxmLowerIdentifier,              lxmSubstraction,       /* - */
	 lxmInteger,                      lxmMultiplication,     /* * */
	 lxmReal,                         lxmRealDivision,       /* / */
	 lxmString,                       lxmIntegerDivision,    /* div */
	 lxmAmpersand,        /* & */       lxmRemainder,          /* mod */
	 lxmColon,            /* : */
	 lxmSemicolon,        /* ; */      lxmDisjunction,        /* | */
	 lxmComma,            /* , */      lxmImplication,        /* -> */
	 lxmDot,              /* . */      lxmEquivalence,        /* <=> */
	 lxmEqual,            /* = */      lxmLessGreater,        /* <> */
	 lxmGreater,          /* > */      lxmGreaterEqual,       /* >= */
	 lxmLess,             /* < */      lxmLessEqual,          /* <= */
	 lxmLeftBrance,       /* { */      lxmRightBrance,        /* } */
	 lxmLeftBracket,      /* [ */      lxmRightBracket,       /* ] */
	 lxmLeftParenth,      /* ( */      lxmRightParenth,       /* ) */
	 lxmOf,               /* из */
	 lxmUnknown,                      lxmEmpty,
	 lxmUnQuan,                       lxmExQuan,
	 lxmQuotationMark     /* ' */
   };
/*
typedef EAbort ELexAnError;
typedef EAbort ESynAnError;    */

AnsiString TokenAsString(TToken);
#endif
