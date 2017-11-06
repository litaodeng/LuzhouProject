//---------------------------------------------------------------------------

#ifndef ModifyPasswordH
#define ModifyPasswordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TModifyPasswordFrame : public TForm
{
__published:	// IDE-managed Components
    TRzEdit *OldNameInputEdit;
    TRzLabel *oldPWD;
    TRzLabel *newPWD;
    TRzLabel *RzLabel1;
    TRzEdit *NewNameInputEdit;
    TRzEdit *NewInputPasswordAgain;
    TRzButton *ValidButton;
    void __fastcall ValidButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TModifyPasswordFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModifyPasswordFrame *ModifyPasswordFrame;
//---------------------------------------------------------------------------
#endif
