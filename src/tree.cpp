#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

namespace
{
	struct TreeNode
	{
		std::shared_ptr<TreeNode> left;
		std::shared_ptr<TreeNode> right;
	};
}

int32_t GetHeight(std::shared_ptr<TreeNode>& root)
{
    if(!root)
    {
        return 0;
    }
    
    int32_t leftHeight = GetHeight(root->left);
    int32_t rightHeight = GetHeight(root->right);
    
    if(leftHeight >= rightHeight)
    {
        return leftHeight + 1;
    }
    else
    {
        return rightHeight + 1;
    }
}

int32_t MaxDistance(std::shared_ptr<TreeNode>& root)
{
    if(!root)
    {
        return 0;
    }
    
    int32_t leftHeight = GetHeight(root->left);
    int32_t rightHeight = GetHeight(root->right);
    
    int32_t leftDistance = MaxDistance(root->left);
    int32_t rightDistance = MaxDistance(root->right);
    
    int32_t max = leftHeight + rightHeight + 1;
    if(leftDistance > max)
    {
        max = leftDistance;
    }
    else if(rightDistance > max)
    {
        max = rightDistance;
    }
    
    return max;
}

TEST(tree, max_distance)
{
    std::shared_ptr<TreeNode> node1(new TreeNode());
    std::shared_ptr<TreeNode> node2(new TreeNode());
    std::shared_ptr<TreeNode> node3(new TreeNode());
    node1->left = node2;
    node1->right = node3;
    
    std::shared_ptr<TreeNode> node4(new TreeNode());
    std::shared_ptr<TreeNode> node5(new TreeNode());
    node2->left = node4;
    node2->right = node5;
    
    std::shared_ptr<TreeNode> node6(new TreeNode());
    node3->right = node6;
    
    ASSERT_EQ(5, MaxDistance(node1));
}

TEST(tree, max_distance2)
{
    std::shared_ptr<TreeNode> node1(new TreeNode());
    std::shared_ptr<TreeNode> node2(new TreeNode());
    std::shared_ptr<TreeNode> node3(new TreeNode());
    node1->left = node2;
    node1->right = node3;
    
    std::shared_ptr<TreeNode> node4(new TreeNode());
    std::shared_ptr<TreeNode> node5(new TreeNode());
    node2->left = node4;
    node2->right = node5;
    
    std::shared_ptr<TreeNode> node6(new TreeNode());
    node4->left = node6;
    
    std::shared_ptr<TreeNode> node7(new TreeNode());
    node5->right = node7;
    
    std::shared_ptr<TreeNode> node8(new TreeNode());
    node6->left = node8;
    
    std::shared_ptr<TreeNode> node9(new TreeNode());
    node7->right = node9;
    
    ASSERT_EQ(7, MaxDistance(node1));
}