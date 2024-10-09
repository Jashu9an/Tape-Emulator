#ifndef TAPEEMULATOR_H
#define TAPEEMULATOR_H

#include "TapeInterface.h"

class TapeEmulator : public TapeInterface
{
private:
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::vector<int> buffer;
    size_t currentPosition;
    int readDelay;
    int writeDelay;

public:
    TapeEmulator(const std::string& inputFileName, const std::string& outputFileName, int readDelay, int writeDelay);
    ~TapeEmulator();

    int read() override;
    void write(int value) override;
    void rewind() override;
    void moveNext() override;
    bool isEnd() override;

    void flush();
};

#endif // TAPEEMULATOR_H
