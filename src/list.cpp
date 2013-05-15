#include <gtest/gtest.h>

#include <cstdint>
#include <list>

struct Node
{
	Node(int value) : value_(value), next_(nullptr)
	{
	}
	int value_;
	Node* next_;
};

Node* CreateList(const std::vector<int>& ve)
{
	Node* previous = nullptr;
	Node* head = nullptr;
	for(auto iter = ve.begin(); iter != ve.end(); ++iter)
	{
		Node* current = new Node(*iter);
		if(previous != nullptr)
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
	Node* next = nullptr;
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
	Node* second = nullptr;
	Node* third = nullptr;
	Node* fourth = nullptr;
	bool firstPair = true;
	
	while(first && (second = first->next_))
	{

		third = second->next_;
		fourth = nullptr;
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
	ASSERT_EQ(nullptr, head);

	
	FreeList(freePoint);
	
	std::vector<int> ve2 = {5, 7};
	
	head = CreateList(ve2);
	
	head = reverseList(head);
	
	freePoint = head;
	
	ASSERT_EQ(7, head->value_);
	head = head->next_;
	ASSERT_EQ(5, head->value_);
	head = head->next_;
	ASSERT_EQ(nullptr, head);

	
	FreeList(freePoint);
}
