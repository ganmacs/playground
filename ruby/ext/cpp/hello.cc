#include "hello.hpp"

int hello(int x) {
    printf("hello world, %d\n", x);
    return x + 1;
}

Hello::Hello(): n_{0} {
    printf("init\n");
}

Hello::~Hello() {
    printf("destruct\n");
}
void Hello::say() {
    printf("hello hello %d\n", n_);
}
