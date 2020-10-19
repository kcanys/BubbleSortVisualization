#include <iostream>
#include "sort.h"

int main()
{
    sort bubbleSort;
    //Sort loop
    while (bubbleSort.running())
    {
        //Update
        bubbleSort.update();

        //Render
        bubbleSort.render();
    }
    return 0;
}