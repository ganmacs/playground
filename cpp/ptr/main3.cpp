#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

void EncodeFixed32(char* buf, uint32_t value) {
    buf[0] = value & 0xff;
    buf[1] = (value >> 8) & 0xff;
    buf[2] = (value >> 16) & 0xff;
    buf[3] = (value >> 24) & 0xff;
}


void parse_uint8(char* ui8) {
    printf("%d\n", static_cast<uint8_t>(ui8[0]));
}

inline void parse_uint32(char* ui8) {
    // printf("%d\n",
    //        );
}

void test1() {
    char b[4];
    EncodeFixed32(b, 25100);
    parse_uint8(b);
    parse_uint32(b);
}

void test2() {
    std::string s {};
    s.append("a");
    char buf[1];
    std::ofstream file("./person.txt");

    buf[0] = 8;
    s.append(buf);

    file << s;
}

void set(std::string& s, uint8_t v) {
    char buf[sizeof(uint8_t)];
    buf[0] = v;
    s.append(buf);
}

class A {
public:
    virtual void a() = 0;
};

class B: public A {
public:
    void a() override {
        puts("\n===================================== start print");
    };
};

using APtr = std::shared_ptr<A>;
using BPtr = std::shared_ptr<B>;

void hoge(std::queue<APtr>& q) {
    q.emplace(BPtr {new B {}});
    B b{};
    q.emplace(BPtr{&b});
}

void test4() {
    std::queue<APtr> a;
    hoge(a);

    // a.emplace(BPtr {new B {}});
    auto v = a.front();
    a.pop();
    v->a();

    auto v2 = a.front();
    a.pop();
    v2->a();
}

void test3() {
    std::string str;
    std::cout << str.size() << "\n";      //  0 が表示される
    std::cout << str.length() << "\n";

    std::string a ;
    set(a, 10);

    std::ofstream file("./person2.txt");
    puts("\n===================================== start print");
    file.write(a.c_str(), 1);
}


void test5(){
    std::map<std::string, std::string> v = { {"a", "200"} };

}

struct AAA {
public:
    AAA() {
        puts("construtor AAA");
    };
    ~AAA() {
        puts("destructor AAA");
    }
    AAA(AAA &&a) noexcept {
        *this = std::move(a);
        puts("Move AAA");
    }

    AAA& operator = (AAA &&a) noexcept {
        std::cout << "Move = " << this << std::endl;
        this->v = a.v;
        this->str = std::move(a.str);

        a.v = nullptr;
        return *this;
    }

    AAA(AAA &a) noexcept {
        puts("copy");
    }

    AAA(uint8_t *vv): v{vv} {};
    uint8_t *v;
    std::string str;
};

void test6(){
    std::map<std::string, std::string> v = {
        {"aasdfghjkldkfjaslkdjalkjljf;lakfjaldk", "200"},
        {"b;asdfjlaksdfjaldskfjaldfkjldskfjadkfjafkj8g", "300"},
        {"d;asdkfjlaksdfjaldskfjaldfkjldskfjadkfjafkj8g", "300"},
        {"e;asdfjlaksdfjaldskfjaldfkjldskfjadkfjafkj8g", "300"},
        {"f;asdfjlaksdfjaldskfjaldfkjldskfjadkfjafkj8g", "300"},
        {"g;asdfjlaksdfjaldskfjaldfkjldskfjadkfjafkj8g", "300"}
    };
    AAA hdrs[10];

    int j = 0;
    for(auto i = v.begin(); i != v.end() ; ++i) {
        auto a = &i->first;
        printf("%s\n", a->c_str());
        hdrs[j].v =  (uint8_t*)a->c_str();
    }

    puts("\n===================================== start print");
    printf("%s\n", hdrs[0].v);
}

void hoge7(AAA &aaa) {
    std::string a = "kkkkkkkkkkkkkkkkkkkkkkkkkkkkasfsdfghjklsdfghjkldfghjsssssssssssssssssssssssssss";
    aaa.v = (uint8_t *)a.data();
    aaa.str = std::move(a);

    printf("%p\n", &a);
    printf("%p\n", aaa.v);
    printf("%p\n", &aaa.str);
    printf("%s\n", aaa.v);
    puts("\n===================================== start print");
    // return std::move(aaa);
}

std::string hoge7_1() {
    auto v = "asdfghjkldfghjklqwertyuiopsdfghjklbnm, dfghjkrkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkktyuio";
    printf("%p\n", &v);
    return std::move(v);
}

void test7() {
    AAA a;

    puts("\n===================================== start print");
    // auto b = hoge7(a);
    // hoge7(a);
    // std::cout << a.str.data() << std::endl;
    // printf("%p\n", &a);
    // printf("%d\n", a.str.length());
    // printf("%s\n", a.v);
    // printf("%p\n", a.v);
    // printf("%p\n", &a.str);

    auto v = hoge7_1();
    printf("%p\n", &v);

    puts("===================================== finish print\n");
}

int main(int argc, char *argv[])
{
    // test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    test7();
    return 0;
}
