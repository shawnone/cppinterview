//
//  2pointers_and_sliding_win.cpp
//  cppinterview
//
//  Created by Shawnone on 13-4-20.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

template <typename T>
void RemoveDuplicateElement(std::vector<T>& input)
{
	std::sort(input.begin(), input.end());
	
	int readPos = 0;
	int writePos = 0;
	int lastWritePos = -1;
	
	for(int i = 0; i < input.size(); ++i)
	{
		if(lastWritePos != writePos)
		{
			input[writePos] = input[readPos];
			lastWritePos = writePos;
		}
		if(i != input.size() - 1)
		{
			if(input[i + 1] != input[i])
			{
				++writePos;
			}
		    ++readPos;
		}
	    
	}
	
	input.erase(input.begin() + writePos + 1, input.end());
}

TEST(pointers_and_sliding_win, removedublicate)
{
	std::vector<int> input = {1, 2, 2, 2, 2, 2};
	RemoveDuplicateElement(input);
	
	std::vector<int> out = {1, 2};
	ASSERT_EQ(out, input);
	
	input = {1, 2, 2, 2, 3};
	RemoveDuplicateElement(input);
	
	out = {1, 2, 3};
	ASSERT_EQ(out, input);
	
	input = {1, 1, 1, 1};
	RemoveDuplicateElement(input);
	
	out = {1};
	ASSERT_EQ(out, input);
	
	input = {1, 2, 3, 3};
	RemoveDuplicateElement(input);
	
	out = {1, 2, 3};
	ASSERT_EQ(out, input);
	
	input = {1, 2, 3};
	RemoveDuplicateElement(input);
	
	out = {1, 2, 3};
	ASSERT_EQ(out, input);
}

template <typename T>
void CountMaxNoDuplication(const std::vector<T>& input, std::vector<T>& output)
{
	int maxLen = 0;
	int maxBegin = 0;
	int maxEnd = 0;
	int start = 0;
	
	std::set<T> flags;
	
	for(int i = 0; i < input.size(); ++i)
	{
		if(!flags.insert(input[i]).second)
		{
			int currentMaxLen = i - start;
			if(currentMaxLen > maxLen)
			{
				maxLen = currentMaxLen;
				maxBegin = start;
				maxEnd = i;
			}
			start = i + 1;
		}
	}
	
	output.insert(output.end(), input.begin() + maxBegin, input.begin() + maxEnd);
}

TEST(pointers_and_sliding_win, maxnodup)
{
	std::vector<int> input = {1, 2, 3, 1, 2, 3, 2, 2};
	
	std::vector<int> output;
	
	CountMaxNoDuplication(input, output);
	
	std::vector<int> expected = {1, 2, 3};
	ASSERT_EQ(expected, output);
	
	output.clear();
	input = {2, 2, 2, 2, 2, 2};
	CountMaxNoDuplication(input, output);
	
	expected = {2};
	ASSERT_EQ(expected, output);
}