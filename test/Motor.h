#ifndef MotorH
#define MotorH

#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "iVCLComponent.hpp"
#include <ExtCtrls.hpp>
#include "iPlot.hpp"
#include "iPlotComponent.hpp"
#include "iAnalogDisplay.hpp"
#include <jpeg.hpp>
#include "iAngularGauge.hpp"
#include <Buttons.hpp>
#include "RzPanel.hpp"
#include "RzLabel.hpp"
#include "Unit1.h" 
#include "iOdometer.hpp"
#include "Frame.h"
class Motor
{
  void __fastcall  ClickedMotor(TObject* sender);
public:
        TRzPanel *panel;
        TRzLabel *numLabel;
        TRzLabel *numShow;
        TRzLabel *nameLabel;
        TRzLabel *nameShow;
        TRzLabel *settingValueLabel;
        TRzLabel *settingValueShow;
        TRzLabel *SpeedLabel;
        TRzLabel *frequencySpeedRatioValue;
        TRzLabel *busSpeedRatioValue;
        TRzLabel *PID;
        TiOdometer *dometer;
	Motor(TRzPanel* panelInFrame);
        ~Motor();
    void CreateMotor();

private:
        
       // TImage *connectLine;
};
#endif
