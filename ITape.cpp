#include "libs.h"

class ITape 
{
public:
    virtual int read() = 0; // Считывание элемента
    virtual void write(int value) = 0; // Запись элемента
    virtual void rewind() = 0; // Перемотка ленты
    virtual void moveForward() = 0; // Сдвиг ленты вперед
    virtual bool isEnd() = 0; // Проверка конца ленты
    virtual ~ITape() = default;
};
