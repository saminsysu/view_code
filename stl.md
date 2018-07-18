# c++

==通过 empty 都可以判断是否为空；通过 size 都可以获得元素个数==

## deque

- push_back	在末尾增加一个元素
- push_front	在开头增加一个元素
- pop_back	删除最后一个元素
- pop_front	删除第一个元素
- operator[]	访问元素
- at	访问元素
- front	访问第一个元素
- back	访问最后一个元素

## list

- front
- back
- push_front
- pop_front
- push_back
- pop_back

## map

- insert (借助 make_pair 或 pair)或以数组的方式插入数据
- 通过find获取数据。通过[]获取元素，当元素不存在时会自定创建

## queue

- push
- pop
- front
- back

## set
==set不支持随机访问==
- insert
- find

## stack

- push
- pop
- top

## vector

- void push_back(const T& x):向量尾部增加一个元素X
- iterator insert(iterator it, const T& x):向量中迭代器指向元素前增加一个元素x
- iterator insert(iterator it, int n, const T& x):向量中迭代器指向元素前增加n个相同的元素x
- iterator insert(iterator it, const_iterator first, const_iterator last):向量中迭代器指向元素前插入另一个相同类型向量的[first,last)间的数据
- void pop_back():删除向量中最后一个元素
- iterator erase(iterator it):删除向量中迭代器指向元素
iterator erase(iterator first, iterator last):删除向量中[first,last)中元素
