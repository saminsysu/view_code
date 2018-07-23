// 快排
void quick_sort(int[] input, int l, int h) {
    if (l >= h)
        return;
    int i = l;
    int j = h;
    int pivot = input[l];
    while (i < j) {
        while (i < j && pivot <= input[j])
            j--;
        while (i < j && input[i] <= pivot) {
            i++;
        if (i < j)
            int tp = input[j]
            input[j] = input[i];
            input[i] = tp; 
        }
    }
    input[l] = input[j];
    input[j] = pivot;
    quick_sort(input, l, j - 1);
    quick_sort(input, j + 1, h);
}

// 根据前序和中序构建二叉树

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* reConstructBinaryTree(vector<int> &pre, int p_s, int p_e, 
    vector<int> &vin, int v_s, int v_e) {
    if (p_s > p_e || v_s > v_e)
        return NULL;
    int root = pre[p_s];
    TreeNode* tree = new TreeNode(root);
    if (p_s == p_e || v_s == v_e)
        return tree;
    int r_vin_index;
    for (int i = v_s; i < v_e; i++)
        if (vin[i] == root) {
            r_vin_index = i;
            break;
        }
    int left_tree_len = r_vin_index - v_s;
    tree -> left = reConstructBinaryTree(pre, p_s + 1, p_s + left_tree_len, vin, v_s, r_vin_index - 1);
    tree -> right = reConstructBinaryTree(pre, p_s + left_tree_len + 1, p_e, vin, r_vin_index + 1, v_e);
    return tree;
}

// 二叉树的镜像

void Mirror(TreeNode *pRoot) {
    if (!pRoot)
        return;
    
    TreeNode *tp = pRoot -> left;
    pRoot -> left = pRoot -> right;
    pRoot -> right = tp;

    Mirror(pRoot -> left);
    Mirror(pRoot -> right);
}

// 最小的k个数，可使用最大堆、快排、自带sort算法、自带heap相关库函数

vector<int> GetLeastNumbers_Solution(vector<int> input, int k) { // 1. 建立 k 个数的最大堆，然后遍历第 k 以后的数，如果当前数小于堆顶，则交换堆顶和当前数，并调整堆。当遍历完成后，前 k 个数
    vector<int> r;                                               // 即为最小的 k 个数； 2. 直接使用快排； 3. 使用 c++ 自带的sort。
    if (input.size() == k)
        return input;
    if (k == 0 || input.size() < k)
        return r;
    /*
    make_heap(input.begin(), input.end());
    sort_heap(input.begin(), input.end());
    */
    buildMaxHeap(input, k);
    for (int i = k; i < input.size(); i++) {
        if (input[0] > input[i]) {
            swap(input[0], input[i]);
            maxHeapify(input, 0, k);
        }
    }
    // quick_sort(input, 0, input.size() - 1);
    // sort(input.begin(),input.end());
    for (int i = 0; i < k; i++)
        r.push_back(input[i]);
    return r;
}

void buildMaxHeap(vector<int> &input, int heapSize) {
    if (heapSize <= 1)
        return;
    int iParent = heapSize / 2 - 1;
    for (int i = iParent; i >= 0; i--) {
        maxHeapify(input, i, heapSize);
    }
}

void maxHeapify(vector<int> &input, int index, int heapSize) {
    int iMax = index;
    int iLeft = 2 * index + 1;
    int iRight = 2 * index + 2;
    if (iLeft < heapSize && input[iLeft] > input[iMax])
        iMax = iLeft;
    if (iRight < heapSize && input[iRight] > input[iMax])
        iMax = iRight;
    if (index != iMax) {
        swap(input[index], input[iMax]);
        maxHeapify(input, iMax, heapSize);  // 每一次移动都需要看移动是否对子树有影响；可以使用迭代，也可以使用递归
    }
}

// 回溯法判断矩阵中是否存在特定字符串的路径

bool hasPath(char* matrix, int rows, int cols, char* str)
{
    if (!matrix || rows < 0 || cols < 0 || !str)
        return false;
    bool* visited = new bool[rows * cols];
    int index = 0;
    memset(visited, false, rows * cols);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) { 
            if (_hasPath(matrix, rows, cols, r, c, visited, index, str))
                return true;
        }
    delete[] visited;
    visited = NULL;
    return false;
}

bool _hasPath(char* matrix, int rows, int cols, int row, int col, bool* visited, int& index, char* str) {
    if (str[index] == '\0') // 判断遍历完 str
        return true;
    bool has_path = false;
    if (row >= 0 && row < rows && col >= 0 && col < cols && matrix[row * cols + col] == str[index]
       && !visited[row * cols + col]) {
        visited[row * cols + col] = true;
        index++;
        has_path = _hasPath(matrix, rows, cols, row, col+1, visited, index, str) ||
            _hasPath(matrix, rows, cols, row, col-1, visited, index, str) ||
            _hasPath(matrix, rows, cols, row+1, col, visited, index, str) ||
            _hasPath(matrix, rows, cols, row-1, col, visited, index, str);
        if (!has_path) {
            index--;
            visited[row * cols + col] = false;
        } else {
            return true;
        }
    }
    return false;
}

// 找出数组中和为s且积最小的两个数
// 1. 如果未排序，先排序；
// 2. 离得最远的满足条件的两个数即为所求；如果是求最大值，则找最近的满足条件的两个数

vector<int> FindNumbersWithSum(vector<int> array,int sum) {
    int half = sum / 2;
    if (array.size() == 0)
        return array;
    vector<int> r;
    vector<int>::iterator other;
    for (vector<int>::iterator i = array.begin(); i < array.end(); i++) {
        if (*i < half) {
            other = find(i, array.end(), sum - *i);
            if (other != array.end()) {
                r.push_back(*i);
                r.push_back(*other);
                break;
            }
        }
    }
    return r;
}

// 把数字排成最小的数

static bool cmp(int a, int b) {
    string a_str = to_string(a);
    string b_str = to_string(b);
    return a_str + b_str < b_str + a_str;
}

string PrintMinNumber(vector<int> numbers) {
    sort(numbers.begin(), numbers.end(), cmp);
    string r = "";
    for (int i = 0; i < numbers.size(); i++) 
        r += to_string(numbers[i]);
    return r;
}

// heap 相关库函数使用说明，需要使用相同的排序准则less<int>()或greater<int>()或自定义，默认使用ess<int>()建立最大堆构建升序序列

make_heap(a, a+n) || make_heap(a, a+n, less<int>()); // 构建最大堆
make_heap(a, a+n, greater<int>()); // 构建最小堆
push_heap(a, a+n); // 向堆中加入元素，需确保区间（除最后一个元素）已经是一个堆
pop_heap(a, a+n); // 把堆顶元素交换到区间尾，然后把除了尾部的元素的剩余区间重新调整成堆，需确保区间已经是一个堆
sort_heap(a, a+n); // 堆排序，需确保区间已经是一个堆，默认升序 

// 二叉搜索树、有序二叉树、排序二叉树：左子树所有节点比根节点小，右子树所有节点比根节点大
// 查找树的第k小节点，中序遍历，左子树->根节点->右子树
// 查找树的第k大节点，右子树->根节点->左子树


int count = 0;

TreeNode* KthNode(TreeNode* pRoot, int k)
{
    if (pRoot) {
        TreeNode* r = KthNode(pRoot->left, k);
        if (r)
            return r;
        if (++count == k)
            return pRoot;
        r = KthNode(pRoot->right, k);
        if (r)
            return r;
    }
    return nullptr;
}

// 数组中重复的第一个数字

bool duplicate(int numbers[], int length, int* duplication) {
    if (length <= 0)
        return false;
    bool dup[length];
    memset(dup, false, length);
    for (int i = 0; i < length; i++) {
        if (dup[numbers[i]]) {
            *duplication = numbers[i];
            return true;
        }
        dup[numbers[i]] = true;
    }
    return false;
}

// 滑动窗口的最大值，使用双向队列实现，只需遍历一次数组，每个数组元素最多进出队列一次

vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
    vector<int> r;
    deque<int> d;
    if (!size)
        return r;
    for (int i = 0; i < num.size(); i++) {
        while (d.size() && num[d.back()] <= num[i])
            d.pop_back();
        while (d.size() && i - d.front() >= size)
            d.pop_front();
        d.push_back(i);
        if (i + 1 >= size)
            r.push_back(num[d.front()]);
    }
    return r;
}

// 全排列问题，从第一个字符起，对于它后面的每一个字符，如果该字符没出现过，则交换；否则不交换。

// 依次选择，直到全部元素都确定位置。

vector<string> Permutation(string str) {
    vector<string> r;
    if (str == "")
        return r;
    _Permutation(r, str, 0, str.size() - 1);
    sort(r.begin(), r.end());
    return r;
}

void _Permutation(vector<string> &result, string str, int start, int end) {
    if (start == end)
        result.push_back(str);;
    for (int i = start; i <= end; i++) {
        if (_isExisted(str, start, i-1, str[i]))
            continue;
        swap(str[i], str[start]); // 从 start 到 end 中选择第一个元素
        _Permutation(result, str, start+1, end); // 确认剩余元素
        swap(str[i], str[start]); // 回溯
    }
}
 
bool _isExisted(string str, int start, int end, char c) {
    for (int i = start; i <= end; i++)
        if (str[i] == c)
            return true;
    return false;
}

// 翻转链表

// 非递归

ListNode* ReverseList(ListNode* pHead) {
    if (pHead == nullptr || pHead -> next == nullptr)
        return pHead;
    ListNode* cur = pHead;
    ListNode* next = cur -> next;
    ListNode* pre = nullptr;
    while (next) {
        cur -> next = pre;
        pre = cur;
        cur = next;
        next = next -> next;
    }
    cur -> next = pre;
    return cur;
}

// 递归

ListNode* ReverseList(ListNode* pHead) {
    if (pHead == nullptr || pHead -> next == nullptr)
        return pHead;
    ListNode* r = ReverseList(pHead -> next);
    pHead -> next -> next = pHead;
    pHead -> next = nullptr; // 注意置为空
    return r;
}

// 逆序打印链表

// 1. 可以先用上述方法翻转链表，再输出链表，这样会遍历两次链表
// 2. 递归，只需遍历一次

vector<int> r; // 不要把变量定义在递归中
vector<int> printListFromTailToHead(ListNode* head) {
    if (head != nullptr) {
        if (head -> next != nullptr)
            r = printListFromTailToHead(head -> next);
        r.push_back(head -> val);
    }
    return r;
}

// 删除链表中重复元素

ListNode* deleteDuplication(ListNode* pHead)
{
    if (pHead == nullptr || pHead -> next == nullptr)
        return pHead;
    if (pHead -> next -> val == pHead -> val) {
        ListNode* cur = nullptr;
        cur = pHead -> next -> next;
        while (cur != nullptr && cur -> val == pHead -> val)
            cur = cur -> next;
         return deleteDuplication(cur);
    } else {
        pHead -> next = deleteDuplication(pHead -> next);
        return pHead;
    }
}

// 输出链表倒数第k个元素
// 遍历一次，定义两个相同指针，先让一个指针走k步，然后再同时前进
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    int count = 0;
    ListNode* r = pListHead;
    ListNode* tp = pListHead;
    while (tp) {
        if (count >= k)
            r = r -> next;
        tp = tp -> next;
        count++;
    }
    return k > count ? nullptr : r;
}

// 遍历两次，先确认链表长度，然后再前进到需要的位置
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    int count = 0;
    ListNode* r = pListHead;
    ListNode* tp = pListHead;
    while (tp) {
        count++;
        tp = tp -> next;
    }
    int index = count - k;
    while (index-- && r != nullptr) {
        r = r -> next;
    }
    return r;
}

// 替换字符串空格

// 1. 统计空格字数；
// 2. 从后往前替换空格，因为从后往前，每个空格后面的字符只需要移动一次。
// 从前往后，当遇到第一个空格时，要移动第一个空格后所有的字符一次；当遇到第二个空格时，要移动第二个空格后所有的字符一次；以此类推。所以总的移动次数会更多。
// 3. 考虑字符串结束符'\0'

void replaceSpace(char *str,int length) {
    int count = 0; // 空格数
    for (int i = 0; i < length; i++)
        if (str[i] == ' ')
            count++;
    for (int i = length; i >= 0; i--) { // 将'\0'考虑在内，从后往前遍历
        if (str[i] != ' ') {
            str[i+count*2] = str[i];
        } else {
            count--;
            str[i+2*count] = '%';
            str[i+2*count+1] = '2';
            str[i+2*count+2] = '0';
        }
    }
}


/* 请实现两个函数，分别用来序列化和反序列化二叉树
1. 广度优先搜索
2. 前序遍历
*/

char* Serialize(TreeNode *root) {    
    string str;
    Serialize(root, str);
    char* r = new char[str.length()+1];
    for (int i = 0; i < str.length(); i++)
        r[i] = str[i];
    r[str.length()] = '\0';
    return r;
}
TreeNode* Deserialize(char *str) {
    if (str == nullptr)
        return nullptr;
    TreeNode* r = deserialize(&str);
    return r;
}
void Serialize(TreeNode *root, string &str) {
    if (root) {
        str.append(to_string(root->val));
        str.append(",");
        Serialize(root->left, str);
        Serialize(root->right, str);
    }
    else {
        str.append("#");
        return;
    }
}
TreeNode* deserialize(char **str) {
    if (**str == '#') {
        (*str)++;
        return nullptr;
    }
    if (**str == '\0')
        return node;
    int num = 0;
    while (**str != ',') {
        num = 10 * num + (**str - '0');
        (*str)++;
    }
    TreeNode *node = new TreeNode(num);
    (*str)++;
    node -> left = deserialize(str);
    node -> right = deserialize(str);
    return node;
}

/* 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
二叉搜索树的后序遍历
*/
bool VerifySquenceOfBST(vector<int> sequence) {
    if (sequence.empty())
        return false;
    return VerifySquenceOfBST(sequence, 0, sequence.size() - 1);
    
}
bool VerifySquenceOfBST(vector<int> &sequence, int left_start, int root_index) {
    if (left_start >= root_index)
        return true;
    int right_start = left_start;
    for (; right_start < root_index; right_start++)
        if (sequence[right_start] > sequence[root_index])
            break;
    for (int i = right_start; i < root_index; i++)
        if (sequence[i] < sequence[root_index])
            return false;
    return VerifySquenceOfBST(sequence, left_start, right_start - 1) && VerifySquenceOfBST(sequence, right_start, root_index - 1);
}


/*
正则表达式匹配

请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，
而'*'表示它前面的字符可以出现任意次（包含0次）。 
在本题中，匹配是指字符串的所有字符匹配整个模式。
例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配

要分为几种情况：（状态机）
1. 当第二个字符不为‘*’时：匹配就是将字符串和模式的指针都下移一个，不匹配就直接返回false
2. 当第二个字符为'*'时：
    匹配：
        a.字符串下移一个，模式不动
        b.字符串下移一个，模式下移两个
        c.字符串不动，模式下移两个
    不匹配：字符串下移不动，模式下移两个
搞清楚这几种状态后，用递归实现即可
*/

bool match(char* str, char* pattern)
{
    if (*str == '\0' && *pattern == '\0')
        return true;
    if (*str != '\0' && *pattern == '\0')
        return false;
    if (*(pattern+1) == '*') {
        if (*str == *pattern || (*pattern == '.' && *str != '\0')) 
            return match(str, pattern+2) || match(str+1, pattern) || match(str+1, pattern+2);
        return match(str, pattern+2);
    } else {
        if (*str == *pattern || *pattern == '.')
            return match(str+1, pattern+1);
        return false;
    }
} 

/*
数组中只出现一次的数字
一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
1. 数组全部元素进行异或，得到异或值；
2. 根据异或值找出要找的两个数二进制表示中不同的一位（通过与一个只有一位为1的二进制数）；
3. 根据上一步骤得到的数将数组分为两部分，然后分别异或
*/

void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
    int flag = 1;
    int res = 0;
    for (int i = 0; i < data.size(); i++)
        res ^= data[i]; 
    while((flag & res) == 0)
        flag <<= 1;
    for (int i = 0; i < data.size(); i++)
        if (flag & data[i])
            *num1 ^= data[i];
        else
            *num2 ^= data[i];
}

/*
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
如果不存在则输出0。

在遍历数组时保存两个值：一是数组中一个数字，一是次数。
遍历下一个数字时，若它与之前保存的数字相同，则次数加1，否则次数减1；
若次数为0，则保存下一个数字，并将次数置为1。遍历结束后，所保存的数字即为所求。然后再判断它是否符合条件即可。
*/

int MoreThanHalfNum_Solution(vector<int> numbers) {
    if (numbers.empty())
        return 0;
    int num = numbers[0];
    int count = 1;
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] == num)
            count++;
        else
            count--;
        if (count == 0) {
            num = numbers[i];
            count = 1;
        }
    }
    count = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (num == numbers[i])
            count++;
    }
    if (count > numbers.size() / 2)
        return num;
    return 0;
}

// 二分查找
// 非递归实现二分查找
int BinarySearch(vector<int> data, int k) {
    if (data.empty())
        return -1;
    int start = 0;
    int end = data.size();
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (data[mid] = k)
            return mid;
        else if (data[mid] < k)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}

//递归实现二分查找

int BinarySearch(vector<int> data, int k, int start, int end) {
    if (data.empty())
        return -1;
    if (start < end)
        return -1;
    int mid = (start + end) >> 1;
    if (data[mid] = k)
        return mid;
    else if (data[mid] < k)
        return BinarySearch(data, k, mid+1, end);
    else
        return BinarySearch(data, k, start, mid-1);
}

/*
统计一个数字k在排序数组中出现的次数
一见到排序数组的第一反应必须是！！！二分查找！！！
解法1：遍历一次；
解法2：找到第一个k和最后一个k；
解法3：找到k-0.5和k+0.5
*/

int GetNumberOfK(vector<int> data ,int k) {
    return GetK(data, k+0.5) - GetK(data, k-0.5);
}

int GetK(vector<int>& data, double k) {
    int start = 0;
    int end = data.size() - 1;
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (data[mid] < k)
            start = mid + 1;
        else if (data[mid] > k)
            end = mid - 1;
    }
    return start;
}
