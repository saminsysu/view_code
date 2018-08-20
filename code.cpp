// 快排
void quick_sort(int *input, int start, int end) {
    if (start >= end || input == nullptr)
        return;
    int i = start;
    int j = end;
    int pivot = input[start];
    while (i < j) {
        while (i < j && pivot <= input[j])
            j--;
        while (i < j && input[i] <= pivot) {
            i++;
        if (i < j)
            swap(input[i], input[j]);
        }
    }
    input[start] = input[j];
    input[j] = pivot;
    quick_sort(input, start, j - 1);
    quick_sort(input, j + 1, end);
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

bool duplicate(int *numbers, int length, int* duplication) {
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
        result.push_back(str);
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

/* 确定一个数的二进制表示中有多少个1
*/

int number_of_1(int num) {
    int flag = 1;
    int count = 0;
    while (flag) {
        if (num & flag) {
            count++;
        }
        flag << 1; // 需要移动32位
    }
    return count;
}

// 优化，有多少个1则执行几次

int number_of_1(int num) {
    int count = 0;
    while (num) {
        num = num & (num - 1); // num & (num - 1) 后右边全变成0
        count++;
    }
    return count;
}

/* 
输入一颗二叉树的跟节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
*/

vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
    vector<vector<int> > paths;
    if (root == nullptr)
        return paths;
    int sum = 0;
    vector<int> path;
    FindPath(root, expectNumber, paths, path, sum);
    return paths;
}
void FindPath(TreeNode* root, int &expectNumber, vector<vector<int> > &paths, vector<int> &path, int &sum) {
    if (root == nullptr)
        return ;
    if (root -> val <= expectNumber - sum) {
        path.push_back(root -> val);
        sum += root -> val;
        if (root -> left == nullptr && root -> right == nullptr && sum == expectNumber) {
            paths.push_back(path);
        }
        FindPath(root -> left, expectNumber, paths, path, sum);
        FindPath(root -> right, expectNumber, paths, path, sum);
        path.pop_back();
        sum -= root -> val;
    }
}

/*
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），
返回结果为复制后复杂链表的head。
*/

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
        label(x), next(NULL), random(NULL) {
    }
};

// 使用一个 map 保存 node 映射信息，空间换时间

RandomListNode* Clone(RandomListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
    map<RandomListNode*, RandomListNode*> node_map;
    RandomListNode* cur = pHead;
    RandomListNode* head = nullptr;
    RandomListNode* copy_cur = nullptr;
    while (cur) {
        RandomListNode* temp = new RandomListNode(cur -> label);
        node_map.insert(pair<RandomListNode*, RandomListNode*>(cur, temp));
        if (head == nullptr) {
            head = temp;
            copy_cur = temp;
        } else {
            copy_cur -> next = temp;
            copy_cur = copy_cur -> next;
        }
        cur = cur -> next;
    }
    cur = pHead;
    copy_cur = head;
    while (cur) {
        if (cur -> random) {
            copy_cur -> random = node_map[cur -> random];
        }
        cur = cur -> next;
        copy_cur = copy_cur -> next;
    }
    return head;
}

// 优化，不使用额外空间。首先将复制结点放到原结点后面，然后操作特殊指针，最后再拆分（避免修改原链表）

RandomListNode* Clone(RandomListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;
    RandomListNode* cur = pHead;
    RandomListNode* head = nullptr;
    while (cur) {
        RandomListNode* temp = new RandomListNode(cur -> label);
        temp -> next = cur -> next;
        cur -> next = temp;
        cur = cur -> next -> next;
    }
    cur = pHead;
    while (cur) {
        if (cur -> random) {
            cur -> next -> random = cur -> random -> next;
        }
        cur = cur -> next -> next;
    }
    cur = pHead;
    head = cur -> next;
    RandomListNode* temp = nullptr;
    while (cur) { // 注意还原原列表，原则上复制是只读不写
        temp = cur -> next;
        if (temp) {
            cur -> next = temp -> next;
        } else {
            cur -> next = nullptr;
        }
        cur = temp;
    }
    return head;
}

/* 连续子数组的最大和
给一个数组，返回它的最大连续子序列的和
*/

int FindGreatestSumOfSubArray(vector<int> array) {
    if (array.empty()) {
        return 0;
    }
    int cur_max = 0;
    int max = INT_MIN;
    for (int i = 0; i < array.size(); i++) {
        cur_max += array[i];
        if (cur_max > max) {
            max = cur_max;
        }
        if (cur_max < 0) {
            cur_max = 0;
        }
    }
    return max;
}

// 或者

int FindGreatestSumOfSubArray(vector<int> array) {
    if (array.empty()) {
        return 0;
    }
    int cur_max = 0;
    int max = INT_MIN;
    for (int i = 0; i < array.size(); i++) {
        if (cur_max <= 0) {
            cur_max = array[i];
        } else {
            cur_max += array[i];
        }
        if (cur_max > max) {
            max = cur_max;
        }
    }
    return max;
}

/* 从1到n，1（数位）出现的次数
分别对每个数位为1时的数进行统计分析
*/
int NumberOf1Between1AndN_Solution(int n)
{
    int count = 0;
    for (int i = 1; i <= n; i *= 10) {
        int h = n / i, l = n % i;
        count = count + (h + 8) / 10 * i + (h % 10 == 1) * (l + 1); // 加8是因为数位>=2、<=1需要分开讨论
    }
    return count;
}

/* 输出第n个丑数
把只包含质因子2、3和5的数称作丑数（Ugly Number）。
例如6、8都是丑数，但14不是，因为它包含质因子7。 
习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
*/

int GetUglyNumber_Solution(int index) {
    if (index < 1)
        return 0;
    int count = 1;
    int i_two = 0, i_three = 0, i_five = 0;
    int *arr = new int[index]; // 不能通过arr[index]创建数组
    arr[0] = 1;
    while (count < index) {
        while ((arr[i_two] * 2) <= arr[count-1]) {
            i_two++;
        }
        while ((arr[i_three] * 3) <= arr[count-1]) {
            i_three++;
        }
        while ((arr[i_five] * 5) <= arr[count-1]) {
            i_five++;
        }
        arr[count++] = min( min(arr[i_two] * 2, arr[i_three] * 3), arr[i_five] * 5);
    }
    return arr[count-1];
}

/* 输入两个链表，找出它们的第一个公共结点。
先让长链表走k步使得长链表剩余长度和短链表一样，然后同时遍历到第一个相同结点。
如果没有相同结点，会同时遍历到nullptr结点，返回nullptr。
*/

ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
    if (pHead1 == nullptr || pHead2 == nullptr)
        return nullptr;
    int len_1 = 0, len_2 = 0;
    ListNode *cur_1 = pHead1, *cur_2 = pHead2;
    while (cur_1) {
        len_1++;
        cur_1 = cur_1 -> next;
    }
    while (cur_2) {
        len_2++;
        cur_2 = cur_2 -> next;
    }
    ListNode *long_list_head, *short_list_head;
    int steps;
    if (len_1 > len_2) {
        long_list_head = pHead1;
        short_list_head = pHead2;
        steps = len_1 - len_2;
    } else {
        long_list_head = pHead2;
        short_list_head = pHead1;
        steps = len_2 - len_1;
    }
    while (steps) {
        long_list_head = long_list_head -> next;
        steps--;
    }
    while (long_list_head != short_list_head) {
        long_list_head = long_list_head -> next;
        short_list_head = short_list_head -> next;
    }
    return long_list_head;
}

/* 第一次只出现一次的字符
在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符，
并返回它的位置, 如果没有则返回 -1（需要区分大小写）
使用一个数组统计出现次数
*/
int FirstNotRepeatingChar(string str) {
    if (str.empty())
        return -1;
    int chars[256] = {0};
    for (int i = 0; i < str.size(); i++) {
        chars[str[i]]++;
    }
    for (int i = 0; i < str.size(); i++) {
        if (chars[str[i]] == 1) {
            return i;
        }
    }
    return -1;
}

/* 二叉树的深度
输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
*/

// 递归

int TreeDepth(TreeNode* pRoot)
{
    if (pRoot == nullptr)
        return 0;
    int left = TreeDepth(pRoot -> left);
    int right = TreeDepth(pRoot -> right);
    return left > right ? (left + 1) : (right + 1);
}

// 广搜

int TreeDepth(TreeNode* pRoot)
{
    if (pRoot == nullptr)
        return 0;
    queue<TreeNode*> node_queue;
    node_queue.push(pRoot);
    int depth = 0;
    TreeNode* temp;
    int size;
    while (!node_queue.empty()) {
        size = node_queue.size();
        depth++;
        while (size > 0) {
            temp = node_queue.front();
            node_queue.pop();
            if (temp -> left) {
                node_queue.push(temp -> left);
            }
            if (temp -> right) {
                node_queue.push(temp -> right);
            }
            size--;
        }
    }
    return depth;
}

/* 左旋转字符串
可以直接用 string 的 substr，或者
先分别翻转0～n-1 和 n~len（其中 n<len）的字符串，然后再翻转整个字符串
*/

string LeftRotateString(string str, int n) {
    if (str.empty()) {
        return str;
    }
    n = n % str.size();
    if (n == 0) {
        return str;
    }
    string str1 = str.substr(0, n);
    string str2 = str.substr(n, str.size() - n);
    return str2+str1;
}

/* 链表中环的入口
先求出环的长度 len，再使用一个快结点先走 len 步，然后快慢结点同时走，直到相遇即为所求

和 求链表倒数第 k 个结点解法相似
*/
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    if (pHead == nullptr || pHead -> next == nullptr || pHead -> next -> next == nullptr) {
        return nullptr;
    }
    ListNode *first = pHead -> next, *second = pHead -> next -> next;
    int loop_len = 0;
    while (second -> next != nullptr && second -> next -> next != nullptr) {
        if (second == first) {
            loop_len++;
            first = first -> next;
            while (first != second) {
                loop_len++;
                first = first -> next;
            }
            break;
        }
        second = second -> next -> next;
        first = first -> next;
    }
    first = second = pHead;
    for (int i = 0; i < loop_len && first != nullptr; i++) {
        first = first -> next;
    }
    while (first != second) {
        first = first -> next;
        second = second -> next;
    }
    return second;
}

/* 翻转单词顺序表
方案一 使用栈辅助，后进先出
方案二 先翻转每个单词，然后再翻转整个字符串
*/

string ReverseSentence(string str) {
    stack<string> words;
    if (str.empty()) {
        return str;
    }
    int first = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            words.push(str.substr(first, i - first));
            first = i + 1;
        }
    }
    words.push(str.substr(first, str.size() - first));
    string r = "";
    bool is_first = true;
    int len = words.size();
    for (int i = 0; i < len; i++) { // 注意此处用 len 而不是 words.size()，因为 words.size() 一直在变
        if (is_first) {
            is_first = false;
        } else {
            r += " ";
        }
        r += words.top();
        words.pop();
    }
    return r;
}

/* 栈的压入、弹出序列
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
*/
bool IsPopOrder(vector<int> pushV,vector<int> popV) {
    int top;
    int index_of_pop = 0, index_of_push = 0;
    stack<int> sta;
    sta.push(pushV[index_of_push++]);
    while (index_of_pop < popV.size()) {
        if (popV[index_of_pop] != sta.top() && index_of_push < pushV.size()) {
            sta.push(pushV[index_of_push++]);
        } else if (popV[index_of_pop] == sta.top()) {
            index_of_pop++;
            sta.pop();
        } else { // index_of_push >= pushV.size() && popV[index_of_pop] != sta.top()
            break;
        }
    }
    if (!sta.empty()) {
        return false;
    } else {
        return true;
    }
}

/* 按之字形顺序打印二叉树
请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，
第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

交替使用两个栈来实现
*/

vector<vector<int> > Print(TreeNode* pRoot) {
    vector<vector<int> > r;
    if (pRoot == nullptr) {
        return r;
    }
    stack<TreeNode*> sta1;
    stack<TreeNode*> sta2;
    sta1.push(pRoot);
    while (!sta1.empty() || !sta2.empty()) {
        vector<int> vec;
        if (!sta1.empty()) {
            while (!sta1.empty()) {
                TreeNode* temp = sta1.top();
                vec.push_back(temp -> val);
                sta1.pop();
                if (temp -> left) {
                    sta2.push(temp -> left);
                }
                if (temp -> right) {
                    sta2.push(temp -> right);
                }
            }
        } else {
            while (!sta2.empty()) {
                TreeNode* temp = sta2.top();
                vec.push_back(temp -> val);
                sta2.pop();
                if (temp -> right) {
                    sta1.push(temp -> right);
                }
                if (temp -> left) {
                    sta1.push(temp -> left);
                }
            }
        }
        r.push_back(vec);
    }
    return r;
} 

/* 调整数组元素顺序使奇数位于偶数前面

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，
并保证奇数和奇数，偶数和偶数之间的相对位置不变。

方案一 使用额为空间
方案二 类插入排序
*/


void reOrderArray(vector<int> &array) {
    if (array.empty()) {
        return ;
    }
    vector<int> odds;
    vector<int> evens;
    for (int i = 0; i < array.size(); i++) {
        if (array[i] & 1) { // 奇数
            odds.push_back(array[i]);
        } else {
            evens.push_back(array[i]);
        }
    }
    for (int i = 0; i < odds.size(); i++) {
        array[i] = odds[i];
    }
    for (int i = 0; i < evens.size(); i++) {
        array[i+odds.size()] = evens[i];
    }
}

// 类插入排序

void reOrderArray(vector<int> &array) {
    if (array.empty()) {
        return ;
    }
    int index_of_odds = 0, temp;
    for (int i = 0; i < array.size(); i++) {
        if (array[i] & 1) {
            temp = array[i];
            for (int j = i; j > index_of_odds; j--) {
                array[j] = array[j - 1];
            }
            array[index_of_odds] = temp;
            index_of_odds++;
        }
    }
}

/* 扑克牌顺子
*/

bool IsContinuous( vector<int> numbers ) {
    if (numbers.empty()) {
        return false;
    }
    sort(numbers.begin(), numbers.end());
    int num_of_kings = 0;
    int diff = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] == 0) {
            num_of_kings++;
        } else {
            if (i > 0 && numbers[i - 1] != 0) {
                if (numbers[i - 1] == numbers[i]) {
                    return false;
                }
                diff += numbers[i] - numbers[i - 1] - 1;
            }
        }
    }
    if (diff > num_of_kings) {
        return false;
    } else {
        return true;
    }
}

/* 和为 S 的连续正数序列（至少包括两个数）
输出所有和为 S 的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
*/

vector<vector<int> > FindContinuousSequence(int sum) {
    vector<vector<int> > r;
    if (sum <= 1) {
        return r;
    }
    int start = 1, end = 1, _sum = 0;
    while (end <= sum / 2 + 2 && start <= end) {
        if (_sum < sum) {
            _sum += end;
            end++;
        } else if (_sum == sum) {
            vector<int> temp;
            for (int j = start; j < end; j++) { // 不含 end
                temp.push_back(j);
            }
            r.push_back(temp);
            _sum -= start;
            start++;
        } else {
            _sum -= start;
            start++;
        }
    }
    return r;
}

/* 合并两个排序的链表
*/

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr) {
        return pHead2;
    }
    if (pHead2 == nullptr) {
        return pHead1;
    }
    ListNode *head = nullptr, *cur = nullptr;
    while (pHead1 != nullptr && pHead2 != nullptr) {
        if (pHead1 -> val < pHead2 -> val) {
            if (head == nullptr) {
                head = cur = pHead1;
            } else {
                cur -> next = pHead1;
                cur = cur -> next;
            }
            pHead1 = pHead1 -> next;
        } else {
            if (head == nullptr) {
                head = cur = pHead2;
            } else {
                cur -> next = pHead2;
                cur = cur -> next;
            }
            pHead2 = pHead2 -> next;
        }
    }
    if (pHead1 != nullptr) {
        cur -> next = pHead1;
    }
    if (pHead2 != nullptr) {
        cur -> next = pHead2;
    }
    return head;
}

/* 二叉树的下一个结点
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) { 
    }
};

TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
    TreeLinkNode* next = pNode -> right;
    if (next == nullptr) {
        TreeLinkNode* par = pNode -> next, *kid = pNode;
        if (par != nullptr) {
            if (par -> left == kid) {
                return par;
            } else {
                kid = par;
                par = kid -> next;
                while (par && par -> right == kid) {
                    kid = par;
                    par = par -> next;
                }
                return par;
            }
        } else {
            return nullptr;
        }
    } else {
        while (next -> left != nullptr) {
            next = next -> left;
        }
        return next;
    }
}

/* 旋转数组的最小数字
输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
*/

int minNumberInRotateArray(vector<int> rotateArray) {
    if (rotateArray.empty()) {
        return 0;
    }
    for (int i = 1; i < rotateArray.size(); i++) {
        if (rotateArray[i] < rotateArray[i - 1] ) {
            return rotateArray[i];
        }
    }
    return rotateArray[0];
}

// 二分查找

int minNumberInRotateArray(vector<int> rotateArray) {
    if (rotateArray.empty()) {
        return 0;
    }
    int left = 0, right = rotateArray.size() - 1, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (rotateArray[mid] > rotateArray[right]) {
            left = mid + 1;
        } else if (rotateArray[mid] < rotateArray[right]) {
            right = mid;
        } else {
            right--;
        }
    }
    return rotateArray[left];
}

/* 判断二叉树是否平衡
输入一棵二叉树，判断该二叉树是否是平衡二叉树。
*/

bool IsBalanced_Solution(TreeNode* pRoot) {
    int depth;
    return IsBalanced_Solution(pRoot, depth);
}
bool IsBalanced_Solution(TreeNode* pRoot, int &depth) {
    if (pRoot == nullptr) {
        depth = 0;
        return true;
    }
    int left_depth;
    bool is_left_balanced = IsBalanced_Solution(pRoot -> left, left_depth);
    int right_depth;
    bool is_right_balanced = IsBalanced_Solution(pRoot -> right, right_depth);
    if (is_left_balanced && is_right_balanced && abs(left_depth - right_depth) <= 1) {
        depth = max(left_depth, right_depth) + 1;
        return true;
    } else {
        depth = max(left_depth, right_depth) + 1;
        return false;
    }
}

/* 求二叉树深度
*/

int get_depth(TreeNode* pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    int left_depth = get_depth(pRoot -> left);
    int right_depth = get_depth(pRoot -> right);
    return left_depth > right_depth ? (left_depth + 1) : (right_depth + 1);
}

/* 用两个栈实现队列
栈1保存插入数据，栈2保存将要输出的数据。
当要输出数据时，判断栈二是否为空，如果为空，将栈1的所有元素复制到栈2中，然后弹出栈2首元素，否则直接弹出栈2首元素。
*/

/* 圆圈中最后的数
随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,
然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,
继续0...m-1报数....这样下去....直到剩下最后一个小朋友。
使用链表实现
*/

int LastRemaining_Solution(int n, int m)
{
    if (n <= 0 || m <= 0) {
        return -1;
    }
    list<int> childs;
    for (int i = 0; i < n; i++) {
        childs.push_back(i);
    }
    auto iter = childs.begin();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j < m; ++j) {
            ++iter;
            if (iter == childs.end()) {
                iter = childs.begin();
            }
        }
        auto next = ++iter;
        if (next == childs.end()) {
            next = childs.begin();
        }
        --iter;
        childs.erase(iter);
        iter = next;
    }
    return childs.front();
}

