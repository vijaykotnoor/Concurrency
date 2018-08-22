#include <iostream>
#include <stdlib.h>
#include <gmock/gmock.h>
#include "../src/ParellelAccumulate.h"

using namespace testing;
std::vector<ulong> numbers;
TEST(AccumulateTest, ParellelAccumulate) {
   //Create a vector of random numbers

    auto result = parellel_accumulate(numbers.begin(), numbers.end(), numbers[0]);
    EXPECT_NE(result, 0);
}

TEST(AccumulateTest, SerialAccumulate) {
   //Create a vector of random numbers

    auto result = std::accumulate(numbers.begin(), numbers.end(), numbers[0]);
    EXPECT_NE(result, 0);
}


int main( int argc, char *argv[] ) {
    for(auto i = 0; i< 25000000 ;i++)
    {
        numbers.push_back(rand() % 10 + 1);
    }
    ::testing::InitGoogleMock( &argc, argv );
    return RUN_ALL_TESTS( );
}
