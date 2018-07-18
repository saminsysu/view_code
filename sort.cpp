/* 冒泡排序：每一次把最大的元素不断地往后冒
*/
void bubble_sort(int[] arr, int len) {
	if (len == 0 || len == 1 || arr == nullptr)
		return ;
	for (int i = 0; i < len - 1; i++) // n个数，只需要冒n-1次
		for (int j = 0; j < len - 1 - i; j++)
			if (arr[j] > arr[j++])
				swap(a[j], a[j+1]);
}

/* 选择排序：每一次把未排序序列中最小的元素放在未排序序列的最前面（排序序列的最后面）
*/
void select_sort(int[] arr, int len) {
	if (len == 0 || len == 1 || arr == nullptr)
		return ;
	int min_index;
	for (int i = 0; i < len - 1; i++) // n个数，只需要选择n-1次
		min_index = i;
		for (int j = i + 1; j < len; j++)
			if (arr[j] < min)
				min_index = j;
		if (i != min_index)
			swap(arr[i], arr[min_index]);
}

/* 插入排序：将未排序序列的第一个元素插入到排序序列的合适位置
*/
void insert_sort(int[] arr, int len) {
	if (len == 0 || len == 1 || arr == nullptr)
		return ;
	for (int i = 1; i < len; i++) { // 从数组第二个数开始
		int j = i - 1;
		int cur = arr[i];
		while (j >= 0 && cur < arr[j]) {
			arr[j+1] = arr[j];
			j--; 
		}
		arr[j+1] = cur; // arr[j]大于等于cur或者j<0时，将cur放在数组j+1处
	}
}

/* 快速排序：选择一个基准，然后使得基准左边的元素不大于基准，基准右边的元素不小于基准
*/
void quick_sort(int[] arr, int start, int end) {
	if (start >= end || arr == nullptr)
		return ;
	if (start < end)
	int i = start;
	int j = end;
	int pivot = arr[start];
	while (i < j) {
		while (i < j && pivot <= arr[j]) // 先从右边开始
			j--;
		while (i < j && pivot >= arr[i])
			i++;
		if (i < j)
			swap(arr[i], arr[j]);
	}
	arr[start] = a[i];
	arr[i] = pivot;
	quick_sort(arr, start, i-1);
	quick_sort(arr, i+1, end);
}
