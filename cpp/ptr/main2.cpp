#include <memory>
#include <iostream>

class D {
public:
    D() {
        std::cout << "Constructor D " << this << std::endl;
    }

    ~D() {
        std::cout << "Destructor D " << this << std::endl;
    }

    D(D &&a) noexcept { std::cout << "Move Constructor D " << this << std::endl; }
    D& operator = (D &&a) noexcept {
        std::cout << "Move = " << this << std::endl;
        return *this;
    }
    D(D &a) noexcept { std::cout << "Copy Constructor D " << this << std::endl; }
    D& operator = (D &a) noexcept {
        std::cout << "Copy = " << this << std::endl;
        return *this;
    }
};

using DPtr = std::unique_ptr<D>;

class A {
public:
    A() {
        puts("A");
        a_ = malloc(10000);
    }

    ~A() {
        puts("~A");
        free(a_);
    }

    void hello() {
        puts("a");
    }

    void setD() {
        dp = DPtr { new D() };  // Move?
        d = {};                 // Move
    }

    void* a_;
    D d;
    DPtr dp;
};

using APtr = std::unique_ptr<A>;

class B {
public:
    B() {
        puts("B");
    };

    ~B() {
        puts("~B");
    };

    D d;
};

void test1() {
    puts("test1 start");

    APtr a { new A() };
    a->setD();

    puts("test1 finish");
}

void test2() {
    // new B();
    B b {};
}

int main(int argc, char *argv[])
{
    // test1();
    test2();
    return 0;
}
