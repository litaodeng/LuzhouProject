//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "ChangeMotorName.h"
#include "Unit1.h"
#include "PreViewForm.h"
#include<strstream>
#include<deque.h>
#include<map.h>
#include<set.h>
#include<time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "iComponent"
#pragma link "iCustomComponent"
#pragma link "iStripChart"
#pragma link "iVCLComponent"
#pragma link "iPlot"
#pragma link "iPlotComponent"
#pragma link "iMotor"
#pragma link "iPipe"
#pragma link "iSevenSegmentClockSMPTE"
#pragma link "iSevenSegmentDisplay"
#pragma link "iAnalogDisplay"
#pragma link "iSevenSegmentAnalog"
#pragma link "iKnob"
#pragma link "iPositionComponent"
#pragma link "iScaleComponent"
#pragma link "iAngularGauge"
#pragma link "iGaugeComponent"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "iOdometer"
#pragma link "iLed"
#pragma link "iLedRound"
#pragma link "RzButton"
#pragma link "pngimage"
#pragma link "RzLstBox"
#pragma link "RzShellDialogs"
#pragma link "iLabel"
#pragma link "iSevenSegmentCharacter"
#pragma link "iLinearGauge"
#pragma link "iSlider"
#pragma link "RzBorder"
#pragma resource "*.dfm"
#define PI 3.1415926
#define TRANSTATIONRATIO 1
#define CAN_PACK_SIZE 13
#define RS485_PACK_SIZE 11

typedef struct {
	int num;
	double speed;
	bool active;
	int errorcode;
	int count;
} CAMERAINFO;
std::deque<byte> receiveQueue;
std::set<int> aliveMotor;
int backBeforePositionNumber=0;
const int maxCountOfMotor=10;
const String iniFile="config.ini";
const String topSection="TopSection";
const String applicationWidth="ApplicationWidth";
const String leftMargin="LeftWidthPercent";
const String rightMargin="rightWidthPersent";
const String configFileName="defaultConfig";
const String removedPath="DeletedFolder";
const AnsiString sPath="Configuration";
const String xorKey="generaticKey";
const String busSpeed="BusSpeed";
const String spanName="SpanOfBottle";
const String iSlider="IncrementPerSecondValue";
const String busSpeedRatioName="BusSpeedRatio";
String password;
String superPassword="zlhl110";
float appWidth=1000;
float persentLeft=0.10;
float persentRight=0.10;
const String motorNodeSection="MotorNodeSection";
const String motorNum="MotorCount";
const String nodePosition="Motor";
const String frequencySpeedRatio="FrequencySpeedRotio";
String currentMotorConfig="";
int currentMotorIndex;
TMainForm *MainForm;
int x;
Motor* currentMotor;
TImage* connectLines[maxCountOfMotor];
Motor* motors[maxCountOfMotor];
const int totalSize=10;
int motorCount=0;
bool isRunning=false;
AnsiString currentPath="";
TSearchRec sr;
bool isLogin=false;
int beforePosition;
int countdownTime=5;
int expectBusSpeed;
bool canceledIncrementSpeed=true;
int speedOfCurrentBus;
bool noAdminPassword=true;
//const String  Node_X="X";
int predictionByCamera=0;
int setingByKnob=0;
TQueue *sendQueue=new TQueue;
TQueue *reciveQueue=new TQueue;
int changeInterval;
int span;
int busSpeedRatio;
AnsiString nowCamera = "null";
int intimeSpeed=0;

//---------------------------------------------------------------------------
/*
    程序启动，获取当前路径保存到currentPath,并判断是否存在目录"Configuration"
    再判断是否存在用于保存删除文件的目录
    启动酒瓶计数程序
    并从Config.ini加载配置文件
*/



__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    currentPath=GetCurrentDir();
    if(!(DirectoryExists(removedPath))){
        if(!CreateDir(removedPath)){
            throw Exception("Cannot create delete folder:"+removedPath);
        }
    }
    if(!(DirectoryExists(sPath))){
        if(!CreateDir(sPath)){
            throw Exception("Cannot create delete folder:"+sPath);
        }
    }
    
    //加载配置文件
    loadFromIniFile();
    //刷新左边的文件列表
    RefreshList();

}
/*
    从配置文件加载配置参数
*/
//---------------------------------------------------------------------------
void __fastcall TMainForm::loadFromIniFile(){
    TIniFile* ini=new TIniFile(ExtractFilePath(Application->ExeName)+iniFile);
    appWidth=ini->ReadInteger(topSection,applicationWidth,GetSystemMetrics(SM_CXSCREEN));
    persentLeft=ini->ReadFloat(topSection,leftMargin,0.1);
    persentRight=ini->ReadFloat(topSection,rightMargin,0.05);
    const String encrytKey=ini->ReadString(topSection,"AdminPWD","");
    password=KeySymmetry(encrytKey,xorKey);
    if(password!="")
        noAdminPassword=false;
    MainForm->Width=appWidth;
    TopLeftPanel->Width=appWidth*persentLeft;
    TopRightPanel->Width=appWidth*persentRight;
    currentMotorConfig=ini->ReadString(motorNodeSection,configFileName,"默认.ini");
    loadMotorNodeFromIniFile(currentMotorConfig);
    delete ini;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::loadMotorNodeFromIniFile(AnsiString ConfigName){
    TIniFile* ini;
    if(FileExists(ConfigName)){
        ini=new TIniFile(ConfigName);
        int readCount=ini->ReadInteger(motorNodeSection,motorNum,0);
        int before_Speed=ini->ReadInteger(motorNodeSection,busSpeed,0);
        iSlider1->Position=ini->ReadInteger(motorNodeSection,iSlider,1);
        span=ini->ReadInteger(motorNodeSection,spanName,5);
        RzLabel18->Caption="爬坡率："+FloatToStr((int)iSlider1->Position)+"瓶/时";
        iKnob1->Position=before_Speed;
        DotAngle();
        for(int i=0;i<readCount;i++){
            CreateNode(i);
            motors[i]->numShow->Caption=ini->ReadString(motorNodeSection,nodePosition+"_"+i+"_Number",motors[i]->numShow->Caption);
            motors[i]->nameShow->Caption=ini->ReadString(motorNodeSection,nodePosition+"_"+i+"_Name",motors[i]->nameShow->Caption);
            motors[i]->dometer->Value=ini->ReadFloat(motorNodeSection,nodePosition+"_"+i+"_MotorSpeed",motors[i]->dometer->Value);
            motors[i]->settingValueShow->Caption=ini->ReadString(motorNodeSection,nodePosition+"_"+i+"_SettingValue",motors[i]->settingValueShow->Caption);
            motors[i]->frequencySpeedRatioValue->Caption=ini->ReadFloat(motorNodeSection,nodePosition+"_"+i+"_FrequencySpeedRatioValue",motors[i]->frequencySpeedRatioValue->Caption.ToDouble());
            motors[i]->busSpeedRatioValue->Caption=ini->ReadFloat(motorNodeSection,nodePosition+"_"+i+"_"+busSpeedRatioName,motors[i]->busSpeedRatioValue->Caption.ToDouble());
            motors[i]->PID->Caption=ini->ReadInteger(motorNodeSection,nodePosition+"_"+i+"_PID",motors[i]->PID->Caption.ToInt());
        }
        delete ini;
    }
}
//-----------------------------------------------------------------------------
void __fastcall TMainForm::CreateNode(int index){
    if(index>=0&&index<totalSize){
        motors[index]=new Motor(TopCenterPanel);
        AnsiString s="motor_"+AnsiString(index);
        motors[index]->panel->Name=s;
        connectLines[index]=new TImage(this);
        connectLines[index]->Parent=TopCenterPanel;
        connectLines[index]->Height=50;
        connectLines[index]->Width=17;
        connectLines[index]->Enabled=true;
        connectLines[index]->Visible=true;
        connectLines[index]->Picture->LoadFromFile(currentPath+"\\pipes.jpg");
        CurrentMotor(index);
        motorCount++;
    }
}

//---------------------------------------------------------------------------
int TMainForm::calculateNodeSpace(int NodeCount){
    //计算间距，要减去每个节点本身的长度
    int centerWidth=appWidth*(1-persentLeft-persentRight);
    return (centerWidth-((LeftCameraLine->Width*2)*NodeCount))/(NodeCount+1);
}

//---------------------------------------------------------------------------
int  y=20.0;

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
        iStripChart5->XAxisMax = (1.0/(24.0*60.0)); //1 minute
        //Since the range and number of points that will be plotted on the Strip Chart
        //over a range of 1 minute, we will need to enable the Data Draw Min Max
        //property of the Strip Chart to minimize CPU utilization for this chart.
        iStripChart5->EnableDataDrawMinMax = True;
        MainForm->DoubleBuffered=true;
        MainControlPanel->DoubleBuffered=true;
        iPipe1->FlowOn=false;
        //启动酒瓶计算的程序：
        char* cmd="C:/Users/李涛/Desktop/temp/Release/BottleCounting.exe";
        WinExec(cmd,SW_HIDE);
        //system(cmd);
        Init();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Init(){
    //发送查询电机速度的指令
    for(int i=1;i<=motorCount;i++){
        Instruction *ins=new Instruction(motors[i-1]->PID->Caption.ToInt(),motors[i-1]->PID->Caption.ToInt(),1,0xac,0,0,0);
        ClientSocket1->Socket->SendBuf(ins->getData(),26);
    }

}
void __fastcall TMainForm::Timer2Timer(TObject *Sender)
{
        //Strip Chart #5
        //iStripChart.AddIndexTimeNow (XAxisDateTimeEnabled=TRUE)
        //============================================================================
        //Add index time since the last time we executed ResetElapsedStartTime.
        //(Both Y-components will be synchronized to this X-component)
        iStripChart5->AddIndexTimeNow();  //The units here are in time date format and
        //the value added is the current system time.
        //Set the data point for Channel 0 (this is the Y-component for Channel 0)
        iStripChart5->ChannelData[0][-1] = setingByKnob*TRANSTATIONRATIO;
        //Set the data point for Channel 1 (this is the Y-component for Channel 1)
        if(isRunning){
            iStripChart5->ChannelData[1][-1] = predictionByCamera;
        }else{
            iStripChart5->ChannelData[1][-1] =intimeSpeed*TRANSTATIONRATIO;
        }
        SYSTEMTIME st = {0};
        GetLocalTime(&st);
        char buf[20];
        sprintf(buf,"%02d:%02d:%02d",st.wHour,st.wMinute,st.wSecond);
        RzLEDDisplay1->Caption= AnsiString(buf);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
        
  CreateNode(motorCount);
  RepaintMotor();

}
//---------------------------------------------------------------------------
void TMainForm::CurrentMotor(int i){
    currentMotor=motors[i];
    
}
//---------------------------------------------------------------------------
void  TMainForm::RepaintMotor(){
    if(motorCount>0){
        int spans=calculateNodeSpace(motorCount);
        for(int i=0;i<motorCount;i++){
            if(motors[i]==NULL)
                 return;
            motors[i]->numShow->Caption=motors[i]->panel->Name;
            connectLines[i]->Top=iPipe1->Top+iPipe1->Height;
            connectLines[i]->Left=(i+1)*spans+(i-1)*(LeftCameraLine->Width*2);
            //中间newImage的正中心然后减去motor宽带的二分之一 ，将motor[i]定位到连线的中间
            motors[i]->panel->Left=((connectLines[i]->Left)+(connectLines[i]->Width)/2)-(motors[i]->panel->Width)/2;
            motors[i]->panel->Top=iPipe1->Top+iPipe1->Height+connectLines[i]->Height;
            if(i==currentMotorIndex){
                motors[i]->panel->BorderColor=RGB(22,156,157);
                motors[i]->panel->BorderInner=fsNone;
                motors[i]->panel->BorderOuter=fsNone;

            }else{
                motors[i]->panel->BorderColor=clMedGray;
                motors[i]->panel->BorderInner=fsNone;
                motors[i]->panel->BorderOuter=fsBump;
            }
        }
        MainControlPanel->Width=MainForm->Width-Top->Width;
        iStripChart5->Align=alLeft;
    }
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------//((TImage *)Source)->Left=X-(((TImage *)Source)->Width/2);

//---------------------------------------------------------------------------
void __fastcall TMainForm::saveToIniFile(){

    TIniFile* ini=new TIniFile(currentPath+"\\"+iniFile);
    //ini->EraseSection(motorNodeSection);
    ini->WriteString(topSection,applicationWidth,MainForm->Width);
    ini->WriteString(topSection,leftMargin,persentLeft);
    ini->WriteString(topSection,rightMargin,persentRight);               
    ini->WriteString(topSection,"AdminPWD",KeySymmetry(password,xorKey));
    ini->WriteString(motorNodeSection,configFileName,currentMotorConfig);
    delete ini;
    saveToMotorsConfig(currentMotorConfig,true);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::saveToMotorsConfig(AnsiString fileName,bool isDeleteAllMotors){
    //判断fileName是不是文件
    int pos=fileName.Pos(".ini");
    if(pos>0){
        TIniFile* ini=new TIniFile(fileName);
        ini->EraseSection(motorNodeSection);
        //将每个电机参数写入配置
        //写入电机数量
        ini->WriteInteger(motorNodeSection,motorNum,motorCount);
        ini->WriteInteger(motorNodeSection,busSpeed,iKnob1->Position);
        ini->WriteInteger(motorNodeSection,iSlider,iSlider1->Position);
        ini->WriteInteger(motorNodeSection,spanName,span);
        ini->WriteFloat(motorNodeSection,busSpeedRatioName,busSpeedRatio);
        for(int i=0;i<motorCount;i++){
            ini->WriteInteger(motorNodeSection,nodePosition+"_"+i+"_X",connectLines[i]->Left);
            ini->WriteString(motorNodeSection,nodePosition+"_"+i+"_Number",motors[i]->numShow->Caption);
            ini->WriteString(motorNodeSection,nodePosition+"_"+i+"_Name",motors[i]->nameShow->Caption);
            ini->WriteString(motorNodeSection,nodePosition+"_"+i+"_MotorSpeed",motors[i]->dometer->Value);
            ini->WriteString(motorNodeSection,nodePosition+"_"+i+"_SettingValue",motors[i]->settingValueShow->Caption);
            ini->WriteString(motorNodeSection,nodePosition+"_"+i+"_FrequencySpeedRatioValue",motors[i]->frequencySpeedRatioValue->Caption);
            ini->WriteFloat(motorNodeSection,nodePosition+"_"+i+"_"+busSpeedRatioName,motors[i]->busSpeedRatioValue->Caption.ToDouble());
            ini->WriteInteger(motorNodeSection,nodePosition+"_"+i+"_PID",motors[i]->PID->Caption.ToInt());
            if(isDeleteAllMotors){
                motors[i]->~Motor();
                motors[i]=NULL;
            }
        }
        delete ini;
    }else{

    }
}
//--------------------------------------------------------------------------




void __fastcall TMainForm::TopCenterPanel1Resize(TObject *Sender)
{
    appWidth=MainForm->Width;
    TopCenterPanel->Align=alClient;
    iPipe1->Left=0;
    iPipe1->Width=TopCenterPanel->Width;
    //RzPanel2->Left=(TopCenterPanel->Width)/2-RzPanel2->Width;
    //RzPanel3->Left=(TopCenterPanel->Width)/2;
    TopLeftPanel->Width=MainForm->Width*persentLeft;
    TopRightPanel->Width=MainForm->Width*persentRight;
    LeftCameraLine->Left=40;
    Image2->Left=(LeftCameraLine->Left+LeftCameraLine->Width/2)-Image2->Width/2;
    ComboBox1->Left=Image2->Left+Image2->Width-4;
    RzLabel12->Left=ComboBox1->Left;
    RzLabel12->Top=ComboBox1->Top-RzLabel12->Height;
    flowLabel->Left=Image2->Left+Image2->Width-4;
    RightCameraLine->Left=TopCenterPanel->Width-150;
    Image4->Left=(RightCameraLine->Left+RightCameraLine->Width/2)-Image4->Width/2;
    ComboBox2->Left=Image4->Left+Image4->Width-4;
    RzLabel20->Left=ComboBox2->Left;
    RzLabel20->Top=ComboBox2->Top-RzLabel20->Height;
    iAnalogDisplay1->Left=Image4->Left+Image4->Width-4;
    if(motorCount>0){
        for(int i=0;i<motorCount;i++){
            if(motors[i]==NULL)
                CreateNode(i);
        }
    }
    RepaintMotor();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
    if(currentMotorIndex<motorCount-1)
    {
        currentMotorIndex++;
        RepaintMotor();
    }
    else{
        currentMotorIndex=motorCount-1;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
    if(motorCount>0){
        motors[currentMotorIndex]->~Motor();
        delete(connectLines[currentMotorIndex]);
        for(int i=currentMotorIndex;i<motorCount-1;i++){
            motors[i]=motors[i+1];
            AnsiString s="motor_"+AnsiString(i);
            motors[i]->panel->Name=s;
            connectLines[i]=connectLines[i+1];
        }
        motors[motorCount-1]=NULL;
        connectLines[motorCount-1]=NULL;
        motorCount--;
        if(currentMotorIndex>0){
            currentMotorIndex--;
        }
    }
    else{
         motorCount=0;
    }
    RepaintMotor();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
    if(currentMotorIndex>0){
       currentMotorIndex--;
       RepaintMotor();
    }
    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ChangeNameClick(TObject *Sender)
{
     if(currentMotorIndex<0||currentMotorIndex>motorCount){
        if(motorCount>0){
            currentMotorIndex=0;
        }else{
            ShowMessage("没有设备");
        }
     }else if(motorCount!=0){
        MainForm->Enabled=false;
        ChangeMotorNameForm->Show();
        ChangeMotorNameForm->NewName->SetFocus();
        ChangeMotorNameForm->BeforeName->Caption=motors[currentMotorIndex]->nameShow->Caption;

     }
}
//---------------------------------------------------------------------------


void TMainForm::ChangeMotorName(char* newName){
    motors[currentMotorIndex]->nameShow->Caption=newName;
}




void __fastcall TMainForm::NMUDPSDataReceived(TComponent *Sender,
      int NumberBytes, AnsiString FromIP, int Port)
{

    int i;
    CAMERAINFO cameraInfo;
    NMUDPS->ReadBuffer((char*)&cameraInfo,NumberBytes, i);
    int cameraID=cameraInfo.num;
    bool cameraAlive=cameraInfo.active;
    if(0 > ComboBox1->Items->IndexOf(AnsiString(cameraID))) {
        ComboBox1->Items->Add(AnsiString(cameraID));
    }
    if(0 > ComboBox2->Items->IndexOf(AnsiString(cameraID))) {
        ComboBox2->Items->Add(AnsiString(cameraID));
    }
    int cameraCount=cameraInfo.count;
    if(cameraAlive==true){
    
        predictionByCamera=(int)cameraInfo.speed;
        if(ComboBox1->Text == "" || ComboBox1->Text == NULL) {
            ComboBox1->Text = AnsiString(cameraID);
        }else if(ComboBox1->Text == AnsiString(cameraID)) {
            flowLabel->Value=predictionByCamera;
            //return;
        }
        if(ComboBox2->Text == ""|| ComboBox2->Text == NULL) {
            ComboBox2->Text = AnsiString(cameraID);
        }else if(ComboBox2->Text == AnsiString(cameraID)) {
            iAnalogDisplay1->Value=predictionByCamera;
            //return;
        }
        if(!isRunning){
            iAnalogDisplay1->Value=0;
            flowLabel->Value=0;
        }

        if(ComboBox1->Text == AnsiString(cameraID)){
            RzLabel12->Visible=true;
            RzLabel12->Caption=AnsiString(cameraID)+"号摄像头正常！";
        }
        if(ComboBox2->Text == AnsiString(cameraID)){
            RzLabel20->Visible=true;
            RzLabel20->Caption=AnsiString(cameraID)+"号摄像头正常！";
        }
    }
    else{
        if(ComboBox1->Text == AnsiString(cameraID)){
            RzLabel12->Visible=true;
            RzLabel12->Caption=AnsiString(cameraID)+"号 error " + AnsiString(cameraInfo.errorcode);
        }
        if(ComboBox2->Text == AnsiString(cameraID)){
            RzLabel20->Visible=true;
            RzLabel20->Caption=AnsiString(cameraID)+"号 error  " + AnsiString(cameraInfo.errorcode);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RzButton2Click(TObject *Sender)
{
    WriteConfigDialog->InitialDir=currentPath+"\\"+sPath;
    WriteConfigDialog->FileName="";
    if(WriteConfigDialog->Execute()){
        isRunning=false;
        LoadMotorConfig(WriteConfigDialog->FileName);
        SettingItemsRunning();
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadMotorConfig(AnsiString newConfigPath){
    if(newConfigPath==currentMotorConfig){
    }
    else if(newConfigPath!=""){
        /*String oldConfigName="";
        AnsiString tmp=WriteConfigDialog->FileName;
        int pos=tmp.Pos("历史配置");
        if(pos!=0){
            oldConfigName=WriteConfigDialog->FileName;
            currentMotorConfig=WriteConfigDialog->FileName.SubString(0,pos-1)+".ini";
        }else{
            String subStr=WriteConfigDialog->FileName.SubString(0,WriteConfigDialog->FileName.Length()-4);
            oldConfigName=subStr+"历史配置.ini";
        }
        remove(oldConfigName.c_str());
        rename(currentMotorConfig.c_str(),oldConfigName.c_str());
        */
        saveToMotorsConfig(currentMotorConfig,true);
        for(int i=0;i<motorCount;i++)
            connectLines[i]->Free();
        motorCount=0;
        loadMotorNodeFromIniFile(newConfigPath);
        currentMotorConfig=newConfigPath;
        iPipe1->FlowOn=false;
        //将选中的电机定位，也就是黑色圈圈
        if(currentMotorIndex<0||currentMotorIndex>motorCount){
            if(motorCount>0){
                currentMotorIndex=0;
            }else{
                ShowMessage("没有设备");
            }
        }
    }
}
//------------------------------------------------------------------------------
void __fastcall TMainForm::SaveConfigButtonClick(TObject *Sender)
{
    SaveConfig->InitialDir=currentPath+"\\Configuration";
    SaveConfig->Title="保存配置文件";
    SaveConfig->Filter="配置文件(*.ini)|(*.ini)";
    if(SaveConfig->Execute()){
        if(SaveConfig->FileName!=""){
            String NewFileName=SaveConfig->FileName+".ini";
            TIniFile* ini=new TIniFile(NewFileName);
            ini->EraseSection(motorNodeSection);
            //将每个电机参数写入配置
            //写入电机数量
            ini->WriteInteger(motorNodeSection,motorNum,0);
            delete ini;
            LoadMotorConfig(NewFileName);
            SettingItemsRunning();
        }
    }else{

    }

    RefreshList();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMainForm::RefreshList(){
    //刷新列表文件
    ConfigList->Clear();

    if(FindFirst(currentPath+"\\"+sPath+"\\*.ini",faAnyFile,sr)==0){
        do{
            ConfigList->Items->Add(sr.Name);
        }while(FindNext(sr)==0);
        FindClose(sr);
    }
    for(int i=0;i<ConfigList->Items->Count;i++){
        AnsiString fileName=ConfigList->Items->Strings[i];
        if(currentMotorConfig.Pos(fileName)!=0)
            ConfigList->Selected[i]=true;
    }
}


void __fastcall TMainForm::ConfigListClick(TObject *Sender)
{
    if(!isRunning){
        //搜索Configuration目录下的文件
        for(int i=0;i<ConfigList->Items->Count;i++){
            if(ConfigList->Selected[i]){
                AnsiString s=ConfigList->Items->Strings[i];
                AnsiString newConig=currentPath+"\\"+sPath+"\\"+s;
                LoadMotorConfig(newConig);
            }
        }
    }
}
//---------------------------------------------------------------------------

int runningIndex=0;


void __fastcall TMainForm::StopClick(TObject *Sender)
{
    if(isRunning){
        ConfigList->Enabled=true;
        RzButton2->Enabled=true;
        iPipe1->FlowOn=false;
        isRunning=false;
        RunningStatusLabel->Caption="停止作业";
        //停止时候，需要将ListBox的节点的Selected设置为正在运行的。
        ConfigList->ItemIndex=runningIndex;
        currentMotorConfig=currentPath+"\\"+sPath+"\\"+ConfigList->Items->Strings[ConfigList->ItemIndex];
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListPopMenuPopup(TObject *Sender)
{
    
    ConfigList->OnClick(this);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::DeleteSelectedConfigClick(TObject *Sender)
{
    int curIndex=ConfigList->ItemIndex;
    if(ConfigList->Count>0&&curIndex>-1){
        String deleteName=ConfigList->Items->Strings[curIndex];
        if(!currentMotorConfig.Pos(deleteName)||!isRunning){
            AnsiString deleteFolderPath=currentPath+"\\"+removedPath;
            if(!(DirectoryExists(deleteFolderPath))){
                if(!CreateDir(deleteFolderPath)){
                    throw Exception("Cannot create delete folder:"+deleteFolderPath);
                }
            }
            String deleteMessage="确定要删除文件："+ConfigList->Items->Strings[ConfigList->ItemIndex]+"?";
            int DeleteResult=Application->MessageBox(deleteMessage.c_str(),"确认信息框",MB_OKCANCEL|MB_ICONWARNING);
            if(DeleteResult==1){
                int retu = MoveFileEx((sPath+"\\"+deleteName).c_str(),(deleteFolderPath+"\\"+deleteName).c_str(),MOVEFILE_REPLACE_EXISTING);
                remove((currentPath+"\\"+sPath+"\\"+deleteName).c_str());
                ConfigList->Items->Delete(curIndex);
                if(ConfigList->Count>0){
                    String newConfigName=currentPath+"\\"+sPath+"\\"+ConfigList->Items->Strings[0];
                    ConfigList->ItemIndex=0;
                    FreeMotors();
                    currentMotorConfig=newConfigName;
                    loadMotorNodeFromIniFile(newConfigName);
                }else{
                    FreeMotors();
                    currentMotorConfig="";
                }
            }else{

            }

        }else{
            Application->MessageBoxA("正在运行中的配置或者当前配置不允许删除！","错误信息框",MB_ICONERROR);
        }
    }else{
            Application->MessageBoxA("没有配置文件！","错误信息框",MB_ICONERROR);

    }
    RefreshList();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FreeMotors(){
    for(int i=0;i<motorCount;i++){
        motors[i]->~Motor();
        connectLines[i]->Free();
    }
    motorCount=0;

}
//----------------------------------------------------------------------------
void __fastcall TMainForm::SettingItemsRunning(){
    for(int i=0;i<ConfigList->Items->Count;i++){
        AnsiString fileName=ConfigList->Items->Strings[i];
        if(currentMotorConfig.Pos(fileName)!=0)
            ConfigList->Selected[i]=true;
        }
}
void __fastcall TMainForm::LoginButtonClick(TObject *Sender)
{
    if(password==""){
        Application->MessageBox("未设置管理员密码！","提示",MB_ICONWARNING);
        noAdminPassword=true;
        AdminLogin->ForgetPWD->OnClick(Sender);
    }else{
        MainForm->Enabled=false;
        AdminLogin->Show();
        AdminLogin->Enabled=true;
        AdminLogin->PasswordEdit->SetFocus();
    }
}
//---------------------------------------------------------------------------


String __fastcall TMainForm::KeySymmetry(const String &encryptedKey,const String &xorKey){
    if(encryptedKey==NULL){
        return NULL;
    }
    String output;
    output.SetLength(encryptedKey.Length());
    for(unsigned int i=1,j=1;i<=encryptedKey.Length();i++){
        output[i]=encryptedKey[i]^xorKey[j==xorKey.Length()?1:j++];
    }
    return output;
}

void __fastcall TMainForm::SetButtionShow(bool isLogined){
    if(isLogined){
        BitBtn1->Visible=true;
        BitBtn2->Visible=true;
        BitBtn3->Visible=true;
        BitBtn4->Visible=true;
        ChangeName->Visible=true;
        RzButton2->Visible=true;
        SaveConfigButton->Visible=true;
        DeleteSelectedConfig->Visible=true;
        Loginout->Visible=true;
        LoginButton->Visible=false;
    }else{
        BitBtn1->Visible=false;
        BitBtn2->Visible=false;
        BitBtn3->Visible=false;
        BitBtn4->Visible=false;
        ChangeName->Visible=false;
        RzButton2->Visible=false;
        SaveConfigButton->Visible=false;
        DeleteSelectedConfig->Visible=false;
        Loginout->Visible=false;
        LoginButton->Visible=true;
    }

}



void __fastcall TMainForm::iKnob1PositionChangeFinished(TObject *Sender)
{
    String deleteMessage="是否将速度以每秒"+FloatToStr((int)iSlider1->Position)+"瓶调整？";
    int DeleteResult=Application->MessageBox(deleteMessage.c_str(),"确认信息框",MB_OKCANCEL|MB_ICONWARNING);
    if(DeleteResult==1){
        iLabel1->Visible=true;
        Countdown->Visible=true;
        DotAngle();
        iLabel1->Visible=true;
        Countdown->Visible=true;
        CountdownTimer->Enabled=true;
        iKnob1->Enabled = false;
        countdownTime=5;
    }else{
        
    }
    iKnob1->Position=beforePosition;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CountdownTimerTimer(TObject *Sender)
{
    if(countdownTime>=0){
        Countdown->Caption=int2str(countdownTime);
        Countdown->Caption=Countdown->Caption+"秒";
        countdownTime--;
    }
    if(countdownTime==-1){
        CountdownTimer->Enabled=false;
        Countdown->Caption="正在调整速度...";
        //创建所有指令
        CreateAllInstruction(2,3,beforePosition,iSlider1->Position,0x0012,expectBusSpeed);
        //Instruction* ins=new Instruction(1,6,2,3,10.30,0x0012,0x0A8C);
        countdownTime=5;
        ClimbSpeed();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateAllInstruction(int command,int codeAddress,int beforeValue,int interval,int oprValue,int expectBusSpeed){
    double beforeFrequency[maxCountOfMotor];
    double freqChange[maxCountOfMotor];
    double endFrequecy[maxCountOfMotor];
    int times=abs(expectBusSpeed-beforeValue)/interval;
    int flag=(expectBusSpeed-beforeValue)>=0?1:-1;
    for(int i=0;i<motorCount;i++){
        beforeFrequency[i]=(((double)iKnob1->Position*span)/motors[i]->busSpeedRatioValue->Caption.ToInt())/motors[i]->frequencySpeedRatioValue->Caption.ToInt();
        //瓶子增加数量*瓶间距/总线到每个电机速度比/速度频率比
        endFrequecy[i]=(((double)expectBusSpeed*span)/motors[i]->busSpeedRatioValue->Caption.ToInt())/motors[i]->frequencySpeedRatioValue->Caption.ToInt();
        freqChange[i]=(((double)flag*interval*span)/motors[i]->busSpeedRatioValue->Caption.ToInt())/motors[i]->frequencySpeedRatioValue->Caption.ToInt();
    }
    for(int i=1;i<=times;i++){
        for(int motorID=1;motorID<=motorCount;motorID++){
            Instruction* ins=new Instruction(motorID,motorID,command,codeAddress,beforeFrequency[motorID-1]+i*freqChange[motorID-1],oprValue,beforeFrequency[motorID-1]+i*freqChange[motorID-1]);
            sendQueue->Push(ins);
        }
    }
    for(int motorID=1;motorID<=motorCount;motorID++){
        Instruction* ins=new Instruction(motorID,motorID,command,codeAddress,endFrequecy[motorID-1],oprValue,endFrequecy[motorID-1]);
        sendQueue->Push(ins);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClimbSpeed(){
    
    //隔1s发送一个指令增加一个速度值
    InCrementSpeedTimer->Interval=1000;
    canceledIncrementSpeed=false;
    InCrementSpeedTimer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::iKnob1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    beforePosition=iKnob1->Position;
    while(sendQueue->Count()){
        sendQueue->Pop();
    }
}


//定时器执行一次，发送改变速度指令和获取实时速度指令
void __fastcall TMainForm::InCrementSpeedTimerTimer(TObject *Sender)
{
    for(int i=0;i<motorCount;i++){
        if(sendQueue->Count()!=0){
            Instruction* ins=(Instruction*)sendQueue->Pop();
            ClientSocket1->Socket->SendBuf(ins->getData(),26);
        }
    }
    int increment=(int)iSlider1->Position;
    speedOfCurrentBus=iKnob1->Position;
    if(abs(speedOfCurrentBus-expectBusSpeed)<increment){
        iKnob1->Position=expectBusSpeed;
        speedOfCurrentBus=expectBusSpeed;
        canceledIncrementSpeed=true;
    }

    if(canceledIncrementSpeed!=true&&speedOfCurrentBus<expectBusSpeed){
        //调用发送指令增加总线转速
        iKnob1->Position+=increment;
        speedOfCurrentBus+=increment;
        //并获得实时的速度


    }else if(canceledIncrementSpeed!=true&&speedOfCurrentBus>expectBusSpeed){
        //速度向低调整
        iKnob1->Position-=increment;
        speedOfCurrentBus-=increment;
        //获得实时的速度
    }else{
        //速度调整完毕或者取消指令发送
        InCrementSpeedTimer->Enabled=false;
        iLabel1->Visible=false;
        Countdown->Visible=false;
        iKnob1->Enabled = true;
    }
    setingByKnob=iKnob1->Position*TRANSTATIONRATIO;
    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CancelChangeClick(TObject *Sender)
{
    canceledIncrementSpeed=true;
    Countdown->Caption="已取消...";
    countdownTime=5;
    CountdownTimer->Enabled=false;
    iLabel1->Visible=false;
    Countdown->Visible=false;
    iKnob1->Enabled = true;
    DotAngle();
    while(sendQueue->Count()){
        sendQueue->Pop();
    }
    setMotorRealValueShow();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LoginoutClick(TObject *Sender)
{
    isLogin=false;
    SetButtionShow(isLogin);
    AdminLogin->PasswordEdit->Text="";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TMainForm::DotAngle(){
    int Konb_Center_X=iKnob1->Left+iKnob1->Width/2;
    int Konb_Center_Y=iKnob1->Top+iKnob1->Height/2;
    int KnobRadius=iKnob1->KnobRadius;
    int TargetValueRadius=KnobRadius+20;//konb的半径增加10然后定位外面那个“目标”坐标
    int angle=iKnob1->RotationStartDegrees-iKnob1->Position*(iKnob1->RotationMaxDegrees/(iKnob1->PositionMax-iKnob1->PositionMin));
    if(angle>360){
        angle=angle-360;
    }
    iLedRound1->Top=Konb_Center_Y-(TargetValueRadius*sin(angle*PI/180))-iLedRound1->Height/2;
    iLedRound1->Left=Konb_Center_X+TargetValueRadius*cos(angle*PI/180)-iLedRound1->Height/2;
    expectBusSpeed=iKnob1->Position;
}
//---------------------------------------------------------------------------
String __fastcall TMainForm::int2str(int& i){
    char buf[10];
    sprintf(buf, "%d", i);
    String str_time = buf;
    return str_time;
}
//---------------------------------------------------------------------------
int   __fastcall TMainForm::char2int(char thousand,char hundred,char decade,char digits){
    return (thousand-'0')*1000+(hundred-'0')*100+(decade-'0')*10+(digits-'0')*1;
}
void __fastcall TMainForm::iLinearGauge1Click(TObject *Sender)
{
    //iLinearGauge1->Position=
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::iSlider1PositionChangeFinished(TObject *Sender)
{
    RzLabel18->Caption="爬坡率："+FloatToStr((int)iSlider1->Position)+"瓶/时";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::RzButton3Click(TObject *Sender)
{
    
    if(!isRunning&&ConfigList->Count>0){
        if(ConfigList->ItemIndex<0)
            ConfigList->ItemIndex=0;
        iPipe1->FlowOn=true;
        isRunning=true;
        ConfigList->Enabled=false;
        RzButton2->Enabled=false;
        RunningStatusLabel->Caption="正在作业："+ConfigList->Items->Strings[ConfigList->ItemIndex].SubString(0,ConfigList->Items->Strings[ConfigList->ItemIndex].Length()-4);
        runningIndex=ConfigList->ItemIndex;
        currentMotorConfig=currentPath+"\\"+sPath+"\\"+ConfigList->Items->Strings[ConfigList->ItemIndex];
    }else{
        ShowMessage("正在运行或者没有配置文件被选中");
    }
    
}

//----------------------------------------------------------------------------

void __fastcall TMainForm::ReadOneInstruction(byte* data){
    byte oneByte;
//    int size=ClientSocket1->Socket->ReceiveLength();
    while(-1 != ClientSocket1->Socket->ReceiveBuf(&oneByte,1)){
        //if(data != 0x5a && reciveQueue->Count()) continue;
        receiveQueue.push_back(oneByte);
    }

    // remove dirty data, deque
    while(receiveQueue.size() > 0 && receiveQueue.front() != 0x5A)
        receiveQueue.pop_front();

    while(receiveQueue.size() >= CAN_PACK_SIZE*2-5) {
        byte checksum=0;
        for(int i = 0; i < 8; i++) {
            checksum += receiveQueue[i];
        }
        checksum += receiveQueue[13];
        checksum += receiveQueue[14];
        if(checksum == receiveQueue[15]) {
            for(int i=0;i<8;i++){
                data[i]=receiveQueue.front();
                receiveQueue.pop_front();
            }
            receiveQueue.pop_front();
            receiveQueue.pop_front();
            receiveQueue.pop_front();
            receiveQueue.pop_front();
            receiveQueue.pop_front();
            data[8]=receiveQueue.front();   receiveQueue.pop_front();
            data[9]=receiveQueue.front();   receiveQueue.pop_front();
            data[10]=receiveQueue.front();  receiveQueue.pop_front();
            ProcessOneInstruction(data);
        }
        else {
            receiveQueue.pop_front();
            while(receiveQueue.size() > 0 && receiveQueue.front() != 0x5A)
                receiveQueue.pop_front();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TestClick(TObject *Sender)
{
    Instruction *ins=new Instruction(1,1,0,0,0,18,10.30);
    byte* data=ins->getData();
    ClientSocket1->Socket->SendBuf(ins->getData(),26);
    //Instruction *recivIns=ReadOneInstruction();
    char buf[100];
    sprintf(buf, "0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x  0x%x 0x%x 0x%x 0x%x",
            data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15],data[16],data[17],data[18],data[19],data[20],data[21],data[22],data[23],data[24],data[25]);
    //Memo1->Lines->Add(recivIns);
    ShowMessage(buf);
    //} */
    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
    
    byte aPackReceiveFromRS485[11];

    //测试接受的11字节是不是返回指令。
    ReadOneInstruction(aPackReceiveFromRS485);
    /*
    
    */

}
//---------------------------------------------------------------------------
void TMainForm::ShowErrorReason(int errorCode){
    switch(errorCode){
        case 1:
            Application->MessageBoxA("加速中过流！","错误",MB_ICONERROR);
            break;
        case 2:
            Application->MessageBoxA("减速中过流！","错误",MB_ICONERROR);
            break;
        case 3:
            Application->MessageBoxA("加速中过流！","错误",MB_ICONERROR);
            break;
        case 4:
            Application->MessageBoxA("加速中过压！","错误",MB_ICONERROR);
            break;
        case 5:
            Application->MessageBoxA("减速中过压！","错误",MB_ICONERROR);
            break;
        case 6:
            Application->MessageBoxA("稳态过程中过压","错误",MB_ICONERROR);
            break;
        case 7:
            Application->MessageBoxA("停机状态中过压","错误",MB_ICONERROR);
            break;
        case 8:
            Application->MessageBoxA("变频器运行中欠压！","错误",MB_ICONERROR);
            break;
        case 9:
            Application->MessageBoxA("变频器过热！","错误",MB_ICONERROR);
            break;
        case 10:
            Application->MessageBoxA("适配电机过载！","错误",MB_ICONERROR);
            break;
        case 11:
            Application->MessageBoxA("变频器过热！","错误",MB_ICONERROR);
            break;
        case 12:
            Application->MessageBoxA("接地故障！","错误",MB_ICONERROR);
            break;
        case 13:
            Application->MessageBoxA("干扰故障！","错误",MB_ICONERROR);
            break;
        case 14:
            Application->MessageBoxA("输出缺相！","错误",MB_ICONERROR);
            break;
        case 15:
            Application->MessageBoxA("IPM故障！","错误",MB_ICONERROR);
            break;
        case 16:
            Application->MessageBoxA("外部设备故障！","错误",MB_ICONERROR);
            break;
        case 17:
            Application->MessageBoxA("电流检测回路故障！","错误",MB_ICONERROR);
            break;
        case 18:
            Application->MessageBoxA("通讯故障！","错误",MB_ICONERROR);
            break;
        default:
            Application->MessageBoxA("未知错误！","错误",MB_ICONERROR);
            break;
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    switch(ErrorCode){
        case 10060:
            ClientSocket1->Socket->Close();
            ClientSocket1->Close();
            Application->MessageBoxA("CAN服务器连接失败！","错误!",MB_ICONERROR);
            saveToIniFile();
            system("taskkill /f /t /im BottleCounting.exe");
            Application->Terminate();
            ErrorCode=0;
        case 10061:
            ClientSocket1->Socket->Close();
            ClientSocket1->Close();
            Application->MessageBoxA("CAN服务器连接失败！","错误!",MB_ICONERROR);
            saveToIniFile();
            system("taskkill /f /t /im BottleCounting.exe");
            Application->Terminate();
            ErrorCode=0;
        break;
        
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox1KeyPress(TObject *Sender, char &Key)
{
    Key = 0;
    return;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox2KeyPress(TObject *Sender, char &Key)
{
    Key = 0;
    return;

}
//---------------------------------------------------------------------------

void TMainForm::setMotorRealValueShow(){
    //计算设定值
    double endFrequecy[maxCountOfMotor];
    for(int i=0;i<motorCount;i++){
        //瓶子增加数量*瓶间距/总线到每个电机速度比/速度频率比
        endFrequecy[i]=(((double)expectBusSpeed*span)/motors[i]->busSpeedRatioValue->Caption.ToInt())/motors[i]->frequencySpeedRatioValue->Caption.ToInt();
    }
    //设定电机motors的设定值
    for(int i=0;i<motorCount;i++){
        motors[i]->settingValueShow->Caption=AnsiString(endFrequecy[i])+"瓶/时";
    }
}
//---------------------------------------------------------------------------
void TMainForm::ProcessOneInstruction(byte* aPackReceiveFromRS485){


    int PID_of_pack=aPackReceiveFromRS485[1];
    aliveMotor.insert(PID_of_pack);
    //判断从机相应码
    if(aPackReceiveFromRS485[2]==0x0||aPackReceiveFromRS485[2]==0x1){
        setMotorRealValueShow();
        //设置每个小电机的设定值和实际值
        for(int i=1;i<=motorCount;i++){
            if(PID_of_pack==motors[i-1]->PID->Caption.ToInt()){
                int val=((aPackReceiveFromRS485[9]<<8)|aPackReceiveFromRS485[8]);
                motors[i-1]->dometer->Value=val/100.0;
                // 计算实时速度

                intimeSpeed=(motors[i-1]->dometer->Value*motors[i-1]->busSpeedRatioValue->Caption.ToInt())*motors[i-1]->frequencySpeedRatioValue->Caption.ToInt()/span;
                RzLabel16->Caption=AnsiString(intimeSpeed/100)+"米/小时";
                RzLabel17->Caption=AnsiString(val)+"瓶/小时";
            }
        }
    }else if(aPackReceiveFromRS485[2]==0x2){
        int errorCode=aPackReceiveFromRS485[8];
        ShowErrorReason(errorCode);
    }else{
        
    }

}












void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    saveToIniFile();
    system("taskkill /f /t /im BottleCounting.exe");
    motorCount=0;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==27){
        MainForm->Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Image5Click(TObject *Sender)
{

    MainForm->Close();    
}
//---------------------------------------------------------------------------


