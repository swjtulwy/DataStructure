# Data Structure

## Task1 数组+链表

- 数组

  - 实现一个支持动态扩容的数组，支持动态增删改操作
  - 实现两个有序数组合并为一个有序数组
  - 学习哈希表思想，并完成leetcode上的两数之和(1)及Happy Number(202)！(要求全部用哈希思想实现！)（选做）（注意：在第四天会进行继续学习）
- 链表

  - 实现单链表、循环链表、双向链表，支持增删操作
- 实现单链表反转
  - 实现两个有序的链表合并为一个有序链表
- 实现求链表的中间结点

---

## Task1 Solution

#### 动态数组实现（扩容、增删改，合并等）：

https://github.com/swjtulwy/DataStructure/blob/master/Task1/dynamic_array.h

#### 单链表及其操作（反转、合并、中间结点等）:

https://github.com/swjtulwy/DataStructure/blob/master/Task1/single_linked_list.h

#### 总结

**模板类的实现要放在头文件中**

有些基础知识的coder都知道，C/C++都是先编译（compile）、再链接(link)（严格来说，编译过程还可以细分，但是与本次说说明问题无关），模板方法的特化过程其实是在编译(compile)阶段完成的，也就是说在编译过程中，模板被实例为几个实际的方法或者类就已经确定了。当你不使用这个模版函数或模版类,编译器并不实例化它 ,当你使用时，编译器需要实例化它，  

因为编译器是一次只能处理一个编译单元, 也就是一次处理一个cpp文件,所以实例化时需要看到该模板的完整定义 . 所以都放在头文件中 ，这不同于普通的函数, 在使用普通的函数时，编译时只需看到该函数的声明即可编译, 而在链接时由链接器来确定该函数的。模板实现不能放在cpp文件中，主要就是因为CPP在c++编译期间不能决定模板参数的类型，所以不能生成模板函数的实例，所以他会把模板类型带到链接期间，如果这个期间有函数调用了该实例，这个时候由于没有把模板实例到特定类型，就会导致链接错误。但是如果不调用该模板函数，那么是不会出现错误的。

类模板的模板友元函数定义有2种方式:
1. 将友元模板函数直接定义在类模板中。这种方式比较简单直接。
2. 将友元模板函数声明在类模板中，定义在类模板之外。这种方式的写法，如果不小心，通常会出现编译没问题，链接时无法解析的错误。

请注意当模板函数被声明为类模板的友元时，在函数名之后必须紧跟模板实参表，用来代表该友元声明指向函数模板的实例。否则友元函数会被解释为一个非模板函数，链接时无法解析。

友元模板函数的模板参数类型，并不一定要求是类模板的参数类型，也可以另外声明。

---

## Task 2： 栈 + 队列 + 递归

- 【栈】
  - 用数组实现一个顺序栈
  - 用链表实现一个链式栈
  - 编程模拟实现一个浏览器的前进、后退功能（选做）

- 【队列】
  - 用数组实现一个顺序队列
  - 用链表实现一个链式队列
  - 实现一个循环队列

- 【递归】
  - 编程实现斐波那契数列求值 f(n)=f(n-1)+f(n-2)
  -  编程实现求阶乘 n!
  -  编程实现一组数据集合的全排列

---

## Task2 Solution

#### 栈的实现：

数组实现：https://github.com/swjtulwy/DataStructure/blob/master/Task2/stack_array.h

链表实现：https://github.com/swjtulwy/DataStructure/blob/master/Task2/stack_linked_list.h

#### 队列的实现：

数组实现：https://github.com/swjtulwy/DataStructure/blob/master/Task2/queue_array.h

链表实现：https://github.com/swjtulwy/DataStructure/blob/master/Task2/queue_linked_list.h

循环队列实现：https://github.com/swjtulwy/DataStructure/blob/master/Task2/queue_circle.h

#### 递归算法：

https://github.com/swjtulwy/DataStructure/blob/master/Task2/recursion.cpp

#### 总结

这次把基本的栈和队列分别用数组和链表实现了一遍，有了上次的基础，写了稍微快一些，但是还要努力。在实现的过程中会去看STL中有哪些函数，再参考网上其他人的实现，最后自己总结一下。最大的收获在于循环队列的判断的处理，还有一个是顺序数组实现队列中的假溢出问题，最终还是解决了，理解到不同的数据结构有各自的优点和缺点。

---

## Task 3：排序 + 二分查找 

- 【排序】
  - 实现归并排序、快速排序、插入排序、冒泡排序、选择排序、堆排序（完成leetcode上的返回滑动窗口中的最大值(239)，这是上一期第三天的任务进行保留（涉及队列可以对第二天进行整理复习））
  - 编程实现 O(n) 时间复杂度内找到一组数据的第 K 大元素

- 【二分查找】
  - 实现一个有序数组的二分查找算法
  - 实现模糊二分查找算法（比如大于等于给定值的第一个元素）

---

## Task3 Solution

#### 排序（八大排序的实现）：

https://github.com/swjtulwy/DataStructure/blob/master/Task3/sorting.h

#### 二分查找的实现：

https://github.com/swjtulwy/DataStructure/blob/master/Task3/binary_search.h

#### 总结

难点在于处理各个数组中的边界问题，判断条件问题，特别是快速排序。快速排序的思想很重要，其效率也很高，是二十世纪十大算法之一。另外堆的数据结构也牵扯到完全二叉树的概念以及怎么计算孩子结点位置，树的高度，宽度等，这些知识需要牢牢掌握。

---

## Task 4：散列表(哈希表) + 字符串

- 【散列表（哈希表）】
  - 实现一个基于链表法解决冲突问题的散列表
  - 实现一个 LRU 缓存淘汰算法

- 【字符串】
  - 实现一个字符集，只包含 a～z 这 26 个英文字母的 Trie 树
  - 实现朴素的字符串匹配算法

---

## Task4 Solution

#### 散列表

散列表拉链法解决冲突：https://github.com/swjtulwy/DataStructure/blob/master/Task4/hash_table.h

LRU缓存淘汰算法：https://github.com/swjtulwy/DataStructure/blob/master/Task4/LRU_cache.cpp

#### 字符串

字符集实现：https://github.com/swjtulwy/DataStructure/blob/master/Task4/tries_treee.cpp

朴素字符串匹配：https://github.com/swjtulwy/DataStructure/blob/master/Task4/string_match.cpp

---

## Task 5：二叉树 + 堆 

- 【二叉树】
  - 实现一个二叉查找树，并且支持插入、删除、查找操作
  - 实现查找二叉查找树中某个节点的后继、前驱节点
  - 实现二叉树前、中、后序以及按层遍历

- 【堆】
  - 实现一个小顶堆、大顶堆、优先级队列
  - 实现堆排序
  - 利用优先级队列合并 K 个有序数组
  - 求一组动态数据集合的最大 Top K

---

## Task5 Solution

#### 二叉搜索树实现(BST)

https://github.com/swjtulwy/DataStructure/blob/master/Task5/binary_search_tree.h

#### 堆的实现

堆：https://github.com/swjtulwy/DataStructure/blob/master/Task5/heap_array.h

优先队列(包括合并 K 个有序数组和 Top K):

https://github.com/swjtulwy/DataStructure/blob/master/Task5/priority_queue.h

https://github.com/swjtulwy/DataStructure/blob/master/Task5/priority_queue.cpp

---

## Task 6：图 

- 【图】
  - 实现有向图、无向图、有权图、无权图的邻接矩阵和邻接表表示方法
  - 实现图的深度优先搜索、广度优先搜索
  - 实现 Dijkstra 算法
  - 实现拓扑排序

---

## Task6 Solution

图的邻接矩阵存储方式是用两个数组来表示图，一个一维数组存储图中的顶点信息，一个二维数组(邻接矩阵)存储图中的边或弧的信息。

图的邻接表存储方式是用一个存放指向顶点的指针的数组表示，其中数组每一项可以是一个链表，用来表示该项代表顶点所邻接哪些顶点。

由此可以看出，无向图的邻接矩阵是对称的，有向图的邻接矩阵则不一定。有向图的邻接表只链接顶点指向的顶点，不记录顶点被指向的边。有权图的邻接矩阵表示法相对于无权图的区别就是，有权图的邻接矩阵即二维数组中每一项存储的是边的权值，而无权图只存储有或无边的信息（用0/1表示）。有权图的邻接表表示相对于无权图表示，边表结构中需要多用一个量表示权值，而无权图只需记录顶点信息和指针域即可。

#### 图的邻接矩阵表示以及增删顶点、边操作和两种遍历：

https://github.com/swjtulwy/DataStructure/blob/master/Task6/graph_adjmat.cpp

---

## Task 7：递归 + 回溯 + 分治 + 动态规划 

- 【递归】
  - 通过LeetCode上【70. 爬楼梯】学习

- 【回溯】
  - 利用回溯算法求解八皇后问题
  - 利用回溯算法求解 0-1 背包问题

- 【分治】
  - 利用分治算法求一组数据的逆序对个数

- 【动态规划】
  - 0-1 背包问题
  - 最小路径和（详细可看 Minimum Path Sum）
  - 编程实现莱文斯坦最短编辑距离
  - 编程实现查找两个字符串的最长公共子序列
  - 编程实现一个数据序列的最长递增子序列

## Task7 Solution

https://github.com/swjtulwy/DataStructure/tree/master/Task7

