//
//  124.cpp
//  cppinterview
//
//  Created by Shawnone on 13-6-8.
//
//

#include <gtest/gtest.h>

#include <toolkit.h>
#include <cstdint>

/**
Binary Tree Maximum Path Sum
 
 Given a binary tree, find the maximum path sum.
 The path may start and end at any node in the tree.
 For example:
 Given the below binary tree,
 
   1
  / \
 2   3
 
 Return 6.
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
    int maxPathSum(TreeNode *root)
    {
		if(!root)
		{
			return 0;
		}
		
		maxSum_ = 0;
		firstValue_ = true;
		
		CountPathSum(root);
		
		return maxSum_;
    }
	
private:
	int CountPathSum(TreeNode* root)
	{
		if(root->left == 0 && root->right == 0)
		{
			if(firstValue_ || root->val > maxSum_)
			{
				maxSum_ = root->val;
				firstValue_ = false;
			}
			return root->val;
		}
		else
		{
			int left = 0;
			int right = 0;
			if(root->left)
			{
				left = CountPathSum(root->left);
			}
			
			if(root->right)
			{
				right = CountPathSum(root->right);
			}
			
			int currentBest = 0;
			int sumInPah = 0;
			
			if(left > 0 && right > 0)
			{
				currentBest = left + right;
				
				sumInPah = left > right ? left : right;
			}
			else if(left > 0)
			{
				currentBest = left;
				sumInPah = left;
			}
			else if(right > 0)
			{
				currentBest = right;
				sumInPah = right;
			}
			else
			{
				if(!root->left)
				{
					currentBest = right;
				}
				else if(!root->right)
				{
					currentBest = left;
				}
				else
				{
					currentBest = left > right ? left : right;
					
				}
				sumInPah = currentBest;
			}
			
			if(sumInPah < 0)
			{
				sumInPah = root->val;
			}
			else
			{
				sumInPah += root->val;
			}
			
			if(currentBest < 0)
			{
				currentBest = root->val;
			}
			else
			{
			    currentBest += root->val;	
			}
	
			if(currentBest > maxSum_)
			{
				maxSum_ = currentBest;
			}
			
			return sumInPah;
		}
	}
	
	int maxSum_;
	bool firstValue_;
};

TEST(L124, normal)
{
	std::shared_ptr<TreeNode> node1(new TreeNode(1));
    std::shared_ptr<TreeNode> node2(new TreeNode(2));
    std::shared_ptr<TreeNode> node3(new TreeNode(3));
	
    Solution solution;
	
	ASSERT_EQ(1, solution.maxPathSum(node1.get()));
	node1->val = -3;
	ASSERT_EQ(-3, solution.maxPathSum(node1.get()));
	
	node1->val = 2;
	node2->val = -1;
	node1->left = node2.get();
	node1->right = 0;
	ASSERT_EQ(2, solution.maxPathSum(node1.get()));
	
	node1->val = -2;
	node3->val = -3;
	node1->right = node3.get();
	node1->left = 0;
	ASSERT_EQ(-2, solution.maxPathSum(node1.get()));
	
	node1->val = 2;
	node2->val = -1;
	node3->val = 2;
	node1->right = node3.get();
	node1->left = node2.get();
	ASSERT_EQ(4, solution.maxPathSum(node1.get()));
	
	node1->val = 5;
	node2->val = 4;
	node3->val = 8;
	std::shared_ptr<TreeNode> node4(new TreeNode(11));
    std::shared_ptr<TreeNode> node5(new TreeNode(13));
    std::shared_ptr<TreeNode> node6(new TreeNode(4));
	std::shared_ptr<TreeNode> node7(new TreeNode(7));
	std::shared_ptr<TreeNode> node8(new TreeNode(2));
	std::shared_ptr<TreeNode> node9(new TreeNode(5));
	std::shared_ptr<TreeNode> node10(new TreeNode(1));

	node2->left = node4.get();
	node3->left = node5.get();
	node3->right = node6.get();
	node4->left = node7.get();
	node4->right = node8.get();
	node6->left = node9.get();
	node6->right = node10.get();
	
	ASSERT_EQ(48, solution.maxPathSum(node1.get()));
}
