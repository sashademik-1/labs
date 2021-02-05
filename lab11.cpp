#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <mutex>
#include <chrono>
#include <algorithm>
std::mutex myMutex;
int main() {
    std::vector<int> numbers;
    std::vector<int> min;
    std::srand(std::time(nullptr));
    double b=0;
    std::cin>>b;
    for (int i = 0; i <= b; i++) {
        numbers.push_back(std::rand());
    }
    unsigned int kolvo = 0;
    std::cin >> kolvo;
    std::vector<int>::iterator iter;
    double p = b / kolvo;
    unsigned int i = 0;
    auto start = std::chrono::system_clock::now();
    std::vector<std::thread> myThreads(kolvo);
    iter=numbers.begin();
    for (std::thread &thread : myThreads) {
        thread=std::thread([&min, iter, p](int b = 0) mutable {
            b = *std::min_element(iter , iter + p-1);
            myMutex.lock();
            std::cout << "Thread id is " << std::this_thread::get_id() << " min element is " << b << std::endl;
            myMutex.unlock();
            min.push_back(b);
        });
        i++;
        iter=iter+p;
    }
    for (std::thread &thread:myThreads) {
        thread.join();
    }
    i = *std::max_element(min.begin(), min.end());
    auto end = std::chrono::system_clock::now();
    std::cout << "Max element is " << i << std::endl;
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "The time " << time.count() << std::endl;
    min.clear();
    auto start1 = std::chrono::system_clock::now();
    iter=numbers.begin();
    for(int i=0, b;i<kolvo;i++,iter=iter+p){
        b = *std::min_element(iter , iter + p-1);
        std::cout << "Thread id is " << std::this_thread::get_id() << " min element is " << b << std::endl;
        min.push_back(b);}
        i=*std::max_element(min.begin(), min.end());
    auto end1 = std::chrono::system_clock::now();
    std::cout << "Max element is " << i << std::endl;
    auto time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
    std::cout << "The time " << time1.count() << std::endl;




    return 0;
}