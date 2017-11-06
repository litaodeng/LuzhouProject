//---------------------------------------------------------------------------

#ifndef PreViewFormH
#define PreViewFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAdminLogin : public TForm
{
__published:	// IDE-managed Components
    TRzLabel *PasswordLabel;
    TRzEdit *PasswordEdit;
    TRzBitBtn *LoginIn;
    TRzBitBtn *ForgetPWD;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall LoginInClick(TObject *Sender);
    void __fastcall ForgetPWDClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAdminLogin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAdminLogin *AdminLogin;
//---------------------------------------------------------------------------
#endif
