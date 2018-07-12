#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <algorithm>

std::mutex mutex_;
void print(const std::string& s)
{
    (std::lock_guard<std::mutex>(mutex_)), (std::cout << s << std::endl);
}

void f() { print("f"); }
void g() { print("g"); }

int main()
{
    std::vector<std::thread> threads;

    threads.emplace_back(f);
    threads.emplace_back(g);

//  threads.push_back(std::thread(f));
//  threads.push_back(std::thread(g));

    std::for_each(threads.begin(), threads.end(), [](std::thread& t) { t.join(); });
}
