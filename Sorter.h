#ifndef SORTER_H
#define SORTER_H

#include "TapeInterface.h"

class Sorter 
{
private:
    TapeInterface& tape;

public:
    Sorter(TapeInterface& tape);
    void sort();
};

#endif // SORTER_H
