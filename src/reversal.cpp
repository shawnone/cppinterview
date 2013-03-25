#include <gtest/gtest.h>

void reversal(char* input, int16_t size)
{
    int i = 0;
    char temp = ' ';
    while(size > i)
    {
        temp = input[i];
        input[i] = input[size - 1];
        input[size - 1] = temp;
        
        ++i;
        --size;
    }
}

TEST(reversal, normal)
{
    char* input = new char[32];
    strcpy(input, "abcdefg");
    reversal(input, strlen("abcdefg"));
    
    ASSERT_STREQ(input, "gfedcba");
    
    strcpy(input, "");
    reversal(input, strlen(""));
    ASSERT_STREQ(input, "");
    
    strcpy(input, "a");
    reversal(input, strlen("a"));
    ASSERT_STREQ(input, "a");
    
    strcpy(input, "abc");
    reversal(input, strlen("abc"));
    ASSERT_STREQ(input, "cba");
}