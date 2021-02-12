#include <iostream>

template<typename T>
struct harddata {
    T data;
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const harddata<T> &data) {
    out << data.data << std::endl;
    return out;
}

template<typename T>
bool operator!=(const harddata<T> data1, const harddata<T> data2) {
    return data1.data != data2.data;
}

template<typename T>
struct Node {
    Node *pNext = nullptr;
    Node *pPrev = nullptr;
    T data = T();
};
template<typename T>
struct List {
    Node<T> *top;
    Node<T> *tail;
};

template<typename T>
List<T> &constructor(List<T> &is) //1
{
    is.top = nullptr;
    is.tail = nullptr;
    return is;
}

template<typename T>
List<T> &pushtop(List<T> &is, T data) //4
{
    Node<T> *point = new Node<T>;
    point->data = data;
    if (is.top == nullptr) {
        is.tail = point;
    } else {
        is.top->pNext = point;
        point->pPrev = is.top;
    }
    point->pNext = is.tail;
    is.top = point;
    is.tail->pPrev = is.top;
    return is;
}

template<typename T>
List<T> &pushtail(List<T> &is, T data) //5
{
    Node<T> *point = new Node<T>;
    point->data = data;
    if (is.tail == nullptr) {
        is.top = point;
    } else {
        is.tail->pPrev = point;
        point->pNext = is.tail;
    }
    point->pPrev = is.top;
    is.tail = point;
    is.top->pNext = is.tail;
}

template<typename T>
List<T> &pushindex(List<T> &is, unsigned int index, T data) //6
{
    if (index == 0) {
        pushtop(is, data);
    } else if (index == size(is)) {
        pushtail(is, data);
    } else if (index < size(is)) {
        Node<T> *iter = is.top->pPrev;
        for (int i = 1; i < index; i++) {
            iter = iter->pPrev;
        }
        Node<T> *point = new Node<T>;
        point->data = data;
        point->pNext = iter->pNext;
        iter->pNext->pPrev = point;
        iter->pNext = point;
        point->pPrev = iter;
    }
    return is;
}

template<typename T>
List<T> &pushukaz(List<T> &is, Node<T> *ukaz, T data) {
    if (ukaz == is.tail) {
        pushtail(is, data);
    } else {
        Node<T> *point = new Node<T>;
        ukaz->pPrev->pNext = point;
        point->pPrev = ukaz->pPrev;
        ukaz->pPrev = point;
        point->pNext = ukaz;
    }

    return is;
}

template<typename T>
unsigned int size(const List<T> &is) //3
{
    int i = 0;
    if (is.top != nullptr) {
        for (Node<T> *iter = is.top; iter != is.tail; iter = iter->pPrev) {
            i++;
        }
        i++;
    }
    return i;
}

template<typename T>
List<T> &poptop(List<T> &is) //8
{
    if (is.top == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else if (is.top == is.tail) {

        Node<T> *point = is.top;
        is.top = nullptr;
        is.tail = nullptr;
        delete point;
    } else {
        Node<T> *point = is.top;
        is.top = is.top->pPrev;
        is.tail->pPrev = is.top;
        is.top->pNext = is.tail;
        delete point;
    }
    return is;
}

template<typename T>
List<T> &poptail(List<T> &is) //9
{
    if (is.tail == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else if (is.top == is.tail) {
        Node<T> *point = is.tail;
        is.top = nullptr;
        is.tail = nullptr;
        delete point;
    } else {
        Node<T> *point = is.tail;
        is.tail = is.tail->pNext;
        is.top->pNext = is.tail;
        is.tail->pPrev = is.top;
        delete point;
    }
}

template<typename T>
T popindex(List<T> &is, unsigned int index) // 10
{
    if (index < size(is)) {
        Node<T> *iter = is.top;
        for (int i = 0; i < index; i++) {
            iter = iter->pPrev;
        }
        T data = iter->data;
        if (iter == is.top) {
            poptop(is);
        } else if (iter == is.tail) {
            poptail(is);
        } else {
            iter->pNext->pPrev = iter->pPrev;
            iter->pPrev->pNext = iter->pNext;
            delete iter;
        }
        return data;
    } else { return T(); }
}

template<typename T>
T popukaz(List<T> &is, Node<T>(*ukaz)) // 11
{
    if (is.top == nullptr) {
        std::cout << "list dont have element" << std::endl;
    } else {
        T data = ukaz->data;
        if (ukaz == is.top) {
            poptop(is);
        } else if (ukaz == is.tail) {
            poptail(is);
        } else {
            ukaz->pNext->pPrev = ukaz->pPrev;
            ukaz->pPrev->pNext = ukaz->pNext;
            delete ukaz;
        }
        return data;
    }
}

template<typename T>
T show(const List<T> &is, unsigned int index) //12
{
    if (index < size(is)) {
        Node<T> *iter = is.top;
        for (int i = 0; i < index; i++) {
            iter = iter->pPrev;
        }
        std::cout << iter->data << std::endl;
        return iter->data;
    } else { std::cout << "the index is clear" << std::endl; }
}

template<typename T>
int search(const List<T> &is, T data) //13
{
    unsigned int i = 0;
   // Node<T> *iter = is.top;
   for (Node<T> *iter = is.top;iter->data != data || i == size(is); iter = iter->pPrev, i++) {}


    if (i < size(is)) {
        std::cout << i << std::endl;
        return i;
    } else {
        std::cout << "list dont have this data" <<
                  std::endl;
    }
}

template<typename T>
void print(const List<T> &is) //14
{
    if (is.top == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else {
        Node<T> *iter = is.top;
        do {
            std::cout << iter->data << " ";
            iter = iter->pPrev;
        } while (iter != is.top);
        std::cout << std::endl;
    }
}

template<typename T>
List<T> &distructor(List<T> &is) //2
{
    if (is.top == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else {
        while (is.tail != nullptr) {
            is.top = is.top->pPrev;
            delete is.top->pNext;
            is.top = nullptr;
            is.tail = nullptr;
        }
    }
    return is;
}


int main() {
    List<int> p;
    constructor(p);
    pushtail(p, 13);
    print(p);
    pushtail(p, 60);
    print(p);
    pushtail(p, 90);
    print(p);
    pushtop(p, 9);
    print(p);
    pushindex(p, 1, 20);
    print(p);
    poptop(p);
    print(p);
    poptail(p);
    print(p);
    popindex(p,2);
    print(p);
    size(p);
    search(p, 20);
    show(p,0);

    distructor(p);
    return 0;
}