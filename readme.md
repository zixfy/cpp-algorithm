###  Algorithms and Data structures in C++

[![Static Badge](https://img.shields.io/badge/license-MIT-blue?logo=git&logoColor=%20)]() [![Static Badge](https://img.shields.io/badge/C%2B%2B-20-green?logo=cplusplus&logoColor=blue)]() [![Static Badge](https://img.shields.io/badge/cmake-3.22%2B-green?logo=cmake&logoColor=deepskyblue)]() [![Static Badge](https://img.shields.io/badge/compiler-x86%20MSVC%2019.29%2B-green?logo=compilerexplorer)]() 

---
一些算法/数据结构在现代`C++`的模板实现

**TODO:**

**数据结构**

- [x] [AA树](data-structure/AA_treeset.hpp)
- [x] [树状数组(Binary Index Tree)](data-structure/binary_index_tree.hpp)
- [x] [左偏红黑树(Left Leaning RBT)](data-structure/left_leaning_red_black_treeset.hpp)
- [ ] 渐进式散列表(rehash in Redis)
- [x] [优先队列(二叉堆)](https://zhuanlan.zhihu.com/p/659218897), [priority_queue.hpp](data-structure/priority_queue.hpp)
- [ ] LinkedHashset
- [x] [跳表(Skiplist)](data-structure/skiplist.hpp)
- [ ] B+树
- [ ] 字典树(Trie)
- [ ] LRU
- [ ] 线段树(SegmentTree)
- [ ] 稀疏表(SparseTable)
- [ ] 伸展树(Splay)
- [x] [并查集(UnionFind)](data-structure/union_find.hpp)
- [ ] LFU
- [ ] 跳舞链(DancingLink)

**搜索**

- [x] [快速排序](https://zhuanlan.zhihu.com/p/659147057), [quick_sort.hpp](search/quick_sort.hpp)
- [ ] A*

**几何**

- [ ] 凸包  
**图论**
- [ ] 最小生成树
- [ ] 强连通分量(Tarjan)

**数论**

- [ ] 乘法逆元
- [ ] 欧拉素数筛

**泛型**

- [x] [具名元组(namedtuple)](https://zhuanlan.zhihu.com/p/659506997), [named_tuple.hpp](template/named_tuple.hpp)
- [ ] 变长模板参数(TypeList)
- [ ] 匿名结构体
- [ ] 扩展方法
- [x] 柯里化(curry), [curry.hpp](functional/curry.hpp)
- [x] 函数组合，[compose.hpp](functional/compose.hpp)

**杂项**

+ [x] [信号量(Semaphore)](util/semaphore.hpp)
+ [x] [属性(properties)](https://zhuanlan.zhihu.com/p/659323767),[getter_setter.hpp](design/getter_setter.hpp) 

