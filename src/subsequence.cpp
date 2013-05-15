#include <gtest/gtest.h>

#include <cstdint>
#include <vector>


template <typename Comparable>
Comparable MaxMultipleSubSeq( const std::vector<Comparable>& v)
{
    Comparable max = 1;
    Comparable min = 1;
    Comparable maxCurrent = 1;
    Comparable minCurrent = 1;
	Comparable temp;
	
	for(int i = 0; i < v.size(); ++i)
	{
		maxCurrent *= v[i];
		minCurrent *= v[i];
		
		if(maxCurrent > max)
		{
			max = maxCurrent;
		}
		
		if(minCurrent > max)
		{
			max = minCurrent;
		}
		
		if(maxCurrent < min)
		{
			min = maxCurrent;
		}
		
		if(minCurrent < min)
		{
			min = minCurrent;
		}
		
		if(minCurrent > maxCurrent)
		{
			temp = minCurrent;
			minCurrent = maxCurrent;
			maxCurrent = temp;
		}
		
		if(maxCurrent < 1)
		{
			maxCurrent = 1;
		}
	}
	
	return max;
}

TEST(subsequence, multiple)
{
	std::vector<double> ve = {-2.5, 4, 0, 3, 0.5, 8, -1};
	
	ASSERT_EQ(12, MaxMultipleSubSeq(ve));
	
	std::vector<double> ve2 = {-1, 0, 0, 0, 5};
	ASSERT_EQ(5, MaxMultipleSubSeq(ve2));
	
	std::vector<double> ve3 = {-1, -5, -3, 6};
	ASSERT_EQ(90, MaxMultipleSubSeq(ve3));

	std::vector<double> ve4 = {-4, 2};
	ASSERT_EQ(2, MaxMultipleSubSeq(ve4));
	
}

