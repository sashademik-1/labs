#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <set>
int main() {// Zadanie 1
    std::unordered_multimap<int, std::string> map;
    std::cout << "vvedite kol vo elementov" << std::endl;
    int length = 0;
    std::cin >> length;
    for (int i = 0; i < length; ++i) {
        std::string str;
        std::cout << "vvedite strochku" << std::endl;
        std::cin >> str;
        srand(time(nullptr));
        map.insert(make_pair((rand() % 17 - 8), str));
    }
    std::for_each(map.begin(), map.end(), [](const auto &i) { std::cout << i.first << " " << i.second << std::endl; });
    std::cout << "--------------" << std::endl;
    auto iter = map.begin();
    while (iter != map.end()) {
        if (iter->first == 1) {
            iter = map.erase(iter);
        } else ++iter;
    }
    std::for_each(map.begin(), map.end(), [](const auto &i) { std::cout << i.first << " " << i.second << std::endl; });
    for (int i = 0; i < 2; ++i) {
        std::string str;
        std::cout << "vvedite strochku" << std::endl;
        std::cin >> str;
        srand(time(nullptr));
        map.insert(make_pair(1, str));
    }
    std::for_each(map.begin(), map.end(), [](const auto &i) { std::cout << i.first << " " << i.second << std::endl; });
    std::cout << "--------------" << std::endl;
    //Zadanie 2
    std::map<int, std::string> map1;
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
        map1[iter->first] = iter->second;
    }
    std::for_each(map1.begin(), map1.end(),
                  [](const auto &i) { std::cout << i.first << " " << i.second << std::endl; });
    std::cout << " kol-vo keys bolshe 6: "
              << std::count_if(map1.begin(), map1.end(), [](const auto &i) mutable { return i.first > 6; })
              << std::endl;
    std::cout << "--------------" << std::endl;
    std::vector<int> vec;
    //std::transform(map1.begin(), map1.end() ,vec.begin(),[vec]( const auto  &i) mutable { return i.first  ;});
    std::transform(map1.begin(), map1.end(), std::back_inserter(vec), [](const auto &i) { return i.first; });
    std::for_each(vec.begin(), vec.end(), [](const auto &i) { std::cout << i << std::endl; });
    std::cout << "--------------" << std::endl;
    auto a = std::find(vec.begin(), vec.end(), 1);
    if (a != vec.end()) {
        std::cout << "contains 1" << std::endl;
    } else {
        std::cout << "does not contains 1" << std::endl;
    }
    std::cout << "--------------" << std::endl;
    std::replace_if(vec.begin(), vec.end(), std::bind(std::less<int>(), std::placeholders::_1, 0), -2);
    std::for_each(vec.begin(), vec.end(), [](const auto &i) { std::cout << i << std::endl; });
    std::cout << "--------------" << std::endl;
    std::sort(vec.begin(), vec.end(), [](int q1, int q2) { return q1 > q2; });
    std::for_each(vec.begin(), vec.end(), [](const auto &i) { std::cout << i << std::endl; });
    std::cout << "--------------" << std::endl;
    std::set<int> s(vec.begin(),vec.end());
    std::for_each(s.begin(), s.end(), [](const auto &i) { std::cout << i << std::endl; });
    return 0;
}