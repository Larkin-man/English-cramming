//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FindForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFind *FormFind;
//---------------------------------------------------------------------------
__fastcall TFormFind::TFormFind(TComponent* Owner)
	: TForm(Owner)
{
	Out->RowHeights[0] = 10;
}
//---------------------------------------------------------------------------
void __fastcall TFormFind::FindBtnClick(TObject *Sender)
{
	UnicodeString *FindField;
	if (WordBox->Checked)
		FindField = Field[0]; //FindField = Form1->Words;
	if (TransBox->Checked)
		FindField = Field[1]; //FindField = Form1->Trans;
	if (RusBox->Checked)
		FindField = Field[2]; //FindField = Form1->Rus;
	//int Count = Form1->AllCount;
	int row = 1;
	for (int Idx = 0; Idx < AllCount; ++Idx)
		if (FindField[Idx].Pos(FindEdit->Text))
		{
			if (Out->RowCount <= row)
				Out->RowCount++;
			Out->Cells[0][row] = Idx;
			Out->Cells[1][row] = Form1->Words[Idx];
			Out->Cells[2][row] = Form1->Group[Idx];
			Out->Cells[3][row] = Form1->Freq[Idx];
			Out->Cells[4][row] = Form1->Hide[Idx];
			Out->Cells[5][row] = Form1->Rus[Idx];
			row++;
		}
	if ((Out->RowCount > row)&&(row > 1))
		Out->RowCount = row;
}
//---------------------------------------------------------------------------

void __fastcall TFormFind::OutContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
{
	int c;
	Out->MouseToCell(MousePos.x,MousePos.y,c,PrintIdx);
	//ShowMessage(IntToStr(c)+" "+IntToStr(r));
	PrintIdx = Out->Cells[0][PrintIdx].ToIntDef(-1);
	//Form1->Print(c);
}
//---------------------------------------------------------------------------

void __fastcall TFormFind::FormShow(TObject *Sender)
{
	PrintIdx = -1;
	Out->ColWidths[5] = Out->Width - Out->ColWidths[0] - Out->ColWidths[1]
		- Out->ColWidths[2] - Out->ColWidths[3] - Out->ColWidths[4] - 28;
   FindEdit->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormFind::Label1Click(TObject *Sender)
{
	Label1->Caption = AllCount;
}
//---------------------------------------------------------------------------

