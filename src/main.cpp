//
//  main.cpp
//  cppinterview
//
//  Created by Shawnone on 13-3-25.
//
//

#include <gtest/gtest.h>

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello, World!\n";
    
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
