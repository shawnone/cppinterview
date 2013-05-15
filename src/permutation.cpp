//
//  permutation.cpp
//  cppinterview
//
//  Created by Shawnone on 13-4-20.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

#include <iostream>
#include <math.h>
#include <vector>


void Permutation(std::vector<int>& input, std::vector<std::vector<int>>& result, int start, int end)
{
	if(start < end - 1)
	{
		Permutation(input, result, start + 1, end);
		
		for(int i = start + 1; i < end; ++i)
		{
			Swap(input[start], input[i]);
			Permutation(input, result, start + 1, end);
			Swap(input[i], input[start]);
		}
	}
	else
	{
		result.push_back(input);
	}
}

TEST(permutation, normal)
{
	std::vector<int> input = { 1, 2, 3, 4 };
	std::vector<std::vector<int>> result;
	
	Permutation(input, result, 0, input.size());
	
	ASSERT_EQ(24, result.size());

	result.clear();
	input.clear();
	input = { 1, 2, 3};
	Permutation(input, result, 0, input.size());
	
	ASSERT_EQ(6, result.size());
	
	Print2LevelVector(result);
}

void SubsetPermutation(std::vector<int>& input, int N, std::vector<std::vector<int>>& result, int start, int end)
{
	if(start < N)
	{
		SubsetPermutation(input, N, result, start + 1, end);
		
		for(int i = start + 1; i < end; ++i)
		{
			
			Swap(input[start], input[i]);
			SubsetPermutation(input, N, result, start + 1, end);
			Swap(input[i], input[start]);
		}
	}
	else
	{
		std::vector<int> one(input.begin(), input.begin() + N);
		result.push_back(one);
	}
}

TEST(permutation, subset)
{
	std::vector<int> input = { 1, 2, 3, 4 };
	std::vector<std::vector<int>> result;
	
	SubsetPermutation(input, 2, result, 0, 4);
	ASSERT_EQ(12, result.size());
	
	result.clear();
	input.clear();
	input = { 1, 2, 3};
	SubsetPermutation(input, 2, result, 0, input.size());
	ASSERT_EQ(6, result.size());
	
	result.clear();
	input.clear();
	input = { 1, 2, 3};
	SubsetPermutation(input, 1, result, 0, input.size());
	ASSERT_EQ(3, result.size());
	
	Print2LevelVector(result);

}

void DoPermutation(std::vector<int>& input, int N, std::vector<std::vector<int>>& result, std::vector<int>& path
				   , std::vector<bool>& flags)
{
	if(path.size() == N)
	{
		result.push_back(path);
		
		return;
	}
	
	for(int i = 0; i < input.size(); ++i)
	{
		if(flags[i] || (i != 0 && input[i] == input[i - 1]))
		{
			continue;
		}
		
		flags[i] = true;
		path.push_back(input[i]);
		DoPermutation(input, N, result, path, flags);
		flags[i] = false;
		path.pop_back();
	}
}

void PermutationFilteringDuplication(std::vector<int>& input, int N, std::vector<std::vector<int>>& result)
{
	std::vector<bool> flags(input.size(), false);
	std::vector<int> path;
	
	std::sort(input.begin(), input.end());
	
	DoPermutation(input, N, result, path, flags);
}


TEST(permutation, dublicated)
{
	std::vector<int> input = { 4, 2, 1, 2, 3, 4 };
	std::vector<std::vector<int>> result;
	
	PermutationFilteringDuplication(input, 4, result);
	
	ASSERT_EQ(24, result.size());
	
	result.clear();
	PermutationFilteringDuplication(input, 2, result);
	
	ASSERT_EQ(12, result.size());

	
}

void DoCombination(std::vector<int>& input, int N, std::vector<std::vector<int>>& result, std::vector<int>& oneResult
				   , int position)
{
	if(oneResult.size() == N)
	{
		result.push_back(oneResult);
	}
	else
	{
		for(int i = position; i < input.size(); ++i)
		{
			oneResult.push_back(input[i]);
			DoCombination(input, N, result, oneResult, ++position);
			oneResult.pop_back();
		}
	}
	
}

void Combine(std::vector<int>& input, int N, std::vector<std::vector<int>>& result)
{
	std::vector<int> oneResult;
	
	DoCombination(input, N, result, oneResult, 0);
}

TEST(permutation, combine)
{
	std::vector<int> input = { 1, 2, 3, 4 };
	std::vector<std::vector<int>> result;
	
	Combine(input, 3, result);
	ASSERT_EQ(4, result.size());
	
	result.clear();
	Combine(input, 1, result);
	ASSERT_EQ(4, result.size());

}

void FindSubSet(std::vector<int>& input, int SUM, int current, std::vector<std::vector<int>>& result
				, std::vector<int> oneResult, int position, bool reuse)
{
	if(current > SUM || current < -SUM)
	{
		return;
	}
	
	if(current == SUM)
	{
		result.push_back(oneResult);
	}
	else
	{
		for(int i = position; i < input.size(); ++i)
		{
			oneResult.push_back(input[i]);
			current += input[i];
			
			if(i > position)
			{
				position = i;
			}
			
			if(reuse)
			{
				FindSubSet(input, SUM, current, result, oneResult, position, reuse);
			}
			else
			{
				FindSubSet(input, SUM, current, result, oneResult, ++position, reuse);
			}

			
			oneResult.pop_back();
			current -= input[i];

		}
	}
}

void GetAllSub(std::vector<int>& input, int SUM, std::vector<std::vector<int>>& result, bool reuse)
{
	std::vector<int> oneResult;
	
	FindSubSet(input, SUM, 0, result, oneResult, 0, reuse);
}

TEST(permutation, allsub)
{
	std::vector<int> input = { 7,6, 2, 3 };
	std::vector<std::vector<int>> result;
	
	GetAllSub(input, 7, result, true);
	
	ASSERT_EQ(2, result.size());
	
	result.clear();
	input = { 1, 2, 3, 4};
	GetAllSub(input, 5, result, false);
		
	ASSERT_EQ(2, result.size());
	Print2LevelVector(result);
}

void GetAllSubset(std::vector<int>& input, std::vector<std::vector<int>>& result)
{
	int count = pow(2, input.size());
	
	std::vector<int> oneResult;
	
	int mask = 0;
	int pos = 0;
	
	for(int i = 0; i < count; ++i)
	{
		mask = 1;
		pos = 0;
		oneResult.clear();
		
		while(mask <= i)
		{
			if(mask & i)
			{
				oneResult.push_back(input[pos]);
			}
			
			mask *= 2;
			++pos;
		}
		
		result.push_back(oneResult);
	}
}

TEST(permutation, allsubset)
{ 
	std::vector<int> input = { 7, 6, 2, 3 };
	std::vector<std::vector<int>> result;
	
	GetAllSubset(input, result);
	ASSERT_EQ(16, result.size());
	Print2LevelVector(result);
}
