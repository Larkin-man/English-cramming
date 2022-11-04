//---------------------------------------------------------------------------

#ifndef EnglishH
#define EnglishH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <time.h>
#include <stdlib.h>
#include "TableLoader.cpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TRadioGroup *RLang;
   TListBox *ListBox1;
   TStaticText *RusOut;
   TGroupBox *GroupBox1;
   TCheckBox *CheckBox1;
   TCheckBox *CheckBox2;
   TCheckBox *CheckBox3;
   TStaticText *EngOut;
   TPanel *Panel2;
   TButton *Button1;
   void __fastcall Panel2Click(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
   int inline random(const int& min, const int& max)
   {    //От мин до макс включительно

        return (min + rand() % (max+1-min));
   }
   AnsiString *Rus, *Eng;
   int Count;
   TableLoader file;
   int w;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
