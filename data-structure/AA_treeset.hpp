//
// Created by wwww on 2023/9/24.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_AA_TREESET_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_AA_TREESET_HPP

#include <algorithm>
#include <vector>
#include  <memory>

template<typename Key, typename Compare = std::less<Key>>
class AATree {

private:
    struct Node;

public:
    explicit AATree(Compare cmp = Compare{}) : _size{0}, _cmp{cmp}, _root{nullptr} {}

    ~AATree() { delete _root; }

    [[nodiscard]] inline std::size_t size() const { return _size; }

    [[nodiscard]] inline bool empty() const { return _size == 0; }

    inline Key min() {
        return _min(_root);
    }

    inline Key max() {
        return _max(_root);
    }

    void clear() {
        delete _root;
        _root = nullptr;
        _size = 0;
    }

    bool contains(const Key &key) {
        // BST search
        auto current = _root;
        while (current != nullptr) {
            if (_cmp(key, current->key))
                current = current->left;
            else if (_cmp(current->key, key))
                current = current->right;
            else return true;
        }
        return false;
    }

    inline bool insert(const Key &key) {
        return _insert(_root, key);
    }

    inline bool erase(const Key &key) {
        return _erase(_root, key);
    }

private:
    struct Node {
        Key key;
        int level;
        Node *left, *right;

        ~Node() {
            delete left;
            delete right;
        }

        Node *detach() {
            left = right = nullptr;
            return this;
        }
    };

    Compare _cmp;
    std::size_t _size;
    Node *_root;

    Key _min(Node *current) const {
        auto p = current;
        while (p->left != nullptr)
            p = p->left.get();
        return p->key;
    }

    Key _max(Node *current) const {
        auto p = current;
        while (p->right != nullptr)
            p = p->right.get();
        return p->key;
    }

    inline void _split(Node *&current) {
        if (current == nullptr)
            return;
        auto right_child = current->right;
        if (right_child != nullptr && right_child->right != nullptr &&
            right_child->right->level == current->level) {
            current->right = right_child->left;
            right_child->left = current;

            current = right_child;
            ++current->level;
        }
    }

    inline void _skew(Node *&current) {
        if (current == nullptr)
            return;
        auto left_child = current->left;
        if (left_child != nullptr && left_child->level == current->level) {
            current->left = left_child->right;
            left_child->right = current;

            current = left_child;
        }
    }

    bool _insert(Node *&current, const Key &key) {
        auto has_inserted = false;
        if (current == nullptr) {
            current = new Node{key, 1, nullptr, nullptr};
            ++_size;
            has_inserted = true;
        } else if (_cmp(key, current->key))
            has_inserted = _insert(current->left, key);
        else if (_cmp(current->key, key))
            has_inserted = _insert(current->right, key);
        _skew(current);
        _split(current);
        return has_inserted;
    }

    void _maintain_after_erase(Node *&current) {
        auto left_child = current->left, right_child = current->right;
        auto left_level = (left_child != nullptr) ? left_child->level : 0;
        auto right_level = (right_child != nullptr) ? right_child->level : 0;
        if ((left_level < current->level - 1) ||
            (right_level < current->level - 1)) {
            --current->level;
            if (right_child != nullptr && (right_level > current->level))
                right_child->level = current->level;
            _skew(current);
            _skew(current->right);
            if (current->right != nullptr)
                _skew(current->right->right);
            _split(current);
            _split(current->right);
        }
    }

    bool _erase(Node *&current, const Key &key) {
        if (nullptr == current)
            return false;
        if (_cmp(key, current->key)) {
            // case <
            auto has_erased = _erase(current->left, key);
            if (has_erased)
                _maintain_after_erase(current);
            return has_erased;
        } else if (_cmp(current->key, key)) {
            // case >
            auto has_erased = _erase(current->right, key);
            if (has_erased)
                _maintain_after_erase(current);
            return has_erased;
        }
        // case ==
        if ((current->left == nullptr) || (current->right == nullptr)) {
            // no more than 2 children
            auto old = current;
            current = (current->left == nullptr) ? current->right : current->left;
            old = old->detach();
            delete old;
            --_size;
        } else {
            // have 2 children
            auto next = current->right;
            while (next->left != nullptr)
                next = next->left;
            current->key = next->key;
            _erase(current->right, next->key);
            _maintain_after_erase(current);
        }
        return true;
    }
};

#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_AA_TREESET_HPP
