#include "libs.h"
#include "ITape.cpp"

class Tape : public ITape 
{
private:
    std::fstream file;
    std::string filename;
    int delayRead; // Задержка на чтение
    int delayWrite; // Задержка на запись
    int delayMove; // Задержка на перемотку
public:
    Tape(const std::string& filename, int delayRead = 0, int delayWrite = 0, int delayMove = 0)
        : filename(filename), delayRead(delayRead), delayWrite(delayWrite), delayMove(delayMove) 
        {
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("Could not open file " + filename);
    }

    int read() override 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayRead)); // эмуляция задержки чтения
        int value;
        file.read(reinterpret_cast<char*>(&value), sizeof(int));
        return value;
    }

    void write(int value) override 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayWrite)); // эмуляция задержки записи
        file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }

    void rewind() override 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMove)); // эмуляция задержки перемотки
        file.clear();
        file.seekg(0);
        file.seekp(0);
    }

    void moveForward() override 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMove)); // эмуляция задержки сдвига
        file.seekg(sizeof(int), std::ios::cur);
        file.seekp(sizeof(int), std::ios::cur);
    }

    bool isEnd() override 
    {
        return file.eof();
    }

    ~Tape() 
    {
        file.close();
    }
};
