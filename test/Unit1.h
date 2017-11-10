//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#include <Classes.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "iComponent.hpp"
#include "iCustomComponent.hpp"
#include "iStripChart.hpp"
#include "iVCLComponent.hpp"
#include <ExtCtrls.hpp>
#include "iPlot.hpp"
#include "iPlotComponent.hpp"
#include "iMotor.hpp"
#include "iPipe.hpp"
#include "iSevenSegmentClockSMPTE.hpp"
#include "iSevenSegmentDisplay.hpp"
#include "iAnalogDisplay.hpp"
#include <jpeg.hpp>
#include <inifiles.hpp>
#include <MPlayer.hpp>
#include "iSevenSegmentAnalog.hpp"
#include "iKnob.hpp"
#include "iPositionComponent.hpp"
#include "iScaleComponent.hpp"
#include "iAngularGauge.hpp"
#include "iGaugeComponent.hpp"
#include <Buttons.hpp>
#include "Motor.cpp"
#include "RzPanel.hpp"
#include "RzLabel.hpp"
#include "iOdometer.hpp"
#include "iLed.hpp"
#include "iLedRound.hpp"
#include "math.h"
#include "RzButton.hpp"
#include <ScktComp.hpp>
#include "pngimage.hpp"
#include "RzLstBox.hpp"
#include <NMUDP.hpp>
#include "RzShellDialogs.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "iLabel.hpp"
#include "iSevenSegmentCharacter.hpp"
#include "iLinearGauge.hpp"
#include "iSlider.hpp"
#include "Instruction.cpp"
#include "RzBorder.hpp"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer2;
        TPanel *Top;
        TiPipe *iPipe1;
        TiStripChart *iStripChart5;
        TImage *LeftCameraLine;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TRzPanel *TopLeftPanel;
        TRzPanel *TopRightPanel;
        TRzPanel *TopCenterPanel;
        TRzPanel *RzPanel1;
        TiOdometer *iOdometer1;
        TRzLabel *RzLabel1;
        TRzLabel *RzLabel2;
        TRzLabel *RzLabel3;
        TRzLabel *RzLabel4;
        TRzLabel *RzLabel5;
        TRzLabel *RzLabel6;
        TRzLabel *RzLabel7;
        TiKnob *iKnob1;
        TClientSocket *ClientSocket1;
        TRzButton *ChangeName;
        TImage *Image2;
        TImage *RightCameraLine;
        TImage *Image4;
        TRzLabel *RzLabel8;
        TRzLabel *RzLabel9;
        TRzLabel *RzLabel10;
        TRzLabel *RzLabel11;
        TiAnalogDisplay *flowLabel;
        TNMUDP *NMUDPS;
        TRzButton *RzButton2;
        TRzListBox *ConfigList;
        TRzOpenDialog *WriteConfigDialog;
        TRzSaveDialog *SaveConfig;
        TRzButton *SaveConfigButton;
        TRzButton *Stop;
        TPopupMenu *ListPopMenu;
        TMenuItem *DeleteConfig;
        TRzLabel *RunningStatusLabel;
        TRzButton *DeleteSelectedConfig;
    TiLabel *iLabel1;
    TiLabel *Countdown;
    TTimer *CountdownTimer;
    TTimer *InCrementSpeedTimer;
    TRzButton *CancelChange;
    TiSlider *iSlider1;
    TRzLabel *RzLabel14;
    TRzPanel *RzPanel2;
    TRzPanel *RzPanel3;
    TRzLabel *RzLabel15;
    TRzLabel *RzLabel16;
    TRzLabel *RzLabel17;
    TRzLabel *RzLabel18;
    TRzButton *RzButton3;
    TRzLabel *RzLabel19;
    TiAnalogDisplay *iAnalogDisplay1;
    TButton *Test;
    TComboBox *ComboBox1;
    TComboBox *ComboBox2;
    TRzLabel *RzLabel12;
    TRzLabel *RzLabel20;
    TRzPanel *Caption;
    TRzPanel *MainControlPanel;
    TRzLEDDisplay *RzLEDDisplay1;
    TImage *Image1;
    TiLedRound *iLedRound1;
    TImage *Image3;
    TRzButton *Loginout;
    TRzButton *LoginButton;
    TRzLabel *RzLabel21;
    TRzLabel *RzLabel13;
    TImage *Image5;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Timer2Timer(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall saveToIniFile();
    void __fastcall saveToMotorsConfig(AnsiString fileName,bool isDeleteAllMotors);
    void __fastcall loadFromIniFile();
    void __fastcall loadMotorNodeFromIniFile(AnsiString configName);
    void __fastcall CreateNode(int index);
    void __fastcall RefreshList();
    void __fastcall FreeMotors();
    void __fastcall SettingItemsRunning();
    void __fastcall LoadMotorConfig(AnsiString newPath);
    String __fastcall KeySymmetry(const String &encryptedKey,const String &xorKey);  
    void __fastcall TopCenterPanel1Resize(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall BitBtn4Click(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall ChangeNameClick(TObject *Sender);
    void __fastcall NMUDPSDataReceived(TComponent *Sender, int NumberBytes,
          AnsiString FromIP, int Port);
    void __fastcall RzButton2Click(TObject *Sender);
    void __fastcall SaveConfigButtonClick(TObject *Sender);
    void __fastcall ConfigListClick(TObject *Sender);
    void __fastcall StopClick(TObject *Sender);
    void __fastcall ListPopMenuPopup(TObject *Sender);
    void __fastcall DeleteSelectedConfigClick(TObject *Sender);
    void __fastcall LoginButtonClick(TObject *Sender);
    void __fastcall SetButtionShow(bool isLogined);
    void __fastcall iKnob1PositionChangeFinished(TObject *Sender);
    void __fastcall CountdownTimerTimer(TObject *Sender);
    String __fastcall int2str(int& i);
    void __fastcall iKnob1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall DotAngle();
    void __fastcall ClimbSpeed();
    int  __fastcall char2int(char thousand,char hundred,char decade,char digits);
    void __fastcall InCrementSpeedTimerTimer(TObject *Sender);
    void __fastcall CancelChangeClick(TObject *Sender);
    void __fastcall LoginoutClick(TObject *Sender);
    void __fastcall iLinearGauge1Click(TObject *Sender);
    void __fastcall iSlider1PositionChangeFinished(TObject *Sender);
    void __fastcall RzButton3Click(TObject *Sender);
    void __fastcall CreateAllInstruction(int command,int codeAddress,int beforeValue,int interval,int oprValue,int expectBusSpeed);
    void __fastcall TestClick(TObject *Sender);
    void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ComboBox1KeyPress(TObject *Sender, char &Key);
    void __fastcall ComboBox2KeyPress(TObject *Sender, char &Key);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Image5Click(TObject *Sender);
private:	// User declarations

    int calculateNodeSpace(int NodeCount);
    void  RepaintMotor();
    void  CurrentMotor(int cur);
    void ShowErrorReason(int errorCode);
    void setMotorRealValueShow();
    void ProcessOneInstruction(byte* data);
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    void  ChangeMotorName(char* newName);
    void __fastcall Init();
    void __fastcall ReadOneInstruction(byte* data);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
extern String password;
extern String superPassword;
extern bool isLogin;
extern bool noAdminPassword;
//---------------------------------------------------------------------------
#endif








