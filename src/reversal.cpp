#include <gtest/gtest.h>

#include <cstdint>

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

/**
@param shiftCount Positive value means right shift, negative value means left shift.
*/
void shift(char* input, int16_t size, int16_t shiftCount)
{
    //0 to check pointer to support old compiler
	if(shiftCount == 0 || input == 0 || size == 0)
	{
		return;
	}

	if(shiftCount > size)
	{
		shiftCount = shiftCount % size;
	}

	if(shiftCount < 0)
	{
		shiftCount = -shiftCount;
		reversal(input, shiftCount);
		reversal(input + shiftCount, size - shiftCount);
		reversal(input, size);
	}
	else if(shiftCount > 0)
	{
		reversal(input, size - shiftCount);
		reversal(input + size - shiftCount, shiftCount);
		reversal(input, size);
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

	delete input;
}

TEST(reversal, shift)
{
	char* input = new char[32];
	strcpy(input, "abcdefg");
	shift(input, strlen("abcdefg"), 2);

	ASSERT_STREQ(input, "fgabcde");

	strcpy(input, "");
	shift(input, strlen(""), 100);
	ASSERT_STREQ(input, "");
	
	strcpy(input, "a");
	shift(input, strlen("a"), 10000);
	ASSERT_STREQ(input, "a");

	strcpy(input, "abc");
	shift(input, strlen("abc"), -1);
	ASSERT_STREQ(input, "bca");

	delete input;
}