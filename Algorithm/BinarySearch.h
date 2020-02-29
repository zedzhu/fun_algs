// 二分查找（折半查找）：对于已排序，若无序，需要先排序

// 非递归
int BinarySearch(vector<int> v, int value)
{
	if (v.size() <= 0)
		return -1;

	int low = 0;
	int high = v.size() - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (v[mid] == value)
			return mid;
		else if (v[mid] > value)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

// 递归
int BinarySearch2(vector<int> v, int value, int low, int high)
{
	if (low > high)
		return -1;
	int mid = low + (high - low) / 2;
	if (v[mid] == value)
		return mid;
	else if (v[mid] > value)
		return BinarySearch2(v, value, low, mid - 1);
	else
		return BinarySearch2(v, value, mid + 1, high);
}

int binary_search(int A[], int low, int high, int key){
    while (low <= high) {
        //int mid = low + (high-low)/2;
        int mid = (low + high) >> 1;
        if (A[mid] == key) {
            return mid;
        }
        else if (key > A[mid]) {
            low = mid + 1;
        }
        else if (key < A[mid]) {
            high = mid - 1;
        }
    }
    return -1;
}