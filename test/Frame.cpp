//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzLabel"
#pragma link "iComponent"
#pragma link "iCustomComponent"
#pragma link "iPipe"
#pragma link "iVCLComponent"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TFrame2 *Frame2;
//---------------------------------------------------------------------------
__fastcall TFrame2::TFrame2(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------

