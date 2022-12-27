//
// Created by k17 on 27.12.2022.
//
#include <gtest/gtest.h>
#include "../TStack.h"

TEST(stack_operations, empty_stack_isEmpty)
{
    TStack<int> stack(3);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(stack_operations, push_updates_size)
{
    TStack<int> stack(10);
    stack.Push(1);
    EXPECT_EQ(stack.getSize(), 1);
}


TEST(stack_operations, full_stack_isFull)
{
    TStack<int> stack(5);
    for(int i = 0; i < 5; ++i)
        stack.Push(i);
    EXPECT_TRUE(stack.isFull());
}

TEST(stack_operations, pop_updates_size)
{
    // Making 1-element stack so that if there weren't any actions in it, it wouldn't pass the test
    TStack<int> stack(10);
    stack.Push(1);
    stack.Push(1);
    stack.Pop();
    EXPECT_EQ(stack.getSize(), 1);
}

TEST(stack_operations, top_returns_top_element)
{
    TStack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);
    EXPECT_EQ(stack.Top(), 4);
}

TEST(stack_operations, full_stack_push_throws)
{
    TStack<int> stack(3);
    stack.Push(1);
    stack.Push(1);
    stack.Push(1);
    EXPECT_ANY_THROW(stack.Push(1));
}
TEST(stack_operations, empty_stack_pop_throws)
{
    TStack<int> stack(3);
    EXPECT_ANY_THROW(stack.Pop());
}
TEST(stack_operations, empty_stack_top_throws)
{
    TStack<int> stack(3);
    EXPECT_ANY_THROW(stack.Top());
}