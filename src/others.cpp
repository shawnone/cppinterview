//
//  others.cpp
//  cppinterview
//
//  Created by Shawnone on 13-5-4.
//
//

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include <vector>

#include <toolkit.h>

int32_t MinDistance(const std::vector<std::vector<int32_t>>& input)
{
	std::vector<std::pair<int32_t, int32_t>> maxMinVec;
	int32_t max = std::numeric_limits<int32_t>::max();
	int32_t min = std::numeric_limits<int32_t>::min();
	
	for(int32_t i = 0; i < input[0].size(); ++i)
	{
		max = std::numeric_limits<int32_t>::min();
		min = std::numeric_limits<int32_t>::max();
		
		for(int32_t j = 0; j < input.size(); ++j)
		{
			if(input[i][j] > max)
			{
				max = input[i][j];
			}
			if(input[i][j] < min)
			{
				min = input[i][j];
			}
		}
		
		maxMinVec.push_back(std::pair<int32_t, int32_t>(max, min));
	}
	
	int32_t result = 0;
	int32_t result2 = 0;
	int32_t final = 0;
	for(auto iter = maxMinVec.begin(); iter != maxMinVec.end(); ++iter)
	{
		auto secondIter = iter + 1;
		if(secondIter != maxMinVec.end())
		{
			result = iter->first - secondIter->second;
			result2 = iter->second - secondIter->first;
		}
		else
		{
			result = iter->first - maxMinVec.begin()->second;
			result2 = iter->second - maxMinVec.begin()->first;
		}
			
		if(result < 0)
		{
			result = -result;
		}
		if(result2 < 0)
		{
			result2 = -result2;
		}
		
		final = result > result2 ? final + result : final + result2;
	}
	
	return final;
}

TEST(others, min_distance)
{
	std::vector<int32_t> A = {-10, 10, 5};
	std::vector<int32_t> B = {5, -5, 10};
	std::vector<int32_t> C = {10, 10, 5};
	
	std::vector<std::vector<int32_t>> input = {A, B, C};
	
	ASSERT_EQ(55, MinDistance(input));
}

