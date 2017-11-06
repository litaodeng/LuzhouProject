//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "ChangeMotorName.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TChangeMotorNameForm *ChangeMotorNameForm;
//---------------------------------------------------------------------------
__fastcall TChangeMotorNameForm::TChangeMotorNameForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TChangeMotorNameForm::RzBitBtn1Click(TObject *Sender)
{
    if(NewName->Text!=""){
        MainForm->ChangeMotorName(NewName->Text.c_str());
        ChangeMotorNameForm->Close();
        MainForm->Enabled=true;
    }
    else{
        ShowMessage("请输入新的电机名");
    }

}
//---------------------------------------------------------------------------

void __fastcall TChangeMotorNameForm::RzBitBtn2Click(TObject *Sender)
{
    ChangeMotorNameForm->Close();
}
//---------------------------------------------------------------------------


void __fastcall TChangeMotorNameForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     MainForm->Enabled=true;
}
//---------------------------------------------------------------------------

