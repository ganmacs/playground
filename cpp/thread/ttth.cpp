#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

class Wroker {
    int& v_;
    std::mutex& mtx_;
public:
    std::thread thread_;

    Wroker(int& v, std::mutex& m) : v_{v}, mtx_{m} {
        thread_ = std::thread { [this]{ add(); } };
    }

    Wroker(Wroker&&  a): v_{a.v_}, mtx_{a.mtx_}, thread_{std::move(a.thread_)} {}

    void wait() {
        thread_.join();
    }

    void add() {
        mtx_.lock();
        v_ = v_ + 10;
        mtx_.unlock();
    }
};

int main(int argc, char *argv[])
{
    std::mutex m;
    std::vector<Wroker> t;
    int value = 10;

    printf("%d\n", value);
    for (int i = 0; i < 100; i++) {
        Wroker a { value, m };
        t.emplace_back(std::move(a));
    }

    for (auto& e : t) {
        e.wait();
    }

    printf("%d\n", value);

    return 0;
}
