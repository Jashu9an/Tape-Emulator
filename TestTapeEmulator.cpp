#include "gtest/gtest.h"
#include "TapeEmulator.h"

TEST(TapeEmulatorTest, ReadWrite) 
{
    // Создаем временные файлы для тестирования
    std::ofstream testInput("test_input.txt");
    testInput << "3\n1\n2\n";
    testInput.close();

    TapeEmulator tape("test_input.txt", "test_output.txt", 0, 0);
    
    EXPECT_EQ(tape.read(), 3);
    EXPECT_EQ(tape.read(), 1);
    
    tape.write(2);
    
    tape.flush();

    tape.rewind();
    
    std::ifstream output("test_output.txt");
    int value;
    
    output >> value;
    EXPECT_EQ(value, 2);
    
    output.close();
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
