//---------------------------------------------------------------------------
#include <time.h>
//#include <stdlib.h>
#include <vcl.h>
#include "inifiles.hpp"
#include "TableLoader.h"
#pragma hdrstop

#include "English.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)	: TForm(Owner)
{
	Group = NULL;
	Added = NULL;
	Indexes = NULL;
	AllCount = 0;
	Count = 0;
	file.IgnoreFirstString = false;
	srand(time(NULL));  //srand(time_t);
	Regrouping = false;
	PageControl1->Pages[0]->Show();
	Memo1->Text = "";
	In = NULL;
	ExzDiff = 0;
	NonFreq = NULL;
	TDateTime Last =  0;
	if (FileExists("etc.ini"))
	{
		Ini = new TIniFile(GetCurrentDir()+"\\etc.ini");
		CurrNum = -1;
		for (int i = 0; i < GroupCount; ++i)
		{      //Memo1->Lines->Add(IntToStr(i)+"="+ti[i]);
			ti[i] = Ini->ReadDateTime("Last recurrence","ti"+IntToStr(i), 0);
			if (ti[i] > Last)
			{
				Last = ti[i];
				CurrNum = i;
			}
		}
		Memo1->Lines->Add("В прошлый раз вы повторяли группу №"+IntToStr(CurrNum));
		TDateTime cu =  cu.CurrentDateTime() - Last;
		if (cu.operator int() > 0)
			Memo1->Lines->Add(IntToStr(cu.operator int())+" дней, "+cu.TimeString()+" назад.");
		else
			Memo1->Lines->Add(cu.TimeString()+" назад.");
	}
	else
	{
		Ini = new TIniFile(GetCurrentDir()+"\\etc.ini");
		for (int i = 0; i < GroupCount; ++i)
			ti[i] = 0;
	}
	//Ini = new TIniFile(GetCurrentDir()+"\\etc.ini");
	CurrNum = -1;
	CurrIdx = -1;
	ExamTime = ExamTime.CurrentDateTime();
	//Memo1->Lines->Add(IntToStr(nFreq)+" "+IntToStr(FreqMin[nFreqMax]));
	AddBtn->Visible = AddEnable->Checked;
	LineSize = (float)(Next->Width+1) / LineykaCount;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenBtnClick(TObject *Sender)
{
	AllCount = file.LoadFromFile(OpenEdit->Text+".txt","ssiiis"
		,&Words,&Trans,&Group,&Freq,&Hide,&Rus);
	if ((AllCount % 10 >= 5)||(AllCount % 10 == 0))
		Form1->Caption = "Зубрилка ("+IntToStr(AllCount)+" слов)";
	else
		if (AllCount % 10 == 1)
			Form1->Caption = "Зубрилка ("+IntToStr(AllCount)+" слово)";
		else
			Form1->Caption = "Зубрилка ("+IntToStr(AllCount)+" слова)";
	for (int i = 0; i < GroupCount; ++i)
		GroupPack[i] = 0;
	Vocabulary = 0;
	Indexes = new int[AllCount];
	Count = 0;
	for (int i = 0; i < AllCount; ++i)
	{
		if ((Group[i] < 0)||(Group[i] >= GroupCount))
			Group[i] = 100; //wrong
		GroupPack[Group[i]]++;
		if ((Hide[i] > 2)||(Group[i] == 0))
			Vocabulary++;
		if (Hide[i] <= MinHide)
			Indexes[Count++] = i;
	}
	CurrNum = -1;
	CurrIdx = -1;
	BaseCount = Count;
	Next->Caption = "Next ("+IntToStr(Count)+")";
	Memo1->Lines->Add("Ваш словарный запас состоит примерно из "+IntToStr(Vocabulary)+" слов.");
	GroupsBox->Clear();
	for (int i = 0; i < GroupCount; ++i)
		GroupsBox->Items->Add(IntToStr(i)+":"+IntToStr(GroupPack[i]));
		//GroupsBox->Checked[i] = true;

	PageControl1->Pages[1]->Show();
	AlphabBtn->Enabled = true;
	LoadFreqtxt->Enabled = true;
	TestNext->Checked = false;
	SaveStringsBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete Added;
	delete []Indexes;
	delete In;
	delete NonFreq;
	delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FindBtnClick(TObject *Sender)
{
	if ((OutRus->SelText.IsEmpty() == false)||(OutWord->SelText.IsEmpty() == false))
   {
		FormFind->FindEdit->Text = OutWord->SelText+" "+OutRus->SelText;
		FormFind->FindEdit->Text = FormFind->FindEdit->Text.Trim();
		if (OutRus->SelText.IsEmpty() == false)
			FormFind->RusBox->Checked = true;
		if (OutWord->SelText.IsEmpty() == false)
			FormFind->WordBox->Checked = true;
		int p=FormFind->FindEdit->Text.Pos(';');
		if (p > 0)
			FormFind->FindEdit->Text = FormFind->FindEdit->Text.Delete(p,1);
	}
	FormFind->AllCount = AllCount;
	FormFind->Field[0] = Words;
	FormFind->Field[1] = Trans;
	FormFind->Field[2] = Rus;
	FormFind->ShowModal();
	if (FormFind->PrintIdx > -1)
	{
		Indexes[Count++] = CurrIdx;
		Indexes[CurrNum] = FormFind->PrintIdx;
		Print(CurrNum);
	}
}
//---------------------------------------------------------------------------
void TForm1::Print(int Idx)
{
	CurrNum = Idx;
	CurrIdx = Indexes[Idx];
	if ((Examine->Checked)&&(ExamineType->ItemIndex != 0))
		OutWord->Text = "";
	else
		OutWord->Text = Words[CurrIdx];
	if ((Examine->Checked)&&(ExamineType->ItemIndex == 2))
		OutTrans->Text = "";
	else
		OutTrans->Text = Trans[CurrIdx];
	//if (OutRus->ReadOnly != 0)
	//	SaveWordBtn->ImageIndex = 0;
	if ((Examine->Checked)&&(ExamineType->ItemIndex != 2))
	{
		OutRus->Text = "";
		OutRus->ReadOnly = true;
		SaveWordBtn->ImageIndex = 1;
	}
	else
	{
		PrintRus();
	}
	Regrouping = false;
	OutGroup->Text = Group[CurrIdx];
	CurrGroup = Group[CurrIdx];
	Regrouping = true;
	//if (NextDistributor->Checked) 		Hide[CurrIdx] = 1;
	OutFreq->Text = Freq[CurrIdx];
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveStringsBtnClick(TObject *Sender)
{
	if (Ini)
	{
		for (int i = 0; i < GroupCount; ++i)
			Ini->WriteDateTime("Last recurrence","ti"+IntToStr(i), ti[i]);
		Ini->UpdateFile();
	}
	TStringList *load = new TStringList;
	for (int i = 0; i < AllCount; ++i)
		load->Append(Words[i]
			+"\t"+Trans[i]
			+"\t"+IntToStr(Group[i])
			+"\t"+IntToStr(Freq[i])
			+"\t"+IntToStr(Hide[i])
			+"\t"+Rus[i]);
	if (Added)
		load->AddStrings(Added);
	if (RewriteBox->Checked)
		load->SaveToFile(OpenEdit->Text+".txt", TEncoding::Unicode);
	else
		load->SaveToFile("Save.txt", TEncoding::Unicode);
	delete load;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddBtnClick(TObject *Sender)
{
	if (Added == NULL)
		Added = new TStringList;
	Added->Append(OutWord->Text+"\t"+OutTrans->Text+"\t"
		+OutGroup->Text.ToIntDef(0)+OutFreq->Text.ToIntDef(0)+"0"+OutRus->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ApplyBtnClick(TObject *Sender)
{
	Applyed.Clear();
	for (int i = 0; i < GroupCount; ++i)
		if (GroupsBox->Checked[i])
			Applyed << i;
	if (Applyed.Empty())
	{
		OutRus->Text = "Группа не выбрана.";
		return;
	}
	Count = 0;
	int Showed = 0;
	for (int i = 0; i < AllCount; ++i)
		if (Applyed.Contains(Group[i]))
		{
			Indexes[Count++] = i;
			if (Hide[i] <= ExzDiff)
				Showed++;
		}
	CurrNum = -1;
	PrintNone();
	BaseCount = Count;
	OutRus->Text = "Всего "+IntToStr(Count)+" На показ "+IntToStr(Showed);
	Next->Caption = "Начать по алфавиту";
	ExamTime = ExamTime.CurrentDateTime();
	//Tick = ::GetTickCount();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RandomBtnClick(TObject *Sender)
{
	int t, r;
	if (Indexes)
		for (int i = 0; i < Count; ++i)
		{
			t = Indexes[i];
			r = rand() % Count;
			Indexes[i] = Indexes[r];
			Indexes[r] = t;
		}
	CurrNum = -1;
	CurrIdx = -1;
	NextClick(NULL);
}
//---------------------------------------------------------------------------
//Next кнопка
void __fastcall TForm1::NextClick(TObject *Sender)
{
	if (CurrIdx >= 0)
	{
		if (Examine->Checked)
		{
			if( OutWord->Text.IsEmpty())
			{
				OutWord->Text = Words[CurrIdx]; HintLabel->Caption = "";
				//return;
			}
			if( OutRus->Text.IsEmpty())
			{
				PrintRus();
				HintLabel->Caption = "";
				return;
			}
			if( OutTrans->Text.IsEmpty())
			{
				OutTrans->Text = Trans[CurrIdx]; HintLabel->Caption = "";
				return;
			}
		}
		//Обработка текщего слова
		TPoint mouse;
		GetCursorPos(&mouse);
		mouse = Next->ScreenToClient(mouse); //Может быть за границей кнопки!!!
		if ((mouse.x < 0)||(mouse.x > Next->Width))
			mouse.x = Next->Width / 2;
		int LineyIndex = mouse.x / LineSize;
		if (TestNext->Checked)
		{
			HintLabel->Caption = IntToStr(LineyIndex)+"]="+IntToStr(Lineyka[LineyIndex]);
			return;
		}
		if (Hide[CurrIdx] < MinHide)
			Hide[CurrIdx] = MinHide;
		Hide[CurrIdx] += Lineyka[LineyIndex];
		if ((Examine->Checked == false)&&(Lineyka[LineyIndex] > 1))
			Hide[CurrIdx]--;
		if ((Lineyka[LineyIndex] >= 5)&&(Hide[CurrIdx] < 2))
			Hide[CurrIdx] = 2;
		else if ((Lineyka[LineyIndex] >= 3)&&(Hide[CurrIdx] < 1))
			Hide[CurrIdx] = 1;
      if (LineyIndex > 16)
			Indexes[Count++] = CurrIdx;
		else if (Group[CurrIdx] == 0)
			Hide[CurrIdx]++;
		//if (Examine->Checked)
			if (Lineyka[LineyIndex] < 0)
				HintLabel->Caption = IntToStr(Lineyka[LineyIndex])+"="+IntToStr(Hide[CurrIdx]);
			else
				HintLabel->Caption = "+"+IntToStr(Lineyka[LineyIndex])+"="+IntToStr(Hide[CurrIdx]);
	}
	//Кто следующий?
	do
	{
		CurrNum++;
		if (CurrNum >= Count)
		{
			PrintNone();
			CurrNum = 0; //Подс4ет на показ
			for (int i = 0; i < BaseCount; ++i)
				if (Hide[Indexes[i]] <= ExzDiff)
					CurrNum++;
			ExamTime = ExamTime.CurrentDateTime() - ExamTime;
			OutRus->Text = "Конец группы.";
			if (Examine->Checked)
				OutRus->Lines->Add("Длительность экзамена: "+ExamTime);
			else
				OutRus->Lines->Add("Длительность урока: "+ExamTime);
			OutRus->Lines->Add("На повтор "+IntToStr(CurrNum));
			CurrNum = -1;
			Count = BaseCount;
			Next->Caption = "Начать снова";
			Helper->Tag = 0;
			for (int i = 0; i < GroupCount; ++i)
				if (Applyed.Contains(i))
					ti[i] = ti[i].CurrentDateTime();
			return;
		}
		Hide[Indexes[CurrNum]]--;
	} while (Hide[Indexes[CurrNum]] >= ExzDiff);
	Next->Caption = IntToStr(CurrNum+1)+"/"+IntToStr(Count)+" Next";
	Print(CurrNum);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OutGroupChange(TObject *Sender)
{
	if (Regrouping)
		Regroup(CurrGroup, OutGroup->Text.ToIntDef(0));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RegTo0Click(TObject *Sender)
{
	Regroup(CurrGroup, 0);
	NextClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RegTo99Click(TObject *Sender)
{
	Regroup(CurrGroup, GroupCount-2);
	NextClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RegTo100Click(TObject *Sender)
{
	Regroup(CurrGroup, GroupCount-1);
	NextClick(NULL);
}
//---------------------------------------------------------------------------

void TForm1::PrintNone()
{
	CurrIdx = -1;
	OutWord->Text = "...";
	OutTrans->Text = "...";
	//OutRus->Text = "End of group";
	Regrouping = false;
	//OutGroup->Text = 0;
	OutFreq->Text = "";
	OutRus->ReadOnly = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadFreqtxtClick(TObject *Sender)
{
	AlphabBtnClick(NULL);
	if (In->Count != AllCount)
	{
		Memo1->Lines->Add("Исходный словарь должен быть отсортирован по алфавиту и не содержать одинаковых слов.");
		return;
	}
	TStringList *freq = new TStringList;
	freq->LoadFromFile(FreqEdit->Text+".txt");
	TStringList *uni = new TStringList;
	int idx;
	for (int f = 0; f < freq->Count; ++f)
		if (In->Find(freq->Strings[f], idx))
		{
			if (Words[idx] != In->Strings[idx])
			{
				Memo1->Lines->Add("Error:"+Words[idx]+IntToStr(idx)+In->Strings[idx]);
				return;
			}
			if (Freq[idx] < 0)
			{
				Freq[idx] = f+1;
				uni->Add(Words[idx]+"\t"+IntToStr(Freq[idx]));
				if (Group[idx] > 0)
					Group[idx] = OwnGroup(Freq[idx]);
				continue;
			}
			if ((NoRiseFreq->Checked)&&(Freq[idx] < f+1))
			{
				uni->Add(Words[idx]+"\tNO "+IntToStr(Freq[idx]));
				continue;
			}
			uni->Add(Words[idx]+"\t"+IntToStr(Freq[idx])+"->"+IntToStr(f+1));
			Freq[idx] = f+1;
			if (Group[idx] > 0)
				Group[idx] = OwnGroup(Freq[idx]);
		}
		else
		{
			uni->Add(freq->Strings[f]);
      }

	uni->SaveToFile("uni.txt");
	delete freq;
	delete uni;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveWordBtnClick(TObject *Sender)
{
	if (CurrIdx < 0)
   	return;
	if (OutRus->Text.IsEmpty()||(OutRus->ReadOnly))
	{
		SaveWordBtn->ImageIndex = 0;
		OutRus->ReadOnly = false;
		OutRus->Text = Rus[CurrIdx];
		return;
	}
	Words[CurrIdx] = OutWord->Text;
	Trans[CurrIdx] = OutTrans->Text;
	Rus[CurrIdx] = OutRus->Text;
	Freq[CurrIdx] = OutFreq->Text.ToIntDef(-1);
	Group[CurrIdx] = OutGroup->Text.ToIntDef(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InsertBtnClick(TObject *Sender)
{
	if (OutRus->SelText.IsEmpty())
		return ShowMessage("Нет выделенного слова");
	UnicodeString FindText = OutRus->SelText.Trim();
	for (int i=0; i < AllCount; ++i)
		if (Words[i].Pos(FindText) == 1)
		{
			OutRus->Text = OutRus->Text +"*"+ Rus[i];
			if (Freq[CurrIdx] < 0)
			{
				Freq[CurrIdx] = Freq[i];
				OutFreq->Text = Freq[i];
			}
			OutGroup->Text = Group[i];
			return;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OutTransDblClick(TObject *Sender)
{
	if (FontDialog1->Execute() == ID_OK)
		OutTrans->Font = FontDialog1->Font;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExzDiffEChange(TObject *Sender)
{
	ExzDiff = ExzDiffE->Text.ToIntDef(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FreqIndicateClick(TObject *Sender)
{
	OutGroup->Text = OwnGroup(OutFreq->Text.ToIntDef(-1));
	FreqIndicate->Visible = false;
}
//---------------------------------------------------------------------------

int TForm1::OwnGroup(int NewFrequensy)
{  //Warning: i=1:если NewFrequensy<1 то в нулевую ,убрал теперь с i=2
	if (NewFrequensy < 1)
		return GroupCount-1;
	for (int i = 2; i < nFreqMax; ++i)
		if (NewFrequensy < FreqMin[i])
			return i-1;
	return nFreqMax;
}
//---------------------------------------------------------------------------
void TForm1::PrintRus()
{
	int p;
	OutRus->ReadOnly = false;
	UnicodeString *pRus = &Rus[CurrIdx];
	if ((ApoChk->Checked)&&(pRus->Pos('\'') > 0))
	{
		CurrRus = Rus[CurrIdx];
		OutRus->ReadOnly = true; //SaveWordBtn->ImageIndex = 1;
		while ((p = CurrRus.Pos('\'')) > 0)
		{
			int e=p+1;
			for (; e <= CurrRus.Length(); ++e)
				if ((CurrRus[e] >= '0')&&(CurrRus[e] <= '9')||(CurrRus[e]=='\'')||(CurrRus[e] == '*'))
				{
					if (CurrRus[e]=='\'')
						e++;
					CurrRus.Delete(p,e-p);
					e = 0;
					break;
				}
			if (e > CurrRus.Length())
				CurrRus.Delete(p,e-p);
		}
		pRus = &CurrRus;
	}
	if (pRus->Pos('*') > 0)
	{
		if (OutRus->ReadOnly == false)
			CurrRus = Rus[CurrIdx];
		OutRus->ReadOnly = true; //SaveWordBtn->ImageIndex = 1;
		//String zv = *pRus;
		OutRus->Text = "";
		while ((p = CurrRus.Pos('*')) > 0)
		{
			OutRus->Lines->Add(CurrRus.SubString(1,p-1));
			CurrRus.Delete(1,p);
		}
		OutRus->Lines->Add(CurrRus.SubString(p+1,pRus->Length()));
	} else
	{
		OutRus->Text = *pRus;
	}
	SaveWordBtn->ImageIndex = OutRus->ReadOnly ? 1 : 0;
	if (OutRus->Text.Length() > 100)
	{
		OutRus->SelStart = 0;
		OutRus->SelLength = 0;
		OutRus->Invalidate();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AlphabBtnClick(TObject *Sender)
{
	In = new TStringList;
	In->Sorted = true;
	In->Duplicates = dupIgnore;
	Memo1->Text = "Дублируются слова:";
	for (int i = 0; i < AllCount; ++i)
	{
		try
		{
			int l = In->Count;
			In->Add(Words[i]);
			if (l == In->Count)
         	Memo1->Lines->Add(Words[i]);
		} catch (EListError&)
		{
			Memo1->Lines->Add(Words[i]);
		}
	}
	if (Memo1->Lines->Count <= 1)
   	Memo1->Text = "Нет дублирующихся слов";
}
//---------------------------------------------------------------------
void __fastcall TForm1::ExamineClick(TObject *Sender)
{
	if (Examine->Checked == false)
		HintLabel->Caption = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ItshardBtnClick(TObject *Sender)
{
	Hide[CurrIdx] = MinHide - 2;
	HintLabel->Caption = "-8";
	CurrIdx = -1;
	NextClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabSheet3Show(TObject *Sender)
{                  //nFreqMax=94
	int Displace = GroupPack[0];
	for (int i = nFreqMax+1; i < GroupCount; ++i)
		Displace += GroupPack[i];
	EvenLabel->Tag = AllCount - Displace;  //Кол-во слов на раздел
	EvenLabel->Caption = "("+IntToStr(AllCount)+"-"+IntToStr(Displace)
		+")/"+IntToStr(nFreqMax)+"="+IntToStr(EvenLabel->Tag / nFreqMax)
		+"+"+IntToStr(EvenLabel->Tag - EvenLabel->Tag / nFreqMax * nFreqMax);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::OutFreqChange(TObject *Sender)
{
	int newFreq = OutFreq->Text.ToIntDef(-1);
	if (newFreq <= 0)
	{
		FreqIndicate->Visible = false;
		return;
   }
	if ((newFreq > 0)&&((Group[CurrIdx] > nFreqMax)||(newFreq < FreqMin[Group[CurrIdx]])) )
	{
		FreqIndicate->Font->Color = clRed;
		FreqIndicate->Visible = true;
	}
	else if (newFreq >= FreqMin[Group[CurrIdx]+1])
	{
		FreqIndicate->Font->Color = clBlue;
		FreqIndicate->Visible = true;
	}
	else
		FreqIndicate->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OutFreqKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '-')
   	OutFreq->Text = "-1";
}
//---------------------------------------------------------------------------
inline void TForm1::Regroup(int oldG, int newG)
{
	if (oldG == newG)
		return;
	Group[CurrIdx] = newG;
	GroupPack[oldG]--;
	GroupPack[newG]++;
	//GroupsBox->Items->BeginUpdate();
	GroupsBox->Items->Strings[oldG] = IntToStr(oldG)+" ("+IntToStr(GroupPack[oldG])+")";
	GroupsBox->Items->Strings[newG] = IntToStr(newG)+" ("+IntToStr(GroupPack[newG])+")";
	//GroupsBox->Items->EndUpdate();
	HintLabel->Caption = "->"+IntToStr(newG);
	CurrGroup = newG;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabSheet1Show(TObject *Sender)
{
	if (Helper->Tag != 0)
		return;
	TDateTime Old = Old.CurrentDateTime();
	TDateTime OldHard = 0;
	TDateTime CurrDate = CurrDate.CurrentDateTime();
	int OldG = -1, NoTeach = -1;
	int OldHardG = -1;
	for (int i = 1; i < GroupCount-2; ++i)
	{
		if (ti[i].operator !=(0))
		{
			if (ti[i] < Old)
			{
				Old = ti[i];
				OldG = i;
			}
			TDateTime Hard = CurrDate - ti[i];
			Hard.Val *= ((GroupCount-i)*(GroupCount-i));
			if (Hard > OldHard)
			{
				OldHard = Hard;
            OldHardG = i;
         }

		}
		else
			if (NoTeach == -1)
				NoTeach = i;

	}
	Helper->Items->Strings[0] = "Вы очень давно не повторяли группу №"+IntToStr(OldG);
	Helper->Items->Strings[1] = "Неплохо бы повторить группу №"+IntToStr(OldHardG);
	Helper->Items->Strings[2] = "Вы еще даже не брались за группу №"+IntToStr(NoTeach);
  	Helper->Tag = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupsBoxContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
{
	for (int i = 0; i < GroupsBox->Count; ++i)
		GroupsBox->Checked[i] = !GroupsBox->Checked[i];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveGCtxtClick(TObject *Sender)
{
	NonFreqBtnClick(NULL);
	RefreshGroupCounts(false);
	TStringList *load = new TStringList;
	load->Append("group\tcount\t-1count\tFreqMin");
	for (int i = 0; i < GroupCount; ++i)
		load->Append(IntToStr(i)
			+"\t"+IntToStr(GroupPack[i])
			+"\t"+IntToStr(NonFreq[i])
			+"\t"+IntToStr(FreqMin[i]) );
	load->SaveToFile("gc.txt", TEncoding::Unicode);
	delete load;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NonFreqBtnClick(TObject *Sender)
{
	if (NonFreq == NULL)
		NonFreq = new int [GroupCount];
	for (int i = 0; i < GroupCount; ++i)
		NonFreq[i] = 0;
	for (int i = 0; i < AllCount; ++i)
		if (Freq[i] <= 0)
			NonFreq[Group[i]]++;
	if (Sender)
	{
		for (int i = 1; i < GroupCount; ++i)
			FreqList->Cells[0][i] = IntToStr(i)+"-"+IntToStr(NonFreq[i]);
		for (int i = 0; i < AllCount; ++i)
			if (WrongGroup(i))
         	Memo2->Lines->Add(Words[i]+"\t"+IntToStr(Group[i]));
		Memo2->Lines->Add("В нулевой:"+IntToStr(NonFreq[0]));
	}
}
//---------------------------------------------------------------------------
void TForm1::RefreshGroupCounts(bool Regroup)
{
	for (int i = 0; i < GroupCount; ++i)
		GroupPack[i] = 0;
	bool AllDistibute = !NearbyBox->Checked;
	//Memo1->Clear();
	for (int i = 0; i < AllCount; ++i)
	{
		if (Regroup && WrongGroup(i))
		{
			int newG = OwnGroup(Freq[i]);
			if (AllDistibute||(abs(Group[i] - newG) < 3) )
				Group[i] = newG;
			else
				Memo1->Lines->Add(Words[i]+IntToStr(Group[i])+"no"+IntToStr(newG));
		}
		GroupPack[Group[i]]++;
	}
	for (int i = 1; i < nFreq; ++i)
		FreqList->Cells[0][i] = IntToStr(i)+":"+IntToStr(GroupPack[i]);
}
//---------------------------------------------------------------------------
//Выровнять
void __fastcall TForm1::ToEvenBtnClick(TObject *Sender)
{                   //nFreqMax=94
	Memo1->Clear();  Memo2->Clear();
	UnicodeString FreqStr = "{0,1";
	UnicodeString CurrStr;
	int IdealCol = EvenLabel->Tag / nFreqMax;
	int Puff = IdealCol*nFreqMax - EvenLabel->Tag + nFreqMax + 1;
	if (Puff < 2)
		Puff = 2;
	Memo2->Text = "Разбивка по "+IntToStr(IdealCol)+ " в группе, и +1 с "+IntToStr(Puff);
	NonFreqBtnClick(NULL);
	for (int i = 2; i < nFreqMax+1; ++i)
	{
		if (i == Puff)
      	IdealCol++;
		int Addition = (IdealCol-GroupPack[i-1])*(FreqMin[i]-FreqMin[i-1]);
		 CurrStr = IntToStr(i)+":"+IntToStr(Addition);
		//Memo2->Lines->Add(GroupPack[i-1]-NonFreq[i-1]);
		Addition /= (double)(GroupPack[i-1]-NonFreq[i-1]);
		 CurrStr += ">"+IntToStr(Addition);
		if ( (Addition == 0)&&(IdealCol < GroupPack[i-1]) )
			Addition = -1;
		else if ( (Addition == 0)&&(IdealCol > GroupPack[i-1]) )
			Addition = 1;
		 CurrStr += "="+IntToStr(Addition);
		int broken = FreqMin[i-1]-FreqMin[i];
		if ((Addition < broken)||(Addition > broken+400))
		{
			Memo1->Lines->Add(CurrStr);
			Memo1->Lines->Add("Стоп на "+IntToStr(i)+":"+IntToStr(Addition)+" b="+IntToStr(broken));
			ShowMessage("Стоп на "+IntToStr(i));
			if (Addition > broken+400)
			{
				Puff = FreqMin[i-1] - FreqMin[i] + 100;
				for (; i < nFreqMax+1; ++i)
					FreqMin[i] += Puff;
			}
			break;
		}
		FreqMin[i] += Addition;
		 CurrStr += " F="+IntToStr(FreqMin[i]);
		GroupPack[i] -= IdealCol-GroupPack[i-1];
		 CurrStr += " K="+IntToStr(GroupPack[i]);
		FreqStr += ","+IntToStr(FreqMin[i]);
		//FreqList->Cells[0][i] = IntToStr(i)+":"+IntToStr(GroupPack[i]);
		FreqList->Cells[1][i] = FreqMin[i];
		Memo1->Lines->Add(CurrStr);
	}
	/*
		 //*/
	Memo2->Lines->Add(FreqStr);
	RefreshGroupCounts(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FreqApplyClick(TObject *Sender)
{
	UnicodeString FreqStr = "";
	if (FreqApply->Caption != FreqApply->Hint)
	{
		for (int i = 1; i < nFreq; ++i)
		{
			FreqList->Cells[1][i] = FreqMin[i];
			FreqStr += IntToStr(GroupPack[i])+",";
		}
		FreqApply->Caption = FreqApply->Hint;
      Memo2->Text = FreqStr;
		return;
	}
	for (int i = 1; i < nFreq; ++i)
	{
		FreqMin[i] = FreqList->Cells[1][i].ToInt();
		FreqStr += IntToStr(FreqMin[i])+",";
	}
	Memo2->Text = FreqStr;
	RefreshGroupCounts(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddEnableClick(TObject *Sender)
{
	AddBtn->Visible = AddEnable->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabSheet2Resize(TObject *Sender)
{
	LineSize = (float)(Next->Width+1) / LineykaCount;
}
//---------------------------------------------------------------------------

