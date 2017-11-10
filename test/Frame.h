//---------------------------------------------------------------------------


#ifndef FrameH
#define FrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzLabel.hpp"
#include "iComponent.hpp"
#include "iCustomComponent.hpp"
#include "iPipe.hpp"
#include "iVCLComponent.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrame2 : public TFrame
{
__published:	// IDE-managed Components
    TRzPanel *PanelInFrame;
private:	// User declarations
public:		// User declarations
    __fastcall TFrame2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame2 *Frame2;
//---------------------------------------------------------------------------
#endif
