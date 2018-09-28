#include <iostream>
#include <string>
using namespace std;

/* 二分查找
* arr 已经有序，查找数组中是否存在值 num，如果找到返回下标，否则返回-1
*/

// 循环实现

int binary_find(int *arr, int length, int num) {
	if (arr == nullptr || length <= 0) {
		return -1;
	}
	int i = 0;
	int j = length - 1;
	int mid;
	while (i <= j) {
		mid = (i + j) / 2;
		if (a[mid] == num) {
			return mid;
		} else if (a[mid] > num) {
			j = mid - 1;
		} else {
			i = mid + 1;
		}
	}
	return -1;
}

// 递归实现

int binary_find(int *arr, int start, int end, int num) {
	if (arr == nullptr || start < end) {
		return -1;
	}
	int mid = (start + end) / 2;
	if (a[mid] == num) {
		return mid;
	} else if (a[mid] > num) {
		return binary_find(arr, mid + 1, end, num);
	} else {
		return binary_find(arr, start, mid - 1, num);
	}
}