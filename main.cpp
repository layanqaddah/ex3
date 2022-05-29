#include <iostream>
#include "Queue.h"
#include <iostream>
using std::cout;
int main() {
    std::cout << "Hello, World!" << std::endl;
    Queue<int> queue1;
    queue1.pushBack(1);
    queue1.pushBack(2);
    queue1.pushBack(3);
    queue1.pushBack(4);
    queue1.pushBack(5);

    Queue<int> queue2=queue1;


    cout<<queue2.front()<< std::endl;
    queue2.popFront();

    cout<<queue2.front()<< std::endl;
    queue2.popFront();

    cout<<queue2.front()<< std::endl;
    queue2.popFront();

    cout<<queue2.front()<< std::endl;
    queue2.popFront();




    return 0;
}
