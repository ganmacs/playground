#include <thread>
#include <iostream>
#include <vector>

class A {
public:
    int a_;
    A() {}
    A(int a) : a_(a) {}
};

int main(int argc, char *argv[])
{
    // auto th = std::thread([] { std::cout << "bbbbbbbbbbb"; });
    // std::cout << "aaaaaaaaaaaaaaaa";
    // th.join();

    // int x {};
    // printf("%d\n", x);
    // std::vector<int> k {1};
    // printf("%d\n", k.at(0));

    A a {};
    printf("%d\n", a.a_);

    A& b {a};
    printf("%d\n", a.a_);
    printf("%d\n", b.a_);

    return 0;
}
