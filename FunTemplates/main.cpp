#include <iostream>
#include "fun.h"

using std::cout;
using std::endl;

int main()
{
    // cout << "fun<name::foo>():           " << fun<name::foo>() << endl;
    // cout << "fun<name::bar>():           " << fun<name::bar>() << endl;
    cout << "fun<name::baz>():           " << fun<name::baz>() << endl;
    // cout << "fun<name::quux>():           " << fun<name::quux>() << endl;

    cout << "fun<name::foo>(0):           " << fun<name::foo>(0) << endl;
    cout << "fun<name::bar>(0):           " << fun<name::bar>(0) << endl;
    // cout << "fun<name::baz>(0):           " << fun<name::baz>(0) << endl;
    cout << "fun<name::quux>(0):          " << fun<name::quux>(0) << endl;
    return 0;
}