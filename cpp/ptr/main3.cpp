#include <fstream>
#include <iostream>

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

int main(int argc, char *argv[])
{
    // test1();
    test2();
    return 0;
}
