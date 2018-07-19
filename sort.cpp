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

// 改进，节省了交换时创建的临时空间

void quick_sort(int[] arr, int start, int end) { // 含 end
	if (start >= end || arr == nullptr)
		return ;
	int i = start;
	int j = end;
	int pivot = arr[start];
	while (i < j) {
		while (i < j && pivot <= arr[j]) // 先从右边开始
			j--;
		if (i < j) // 必要条件
			arr[i] = arr[j];
		while (i < j && pivot >= arr[i])
			i++;
		if (i < j) // 必要条件
			arr[j] == arr[i];
	}
	arr[i] = pivot;
	quick_sort(arr, start, i-1);
	quick_sort(arr, i+1, end);
}

/* 归并排序
归并排序使用了递归分治的思想，先递归划分子问题，然后合并结果。
把待排序列看成由两个有序的子序列，然后合并两个子序列。
*/

void merge_sort(int arr[], int start, int end) { // 含 end
	if (start >= end)
		return;
	int mid = (end + start) / 2; 
	merge_sort(arr, start, mid); // 递归排序左边
	merge_sort(arr, mid+1, end); // 递归排序右边
	int tp[end - start + 1];
	int i = start;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= end) {
		if (arr[i] < arr[j])
			tp[k++] = arr[i++];
		else
			tp[k++] = arr[j++];
	}
	while (i <= mid)
		tp[k++] = arr[i++];
	while (j <= end)
		tp[k++] = arr[j++];
	for (int i = 0; i < k; i++) {
		arr[start+i] = tp[i];
	}

}

/* 堆排序，包括1. 构建堆树（最大堆或大顶堆和最小堆或小顶堆）以及2. 调整堆
堆树是是完全二叉树，因此节点i的子节点分别为2i+1和2i+2
1. 构建堆树
从最后一个非叶子节点开始构建，不断往前，直到根节点
2. 当从堆顶移走元素时，将新增加的元素与左右子节点比较，需要不断往下调整
*/

void heap_sort(int arr[], int len) { // 升序
	build_heap(arr, len);
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		adjust_heap(arr, i, 0);
	}
}

void build_heap(int arr[], int heap_size) {
	if (heapSize <= 1)
        return;
	int index = heap_size / 2 - 1;
	for (int i = index; i >= 0; i--) {
		adjust_heap(arr, heap_size, index);
	}

}

// 递归实现最大堆

void adjust_heap(int arr[], int heap_size, int index) {
	int index_max = index;
	int index_left = index << 1 + 1;
	int index_right = index << 1 + 2;
	if (index_left < heap_size && arr[index_left] > arr[index])
		index_max = index_left;
	if (index_right < heap_size && arr[index_right] > arr[index])
		index_max = index_right;
	if (index != index_max) {
        swap(arr[index], arr[index_max]);
        maxHeapify(arr, heap_size, index_max);  // 每一次移动都需要看移动是否对子树有影响；可以使用迭代，也可以使用递归
    }
}

// 迭代实现最大堆

void adjust_heap(int arr[], int heap_size, int index) {
	int index_max, index_left, index_right;
	while {
		index_max = index;
		index_left = index << 1 + 1;
		index_right = index << 1 + 2;
		if (index_left < heap_size && arr[index_left] > arr[index])
			index_max = index_left;
		if (index_right < heap_size && arr[index_right] > arr[index])
			index_max = index_right;
		if (index != index_max) {
	        swap(arr[index], arr[index_max]);
	        index = index_max;  // 每一次移动都需要看移动是否对子树有影响；可以使用迭代，也可以使用递归
	    } else {
	    	break;
	    }
	}
}

/* 希尔排序
*/
