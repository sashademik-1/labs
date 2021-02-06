#include <iostream>
#include <queue>
#include <string>
#include <cmath>
#include <sstream>

template<typename T>
int dlinna(T data) {
    std::ostringstream ost;
    ost << data;
    return ost.str().size();
}

template<typename T>
struct PersonalData {
    int key = 0;
    T data = T();
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const PersonalData<T> data1) {
    out << data1.data;
    return out;
}

template<typename T>
bool operator!=(const PersonalData<T> data1, const PersonalData<T> data2) {
    return data1.key != data2.key;
}

template<typename T>
bool operator==(const PersonalData<T> data1, const PersonalData<T> data2) {
    return data1.key == data2.key;
}

template<typename T>
bool operator>(const PersonalData<T> data1, const PersonalData<T> data2) {
    return data1.key > data2.key;
}

template<typename T>
bool operator<(const PersonalData<T> data1, const PersonalData<T> data2) {
    return data1.key < data2.key;
}

template<typename T>
std::string mytostring(PersonalData<T> data) {
    return std::to_string(data.data);
}

template<typename T>
struct Node {
    T data = T();
    Node *pRight = nullptr;
    Node *pLeft = nullptr;
};
template<typename T>
struct Tree {
    Node<T> *root;
};

template<typename T>
void littlerihgthspin(Node<T> *&point) {
    Node<T> *x = point->pLeft;
    point->pLeft = x->pRight;
    x->pRight = point;
    point = x;
}

template<typename T>
void littleleftspin(Node<T> *&point) {
    Node<T> *x = point->pRight;
    point->pRight = x->pLeft;
    x->pLeft = point;
    point = x;
}

template<typename T>
void ConditionsforBalance(Node<T> *&point) {
    if (!point) {
        return;
    } else if ((treeHeight(point->pLeft) - treeHeight(point->pRight) == 2) &&
               (treeHeight(point->pLeft->pRight) > treeHeight(point->pLeft->pLeft))) {
        littleleftspin(point->pLeft);
        littlerihgthspin(point);
    } else if ((treeHeight(point->pRight) - treeHeight(point->pLeft) == 2) &&
               (treeHeight(point->pRight->pLeft) > treeHeight(point->pRight->pRight))) {
        littlerihgthspin(point->pRight);
        littleleftspin(point);
    } else if ((treeHeight(point->pRight) - treeHeight(point->pLeft) == 2) &&
               ((treeHeight(point->pRight->pRight) - treeHeight(point->pRight->pLeft) == 1) ||
                (treeHeight(point->pRight->pRight) == treeHeight(point->pRight->pLeft)))) {

        littleleftspin(point);
    } else if ((treeHeight(point->pLeft) - treeHeight(point->pRight) == 2) &&
               ((treeHeight(point->pLeft->pLeft) - treeHeight(point->pLeft->pRight) == 1) ||
                (treeHeight(point->pLeft->pRight) == treeHeight(point->pLeft->pLeft)))) {
        littlerihgthspin(point);
    }
}

template<typename T>
void ElementsforBalance(Node<T> *&point, T data) {
    if (true) {
        if (!point || point->data == data) {
            false;
        } else if (data > point->data) {
            ElementsforBalance(point->pRight, data);
        } else {
            ElementsforBalance(point->pLeft, data);
        }
    }
    ConditionsforBalance(point);
    return;
}

template<typename T>
Tree<T> &constructor(Tree<T> &is) {
    is.root = nullptr;
    return is;
}

template<typename T>
Tree<T> &push(Tree<T> &is, T data) {
    if (!is.root) {
        is.root = new Node<T>;
        is.root->data = data;
    } else {
        Node<T> **point = &is.root;
        while (*point) {

            if (data > (*point)->data) {
                point = &(*point)->pRight;
            } else {
                point = &(*point)->pLeft;
            }
        }
        *point = new Node<T>;
        (*point)->data = data;

        ElementsforBalance(is.root, data);
    }
    return is;
}

template<typename T>
Tree<T> &destructor(Tree<T> &is) {
    Node<T> **point = &is.root;
    while (is.root) {
        point = &is.root;
        while ((*point)->pRight || (*point)->pLeft) {
            if ((*point)->pLeft) {
                point = &(*point)->pLeft;
            } else {

                point = &(*point)->pRight;
            }
        }
        delete (*point);
        *point = nullptr;
    }
    return is;
}

template<typename T>
T pop(Tree<T> &is, T data) {
    Node<T> **point = &is.root;
    bool del = true;
    T dataforsearch = (*point)->data;
    T datareturn = T();
    while ((*point)->data != data) {
        if (data > (*point)->data) {
            point = &(*point)->pRight;
        } else if (data < (*point)->data) {
            point = &(*point)->pLeft;
        }
        if (!*point) {
            std::cout << "Tree hasnt this data" << std::endl;
            del = false;
            break;
        }
        if ((*point)->data != data) {
            dataforsearch = (*point)->data;
        }
    }
    if (del) {
        Node<T> *pointpoint = *point;
        while ((*point)->pRight || (*point)->pLeft) {
            if (!(*point)->pRight) {
                point = &(*point)->pLeft;
                while ((*point)->pRight) {
                    point = &(*point)->pRight;
                }
            } else {
                point = &(*point)->pRight;
                while ((*point)->pLeft) {
                    point = &(*point)->pLeft;
                }
            }
            pointpoint->data = (*point)->data;
            pointpoint = *point;
            if (!pointpoint->pRight || !pointpoint->pLeft) {
                continue;
            }
            dataforsearch = pointpoint->data;
        }
        datareturn = (*point)->data;
        delete (*point);
        *point = nullptr;
        pointpoint = nullptr;
    }
    ElementsforBalance(is.root, dataforsearch);
    return datareturn;
}

template<typename T>
int treeHeight(Node<T> *node) {
    int height = 0;
    if (node) {
        std::queue<Node<T> *> Level;
        Level.push(node);
        size_t CountNode = 1;
        Node<T> *point = nullptr;
        bool b = true;
        while (b) {
            CountNode = Level.size();
            if (CountNode == 0) {
                b = false;
                continue;
            }
            height++;

            while (CountNode != 0) {
                point = Level.front();
                if (point->pLeft) {
                    Level.push(point->pLeft);
                }
                if (point->pRight) {
                    Level.push(point->pRight);
                }
                Level.pop();
                CountNode--;
            }
        }
    }
    return height;
}

template<typename T>
void print(Tree<T> &is) {
    if (is.root) {
        int height = 0;
        int length = 0;
        std::queue<Node<T> *> Level;
        Level.push(is.root);
        size_t CountNode = 1;
        Node<T> *point = nullptr;
        bool b = true;
        while (b) {
            CountNode = Level.size();
            if (CountNode == 0) {
                b = false;
                continue;
            }
            height++;
            while (CountNode != 0) {
                point = Level.front();
                length = dlinna(point->data);
                if (dlinna(point->data) > length) {
                    length = dlinna(point->data);
                }
                if (point->pLeft) {
                    Level.push(point->pLeft);
                }
                if (point->pRight) {
                    Level.push(point->pRight);
                }
                Level.pop();
                CountNode--;
            }
        }
        Level.push(is.root);
        int alltab = (2 * (pow(2, height - 1)) - 1) * length;
        Node<T> *zero = new Node<T>;
        for (int alltab = (2 * (pow(2, height - 1)) - 1) * length; height > 0; height--) {
            CountNode = Level.size();
            int i = (alltab - CountNode * length - 2 * length * ((pow(2, height - 1)) - 1)) / (CountNode - 1);
            b = true;
            while (CountNode != 0) {
                point = Level.front();
                if (b) {
                    for (int b = length * ((pow(2, height - 1)) - 1); b != 0; b--) {
                        std::cout << ' ';
                    }
                    b = false;
                } else {
                    for (int b = i; b != 0; b--) {
                        std::cout << ' ';
                    }
                }
                if (point != zero) {
                    std::cout << point->data;
                    if (length > dlinna(point->data)) {
                        for (int i = length - dlinna(point->data); i != 0; i--) {
                            std::cout << ' ';
                        }
                    }
                } else {

                    for (int b = length; b != 0; b--) {
                        std::cout << ' ';
                    }
                }
                if (point->pLeft) {
                    Level.push(point->pLeft);
                } else {
                    (Level.push(zero));
                }
                if (point->pRight) {
                    Level.push(point->pRight);
                } else {
                    (Level.push(zero));
                }
                Level.pop();
                CountNode--;
            }
            std::cout << std::endl;
        }
        delete zero;
        zero = nullptr;
    }
}

int main() {
    Tree<int> p;
    constructor(p);
    for (int i = 1; i <
                    20; i++) { // у меня в vs code при достижении дерева правого края терминала перестает отображать корректно, проверил в Clion отображает корректно

        push(p, rand() % 1001);
    }
    push(p, 100);
    print(p);
    pop(p, 100);
    print(p);
    destructor(p);
    Tree<PersonalData<char>> p1;
    constructor(p1);
    std::vector<PersonalData<char>> chars(15);
    for (PersonalData<char> &char1 : chars) {
        char1.key = rand() % 301;
        char1.data = 96 + rand() % 25;
        push(p1, char1);
    }
    print(p1);
    print(p1);
    destructor(p1);
    return 0;
}