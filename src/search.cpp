//
//  search.cpp
//  cppinterview
//
//  Created by Shawnone on 13-5-4.
//
//

#include <gtest/gtest.h>
#include <cstdint>

int32_t RotatedBinarySearch(std::vector<int32_t>& input, int32_t target)
{
	int32_t mid = 0;
	int32_t left = 0;
	int32_t right = input.size() - 1;
	
	while(left <= right)
	{
		mid = (left + right) / 2;
		
		if(input[mid] == target)
		{
			return mid;
		}
		else if(input[mid] > input[right])
		{
			if(target < input[mid] && target >= input[left])
			{
				right  = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		else if(input[mid] < input[right])
		{
			if(target > input[mid] && target <= input[right])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		else
		{
			--right;
		}
	}
	
	return -1;
}
	
TEST(search, rotated_bin_search)
{
	std::vector<int32_t> input = {4, 5, 6, 7, 0, 1, 2};
	
	ASSERT_EQ(5, RotatedBinarySearch(input, 1));
	
	input = {1, 2, 3, 4};
	
	ASSERT_EQ(2, RotatedBinarySearch(input, 3));
	
	input = {5, 6, 1, 2, 3, 4};
	
	ASSERT_EQ(1, RotatedBinarySearch(input, 6));
	
	input = {5, 6, 6, 6, 3, 4, 4};
	
	ASSERT_EQ(4, RotatedBinarySearch(input, 3));


}

	
	

