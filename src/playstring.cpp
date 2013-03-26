#include <gtest/gtest.h>
#include <cstdint>
#include <unordered_map>

/**
Variables should be null-terminated 
*/
template <class T>
bool IsIncluded(char* source, char* toBeChecked, T& container)
{
	while(*source != '\0')
	{
		container[*source] += 1;
		++source;
	}

	while(*toBeChecked != '\0')
	{
		if(container[*toBeChecked] < 1)
		{
			return false;
		}

		++toBeChecked;
	}

	return true;
}


TEST(playstring, findsubset)
{
	std::unordered_map<char, int16_t> checkingSet;
	char* input = new char[32];
	char* input2 = new char[32];
    strcpy(input, "abcdefg");
	strcpy(input2, "ace");
    ASSERT_TRUE(IsIncluded(input, input2, checkingSet));

	strcpy(input, "ABCDEFGHLMNOPQRS");
	strcpy(input2, "DCGSRQPOZ");
    ASSERT_FALSE(IsIncluded(input, input2, checkingSet));

	delete input;
	delete input2;
}