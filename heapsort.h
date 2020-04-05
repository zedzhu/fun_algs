/*
 * http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/Sorting/heapSort.htm
 */

#include <algorithm>

#define swap(t,a,b) ( (t) = (a), (a) = (b), (b) = (t) )

void heapSort(int numbers[], int array_size)
{
    int i, temp;

    for (i = (array_size / 2)-1; i >= 0; i--)
        siftDown(numbers, i, array_size-1);

    for (i = array_size-1; i >= 1; i--)
    {
        swap(temp, numbers[0], numbers[i]);
        siftDown(numbers, 0, i-1);
    }
}

void siftDown(int numbers[], int root, int bottom)
{
    int done, leftChild, maxChild, temp;

    done = 0;
    while ((leftChild = root*2 + 1) <= bottom && !done)
    {
        if (leftChild == bottom) //only left child exists
            maxChild = leftChild;
        else if (numbers[leftChild] > numbers[leftChild + 1]) //left child is bigger than right child
            maxChild = leftChild;
        else
            maxChild = leftChild + 1;

        if (numbers[root] < numbers[maxChild])
        {
            swap(temp, numbers[root], numbers[maxChild]);
            root = maxChild;    //go down
        }
        else
            done = 1;
    }
}
