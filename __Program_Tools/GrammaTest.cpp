#include <bits/stdc++.h>
using namespace std;

class A
{
public:
    int operator[](string s)
    {
        cout << s;
        return 0;
    }
};

class B : public A
{
public:

};

int main()
{
    A a;
    B b;
    cout << a["a"] << endl;
    cout << b["b"] << endl;
    return 0;
}
