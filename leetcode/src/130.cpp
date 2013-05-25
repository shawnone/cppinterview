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

#include <mach/mach_time.h>

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

class SolutionV1
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
                    if(!FindPath(board, i, j))
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
		
		bool hasPath = false;
		bool canMove = false;
		
		while(true)
		{
			canMove = false;
			for(int i = 0; i < board.size(); ++i)
			{
				for(int j = 0; j < board[i].size(); ++j)
				{
					if(board[i][j] == 'P')
					{
						if(i - 1 < 0)
						{
							hasPath = true;
						}
						else
						{
							if(board[i-1][j] == 'O')
							{
								board[i-1][j] = 'P';
								canMove = true;

							}
						}
						
						if(j - 1 < 0)
						{
							hasPath = true;
						}
						else
						{
							if(board[i][j - 1] == 'O')
							{
								board[i][j - 1] = 'P';
								canMove = true;
								

							}
						}
						
						if(i + 1 >= board.size())
						{
							hasPath = true;
						}
						else
						{
							if(board[i+1][j] == 'O')
							{
								board[i+1][j] = 'P';
								canMove = true;
							}
						}
						
						if(j + 1 >= board[0].size())
						{
							hasPath = true;
						}
						else
						{
							if(board[i][j + 1] == 'O')
							{
								board[i][j + 1] = 'P';
								canMove = true;
							}
						}
						
						
					}
					
				}
				
			}
			if(!canMove)
			{
				return hasPath;
			}
		}
		
		
		return hasPath;
		
    }

};

class SolutionFinal
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
                    if(!FindPath(board, i, j))
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
		
		
		for(int i = 0; i < board.size(); ++i)
        {
            for(int j = 0; j < board[i].size(); ++j)
            {
                if(board[i][j] == 'D')
                {
                    board[i][j] = 'O';
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
                        board[i][j] = 'D';
                    }
                }
            }
        }
    }
	
	
	bool FindPath(std::vector<std::vector<char>> &board, int X, int Y)
	{
		board[X][Y] = 'P';
		
		bool hasPath = false;
		
		for(int i = 0; i < board.size(); ++i)
		{
			for(int j = 0; j < board[i].size(); ++j)
			{
				if(board[i][j] == 'P')
				{
					if(i - 1 < 0)
					{
						hasPath = true;
					}
					else
					{
						if(board[i-1][j] == 'O')
						{
							board[i-1][j] = 'P';
							
							i -= 2;
							break;
						}
					}
					
					if(j - 1 < 0)
					{
						hasPath = true;
					}
					else
					{
						if(board[i][j - 1] == 'O')
						{
							board[i][j - 1] = 'P';
							
							j -= 2;
							continue;
						}
					}
					
					if(i + 1 >= board.size())
					{
						hasPath = true;
					}
					else
					{
						if(board[i+1][j] == 'O')
						{
							board[i+1][j] = 'P';
							
						}
					}
					
					if(j + 1 >= board[0].size())
					{
						hasPath = true;
					}
					else
					{
						if(board[i][j + 1] == 'O')
						{
							board[i][j + 1] = 'P';
							
						}
					}
				}
			}
			
		}
		
		return hasPath;
		
	}
};


TEST(L130, normal)
{
	std::vector<char> row1 = {'X', 'X', 'O', 'X', 'O'};
    std::vector<char> row2 = {'O', 'X', 'X', 'O', 'X'};
    std::vector<char> row3 = {'O', 'X', 'O', 'X', 'O'};
    std::vector<char> row4 = {'X', 'X', 'O', 'O', 'X'};
	std::vector<char> row5 = {'X', 'O', 'O', 'O', 'X'};
	std::vector<char> row6 = {'O', 'X', 'X', 'X', 'X'};
    
    std::vector<std::vector<char>> board;
    board.push_back(row1);
    board.push_back(row2);
    board.push_back(row3);
    board.push_back(row4);
	board.push_back(row5);
	board.push_back(row6);

    SolutionFinal solution;
    solution.solve(board);

    
    Print2LevelVector(board);
}
