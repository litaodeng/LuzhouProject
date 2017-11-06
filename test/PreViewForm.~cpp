//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PreViewForm.h"
#include "Unit1.h"
#include "ModifyPassword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TAdminLogin *AdminLogin;
extern String password;
extern String superPassword;
//---------------------------------------------------------------------------
__fastcall TAdminLogin::TAdminLogin(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------



void __fastcall TAdminLogin::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    MainForm->Enabled=true;
    MainForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TAdminLogin::LoginInClick(TObject *Sender)
{


        String pwd=PasswordEdit->Text;
        if(pwd==password||pwd==superPassword){
            ShowMessage("µÇÂ¼³É¹¦£¬»¶Ó­Äú£¡");
            isLogin=true;
            MainForm->SetButtionShow(true);
            AdminLogin->Close();
        }else{
            ShowMessage("ÃÜÂë´íÎó£¬ÖØÐÂÊäÈë");
            PasswordEdit->Text="";
            PasswordEdit->SetFocus();
        }

}
//---------------------------------------------------------------------------

void __fastcall TAdminLogin::ForgetPWDClick(TObject *Sender)
{
    AdminLogin->Enabled=false;
    ModifyPasswordFrame->Show();
    ModifyPasswordFrame->OldNameInputEdit->SetFocus();
}
//---------------------------------------------------------------------------



