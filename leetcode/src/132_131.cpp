#include <gtest/gtest.h>

#include <toolkit.h>

#include <cstdint>
#include <map>

/**
 132 - Palindrome Partitioning II
 
 Given a string s, partition s such that every substring of the partition is a palindrome.
 
 Return the minimum cuts needed for a palindrome partitioning of s.
 
 For example, given s = "aab",
 Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/

/**
 131 - Palindrome Partitioning
 
 Given a string s, partition s such that every substring of the partition is a palindrome.
 
 Return all possible palindrome partitioning of s.
 
 For example, given s = "aab",
 Return
 
 ["aa","b"],
 ["a","a","b"]
*/

bool IsPalindrome(const std::string& s, size_t start, size_t end)
{
	bool result = true;
	
	while(start < end)
	{
		if(s[start] != s[end])
		{
			result = false;
			break;
		}
		
		++start;
		--end;
	}
	
	return result;
}

void MakePartition(std::vector<std::vector<std::string>>& result, std::vector<std::string>& oneResult,
				   const std::string& s, size_t start)
{
	if(start < s.size())
	{
		size_t pos = start;
		
		while(pos < s.size())
		{
			if(IsPalindrome(s, start, pos))
			{
				oneResult.push_back(s.substr(start, pos - start + 1));
				MakePartition(result, oneResult, s, pos + 1);
				oneResult.pop_back();
			}
			++pos;
		}
	}
	else
	{
		result.push_back(oneResult);
	}
}


class Solution132
{
public:
	Solution132() : currentCut_(0)
	{
	}
	int FindMinPartition(const std::string& s, size_t start)
	{
		if(start < s.size())
		{			
			int pos = s.size() - 1;
			int partMin = -1;
			int partCut = 0;

			while(pos >= (int)start)
			{
				if(IsPalindrome(s, start, pos))
				{
					int estimate = 0;
					if(pos == s.size() - 1)
					{
						estimate = currentCut_;
					}
					else
					{
						estimate = currentCut_ + 1;
					}
                    
					if(estimate >= partMin && partMin != -1)
					{
						break;
					}					
					
					std::string rest = s.substr(pos + 1, s.size() - pos- 1);
					
					++currentCut_;
					
					if(rest != "")
					{
						std::map<std::string, int>::const_iterator iter = infoMap_.find(rest);
						
						if(iter != infoMap_.end())
						{
							//std::cout << "String: " << rest << "-Count: " << iter->second << std::endl;
							if(currentCut_ + iter->second < partMin || partMin == -1)
							{
								partMin = currentCut_ + iter->second;
							}
							--pos;
							--currentCut_;
							continue;
						}
					}
					
					partCut = FindMinPartition(s, pos + 1);
					if(partCut < partMin || partMin == -1)
					{
						partMin = partCut;
					}
					
					if(rest != "")
					{
						infoMap_[rest] = partCut - currentCut_;
					}
					
					--currentCut_;
				}
				--pos;
			}
			
			return partMin;
		}
		else
		{
			return currentCut_ - 1;
		}
	}
	
private:
	int currentCut_;
	std::map<std::string, int> infoMap_;
};

std::vector<std::vector<std::string>> partition(const std::string& s)
{
	std::vector<std::vector<std::string>> result;
	std::vector<std::string> oneResult;
	
	MakePartition(result, oneResult, s, 0);
	
	return result;
}

class Solution132_v1 {
public:
    int minCut(const std::string& s) {
		
		minCut_ = -1;
		currentCut_ = 0;
		
		FindMinPartition(s, 0);
		
		return minCut_;
		
        
    }
    
    
private:
	
	void FindMinPartition(const std::string& s, size_t start)
	{
		if(start < s.size())
		{
			size_t pos = start;
			
			while(pos < s.size())
			{
				if(IsPalindrome(s, start, pos))
				{
					++currentCut_;
					
					FindMinPartition(s, pos + 1);
					--currentCut_;
				}
				++pos;
			}
		}
		else
		{
			if(currentCut_ - 1 < minCut_ || minCut_ == -1)
			{
				minCut_ = currentCut_ - 1;
			}
		}
	}
	
    int minCut_;
    int currentCut_;
};

class Solution132_v2
{
public:
	Solution132_v2() : currentCut_(0)
	{
		
	}
	int FindMinPartition(const std::string& s, size_t start)
	{
		if(start < s.size())
		{
			
			int pos = start;
			int partMin = -1;
			int partCut = 0;
			
			while(pos < s.size())
			{
				if(IsPalindrome(s, start, pos))
				{
					int estimate = 0;
					if(pos == s.size() - 1)
					{
						estimate = currentCut_;
					}
					else
					{
						estimate = currentCut_ + 1;
					}
					
					if(estimate >= partMin && partMin != -1)
					{
						break;
					}
					
					std::string rest = s.substr(pos + 1, s.size() - pos - 1);
					
					
					
					++currentCut_;
					
					if(rest != "")
					{
						std::map<std::string, int>::const_iterator iter = infoMap_.find(rest);
						
						if(iter != infoMap_.end())
						{
							//std::cout << "String: " << rest << "-Count: " << iter->second << std::endl;
							if(currentCut_ + iter->second < partMin || partMin == -1)
							{
								partMin = currentCut_ + iter->second;
							}
							++pos;
							--currentCut_;
							continue;
						}
					}
					
					
					
					partCut = FindMinPartition(s, pos + 1);
					if(partCut < partMin || partMin == -1)
					{
						partMin = partCut;
					}
					
					if(rest != "")
					{
						infoMap_[rest] = partCut - currentCut_;
					}
					
					--currentCut_;
					
					
					
				}
				++pos;
			}
			
			
			return partMin;
		}
		else
		{
			
			return currentCut_ - 1;
		}
	}
	
private:
	int currentCut_;
	std::map<std::string, int> infoMap_;
};

int minCutV1(const std::string& s)
{
	Solution132_v1 solution;
	
	return solution.minCut(s);
}

int minCutV2(const std::string& s)
{
	Solution132_v2 solution;
	return solution.FindMinPartition(s,0);
}

int minCutFinal(const std::string& s)
{
	Solution132 solution;
	return solution.FindMinPartition(s, 0);
}

TEST(L132_131, 131Normal)
{
	Print2LevelVector(partition("aab"));
}

TEST(L132_131, 132Normal)
{
	std::string longest = "fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi";
	std::string long2 = "eegiicgaeadbcfacfhifdbiehbgejcaeggcgbahfcajfhjjdgj";
	std::string normal = "ababababababababababababcbabababababababababababa";
	std::string finalLong = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	
    ASSERT_EQ(75, minCutFinal(longest));
	ASSERT_EQ(42, minCutFinal(long2));
	ASSERT_EQ(0, minCutFinal(normal));
	ASSERT_EQ(1, minCutFinal(finalLong));
	ASSERT_EQ(4, minCutFinal("coder"));
	ASSERT_EQ(1, minCutFinal("abbab"));
	ASSERT_EQ(3, minCutFinal("cabababcbc"));
	ASSERT_EQ(1, minCutFinal("abcccb"));
}



