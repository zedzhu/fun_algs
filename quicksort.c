/*
 *http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/Sorting/quickSort.htm
 */

void quickSort(int numbers[], int n)
{
    q_sort(numbers, 0, n-1);
}

void q_sort(int numbers[], int left, int right)
{
    if (left < right)
    {
        int mid = partition(numbers, left, right);
        q_sort(numbers, left, mid-1);
        q_sort(numbers, mid+1, right);
    }
}

int partition(int numbers[], int left, int right)
{
    int pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = pivot;

    return left;
}

/*
void q_sort(int numbers[], int left, int right)
{
    if (left >= right) return;

    int pivot, l_hold, r_hold;
    l_hold = left;
    r_hold = right;
    pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    q_sort(numbers, left, pivot-1);
    q_sort(numbers, pivot+1, right);
}
*/

