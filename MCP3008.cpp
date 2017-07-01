#include "MCP3008.h"

MCP3008::MCP3008(int cs, int mosi, int miso, int sck){
  _miso = miso;
  _mosi = mosi;
  _sck = sck; 
  _cs = cs; 
  pinMode(_cs,OUTPUT);
  pinMode(_miso, INPUT);
  pinMode(_mosi, OUTPUT);
  pinMode(_sck, OUTPUT); 
  digitalWrite(_cs,HIGH); 
}

int MCP3008::analogReadChannel(int channel){
  digitalWrite(_cs,HIGH); 
  digitalWrite(_sck, LOW);
  digitalWrite(_cs,LOW); 
  int command = channel | 0x18; 
  command <<= 3; 
  writeBits(command,5);
  int adcResp = readBits(12); 
  digitalWrite(_cs,HIGH);
  adcResp >>=1; 
  return adcResp; 
}

void MCP3008::writeBits(int command, int length){
  for(int i = 0; i < length; i ++){
    if(command & 0x80) digitalWrite(_mosi, HIGH); 
    else digitalWrite(_mosi,LOW); 
    command <<= 1; 
    digitalWrite(_sck, HIGH);
    digitalWrite(_sck,LOW); 
  }
}

int MCP3008::readBits(int length){
  int resp = 0; 
  for(int i = 0; i < length; i ++){
    digitalWrite(_sck,HIGH);
    digitalWrite(_sck,LOW); 
    resp <<= 0x1;
    if(digitalRead(_miso)) resp |= 1; 
  }
  return resp;  
}