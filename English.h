//---------------------------------------------------------------------------

#ifndef EnglishH
#define EnglishH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "inifiles.hpp"
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include "FindForm.h"
#include "inifiles.hpp"
#include "TableLoader.cpp"
const int GroupCount = 101;
const int Lineyka[] = {5,4,3,3,2,2,1,1,1,1,0,0,0,0,0,0,-1,-1,-1,-1,-1};
const int LineykaCount = sizeof (Lineyka) / sizeof (Lineyka[0]);
const int MinHide = -6;
static int ///0 1 2  3   4   5   6   7   8   9   0   11  12  13  14  15  16  17  18  19
 FreqMin[] = {0,1,49,105,161,220,275,337,390,437,489,538,598,651,704,757,802,860,915,972,1029,1066,1116,1159,1202,1255,1295,1345,1394,1450,1503,1562,1628,1690,1804,1962,2118,2264,2393,2536,2664,2803,2896,2989,3097,3196,3274,3380,3523,3660,3789,3919,4011,4116,4228,4397,4482,4590,4690,4854,4973,5207,5455,5788,6111,6332,6406,6452,6532,6657,6812,6912,7069,7209,7427,7709,7937,8070,8248,8411,8499,8806,9034,9288,9569,9918,10194,10487,10776,10967,11255,11572,11882,12246,12463,99999,99999,99999,99999,99999,99999};
//20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39
const int nFreq = sizeof (FreqMin) / sizeof (FreqMin[0]); //101
const int nFreqMax = 94; //Макс группа в которую попадут частотные
//const int GroupCountDEC1 = GroupCount - 1;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TEdit *OutWord;
	TEdit *OutTrans;
	TCheckBox *Examine;
	TButton *RegTo0;
	TButton *Next;
	TLabel *HintLabel;
	TButton *RegTo99;
	TButton *RegTo100;
	TCheckListBox *GroupsBox;
	TButton *RandomBtn;
	TButton *ApplyBtn;
	TButton *AddBtn;
	TButton *FindBtn;
	TEdit *OutGroup;
	TUpDown *UpDown1;
	TSpeedButton *OpenBtn;
	TEdit *OpenEdit;
	TSpeedButton *SaveStringsBtn;
	TEdit *OutFreq;
	TMemo *Memo1;
	TLabel *FreqIndicate;
	TButton *SaveWordBtn;
	TImageList *ImageList1;
	TCheckBox *ApoChk;
	TButton *InsertBtn;
	TCheckBox *RewriteBox;
	TLabeledEdit *ExzDiffE;
	TUpDown *UpDown2;
	TButton *AlphabBtn;
	TRadioGroup *ExamineType;
	TFontDialog *FontDialog1;
	TButton *ItshardBtn;
	TTabSheet *TabSheet3;
	TValueListEditor *FreqList;
	TButton *NonFreqBtn;
	TButton *ToEvenBtn;
	TButton *FreqApply;
	TGroupBox *FreqDictionaryGr;
	TButton *LoadFreqtxt;
	TEdit *FreqEdit;
	TCheckBox *NoRiseFreq;
	TMemo *Memo2;
	TCheckBox *TestNext;
	TMemo *OutRus;
	TCheckBox *NearbyBox;
	TLabel *EvenLabel;
	TListBox *Helper;
	TButton *LoadGCtxt;
	TCheckBox *AddEnable;
	void __fastcall OpenBtnClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FindBtnClick(TObject *Sender);
	void __fastcall SaveStringsBtnClick(TObject *Sender);
	void __fastcall AddBtnClick(TObject *Sender);
	void __fastcall ApplyBtnClick(TObject *Sender);
	void __fastcall RandomBtnClick(TObject *Sender);
	void __fastcall NextClick(TObject *Sender);
	void __fastcall OutGroupChange(TObject *Sender);
	void __fastcall RegTo0Click(TObject *Sender);
	void __fastcall RegTo99Click(TObject *Sender);
	void __fastcall RegTo100Click(TObject *Sender);
	void __fastcall LoadFreqtxtClick(TObject *Sender);
	void __fastcall FreqIndicateClick(TObject *Sender);
	void __fastcall SaveWordBtnClick(TObject *Sender);
	void __fastcall InsertBtnClick(TObject *Sender);
	void __fastcall OutTransDblClick(TObject *Sender);
	void __fastcall ExzDiffEChange(TObject *Sender);
	void __fastcall FreqApplyClick(TObject *Sender);
	void __fastcall AlphabBtnClick(TObject *Sender);
	void __fastcall ToEvenBtnClick(TObject *Sender);
	void __fastcall ExamineClick(TObject *Sender);
	void __fastcall NonFreqBtnClick(TObject *Sender);
	void __fastcall ItshardBtnClick(TObject *Sender);
	void __fastcall TabSheet3Show(TObject *Sender);
	void __fastcall OutFreqChange(TObject *Sender);
	void __fastcall OutFreqKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall TabSheet1Show(TObject *Sender);
	void __fastcall GroupsBoxContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall SaveGCtxtClick(TObject *Sender);
	void __fastcall AddEnableClick(TObject *Sender);
	void __fastcall TabSheet2Resize(TObject *Sender);



private:	// User declarations

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	TableLoader file;
	UnicodeString *Words;
	UnicodeString *Trans;
	UnicodeString *Rus;
	int *Group;
	int *Freq; //Частотный словарь
	int *Hide;
	//////////////////.Word////////
	int Count;
	int AllCount;
	TStringList *In;
	int GroupPack[GroupCount];
	void Print(int Idx);
	TStringList *Added;
	TIniFile *Ini;
	int CurrNum; //Текущий номер из сборки Indexes[CurrNum]
	int CurrIdx; //Текущий индекс AllCount Words[CurrIdx]
	int *Indexes;
	int CurrGroup;
	bool Regrouping;
	int ExzDiff;
	int Vocabulary;
	int BaseCount;
	inline void Regroup(int oldG, int newG);
	void PrintNone();
	void PrintRus();
	UnicodeString CurrRus;
	int OwnGroup(int NewFrequensy);
	void RefreshGroupCounts(bool Regroup);
	int *NonFreq;
	TDateTime ti[GroupCount];
	Set <int, 0, GroupCount> Applyed;
	TDateTime ExamTime;
	float LineSize;
	bool WrongGroup(int i)
	{
		static int GroupCountDEC2 = GroupCount - 2;
		return ((Freq[i] > 0)&&(Group[i] > 0)&&(Group[i] < GroupCountDEC2)
			&&((Freq[i] < FreqMin[Group[i]])||(Freq[i] >= FreqMin[Group[i]+1]) ));
	}
	//DWORD Tick;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
