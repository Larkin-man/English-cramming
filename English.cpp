//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "English.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   srand(time(NULL));   //рандомизация называется. Типа зерно задаем
   Count = file.LoadFromFile("Items.txt","ss\0", &Eng, &Rus);
   Count-=1;
   w=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel2Click(TObject *Sender)
{
   if (RLang->ItemIndex == 0)
   {
      RusOut->Caption = Rus[w];
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   if (RLang->ItemIndex == 0)
   {
      w = random(0, Count);
      EngOut->Caption = Eng[w];
      RusOut->Caption = "";
   }
}
//---------------------------------------------------------------------------
