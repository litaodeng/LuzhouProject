//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", MainForm);
USEFORM("ChangeMotorName.cpp", ChangeMotorNameForm);
USEFORM("PreViewForm.cpp", AdminLogin);
USEFORM("ModifyPassword.cpp", ModifyPasswordFrame);
USEFORM("Frame.cpp", Frame2); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TChangeMotorNameForm), &ChangeMotorNameForm);
         Application->CreateForm(__classid(TAdminLogin), &AdminLogin);
         Application->CreateForm(__classid(TModifyPasswordFrame), &ModifyPasswordFrame);
         Application->Run();

    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
