###  Algorithms and Data structures in C++

[![Static Badge](https://img.shields.io/badge/license-MIT-blue?logo=git&logoColor=%20)]() [![Static Badge](https://img.shields.io/badge/C%2B%2B-20-green?logo=cplusplus&logoColor=blue)]() [![Static Badge](https://img.shields.io/badge/cmake-3.22%2B-green?logo=cmake&logoColor=deepskyblue)]() [![Static Badge](https://img.shields.io/badge/compiler-x86%20MSVC%2019.29%2B-green?logo=compilerexplorer)]() 

---
一些算法/数据结构在现代`C++`的模板实现

下方链接为相关文章

**TODO:**

**数据结构**

- [x] [AA Tree(红黑树变体)](https://zhuanlan.zhihu.com/p/662705188), [AA_treeset.hpp](data-structure/AA_treeset.hpp)
- [x] 树状数组(Binary Index Tree), [binary_index_tree.hpp](data-structure/binary_index_tree.hpp)
- [x] 左偏红黑树(Left Leaning RBT), [left_leaning_red_black_treeset.hpp](data-structure/left_leaning_red_black_treeset.hpp)
- [ ] 渐进式散列表(Rehash)
- [x] [优先队列(Binary Heap)](https://zhuanlan.zhihu.com/p/659218897), [priority_queue.hpp](data-structure/priority_queue.hpp)
- [ ] 定序哈希(LinkedHashset)
- [x] 跳表(Skiplist), [skiplist.hpp](data-structure/skiplist.hpp)
- [ ] B+树
- [ ] 字典树(Trie)
- [ ] LRU
- [x] 线段树(SegmentTree), [segment_tree.hpp](data-structure/segment_tree.hpp), [dynamic_segment_tree.hpp](data-structure/dynamic_segment_tree.hpp)
- [ ] 稀疏表(SparseTable)
- [ ] 伸展树(Splay)
- [x] 并查集(UnionFind), [union_find.hpp](data-structure/union_find.hpp)
- [ ] LFU
- [ ] 跳舞链(DancingLink)

**搜索与排序**

- [x] [快速排序](https://zhuanlan.zhihu.com/p/659147057), [quick_sort.hpp](search/quick_sort.hpp)
- [ ] A*

**几何**

- [ ] 凸包  

**图论**
- [ ] 最小生成树
- [ ] 强连通分量(Tarjan)
- [ ] 单源最短路

**数论**

- [ ] 乘法逆元
- [ ] 素数筛

**泛型**

- [x] [具名元组(namedtuple)](https://zhuanlan.zhihu.com/p/659506997), [named_tuple.hpp](template/named_tuple.hpp)
- [ ] 变长模板参数(TypeList)
- [ ] 匿名结构体 
- [x] [柯里化(currying)](https://zhuanlan.zhihu.com/p/662698843), [curry.hpp](functional/curry.hpp)
- [x] [函数组合(compose)](https://zhuanlan.zhihu.com/p/662698843)，[compose.hpp](functional/compose.hpp)
- [x] [递归lambda](https://zhuanlan.zhihu.com/p/659164782), [recursive_lambda.hpp](util/recursive_lambda.hpp)
- [x] [类装饰器](https://zhuanlan.zhihu.com/p/662750214), [trait.cpp](https://gist.github.com/zixfy/55ba69a3aa9c4c7e5d317a0161e62f21)
- [x] [函数装饰器](https://zhuanlan.zhihu.com/p/668402933)， [decorator.cpp](https://gist.github.com/zixfy/3fae73ccd9845c3334402b96d4399441)
- [x] [打印STL容器](https://zhuanlan.zhihu.com/p/662702455)，[container_printer.hpp](util/container_printer.hpp)

**杂项**

+ [x] [信号量(Semaphore)](util/semaphore.hpp)
+ [x] [属性(properties)](https://zhuanlan.zhihu.com/p/659323767),[getter_setter.hpp](design/getter_setter.hpp) 

