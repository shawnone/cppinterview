//
//  130.cpp
//  cppinterview
//
//  Created by Shawnone on 13-5-20.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

#include <vector>

/*
 Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
 
 A region is captured by flipping all 'O's into 'X's in that surrounded region .
 
 For example,
 X X X X
 X O O X
 X X O X
 X O X X
 
 After running your function, the board should be:
 
 X X X X
 X X X X
 X X X X
 X O X X
 */

class Solution
{
public:
    void solve(std::vector<std::vector<char>> &board)
	{
        
        for(int i = 0; i < board.size(); ++i)
        {
            for(int j = 0; j < board[i].size(); ++j)
            {
                if(board[i][j] == 'O')
                {
                    if(FindPath(board, i, j))
                    {
                        ReplaceBack(board, SURROUNDED);
                    }
                    else
                    {
                        ReplaceBack(board, NOT_SURROUNDED);
                    }
                }
            }
        }
    }
private:
    enum ReplaceMethod
    {
        SURROUNDED,
        NOT_SURROUNDED
    };

    void ReplaceBack(std::vector<std::vector<char>> &board, ReplaceMethod replaceMethod)
    {
        for(int i = 0; i < board.size(); ++i)
        {
            for(int j = 0; j < board[i].size(); ++j)
            {
                if(board[i][j] == 'P')
                {
                    if(replaceMethod == SURROUNDED)
                    {
                        board[i][j] = 'X';
                    }
                    else
                    {
                        board[i][j] = 'O';
                    }
                }
            }
        }
    }

    bool FindPath(std::vector<std::vector<char>> &board, int X, int Y)
    {
        board[X][Y] = 'P';
        while(true)
        {
            for(int i = 0; i < board.size(); ++i)
            {
                for(int j = 0; j < board[i].size(); ++j)
                {
                    if(board[i][j] == 'P')
                    {
                        if(i - 1 < 0 || j - 1 < 0 || i + 1 >= board.size() || j + 1 >= board[0].size())
                        {
                            return false;
                        }
                        else
                        {
                            bool noPath = true;
                            if(board[i-1][j] == 'O')
                            {
                                board[i-1][j] = 'P';
    							noPath = false;
                            }
                            if(board[i][j - 1] == 'O')
                            {
                                board[i][j - 1] = 'P';
								noPath = false;
                            }
                            if(board[i+1][j] == 'O')
                            {
                                board[i+1][j] = 'P';
								noPath = false;
                            }
                            if(board[i][j + 1] == 'O')
                            {
                                board[i][j + 1] = 'P';
								noPath = false;
                            }

							if(noPath)
							{
								return true;
							}
                        }
                    }
                }
            }
        }
        
        return true;
    }
};

TEST(L130, normal)
{
    std::vector<char> row1 = {'X', 'X', 'X', 'X'};
    std::vector<char> row2 = {'X', 'O', 'O', 'X'};
    std::vector<char> row3 = {'X', 'X', 'O', 'X'};
    std::vector<char> row4 = {'X', 'O', 'X', 'X'};
    
    std::vector<std::vector<char>> board;
    board.push_back(row1);
    board.push_back(row2);
    board.push_back(row3);
    board.push_back(row4);
    
    Solution solution;
    solution.solve(board);
    
    Print2LevelVector(board);
}
