#include <iostream>
#include <algorithm>
#include <array>
#include <iterator>

template<typename T, unsigned int size>
struct List {
    std::array<T, size> list;
};

template<typename T, unsigned int size>
List<T, size> &constructor(List<T, size> &is) {
    for (T &data : is.list) {
        data = T();
    }
    return is;
}

template<typename T, unsigned int size>
List<T, size> &destructor(List<T, size> &is) {
    for (T &data : is.list) {
        data = T();
    }
    return is;
}

template<typename T, unsigned int size>
unsigned int sizeList(List<T, size> &is) {
    return std::count_if(is.list.begin(), is.list.end(), [](T data) { return data != T(); });
}

template<typename T, unsigned int size>
List<T, size> &pushtail(List<T, size> &is, T data) {
    is.list[sizeList(is)] = data;
    return is;
}

template<typename T, unsigned int size>
List<T, size> &pushindex(List<T, size> &is, unsigned int index, T data) {
    if (index < sizeList(is)) {
        for (unsigned int i = sizeList(is); is.list[index] != T(); i--) {
            std::swap(is.list[i - 1], is.list[i]);
        }
        is.list[index] = data;
        return is;
    } else {
        std::cout << "List have empty index before this" << std::endl;
    }
}

template<typename T, unsigned int size>
T pophead(List<T, size> &is) {
    T data = is.list[0];
    std::cout << data << std::endl;
    is.list[0] = T();
    for (unsigned int i = 0; is.list[sizeList(is)] != 0; i++) {
        std::swap(is.list[i], is.list[i + 1]);
    }
    return data;
}

template<typename T, unsigned int size>
T poptail(List<T, size> &is) //7
{
    T data = is.list[sizeList(is) - 1];
    std::cout << data << std::endl;
    is.list[sizeList(is) - 1] = T();
    return data;
}

template<typename T, unsigned int size>
T popindex(List<T, size> &is, unsigned int index) {
    T data = is.list[index];
    std::cout << data << std::endl;
    is.list[index] = T();
    for (unsigned int i = index; is.list[sizeList(is)] != T(); i++) {
        std::swap(is.list[i], is.list[i + 1]);
    }
    return data;
}

template<typename T, unsigned int size>
T show(List<T, size> &is, unsigned int index) {
    std::cout << is.list[index] << std::endl;
    return is.list[index];
}

template<typename T, unsigned int size>
T firstelem(List<T, size> &is, T data) {
    if (std::find(is.list.begin(), is.list.end(), data) != std::end(is.list)) {
        int i = std::distance(is.list.begin(), std::find(is.list.begin(), is.list.end(), data));
        std::cout << i << std::endl;
        return i;
    } else {
        std::cout << "List dont have this element" << std::endl;
    }
}

template<typename T, unsigned int size>
void print(List<T, size> &is) {
    for (T data : is.list) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}

int main() {
    List<int, 5> p;
    constructor(p);
    pushtail(p, 5);
    pushtail(p, 9);
    print(p);
    popindex(p, 1);
    pushindex(p, 0, 15);
    pushindex(p, 2, 14);
    print(p);
    firstelem(p, 15);
    pophead(p);
    print(p);
    poptail(p);
    print(p);
    firstelem(p, 15);
    //pophead(p);
    poptail(p);
    destructor(p);

    return 0;
} //убрать структуры;