#include <gtest/gtest.h>

#include <toolkit.h>

int FindMinPath(std::vector<std::vector<int>>& input, int X, int Y, int currentPathValue)
{
    if(X == input.size() - 1)
	{
		return currentPathValue + input[X][Y];
	}

	auto iter = pathInfo.find(Coordinate(X, Y));

	if(iter != pathInfo.end())
	{
		return currentPathValue + iter->second;
	}

	int left = currentPathValue;
	int down = currentPathValue;
	int right = currentPathValue;

	if(Y - 1 >= 0)
	{
		left += FindMinPath(input, X + 1, Y - 1, input[X][Y]);
	}

	if(Y < input[X + 1].size())
	{
		down = FindMinPath(input, X + 1, Y, input[X][Y]);

		if(Y + 1 < input[X + 1].size())
		{
			right += FindMinPath(input, X + 1, Y + 1, input[X][Y]);
		}
	}

	int min = left < right ? left : right;
	
	if(min < down)
	{
		min = down;
	}

	pathInfo[Coordinate(X, Y)] = min;

	return min;
}

int MinPath(std::vector<std::vector<int>>& input)
{
	pathInfo.clear();

	if(input.empty())
	{
		return 0;
	}

	int min = 0;
	int result = 0;

	for(auto i = 0; i < input[0].size(); ++i)
	{
		result = FindMinPath(input, 0, i, 0);

		if(min == 0 || result < min)
		{
			min = result;
		}
	}

	return min;
}
