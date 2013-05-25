//
//  128.cpp
//  cppinterview
//
//  Created by Shawnone on 13-5-24.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

#include <unordered_set>
#include <vector>

/**
 Longest Consecutive Sequence
 
 Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 
 For example,
 Given [100, 4, 200, 1, 3, 2],
 The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 
 Your algorithm should run in O(n) complexity.
 */

class SolutionSort
{
public:
    int longestConsecutive(std::vector<int> &num)
	{
		std::sort(num.begin(), num.end());
		
		int maxLen = 0;
		int currentLen = 0;
		int previous = 0;
		bool newRoundStart = true;
		
		for(auto iter = num.begin(); iter != num.end(); ++iter)
		{
			if(newRoundStart)
			{
				++currentLen;
				
				newRoundStart = false;
			}
			else
			{
				if(*iter == previous)
				{
					continue;
				}
				else if(*iter - 1 == previous)
				{
					++currentLen;
				}
				else
				{
					if(currentLen > maxLen)
					{
						maxLen = currentLen;
					}
					currentLen = 0;
					newRoundStart = true;
					--iter;
				}
			}
			previous = *iter;
		}
		
		if(currentLen > maxLen)
		{
			maxLen = currentLen;
		}
		
		return maxLen;
    }
};

TEST(L128, sorted)
{
	std::vector<int> input = {100, 4, 200, 1, 3, 2};
	
	SolutionSort solution1;
	ASSERT_EQ(4, solution1.longestConsecutive(input));
	
	input = {3, 6, 7, 2, 7};
	ASSERT_EQ(2, solution1.longestConsecutive(input));
	
	input = {0, 1};
	ASSERT_EQ(2, solution1.longestConsecutive(input));
	
	input = {0, 1, 2, 1};
	ASSERT_EQ(3, solution1.longestConsecutive(input));
	
	input = {9,1,4,7,3,-1,0,5,8,-1,6};
	ASSERT_EQ(7, solution1.longestConsecutive(input));

	input = {2147483646,-2147483647,0,2,2147483644,-2147483645,2147483645};
	ASSERT_EQ(3, solution1.longestConsecutive(input));

}

class Solution
{
public:
    int longestConsecutive(std::vector<int> &num)
	{
		for(int i = 0; i < num.size(); ++i)
		{
			flags_.insert(num[i]);
		}
		
		
		int maxLen = 0;
		
		for(int i = 0; i < num.size(); ++i)
		{
			int decendingMax = FindConsecutiveNumbers(DECENDING, num[i]);
			int ascendingMax = FindConsecutiveNumbers(ASCENDING, num[i] + 1);
			
			if(ascendingMax + decendingMax > maxLen)
			{
				maxLen = ascendingMax + decendingMax;
			}

		}
		
		return maxLen;
	}
	
private:
	enum OrderBy
	{
		ASCENDING,
		DECENDING
	};
	
	int FindConsecutiveNumbers(OrderBy orderBy, int value)
	{
		int maxLen = 0;
		
		while(flags_.find(value) != flags_.end())
		{
			++maxLen;
			
			flags_.erase(value);
			
			if(orderBy == ASCENDING)
			{
				++value;
			}
			else
			{
				--value;
			}
			
		}
		
		return maxLen;
	}
	
	std::set<int> flags_;
};

TEST(L128, normal)
{
	
	std::vector<int> input = {100, 4, 200, 1, 3, 2};
	
	
	Solution solution;
	ASSERT_EQ(4, solution.longestConsecutive(input));
	
	input = {3, 6, 7, 2, 7};
	ASSERT_EQ(2, solution.longestConsecutive(input));
	
}
