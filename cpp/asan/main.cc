#include <stdio.h>
#include <memory>

class A {
public:
    int v{10};

};

int main(int argc, char *argv[])
{
    auto v = std::make_unique<A>();
    printf("%d\n", 10);
    auto k = std::move(v);
    printf("%d\n", v->v);
    return 0;
}
