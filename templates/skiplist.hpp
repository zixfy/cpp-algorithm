//
// Created by wwww on 2023/9/9.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_SKIPLIST_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_SKIPLIST_HPP

#include <memory>
#include <cstdint>
#include <random>

template<typename K, typename V>
class SkipList {
private:
    constexpr inline static uint8_t MAX_LEVEL = 32;
    constexpr inline static int S = 0xFFFF;
    constexpr inline static int PS = S >> 2;
    struct SkipListNode;
    std::unique_ptr<SkipListNode> m_head;
    std::size_t m_length{0};
    std::uint8_t m_level{0};
    std::mt19937 m_rng{std::random_device{}()};


public:
    uint8_t random_level() {
        uint8_t lv = 0;
        // MAXL = 32, S = 0xFFFF, PS = S * P, P = 1 / 4
        while ((lv < MAX_LEVEL) && ((m_rng() & S) < PS)) ++lv;
        return lv;
    }

    SkipList() : m_head{std::make_unique<SkipListNode>(K{}, V{}, MAX_LEVEL, nullptr)} {}

    V *find(const K &key) {
        SkipListNode *p = m_head.get();
        for (int i = m_level; i >= 0; --i) {
            while (true) {
                if (auto next = p->link[i]; next != nullptr && next->key <= key) {
                    p = next;
                    if (p->key == key)
                        return &(p->value);
                } else break;
            }
        }
        return nullptr;
    }

    template<typename UK = K, typename UV = V>
    void insert(UK &&key, UV &&value) {
        // 用于记录需要修改的节点
        std::vector<SkipListNode *> update(m_level + 1);
        SkipListNode *p = m_head.get();

        for (int i = m_level; i >= 0; --i) {
            while (true) {
                if (auto next = p->link[i]; next != nullptr && next->key < key)
                    p = next;
                else break;
            }
            update[i] = p;
        }
        p = p->link[0];
        // 若已存在则修改
//        if (p != nullptr && p->key == key) {
//            p->value = std::forward<UV>(value);
//            return;
//        }

        // 获取新节点的最大层数
        auto lv = random_level();
        if (lv > m_level) {
            lv = ++m_level;
            update.emplace_back(m_head.get());
        }

        // 新建节点
        auto new_node = new SkipListNode(std::forward<UK>(key), std::forward<UV>(value), lv);
        // 在第 0~lv 层插入新节点
        for (int i = lv; i >= 0; --i) {
            p = update[i];
            new_node->link[i] = p->link[i];
            p->link[i] = new_node;
        }

        ++m_length;
    }

    template<typename UK = K>
    bool erase(UK &&key) {
        // 用于记录需要修改的节点
        std::vector<SkipListNode *> update(m_level + 1);
        SkipListNode *p = m_head.get();
        for (int i = m_level; i >= 0; --i) {
            while (true) {
                if (auto next = p->link[i]; next != nullptr && next->key < key)
                    p = next;
                else break;
            }
            update[i] = p;
        }
        p = p->link[0];
        // 节点不存在
        if (p == nullptr || p->key != key) return false;

        // 从最底层开始删除
        for (int i = 0; i <= m_level; ++i) {
            // 如果这层没有 p 删除就完成了
            if (update[i]->link[i] != p)
                break;
            // 断开 p 的连接
            update[i]->link[i] = p->link[i];
        }

        delete p;

        // 删除节点可能导致最大层数减少
        while (m_level > 0 && m_head->link[m_level] == nullptr) --m_level;

        // 跳表长度
        --m_length;
        return true;
    }

private:

    struct SkipListNode {
        uint8_t level;
        K key;
        V value;
        std::unique_ptr<SkipListNode *[]> link;

        SkipListNode() = delete;

        template<typename UK = K, typename UV = V>
        SkipListNode(UK &&k, UV &&v, uint8_t l, SkipListNode *nxt = nullptr) : key{std::forward<UK>(k)},
                                                                               value{std::forward<UV>(v)}, level{l},
                                                                               link{std::unique_ptr<SkipListNode *[]>(
                                                                                       new SkipListNode *[l + 1])} {
            std::fill(link.get(), link.get() + level + 1, nxt);
        }

    };

};

#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_SKIPLIST_HPP
