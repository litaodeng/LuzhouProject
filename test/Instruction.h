#ifndef INSTRUCTIONH
#define INSTRUCTIONH
class Instruction{

private:
    byte data[26];
public:
    byte* getData();
    Instruction(int frameID,int motorID,int command,int codeAddress,
                double paramValue,int oprValue,double settingValue);
    Instruction(byte* data);
    ~Instruction();
};
#endif

