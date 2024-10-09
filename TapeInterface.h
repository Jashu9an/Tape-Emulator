#ifndef TAPEINTERFACE_H
#define TAPEINTERFACE_H

#include "libs.h"

class TapeInterface
{
public:
    virtual ~TapeInterface() = default;
    
    virtual int read() = 0;
    virtual void write(int value) = 0;
    virtual void rewind() = 0;
    virtual void moveNext() = 0;
    virtual bool isEnd() = 0;
};

#endif // TAPEINTERFACE_H
