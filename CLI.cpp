#include "libs.h"
#include "tape_emulation.cpp"
#include "insertion_sort.cpp"

int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    int memoryLimit = 1024 * 1024; // 1 MB для примера
    std::string tempDir = "tmp";

    try 
    {
        Tape inputTape(inputFilename);
        Tape outputTape(outputFilename);

        ExternalSorter sorter(memoryLimit, tempDir);
        sorter.sort(inputTape, outputTape);
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    std::cout << "Sorting completed successfully.\n";
    return 0;
}
