#include <gtest/gtest.h>
#include "tape_emulation.cpp"

TEST(TapeTest, ReadWrite) {
    Tape tape("test.dat");

    tape.write(123);
    tape.write(456);
    tape.rewind();

    EXPECT_EQ(tape.read(), 123);
    EXPECT_EQ(tape.read(), 456);
}
