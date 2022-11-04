//---------------------------------------------------------------------------

#ifndef FindFormH
#define FindFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include "English.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormFind : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TEdit *FindEdit;
	TButton *FindBtn;
	TPanel *Panel2;
	TRadioButton *RusBox;
	TRadioButton *TransBox;
	TLabel *Label1;
	TStringGrid *Out;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TRadioButton *WordBox;
	void __fastcall FindBtnClick(TObject *Sender);
	void __fastcall OutContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFormFind(TComponent* Owner);
	UnicodeString FindText;
	int PrintIdx;
	int AllCount;
	PUnicodeString Field[3];
};
//---------------------------------------------------------------------------
extern PACKAGE TFormFind *FormFind;
//---------------------------------------------------------------------------
#endif
