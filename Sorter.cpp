#include "Sorter.h"

Sorter::Sorter(TapeInterface& tape) : tape(tape) {}

void Sorter::sort() 
{
    std::vector<int> elements;

    while (!tape.isEnd()) 
    {
        elements.push_back(tape.read());
        tape.moveNext();
    }

    std::sort(elements.begin(), elements.end());

    for (int value : elements)
        tape.write(value);
}
