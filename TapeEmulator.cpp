#include "TapeEmulator.h"

TapeEmulator::TapeEmulator(const std::string& inputFileName, const std::string& outputFileName, int readDelay, int writeDelay)
    : currentPosition(0), readDelay(readDelay), writeDelay(writeDelay) 
{
    inputFile.open(inputFileName);
    outputFile.open(outputFileName);
}

TapeEmulator::~TapeEmulator() 
{
    if (inputFile.is_open()) inputFile.close();
    if (outputFile.is_open()) outputFile.close();
}

int TapeEmulator::read() 
{
    if (isEnd()) throw std::out_of_range("End of tape reached");
    
    int value;
    inputFile >> value;
    std::this_thread::sleep_for(std::chrono::milliseconds(readDelay));
    
    return value;
}

void TapeEmulator::write(int value) 
{
    outputFile << value << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay));
}

void TapeEmulator::rewind() 
{
    inputFile.clear();
    inputFile.seekg(0);
}

void TapeEmulator::moveNext() 
{
    currentPosition++;
}

bool TapeEmulator::isEnd() 
{
    return inputFile.eof();
}

void TapeEmulator::flush() 
{
    outputFile.flush();
}
