#include <iostream>
enum ElementType{PATH = 100, WALL, FAKE_WALL};
class Base{
protected:
    ElementType type;
public:
    Base(ElementType in_t):type(in_t){}
    virtual ElementType get() const {
        return type;
    }
};
class Derived : public Base{
public:
    Derived():Base(PATH){}
};
int main()
{
    Derived* a = new Derived;
    std::cout << a->get() << std::endl;
    return 0;
}