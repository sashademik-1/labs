#include <iostream>
struct Node
{
    Node *pNext = nullptr;
    int data = 0;
};
struct Stack
{
    Node *top;
};
Stack &constructor(Stack &is)
{
    is.top = nullptr;
    return is;
}
Stack &push(Stack &is, int data)
{
    Node *point = new Node;
    point->data = data;
    point->pNext = is.top;
    is.top = point;
    return is;
};
void print(const Stack &is)
{
    if (is.top == nullptr)
    {
        std::cout << "stack is empty" << std::endl;
    }
    else
    {
        for (auto show = is.top; show != nullptr; show = show->pNext)
        {
            std::cout << show->data << std::endl;
        }
    }
}
int pop(Stack &is)
{
    if (is.top == nullptr)
    {
        std::cout << "stack is empty" << std::endl;
    }
    else
    {
        Node *point = is.top->pNext;
        int i = is.top->data;
        std::cout << is.top->data << std::endl;
        delete is.top;
        is.top = point;
        return i;
    }
}
Stack &distrucor(Stack &is)
{
    if (is.top == nullptr)
    {
        std::cout << "Stack is empty" << std::endl;
    }
    else
    {
        while (is.top != nullptr)
        {
            Node *point = is.top->pNext;
            delete is.top;
            is.top = point;
        }
    }
    return is;
}
unsigned int size(const Stack &is)
{
    size_t length = 0;
    for (auto iter = is.top; iter != nullptr; length++)
    {
        iter = iter->pNext;
    }
    std::cout << "Size: " << length << std::endl;
    return length;
}
int main()

{
    Stack p;
    constructor(p);
    push(p, 8);
    push(p, 9);
    pop(p);
    print(p);
    size(p);
    distrucor(p);
    return 0;
}
