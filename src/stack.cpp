#include <gtest/gtest.h>

#include <cstdint>
#include <stack>

template <typename T>
class StackKnowMin
{
public:
    bool empty()
    {
        return stack_.empty();
    }
    
    size_t size() const
    {
        return stack_.size();
    }
    
    T& top()
    {
        return stack_.top();
    }
    
    const T& top() const
    {
        return stack_.top();
    }
    
    void push(const T& value)
    {
        stack_.push(value);
        if(minStack_.empty())
        {
            minStack_.push(value);
        }
        else
        {
            if(value < minStack_.top())
            {
                minStack_.push(value);
            }
        }
    }
    
    void pop()
    {
        if(stack_.top() == minStack_.top())
        {
            minStack_.pop();
        }
        
        stack_.pop();
    }
    
    T& min()
    {
        return minStack_.top();
    }
    
    const T& min() const
    {
        return minStack_.top();
    }
    
private:
    std::stack<T> stack_;
    std::stack<T> minStack_;
};

TEST(stack, stack_with_min)
{
    StackKnowMin<int32_t> stack;
    
    stack.push(3);
    stack.push(6);
    stack.push(7);
    stack.push(2);
    stack.push(7);
    
    ASSERT_EQ(2, stack.min());
    ASSERT_EQ(5, stack.size());
    
    stack.pop();
    ASSERT_EQ(2, stack.min());
    
    stack.pop();
    ASSERT_EQ(3, stack.min());
    
    stack.pop();
    ASSERT_EQ(3, stack.min());
    
    stack.pop();
    ASSERT_EQ(3, stack.min());
}