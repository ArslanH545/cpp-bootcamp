#include <iostream>
#include "List.h"

int main(){
    // Test 1
    List<int> l;
    for (int i = 1; i <= 1000; ++i) l.back_push(i);
    long s = 0;
    for (auto& x : l) s += x;
    std::cout << "sum=" << s << " size=" << l.getSize() << "\n";   // sum=500500 size=1000


    // Test 2 — rule of three ( destructor, copy constructor and copy assignment operator)
    List<int> a; a.back_push(1); a.back_push(2);
    List<int> b; b.back_push(9);
    b = a;
    b.back_push(99);              // mutate b only
    a.printLL();                  // 1->2->
    b.printLL();                  // 1->2->99->
    List<int>& alias = b;
    b = alias;                    // self-assign, compiler can't prove it                      // self-assign
    b.printLL();                  // 1->2->99->
    std::cout << "a=" << a.getSize() << " b=" << b.getSize() << "\n";   // a=2 b=3
    return 0;
}