//
//  125.cpp
//  cppinterview
//
//  Created by Shawnone on 13-6-6.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

#include <algorithm>

class Solution {
public:
    bool isPalindrome(std::string s)
	{
		if(s.empty())
		{
			return true;
		}
		
        int right = s.size() - 1;
		int left = 0;
		
		while(left < right)
		{
			while(!::isalnum(s[left]))
			{
				++left;
				if(left >= right)
				{
					break;
				}
			}
			
			while(!::isalnum(s[right]))
			{
				--right;
				if(right <= left)
				{
					break;
				}
			}
			
			if(left >= right)
			{
				break;
			}
			
			s[left] = ::tolower(s[left]);
			s[right] = ::tolower(s[right]);
			if(s[left] != s[right])
			{
				return false;
			}
			
			++left;
			--right;
		}
		
		return true;
		
    }
};

TEST(L125, normal)
{
	Solution solution;
	
	std::string input = "A man, a plan, a canal: Panama";
	
	ASSERT_EQ(true, solution.isPalindrome(input));
	
	input = "1a2";
	ASSERT_EQ(false, solution.isPalindrome(input));
	
	input = ".,";
	ASSERT_EQ(true, solution.isPalindrome(input));
}
