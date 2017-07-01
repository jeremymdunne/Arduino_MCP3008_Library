#ifndef MCP3008_h
#define MCP3008_h

#include "Arduino.h"

class MCP3008{
public: 
  MCP3008(int cs, int mosi, int miso, int sck);
  int analogReadChannel(int channel);
private: 
  int _miso, _mosi, _sck, _cs; 
  int readBits(int length); 
  void writeBits(int toSend, int length); 
}; 


#endif 