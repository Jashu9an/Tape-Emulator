#include "libs.h"
#include "tape_emulation.cpp"

class ExternalSorter
{
private:
    int memoryLimit;
    std::string tempDir;

    void sortBlock(Tape& inputTape, Tape& tempTape, int blockSize)
    {
        std::vector<int> buffer;
        buffer.reserve(blockSize);

        // Считываем блок данных в память
        while (blockSize-- && !inputTape.isEnd()) 
        {
            buffer.push_back(inputTape.read());
            inputTape.moveForward();
        }

        // Сортируем блок в памяти
        std::sort(buffer.begin(), buffer.end());

        // Записываем отсортированный блок на временную ленту
        for (int value : buffer) 
        {
            tempTape.write(value);
            tempTape.moveForward();
        }
    }

    void merge(Tape& outputTape, std::vector<Tape>& tempTapes) 
    {
        // Многопутевое слияние из временных лент на выходную ленту
        struct TapeElement 
        {
            int value;
            Tape* tape;
            bool operator>(const TapeElement& other) const { return value > other.value; }
        };

        std::priority_queue<TapeElement, std::vector<TapeElement>, std::greater<TapeElement>> minHeap;

        // Инициализация кучи
        for (Tape& tape : tempTapes) 
        {
            if (!tape.isEnd()) 
            {
                int value = tape.read();
                minHeap.push({value, &tape});
                tape.moveForward();
            }
        }

        // Слияние
        while (!minHeap.empty()) 
        {
            TapeElement smallest = minHeap.top();
            minHeap.pop();

            outputTape.write(smallest.value);
            outputTape.moveForward();

            if (!smallest.tape->isEnd()) 
            {
                int value = smallest.tape->read();
                minHeap.push({value, smallest.tape});
                smallest.tape->moveForward();
            }
        }
    }

public:
    ExternalSorter(int memoryLimit, const std::string& tempDir)
        : memoryLimit(memoryLimit), tempDir(tempDir) {}

    void sort(Tape& inputTape, Tape& outputTape) 
    {
        std::vector<Tape> tempTapes;

        // Разбиение данных на блоки и их сортировка
        while (!inputTape.isEnd()) 
        {
            std::string tempFilename = tempDir + "/temp" + std::to_string(tempTapes.size()) + ".dat";
            Tape tempTape(tempFilename);

            sortBlock(inputTape, tempTape, memoryLimit / sizeof(int));
            tempTape.rewind();
            tempTapes.push_back(std::move(tempTape));
        }

        // Слияние отсортированных блоков
        merge(outputTape, tempTapes);
    }
};
