#include <iostream>
#include "List.h"
using namespace std;


int main(){
    List<int> sl;
    sl.front_push(1);
    sl.front_push(2);
    sl.front_push(3);

    sl.printLL();

    List<int> b(sl);
    b.printLL();

    return 0;
}