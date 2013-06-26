//
//  129.cpp
//  cppinterview
//
//  Created by Shawnone on 13-5-22.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>

#include <list>
#include <memory>

/**
 Sum Root to Leaf Numbers
 
 
 Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 
 An example is the root-to-leaf path 1->2->3 which represents the number 123.
 
 Find the total sum of all root-to-leaf numbers.
 
 For example,
   1
  / \
 2   3

 The root-to-leaf path 1->2 represents the number 12.
 The root-to-leaf path 1->3 represents the number 13.
 
 Return the sum = 12 + 13 = 25.
*/

namespace
{
	struct TreeNode
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
}


class Solution {
public:
    int sumNumbers(TreeNode *root)
	{
	    sum_ = 0;
		path_.clear();
		
		if(root)
		{
			DoSum(root);
		}
		
		
		return sum_;
    }
	
private:
	void DoSum(TreeNode *root)
	{
		path_.push_back((root->val));
		if(root->left == 0 && root->right == 0)
		{
			CountOnePath();
		}
		else
		{
			if(root->left)
			{
				DoSum(root->left);
			}
			if(root->right)
			{
				DoSum(root->right);
			}
		}
		
		path_.pop_back();
	}
	
	void CountOnePath()
	{
		int sum = 0;
		for(auto iter = path_.begin(); iter != path_.end(); ++iter)
		{
			sum = 10 * sum + *iter;
		}
		
		sum_ += sum;
	}
	
	int sum_;
	std::list<int> path_;
};

TEST(L129, normal)
{
	std::shared_ptr<TreeNode> node1(new TreeNode(1));
    std::shared_ptr<TreeNode> node2(new TreeNode(2));
    std::shared_ptr<TreeNode> node3(new TreeNode(3));

    node1->left = node2.get();
    node1->right = node3.get();
	
	Solution solution;
	
	ASSERT_EQ(25, solution.sumNumbers(node1.get()));
	
	node1->right = 0;
	ASSERT_EQ(12, solution.sumNumbers(node1.get()));
}