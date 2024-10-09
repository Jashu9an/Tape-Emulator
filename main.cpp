#include "TapeEmulator.h"
#include "Sorter.h"

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <config_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    
    // Пример конфигурации (можно расширить для чтения из файла)
    int readDelay = 100; // миллисекунды
    int writeDelay = 100; // миллисекунды

    TapeEmulator tape(inputFile, outputFile, readDelay, writeDelay);
    
    Sorter sorter(tape);
    sorter.sort();

    return 0;
}
