//
// Created by wwww on 2023/9/23.
//

#ifndef CPP_ADVANCED_CONTAINER_TEMPLATE_LEFT_LEANING_RED_BLACK_TREESET_HPP
#define CPP_ADVANCED_CONTAINER_TEMPLATE_LEFT_LEANING_RED_BLACK_TREESET_HPP

#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <unordered_map>


template<typename Key, typename Compare = std::less<Key>>
class LeftLeaningRedBlackTreeSet {
private:
    struct Node;
public:

    ~LeftLeaningRedBlackTreeSet() {
        delete _root;
    }

    explicit LeftLeaningRedBlackTreeSet(Compare cmp = Compare{}) : _cmp{cmp}, _root{nullptr}, _size{0} {}

    [[nodiscard]] inline std::size_t size() const { return _size; }

    [[nodiscard]] inline bool empty() const { return _size == 0; }

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

    void insert(const Key &key) {
        _root = _insert(_root, key);
        _root->color = Color::BLACK;
    }

    bool erase(const Key &key) {
        if (!contains(key))
            return false;
        _root = _delete(_root, key);
        if (_root != nullptr)
            _root->color = Color::BLACK;
        return true;
    }

    inline Key min() {
        return _min(_root);
    }

    inline Key max() {
        return _max(_root);
    }


private:
    enum class Color {
        BLACK, RED
    };


    struct Node {
        Key key;
        Color color;
        Node *left, *right;

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node *_root;
    Compare _cmp;
    std::size_t _size;

    inline Color _flipped(Color c) const {
        return c == Color::RED ? Color::BLACK : Color::RED;
    }

    void _flip_color(Node *current) const {
        current->color = _flipped(current->color);
        current->left->color = _flipped(current->left->color);
        current->right->color = _flipped(current->right->color);
    }

    inline bool _is_red(Node *current) const {
        return current != nullptr && (current->color == Color::RED);
    }

    Key _min(Node *current) const {
        auto p = current;
        while (p->left != nullptr)
            p = p->left;
        return p->key;
    }

    Key _max(Node *current) const {
        auto p = current;
        while (p->right != nullptr)
            p = p->right;
        return p->key;
    }

    Node *_rotate_left(Node *current) const {
        auto right_child = current->right;
        current->right = right_child->left;
        right_child->left = current;
        std::swap(current->color, right_child->color);
        return right_child;
    }

    Node *_rotate_right(Node *current) const {
        auto left_child = current->left;
        current->left = left_child->right;
        left_child->right = current;
        std::swap(current->color, left_child->color);
        return left_child;
    }


    Node *_maintain(Node *current) {
        if (_is_red(current->right) && !_is_red(current->left))
            current = _rotate_left(current);
        if (_is_red(current->left) && _is_red(current->left->left))
            current = _rotate_right(current);
        if (_is_red(current->left) && _is_red(current->right))
            _flip_color(current);
        return current;
    }

    Node *_insert(Node *current, const Key &key) {
        if (current == nullptr) {
            ++_size;
            return new Node{key, Color::RED, nullptr, nullptr};
        }
        if (_cmp(key, current->key))
            current->left = _insert(current->left, key);
        else if (_cmp(current->key, key))  // if (key < current->key)
            current->right = _insert(current->right, key);
        return _maintain(current);
    }

    Node *_move_red_left(Node *current) {
        // when left and right is both real black
        _flip_color(current);
        if (_is_red(current->right->left)) {
            // assert that current->right != nullptr when calling this function
            current->right = _rotate_right(current->right);
            current = _rotate_left(current);
            _flip_color(current);
        }
        return current;
    }

    Node *_move_red_right(Node *current) {
        _flip_color(current);
        if (_is_red(current->left->left)) {
            current = _rotate_right(current);
            _flip_color(current);
        }
        return current;
    }

    Node *_delete_min(Node *current) {
        // current not null
        if (current->left == nullptr) {
            delete current;
            --_size;
            return nullptr;
        }
        if (!_is_red(current->left) && !_is_red(current->left->left)) {
            // if so, current has a real black child, then current must have a right child too (all path in a BRT has same number of black nodes)
            // so that calling _move_red_left is safe
            current = _move_red_left(current);
        }
        current->left = _delete_min(current->left);
        return _maintain(current);
    }

    Node *_delete(Node *current, const Key &key) {
        if (_cmp(key, current->key)) {
            if (!_is_red(current->left) && !_is_red(current->left->left)) {
                current = _move_red_left(current);
            }
            current->left = _delete(current->left, key);
        } else {
            if (_is_red(current->left))
                current = _rotate_right(current);
            if (!_cmp(current->key, key) && (current->right == nullptr)) {
                delete current;
                --_size;
                return nullptr;
            }
            if (!_is_red(current->right) && !_is_red(current->right->left))
                current = _move_red_right(current);
            if (!_cmp(current->key, key)) {
                // key equals current's key
                current->key = _min(current->right);
                current->right = _delete_min(current->right);
            } else {
                current->right = _delete(current->right, key);
            }
        }
        return _maintain(current);
    }
};

#endif //CPP_ADVANCED_CONTAINER_TEMPLATE_LEFT_LEANING_RED_BLACK_TREESET_HPP
