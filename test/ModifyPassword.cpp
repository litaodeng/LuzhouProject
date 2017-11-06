//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ModifyPassword.h"
#include "Unit1.h"
#include "PreViewForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TModifyPasswordFrame *ModifyPasswordFrame; 
extern String password;
extern String superPassword;
extern bool isLogin;
extern bool noAdminPassword;
//---------------------------------------------------------------------------
__fastcall TModifyPasswordFrame::TModifyPasswordFrame(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TModifyPasswordFrame::ValidButtonClick(TObject *Sender)
{
    String inputedOldName=OldNameInputEdit->Text;
    if(inputedOldName==""){
        ShowMessage("������ԭ����Ա������߳�������");
        OldNameInputEdit->SetFocus();
    }else{
        //�ȽϺ�����ͬΪfalse��ͬΪtrue;
        bool t=inputedOldName.AnsiCompare(superPassword);
        bool e=inputedOldName.AnsiCompare(password);
        if(t==true&&e==true){
            ShowMessage("ԭ�������");
            OldNameInputEdit->Text="";
            OldNameInputEdit->SetFocus();
        }else{
            String newPWD=NewNameInputEdit->Text;
            String newPWDAgain=NewInputPasswordAgain->Text;
            if(newPWD!=newPWDAgain){
                ShowMessage("�����������벻ͬ");
                NewNameInputEdit->Text="";
                NewInputPasswordAgain->Text="";
                NewNameInputEdit->SetFocus();
            }else if(newPWD.Length()<3){
                ShowMessage("���벻��������λ");
            }else{
                ShowMessage("�޸�����ɹ���");
                OldNameInputEdit->Text="";
                password=NewNameInputEdit->Text.c_str();
                ModifyPasswordFrame->Close();
                //MainForm->Enabled=true;
                //isLogin=true;
                //MainForm->SetButtionShow(isLogin);
            }
        }
    }
}
//---------------------------------------------------------------------------



void __fastcall TModifyPasswordFrame::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if(!noAdminPassword){
        AdminLogin->Enabled=true;
        AdminLogin->PasswordEdit->SetFocus();
    }else{
        MainForm->Enabled=true;
        ModifyPasswordFrame->Visible=false;
    }
}
//---------------------------------------------------------------------------
