#include <vector>
#include <algorithm>
#include <iostream>

class test {
public:
    ~test() = default;

    void getId() {
        std::cout << "get id" << std::endl;
    };
};

class test2 : public test {
public:
    test2() {
        std::cout << "hello" << std::endl;
    }
};

template<typename T = int, typename... Args>
void fct() {
    static int i = 0;

    if (std::is_same<T, int>())
        return;
    std::cout << i << std::endl;
    i++;
    fct<Args...>();
};

template<class T>
class test3 : public T {
public:
    test3() = default;
};

int main() {
    test2 test2;

    std::vector<test> vector = {test2};

    test3<::test2> test3;

    test3.getId();

    for (auto e : vector) {
        e.getId();
    }

    return 0;
}
