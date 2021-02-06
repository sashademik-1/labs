#include <iostream>
struct Node
{
    int data = 0;
    Node *pNext = nullptr;
    Node *pPrev = nullptr;
};
struct Quake
{
    Node *top;
    Node *tail;
};
Quake &constructor(Quake &is)
{
    is.tail = nullptr;
    is.top = nullptr;
    return is;
}
Quake &push(Quake &is, int data)
{
    Node *point = new Node;
    point->data = data;
    point->pNext = is.tail;
    if (is.tail == nullptr)
    {
        is.top = point;
    }
    else
    {
        is.tail->pPrev = point;
    }

    is.tail = point;

    return is;
}
int pop(Quake &is)
{
    if (is.top == nullptr)
    {
        std::cout << "Quake is empty" << std::endl;
    }
    else
    {
        Node *point = is.top;
        std::cout << is.top->data << std::endl;
        int i = is.top->data;
        is.top = is.top->pPrev;
        if (is.top == nullptr)
        {
            delete is.tail;
            is.tail = nullptr;
        }
        else
        {
            is.top->pNext = nullptr;
            delete point;
        }
        return i;
    }
}
void print(const Quake &is)
{
    if (is.top == nullptr)
    {
        std::cout << "Quake is empty" << std::endl;
    }
    else
    {
        for (auto show = is.top; show != nullptr; show = show->pPrev)
        {
            std::cout << show->data << std::endl;
        }
    }
}
Quake &distructor(Quake &is)
{
    if (is.top == nullptr)
    {
        std::cout << "Quake is empty" << std::endl;
    }
    else
    {
        while (is.tail != nullptr)
        {
            pop(is);
        }
    }
    return is;
}
unsigned int size(const Quake &is)
{
    size_t length = 0;
    for (auto iter = is.top; iter != nullptr; length++)
    {
        iter = iter->pPrev;
    }
    std::cout << "Size " << length << std::endl;
    return length;
}
int main()
{
    Quake p;
    constructor(p);
    push(p, 16);
    push(p, 12);
    pop(p);
    pop(p);
    print(p);
    size(p);
    distructor(p);
    print(p);
    return 0;
}
