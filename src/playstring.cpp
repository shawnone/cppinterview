#include <gtest/gtest.h>
#include <cstdint>
#include <bitset>
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

bool IsIncluded(char* source, char* toBeChecked)
{
	std::bitset<10000> checkSet;
	
	while(*source != '\0')
	{
		checkSet.set(*source);
		++source;
	}
	
	while(*toBeChecked != '\0')
	{
		if(!checkSet.test(*toBeChecked))
		{
			return false;
		}
		++toBeChecked;
	}
	return true;
}

TEST(playstring, findsubset_bitset)
{
	char* input = new char[32];
	char* input2 = new char[32];
	strcpy(input, "abcdefg");
	strcpy(input2, "ace");
	ASSERT_TRUE(IsIncluded(input, input2));

	strcpy(input, "ABCDEFGHLMNOPQRS");
	strcpy(input2, "DCGSRQPOZ");
	ASSERT_FALSE(IsIncluded(input, input2));

	delete input;
	delete input2;
}

/**
Variables should be null-terminated 
*/
template <class T>
bool IsMatch(char* source, char* toBeChecked, T& container)
{
	if(strlen(source) != strlen(toBeChecked))
	{
		return false;
	}

	while(*source != '\0')
	{
		container[*source] += 1;
		++source;
	}

	while(*toBeChecked != '\0')
	{
		--container[*source];

		if(container[*source] < 0)
		{
			return false;
		}

		++toBeChecked;
	}

	return true;
}

TEST(playstring, checkmatch)
{
	std::unordered_map<char, int16_t> checkingSet;
	char* input = new char[32];
	char* input2 = new char[32];
	strcpy(input, "ABBA");
	strcpy(input2, "BBAA");
	ASSERT_FALSE(IsMatch(input, input2, checkingSet));

	delete input;
	delete input2;
}

/**
Variables should be null-terminated 
*/
const char* StrStr(const char* source, const char* toBeSearched)
{
	if(source == nullptr || toBeSearched == nullptr)
	{
		return nullptr;
	}

	const char* searchBegin = source;
	const char* toBesearchedBegin = toBeSearched;

	while(*source != '\0')
	{
		searchBegin = source;
		if(*searchBegin == *toBesearchedBegin)
		{
			while(*toBesearchedBegin != '\0')
			{
				if(*searchBegin != *toBesearchedBegin)
				{
					break;
				}
				else
				{
					++toBesearchedBegin;
					++searchBegin;
				}
			}

			if(*toBesearchedBegin == '\0')
			{
				return source;
			}
		}

		++source;
		toBesearchedBegin = toBeSearched;
	}

	return nullptr;
}

TEST(playstring, strstr)
{
	std::unordered_map<char, int16_t> checkingSet;
	char* input = new char[64];
	char* input2 = new char[64];
	strcpy(input, "Variables should be null-terminated ");
	strcpy(input2, "should be null-terminated ");
	ASSERT_STREQ(input2, StrStr(input, input2));

	delete input;
	delete input2;
}