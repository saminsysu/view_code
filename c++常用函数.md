# 常用库函数

## Reference

    1. C++库常用函数一览 https://blog.csdn.net/candyliuxj/article/details/6313191
    
## 标准库字符串类std::string的用法

- begin       得到指向字符串开头的Iterator
- end         得到指向字符串结尾的Iterator
- rbegin      得到指向反向字符串开头的Iterator
- rend        得到指向反向字符串结尾的Iterator
- size        得到字符串的大小
- length      和size函数功能相同
- max_size    字符串可能的最大大小
- capacity    在不重新分配内存的情况下，字符串可能的大小
- empty       判断是否为空
- operator[]  取第几个元素，相当于数组
- c_str       取得C风格的const char* 字符串
- data        取得字符串内容地址
- operator=   赋值操作符
- reserve     预留空间
- swap        交换函数
- insert      插入字符
- append      追加字符
- push_back   追加字符
- erase       删除字符串
- clear       清空字符容器中所有内容
- resize      重新分配空间
- assign      和赋值操作符一样
- replace     替代
- copy        字符串到空间
- find        查找,返回基于0的索引号
- rfind       反向查找
- find_first_of        查找包含子串中的任何字符，返回第一个位置
- find_first_not_of    查找不包含子串中的任何字符，返回第一个位置
- find_last_of         查找包含子串中的任何字符，返回最后一个位置
- find_last_not_of     查找不包含子串中的任何字符，返回最后一个位置
- substr(n1,len)       得到字符串从n1开始的长度为len的子串
- compare              比较字符串(支持所有的关系运算符)
- operator+            字符串链接
- operator+=           += 操作符
- operator==           判断是否相等
- operator!=           判断是否不等于
- operator<            判断是否小于
- operator>>           从输入流中读入字符串
- operator<<           字符串写入输出流
- getline              从输入流中读入一行

## cctype库

- isalpha; //是否字母
- iscntrl; //是否控制符
- isdigit; //是否是数字
- isgraph; //是否字母、数字或标点
- islower; //是否小写
- isprint; //是否可打印字符
- ispunct; //是否标点
- isspace; //是否空格
- isupper; //是否大写
- isxdigit; //是否十六进制数字
- ==tolower; //转为小写==
- ==toupper; //转为大写==


## algorithm 库

- for_each 对序列中的每个元素执行某项操作
- find(a,a+size,n) 返回b,当b=a+size即没找到，a为指针
- swap 交换两个元素
- iter_swap 交换由迭代器所指的两个元素
- reverse 反转元素的次序
- reverse_copy 复制序列时反转元素的次序，不影响原本元素
- sort(a,a+20,cmp) 排序
- merge 归并两个有序序列
- make_heap 从序列构造堆，默认构建最大堆
    
    参考：heap 库函数使用 https://elloop.github.io/c++/2016-11-29/learning-using-stl-72-make-heap

- push_heap 向堆中加入元素，需确保区间（除最后一个元素）已经是一个堆
- pop_heap 把堆顶元素交换到区间尾，然后把除了尾部的元素的剩余区间重新调整成堆，需确保区间已经是一个堆 
- sort_heap 堆排序，需确保区间已经是一个堆
- min 两个值中较小的
- max 两个值中较大的
- min_element(a,a+n) 序列中的最小元素
- max_element(a,a+n) 序列中的最大元素

## cmath库

- abs; //绝对值
- exp; //指数值
- log; //对数
- pow; //计算幂
- sqrt; //开方


## cstdlib库

- double atof(const char *str) 把字符串str转换成double类型
- int atoi(const char *str) 把字符串str转换成int类型
- long atol(const char *str) 把字符串str转换成long类型