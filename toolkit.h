//
//  toolkit.h
//  cppinterview
//
//  Created by Shawnone on 13-4-20.
//
//

#pragma once

template <typename T>
void Swap(T& left, T& right)
{
	T temp = left;
	left = right;
	right = temp;
}

template <typename T>
void Print2LevelVector(const std::vector<std::vector<T>>& input)
{
	for(auto iter = input.begin(); iter != input.end(); ++iter)
	{
		for(auto iter2 = iter->begin(); iter2 != iter->end(); ++iter2)
		{
			std::cout << *iter2 << ", ";
		}
		
		std::cout << std::endl;
	}
}

template <typename T>
void PrintVector(const std::vector<T>& input)
{
	for(auto iter = input.begin(); iter != input.end(); ++iter)
	{
		std::cout << *iter << ", ";
	}
	
	std::cout << std::endl;
}

