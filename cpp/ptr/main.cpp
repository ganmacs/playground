#include <iostream>
#include <memory>

class A {
public:
    A() {
        std::cout << "A " << this << std::endl;
        ptr = malloc(100000);
    }

    ~A() {
        // if (ptr != nullptr) {
            free(ptr);
        // }
        std::cout << "~A " << this << std::endl;
    }

    A(A &&a) noexcept {
        *this = std::move(a);
        std::cout << "Move Constructor " << this << std::endl;
    }

    A& operator = (A &&a) noexcept {
        std::cout << "Move = " << this << std::endl;
        this->n = a.n;
        this->ptr = a.ptr;

        a.ptr = nullptr;
        a.n = 0;
        return *this;
    }

    A(A &a) noexcept {
        ptr = malloc(1000);     // copy constracter must realloc.
        n = 10;
        std::cout << "Copy Constructor " << this << std::endl;
    }

    void hello() {
        std::cout << "hello a" << this << std::endl;
    }

    int n {};
private:
    void *ptr;
};
using APtr = std::unique_ptr<A>;

class A2 {
public:
    A2() {
        std::cout << "A2 " << this << std::endl;
        ptr = malloc(100000);
    }

    ~A2() {
        free(ptr);
        std::cout << "~A2 " << this << std::endl;
    }

    A2(A2 &&a) noexcept {
        std::cout << "Move Constructor " << this << std::endl;
        this->ptr = a.ptr;
        a.ptr = nullptr;
    }

    A2(A2 &a) noexcept {
        std::cout << "Copy Constructor " << this << std::endl;
        memcpy(a.ptr, ptr, 100000);
    }

    void hello() {
        std::cout << "hello a2" << this << std::endl;
    }
private:
    void *ptr;
};
using A2Ptr = std::unique_ptr<A2>;

class B {
public:
    B(): a2_{ A2Ptr{ new A2() } }{
        std::cout << "B\n";
        A a {};
        a_ = &a;
    };

    void hello() {
        std::cout << "hello b\n";
    }

    void hello_a() {
        std::cout << "B call hello_a\n";
        a_->hello();
    }

    A* a_;
    A2Ptr a2_;
};

void test1() {
    std::cout << "---- new A ----\n";
    {
        auto a = new A();
        a->hello();
        delete a;
    }

    std::cout << "---- A {} ----\n";
    {
        A a {};
        a.hello();
    }

    std::cout << "---- unique_ptr A ----\n";
    {
        APtr a {new A()};
        a->hello();
    }

    std::cout << "--- make_ptr A (C++14) ---\n";
    {
        APtr a = std::make_unique<A>();
        a->hello();
    }
}

A stackall() {
    return {};
}

void callmove(A&& a) {
    printf("callmove %d\n", a.n);
}

void set(A a) {
    puts("-- set start --");
    a.n = 10;
    puts("-- set finish--");
}

void test2() {
    std::cout << "---- new B ----\n";
    {
        auto a = new B();
        a->hello();
        a->hello_a();           // undefined?
        delete a;
        a->hello();             // undefined?
    }

    // std::cout << "---- B {} ----\n";
    // {
    //     A a {};
    //     a.hello();
    // }

    // std::cout << "---- unique_ptr A ----\n";
    // {
    //     APtr a {new A()};
    //     a->hello();
    // }

}

void test3() {
    for (uint64_t i = 0; i < 1000000000000; i++) {
        APtr a { new A() };
    }
}

void test4() {
    std::cout << "-- test4 start --" << std::endl;
    A k = stackall();
    std::cout << "-- test4 finish --" << std::endl;
}

void test5() {
    puts("-- test 5 start --");
    A a {};
    set(a);
    puts("-- test 5 finish --");
}

void test6() {
    A a {};
    A c = std::move(a);
    puts("-- test6 --");
}

void test7() {
    A a {};
    a.n = 10;
    A b = std::move(a);
    // callmove(b);
    printf("after move %d %d\n", a.n, b.n);
    puts("-- test7 --");
}

void test8() {
    http://cpp.aquariuscode.com/return-value-optimization
    A a = A();
}

void ref0(A a) {
    a.n = 10;
    puts("--- ref0 ---");
}

void ref1(A& a) {
    a.n = 10;
}

void ref2(A *a) {
    a->n = 9;
}

A ref3(A&& a) {
    A kk {};
    puts("\n===================================== start print");
    A b = a;         // copy occured
    A bb {std::move(a)};
    puts("\n===================================== start print");
    return bb;
}

void test9() {
    auto a = A {};
    ref1(a);
    printf("%d\n", a.n);
    ref2(&a);
    printf("%d\n", a.n);
    auto a2 = ref3(std::move(a));
    printf("%d\n", a.n);

    puts("--");
    {
        auto a = A {};
        ref0(a);
        puts("--");
        ref0(std::move(a));
    }
}

class C {
public:
    C(A a): a_{std::move(a)} {}
    A a_;
};

void test10() {
    // A a {};
    // C c {std::move(a)};
    C c { A{} };
}

int main(int argc, char *argv[]) {
    std::cout << "-- main start --" << std::endl;
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    // test8();
    test9();
    // test10();

    std::cout << "-- main finish --" << std::endl;
    return 0;
}
