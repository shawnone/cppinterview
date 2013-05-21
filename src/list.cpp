#include <gtest/gtest.h>

#include <cstdint>
#include <list>

struct Node
{
	Node(int value) : value_(value), next_(0)
	{
	}
	int value_;
	Node* next_;
};

Node* CreateList(const std::vector<int>& ve)
{
	Node* previous = 0;
	Node* head = 0;
	for(auto iter = ve.begin(); iter != ve.end(); ++iter)
	{
		Node* current = new Node(*iter);
		if(previous != 0)
		{
			previous->next_ = current;
		}
		else
		{
			head = current;
		}
		
		previous = current;
	}
	
	return head;
}

void FreeList(Node* head)
{
	Node* current = head;
	Node* next = 0;
	while(current)
	{
		next = current->next_;
		delete current;
		current = next;
	}
}

Node* reverseList(Node* head)
{
	Node* first = head;
	Node* second = 0;
	Node* third = 0;
	Node* fourth = 0;
	bool firstPair = true;
	
	while(first && (second = first->next_))
	{

		third = second->next_;
		fourth = 0;
		if(third)
		{
			fourth = third->next_;
		}
		
		second->next_ = first;
		
		if(fourth)
		{
			first->next_ = fourth;
		}
		else
		{
			first->next_ = third;
		}
		
		first = third;
		
		if(firstPair)
		{
			firstPair = false;
			head = second;
		}
	}
	
	return head;
}

TEST(list, reverse)
{
	std::vector<int> ve = {1, 2, 3, 4, 5, 6, 7};
	
	Node* head = CreateList(ve);
	
	head = reverseList(head);
	
	Node* freePoint = head;
	
	ASSERT_EQ(2, head->value_);
	head = head->next_;
	ASSERT_EQ(1, head->value_);
	head = head->next_;
	ASSERT_EQ(4, head->value_);
	head = head->next_;
	ASSERT_EQ(3, head->value_);
	head = head->next_;
	ASSERT_EQ(6, head->value_);
	head = head->next_;
	ASSERT_EQ(5, head->value_);
	head = head->next_;
	ASSERT_EQ(7, head->value_);
	head = head->next_;
	ASSERT_EQ(0, head);

	
	FreeList(freePoint);
	
	std::vector<int> ve2 = {5, 7};
	
	head = CreateList(ve2);
	
	head = reverseList(head);
	
	freePoint = head;
	
	ASSERT_EQ(7, head->value_);
	head = head->next_;
	ASSERT_EQ(5, head->value_);
	head = head->next_;
	ASSERT_EQ(0, head);

	
	FreeList(freePoint);
}

/**
 * a->b->c ==> b->a->c
 * a->b->c->d ==> b->a->d->c 
 */
Node* SwapNodePairwise(Node* head)
{
    if(!head)
    {
        return head;
    }
    
    Node* first = head;
    Node* second = 0;
    Node* third = 0;
    Node* previous = 0;
    
    bool firstSwap = true;
    
    while(first)
    {
        second = first->next_;
        third = 0;
        if(second)
        {
    		if(previous)
			{
				previous->next_ = second;
			}
            third = second->next_;
            second->next_ = first;
        
            if(firstSwap)
            {
                head = second;
                firstSwap = false;
            }
            first->next_ = third;
            previous = first;  
        }
        
        first = third;
    }
    
    return head;
    
}

TEST(list, swap_pairwise)
{
    std::vector<int> ve = {1, 2, 3, 4, 5, 6, 7};
    
	Node* head = CreateList(ve);
    
    head = SwapNodePairwise(head);
    
    Node* freePoint = head;
    
	ASSERT_EQ(2, head->value_);
	head = head->next_;
	ASSERT_EQ(1, head->value_);
	head = head->next_;
    ASSERT_EQ(4, head->value_);
	head = head->next_;
	ASSERT_EQ(3, head->value_);
	head = head->next_;
    ASSERT_EQ(6, head->value_);
	head = head->next_;
	ASSERT_EQ(5, head->value_);
	head = head->next_;
    ASSERT_EQ(7, head->value_);
    
    FreeList(freePoint);
    
    ve = {1};
    head = CreateList(ve);
    
    head = SwapNodePairwise(head);
    freePoint = head;
    ASSERT_EQ(1, head->value_);
    FreeList(freePoint);
    
    ve = {1, 2};
    head = CreateList(ve);
    
    head = SwapNodePairwise(head);
    freePoint = head;
    ASSERT_EQ(2, head->value_);
    head = head->next_;
    ASSERT_EQ(1, head->value_);
    FreeList(freePoint);
}
