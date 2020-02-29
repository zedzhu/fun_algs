#include <iostream>
#include <algorithm>
using namespace std;

// 堆排序：（最大堆，有序区）。从堆顶把根卸出来放在有序区之前，再恢复堆。

//做一次堆顶调整：保证堆顶比直系左右孩子都大，但不判断第二代及以上。
void max_heapify(int arr[], int start, int end) {
	//建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 + 1; //根节点从0开始标号，所以左孩子=根*2+1，右孩子=根*2+2。如果是从1开始标号，则左=根*2，右=根*2+1
	while (son <= end) { //若子節點指標在範圍內才做比較
		if (son + 1 <= end && arr[son] < arr[son + 1]) //先比較兩個子節點大小，選擇最大的
			son++;
		
		if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { //否則交換父子內容再繼續子節點和孫節點比較
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len) {
	//初始化，i從最後一個父節點開始調整，调整完毕之后，arr[0]是最大元素。
	for (int i = len / 2 - 1; i >= 0; i--) //最后1个具有孩子节点的是len/2-1
		max_heapify(arr, i, len - 1);
	//先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1); //堆顶元素（0号元素）已经变化，再调整一次堆顶
	}
}

int main() {
	int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
	int len = (int) sizeof(arr) / sizeof(*arr);
	heap_sort(arr, len);
	for (int i = 0; i < len; i++)
		cout << arr[i] << ' ';
	cout << endl;
	return 0;
}