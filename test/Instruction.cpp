#include <vcl.h>
#pragma hdrstop
#include "Instruction.h"
#pragma package(smart_init)

Instruction::Instruction(int frameID,int motorID,int command,int codeAddress,double paramValue,
                         int oprValue,double settingValue){
    memset(data,0,26);
    byte base=0x00;
    int iParam=paramValue * 100;
    int setParam=settingValue*100;
    data[0]=0x08;
    data[4]=(byte)(frameID&0xFF);
    data[3]=(byte)((frameID>>8)&0xFF);
    data[2]=(byte)((frameID>>16)&0xFF);
    data[1]=(byte)((frameID>>24)&0xFF);
    data[5]=0x5A;
    data[6]=base+motorID;
    data[7]=base+command;
    data[8]=base+codeAddress;
    data[9]=(byte)(iParam & 0xFF);
    data[10]=(byte)((iParam >> 8) & 0xFF);
    data[11]=(byte)(oprValue & 0xFF);
    data[12]=(byte)((oprValue >> 8) & 0xFF);

    data[13]=0x03;
    data[17]=(byte)(frameID&0xFF);
    data[16]=(byte)((frameID>>8)&0xFF);
    data[15]=(byte)((frameID>>16)&0xFF);
    data[14]=(byte)((frameID>>24)&0xFF);
    data[18]=(byte)(setParam & 0xFF);
    data[19]=(byte)((setParam >> 8) & 0xFF);
    data[20]=0;
    for(int i = 0; i < 10; i++) {
        if(i<8){
            data[20] += data[i+5];
        }else{
            data[20] += data[i+10];
        }

    }
   /*
    data[20]=data[5]+data[6]+data[7]+data[8]+data[9]+data[10]+data[11]+data[12]+data[18]+data[19];*/
    for(int i = 1; i <= 5; i++) {
        data[20+i] = i;
    }
}

Instruction::Instruction(byte* datas){
    for(int i=0;i<26;i++){
        data[i]=datas[i];
    }
}

Instruction::~Instruction(){
}
byte* Instruction::getData(){
    return data;
}

