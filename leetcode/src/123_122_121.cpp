//
//  123_122_121.cpp
//  cppinterview
//
//  Created by Shawnone on 13-6-8.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

#include <vector>


/*
Best Time to Buy and Sell Stock III
 
 Say you have an array for which the ith element is the price of a given stock on day i.
 
 Design an algorithm to find the maximum profit. You may complete at most two transactions.
 
 Note:
 You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

/*
Best Time to Buy and Sell Stock II
 
 Say you have an array for which the ith element is the price of a given stock on day i.
 
 Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

namespace
{
	class Solution {
	public:
		int maxProfit(std::vector<int> &prices)
		{
			return CaculateProfit(prices, 0, FIRST).profit;
		}
		
	private:
		struct Profit
		{
			Profit() : profit(0), buyPrice(-1), buyDay(0), sellDay(0)
			{
			}
			
			int profit;
			int buyPrice;
			int buyDay;
			int sellDay;
		};
		
		enum Transaction
		{
			FIRST,
			SECOND
		};
		
		Profit CaculateProfit(std::vector<int> &prices, int start, Transaction transaction )
		{
			Profit currentProfit;
			Profit maxProfit;
			Profit secondProfit;
			Profit totalProfit;
			
			for(int day = start; day < prices.size(); ++day)
			{
				if(currentProfit.buyPrice == -1)
				{
					currentProfit.buyPrice = prices[day];
					currentProfit.buyDay = day;
					continue;
				}
				
				currentProfit.profit = prices[day] - currentProfit.buyPrice;
				currentProfit.sellDay = day;
				
				if(currentProfit.profit < 0)
				{
					currentProfit.buyPrice = prices[day];
					currentProfit.buyDay = day;
					currentProfit.profit = 0;
				}
				
				if(currentProfit.profit > maxProfit.profit)
				{
					if(transaction == FIRST)
					{
						secondProfit = CaculateProfit(prices, day + 1, SECOND);
						
						
						if(currentProfit.profit + secondProfit.profit > totalProfit.profit)
						{
							totalProfit.profit = currentProfit.profit + secondProfit.profit;
						}
					}

					maxProfit = currentProfit;
				}
			}
			
			if(transaction == FIRST)
			{
				return totalProfit;
			}
			else
			{
				return maxProfit;
			}
		}
	};
	
	class Solution122
	{
	public:
		int maxProfit(std::vector<int> &prices)
		{
			Profit currentProfit;
			Profit maxProfit;
			int totalProfit = 0;
			
			for(int day = 0; day < prices.size(); ++day)
			{
				if(currentProfit.buyPrice == -1)
				{
					currentProfit.buyPrice = prices[day];
					currentProfit.buyDay = day;
					continue;
				}
				
				currentProfit.profit = prices[day] - currentProfit.buyPrice;
				currentProfit.sellDay = day;
				
				if(currentProfit.profit > maxProfit.profit)
				{
					maxProfit = currentProfit;
				}
				else if(currentProfit.profit < maxProfit.profit)
				{
					totalProfit += maxProfit.profit;
					
					currentProfit.buyPrice = prices[day];
					currentProfit.buyDay = day;
					currentProfit.profit = 0;
					
					maxProfit.profit = 0;
				}
			}
			
			if(maxProfit.profit != 0)
			{
				totalProfit += maxProfit.profit;
			}
			
			return totalProfit;
		}
		
	private:
		struct Profit
		{
			Profit() : profit(0), buyPrice(-1), buyDay(0), sellDay(0)
			{
			}
			
			int profit;
			int buyPrice;
			int buyDay;
			int sellDay;
		};
	};
	
	class Solution121 {
	public:
		int maxProfit(std::vector<int> &prices)
		{
			return CaculateProfit(prices).profit;
		}
		
	private:
		struct Profit
		{
			Profit() : profit(0), buyPrice(-1), buyDay(0), sellDay(0)
			{
			}
			
			int profit;
			int buyPrice;
			int buyDay;
			int sellDay;
		};
		
		Profit CaculateProfit(std::vector<int> &prices)
		{
			Profit currentProfit;
			Profit maxProfit;
			
			for(int day = 0; day < prices.size(); ++day)
			{
				if(currentProfit.buyPrice == -1)
				{
					currentProfit.buyPrice = prices[day];
					currentProfit.buyDay = day;
					continue;
				}
				
				currentProfit.profit = prices[day] - currentProfit.buyPrice;
				currentProfit.sellDay = day;
				
				if(currentProfit.profit < 0)
				{
					currentProfit.buyPrice = prices[day];
					currentProfit.buyDay = day;
					currentProfit.profit = 0;
				}
				
				if(currentProfit.profit > maxProfit.profit)
				{
					maxProfit = currentProfit;
				}
			}

			return maxProfit;
		}
	};

}

TEST(L123, normal)
{
	std::vector<int> prices = {1,2,4};
	
	Solution solution;
	
	ASSERT_EQ(solution.maxProfit(prices), 3);
	
	prices = {1,4,2};
	
	ASSERT_EQ(solution.maxProfit(prices), 3);
	
	prices = {1,2,4,2,5,7,2,4,9,0,9};
	
	ASSERT_EQ(solution.maxProfit(prices), 17);
	
	prices = {1,2,4,2,5,7,2,4,9,0};
	
	ASSERT_EQ(solution.maxProfit(prices), 13);
	
	prices = {2,1,4,5,2,9,7};
	ASSERT_EQ(solution.maxProfit(prices), 11);

}

TEST(L122, normal)
{
	std::vector<int> prices = {1,2,4};
	
	Solution122 solution;
	
	ASSERT_EQ(solution.maxProfit(prices), 3);
	
	prices = {1,4,2};
	
	ASSERT_EQ(solution.maxProfit(prices), 3);
	
	prices = {1,2,4,2,5,7,2,4,9,0,9};
	
	ASSERT_EQ(solution.maxProfit(prices), 24);
	
	prices = {1,2,4,2,5,7,2,4,9,0};
	
	ASSERT_EQ(solution.maxProfit(prices), 15);
	
	prices = {2,1,4,5,2,9,7};
	ASSERT_EQ(solution.maxProfit(prices), 11);
	
}

TEST(L121, normal)
{
	std::vector<int> prices = {1,2,4};
	
	Solution121 solution;
	
	ASSERT_EQ(solution.maxProfit(prices), 3);
	
	prices = {1,4,2};
	
	ASSERT_EQ(solution.maxProfit(prices), 3);
	
	prices = {1,2,4,2,5,7,2,4,9,0,9};
	
	ASSERT_EQ(solution.maxProfit(prices), 9);
	
	prices = {1,2,4,2,5,7,2,4,9,0};
	
	ASSERT_EQ(solution.maxProfit(prices), 8);
	
	prices = {2,1,4,5,2,9,7};
	ASSERT_EQ(solution.maxProfit(prices), 8);
	
}

