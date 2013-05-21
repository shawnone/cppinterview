#include <gtest/gtest.h>
#include <cstdint>
#include <algorithm>
#include <bitset>
#include <map>
#include <unordered_map>

#include <toolkit.h>

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
	if(source == 0 || toBeSearched == 0)
	{
		return 0;
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

	return 0;
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

void SubstringWithConcat(const std::string& s, const std::vector<std::string>& list, std::vector<std::string>& results)
{
	if(list.empty() || s.empty())
	{
		return;
	}
	
	uint32_t unit = list.begin()->size();
	std::string subString;
	std::string unitString;
	uint32_t pos = 0;
	
	bool ok = true;
	
	for(uint32_t length = unit; length <= unit * list.size(); length += unit)
	{
		if(length > s.size())
		{
			break;
		}
		pos = 0;
		while(pos + length <= s.size())
		{
			subString = s.substr(pos, length);
			
			ok = true;
			for(int i = 0; i < length; i += unit)
			{
				unitString = subString.substr(i, unit);
				
				if(std::find(list.begin(), list.end(), unitString) == list.end())
				{
					ok = false;
					break;
				}
				
			}
			
			if(ok)
			{
				results.push_back(subString);
			}
			
			++pos;
		}
	}
}

TEST(playstring, substring_with_concat)
{
	std::string s = "ABCACC";
	std::vector<std::string> list = {"ABC", "ACC", "CBA"};
	std::vector<std::string> results;
	SubstringWithConcat(s, list, results);
	
	std::vector<std::string> expect = {"ABC", "ACC", "ABCACC"};
	ASSERT_EQ(expect, results);
	
	s = "ABCAC";
	list = {"ABC", "BCA", "CAC"};
	results.clear();
	SubstringWithConcat(s, list, results);
	
	expect = {"ABC", "BCA", "CAC"};
	ASSERT_EQ(expect, results);
	
	s = "AB";
	list = {"AB", "CA", "CC"};
	results.clear();
	SubstringWithConcat(s, list, results);
	
	expect = {"AB"};
	ASSERT_EQ(expect, results);
}

void MinimumWindowSubstring(const std::string& input, const std::string& sub
							, std::string& result)
{
	std::vector<int> need(256, 0);
	
	for(auto iter = sub.begin(); iter != sub.end(); ++iter)
	{
		++need[*iter];
	}
	
	std::vector<int> found(256, 0);
	
	int matched = 0;
	
	auto nextStart = input.end();
	auto winStart = input.begin();
	auto winEnd = input.end();
	auto currentBegin = input.begin();
	
	for(auto iter = input.begin(); iter != input.end();)
	{
		if(need[*iter] == 0)
		{
			++iter;
			continue;
		}
		else
		{
			if(++found[*iter] <= need[*iter])
			{
				++matched;
				
				if(matched == 1)
				{
					currentBegin = iter;
					nextStart = iter + 1;
				}
				else if(matched == 2)
				{
					nextStart = iter;
				}
				
				if(matched == sub.size())
				{
					if(iter - currentBegin < winEnd - winStart)
					{
						winStart = currentBegin;
						winEnd = iter;
					}
					matched = 0;
					iter = nextStart;
					for(int i = 0; i < found.size(); ++i)
					{
						found[i] = 0;
					}
				}
				else
				{
					++iter;
				}
			}
			else
			{
				++iter;
			}
		}
		
	}
	
	result.append(winStart, winEnd + 1);
}

TEST(playstring, min_window)
{
	std::string s = "ADOBECODEBANC";
	std::string sub = "ABC";
	
	std::string result;
	
	MinimumWindowSubstring(s, sub, result);
	
	ASSERT_EQ("BANC", result);
	
	s = "AAAA";
	sub = "A";
	
	result.clear();
	
	MinimumWindowSubstring(s, sub, result);
	
	ASSERT_EQ("A", result);
	
	s = "ADOBEMICROSOFT";
	sub = "AIT";
	
	result.clear();
	
	MinimumWindowSubstring(s, sub, result);
	
	ASSERT_EQ("ADOBEMICROSOFT", result);

}

std::string BalanceParanthesis(const std::string& input)
{
	int32_t paranthesisCounter = 0;
	int32_t currentStart = 0;
	int32_t start = 0;
	int32_t end = -1;
	
	for(int i = 0; i < input.size(); ++i)
	{
		if(input[i] == '(')
		{
			++paranthesisCounter;
		}
		else if(input[i] == ')')
		{
			--paranthesisCounter;
		}
		
		if(paranthesisCounter <= 0)
		{
			if(paranthesisCounter < 0)
			{
				currentStart = i + 1;
				paranthesisCounter = 0;

			}
			else
			{
				if(i - currentStart + 1> end - start + 1)
				{
					end = i;
					start = currentStart;
				}
			}
			
		}
		
	}
	

	return input.substr(start, end + 1 - start);
}

TEST(playstring, balance_paranthesis)
{
	std::string input = "(ab(xy)u)2)";
	
	ASSERT_EQ("(ab(xy)u)2", BalanceParanthesis(input));

	input = ")))(((";
	
	ASSERT_EQ("", BalanceParanthesis(input));
	
	input = "))(90)0((800))())";
	
	ASSERT_EQ("(90)0((800))()", BalanceParanthesis(input));
	
	input = "ABCD";
	
	ASSERT_EQ("ABCD", BalanceParanthesis(input));
	
	input = "A";
	
	ASSERT_EQ("A", BalanceParanthesis(input));
	
	input = "(A))((B)";
	
	ASSERT_EQ("(A)", BalanceParanthesis(input));

}

/**
 * Count all the words in the input string(split by space), print in sorted order as per count.
 * If two words has same count, they should be alphabetically sorted.
 */
 
void Record(std::map<std::string, int>& countRecorder, const std::string& s, size_t start, size_t end)
{
    std::string word;
    
    word = s.substr(start, end - start);
    if(countRecorder.find(word) == countRecorder.end())
    {
        countRecorder[word] = 1;
    }
    else
    {  
        ++countRecorder[word];
    }
} 
void CountWords(const std::string& s)
{
    size_t start = 0;
    size_t end = 0;
    std::map<std::string, int> countRecorder;
    
    
    while(end < s.size())
    {
        if(s[end] == ' ')
        {
            if(end == start)
            {
                ++start;
            }
            else
            {
                Record(countRecorder, s, start, end);
            }
            
            start = end + 1;
        }
        ++end;
    }
    
    if(start != end)
    {
        Record(countRecorder, s, start, end);
    }
    
    if(!countRecorder.empty())
    {
        std::vector<std::vector<std::string>> output;
        output.resize(countRecorder.size());
        
        for(auto iter = countRecorder.begin(); iter != countRecorder.end(); ++iter)
        {
           output[iter->second].push_back(iter->first);
        }
        
        for(auto iter = output.rbegin(); iter != output.rend(); ++iter)
        {
            for(auto innerIter = iter->begin(); innerIter != iter->end(); ++innerIter)
            {
                std::cout << *innerIter << ",";
            }
        }
        
        std::cout << std::endl;
    }
}

TEST(playstring, countwords_and_sort)
{
    CountWords("how do you do");
    CountWords("");
    CountWords("   ");
    CountWords("how    do   you   do  ");
}


/*
Given a ternary string, you have to count the total number of contiguous substrings (contigious set of characters), 
that you can form from this given string such that they comprise of either only one or two different characters. 

For example:

input ternary string - aabc
output - 8
The above string comprises of the following substrings that have either one or two of the characters - 
a, a, b, c, aa, ab, bc and aab. So the final answer is a total of eight substrings. 
*/

std::set<char> flags;

int CountString(const std::string& s)
{
    int hit = 0;
    int count = 0;
    
    for(int i = 0; i < s.size(); ++i)
    {
        flags.clear();
        hit = 0;
        for(int j = i; j < s.size(); ++j)
        {
            if(flags.find(s[j]) == flags.end())
            {
                flags.insert(s[j]);
                ++hit;
            }
            
            if(hit > 2)
            {
                break;
            }
            ++count;
        }
    }
    
    return count;
}

TEST(playstring, count_string)
{
    ASSERT_EQ(8, CountString("aabc"));
    ASSERT_EQ(5, CountString("abc"));
    ASSERT_EQ(16, CountString("baaccb"));
}
