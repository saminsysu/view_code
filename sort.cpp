/* 冒泡排序：每一次把最大的元素不断地往后冒
*/
void bubble_sort(int *arr, int len) {
	if (len == 0 || len == 1 || arr == nullptr)
		return ;
	for (int i = 0; i < len - 1; i++) // n个数，只需要冒n-1次
		for (int j = 0; j < len - 1 - i; j++)
			if (arr[j] > arr[j++])
				swap(a[j], a[j+1]);
}

/* 选择排序：每一次把未排序序列中最小的元素放在未排序序列的最前面（排序序列的最后面）
*/
void select_sort(int *arr, int len) {
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
void insert_sort(int *arr, int len) {
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

// 返回 pivot 的下标，将分区的代码提取出来

void partition(int *arr, int start, int end) {
	if (start > end || arr == nullptr || start < 0 || right < 0)
		return -1;
	int i = start;
	int j = end;
	int pivot = arr[start];
	while (i < j) {
		while (i < j && pivot <= arr[j]) // 先从右边开始
			j--;
		if (i < j) // 必要条件
			arr[i] = arr[j]; // 挖空填空
		while (i < j && pivot >= arr[i])
			i++;
		if (i < j) // 必要条件
			arr[j] == arr[i];
	}
	arr[i] = pivot;
	return i;
}

void quick_sort(int *arr, int start, int end) {
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

void quick_sort(int *arr, int start, int end) { // 含 end
	if (start >= end || arr == nullptr)
		return ;
	int i = start;
	int j = end;
	int pivot = arr[start];
	while (i < j) {
		while (i < j && pivot <= arr[j]) // 先从右边开始
			j--;
		if (i < j) // 必要条件
			arr[i] = arr[j]; // 挖空填空
		while (i < j && pivot >= arr[i])
			i++;
		if (i < j) // 必要条件
			arr[j] == arr[i];
	}
	arr[i] = pivot;
	quick_sort(arr, start, i-1);
	quick_sort(arr, i+1, end);
}

// 快排非递归实现，因为递归的本质是操作栈，所以使用栈可以实现快排

void quick_sort(int *arr, int start, int end) { // 含 end
	if (start >= end || arr == nullptr)
		return ;
	
	stack<int> index;
	index.push(end); // 先将end压入
	index.push(start);

	int i, j, index_of_pivot;

	while (!index.empty()) {
		i = index.top();
		index.pop();
		j = index.top();
		index.pop();

		index_of_pivot = partition(arr, i, j);

		if (index_of_pivot - 1 > start) {
			index.push(i - 1);
			index.push(i);
		}

		if (index_of_pivot + 1 < end) {
			index.push(j);
			index.push(i + 1);
		}

	}
}

/* 归并排序
归并排序使用了递归分治的思想，先递归划分子问题，然后合并结果。
把待排序列看成由两个有序的子序列，然后合并两个子序列。
*/

void merge_sort(int arr[], int start, int end) { // 含 end
	if (start >= end || arr == nullptr)
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
	if (heapSize <= 1 || arr == nullptr)
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
简单的插入排序中，如果待排序列是正序时，时间复杂度是O(n)，
如果序列是基本有序的，使用直接插入排序效率就非常高。希尔排序就利用了这个特点。
先将整个待排序列分割成为若干子序列分别进行插入排序，
待整个序列中的记录基本有序时再对全体记录进行一次插入排序。
*/

void shell_sort(int arr[], int len) {
	if (len <= 1 || arr == nullptr)
		return ;
	int d = len / 2; // 增量初始值，可以设计一个增量序列
	while (d >= 1) {
		for (int i = d; i < len; i += d) {
			int j = i - d;
			int cur = arr[i]; // 保存i处的值，因为有可能被改变
			while (j >= 0 && arr[i] < arr[j]) {
				arr[j+d] = arr[j]; // 往后移
				j -= d;
			}
			arr[j+d] = cur;
		}
		d /= 2;
	}
}

/* 计数排序，一种桶排序
一个O(n)时间复杂度的排序算法，只不过有前提条件，
就是待排序的数要满足一定的范围的整数，而且计数排序需要比较多的辅助空间
*/

void count_sort(int arr[], int len) {
	if (len <= 1 || arr == nullptr)
		return ;
	int max = arr[0];
	for (int i = 1; i < len; i++)
		if (max < arr[i])
			max = arr[i];
	int count[max+1] = {0};
	for (int i = 0; i < len; i++)
		count[arr[i]]++;
	int k = 0;
	for (int i = 0; i <= max; i++) {
		int j = count[i];
		while (j > 0) {
			arr[k++] = i;
			j--;
		}
	}

}

/* 基数排序：基数排序(Radix Sort)是桶排序的扩展，
它的基本思想是：将整数按位数切割成不同的数字，然后按每个位数分别比较。 
具体做法是：将所有待比较数值统一为同样的数位长度，数位较短的数前面补零。
然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后（不能从高到低）, 数列就变成一个有序序列。
*/
void radix_sort(int arr[], int len) {
	if (len <= 1 || arr == nullptr)
		return ;
	int max = arr[0];
	for (int i = 1; i < len; i++)
		if (max < arr[i])
			max = arr[i];
	for (int digit = 1; max / digit > 0; digit *= 10) {
		count_sort(arr, digit);
	}
}

void count_sort(int arr[], int len, int digit) {
	int ranges[10] = {0};
	int tp[len];
	for (int i = 0; i < len; i++) {
		ranges[(arr[i]/digit)%10]++;
	}
	for (int i = 1; i < 10; i++) {
		ranges[i] += ranges[i-1]; //统计本应该出现的位置
	}
	for (int i = len - 1; i >= 0; i--) { // 从后往前
		tp[ranges[(arr[i]/digit)%10]-1] = arr[i];
		ranges[(arr[i]/digit)%10]--;
	}
	for (int i = 0; i < len; i++)
		arr[i] = tp[i];
}


/* 桶排序，关键是设置桶映射函数。把数据分组，放在一个个的桶中，
然后对每个桶里面的在进行排序，桶本身是有序的。

给定n个实数x1,x2,...,xn,求这n个实数在实轴上相邻2个数之间的最大差值M,要求设计线性的时间算法

解法：

取数列的最大值和最小值然后均分作桶。因为最大差值 M>= (Max-Min/(n-1)！所以，假如以
(Max-Min/(n-1)为桶宽的话，答案一定不是属于同一个桶的两元素之差。
因此，这样建桶，每次只保留桶里面的最大值和最小值即可。
*/


