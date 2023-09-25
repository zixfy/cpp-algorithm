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

    std::vector<Node *> inorderTraversal(Node *root) {
        std::vector<Node *> res;
        std::stack<Node *> stk;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            res.push_back(root);
            root = root->right;
        }
        return res;
    }

    void printTree(Node *root) {
        if (!root) root = _root;
        if (!root)return;
        auto tmp = root;
        std::vector<Node *> intv = inorderTraversal(tmp);//中序遍历节点数组
        std::string template_str;//模板string，表示每行打印string的长度
        int location = 0;
        std::unordered_map<Node *, int> first_locations;//存储节点对应在本行string中的首位置
        for (auto &i: intv) {
            location = template_str.size();
            template_str += std::to_string(i->key) + " (lv" + std::to_string(i->level) + ")" + " ";
            first_locations[i] = location;
        }
        for (auto &i: template_str)i = ' ';//把模板全部置为空格方便后续使用
        //层序遍历
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            int currentLevelSize = q.size();
            int cur_loc = 0;
            std::string tmp_str1 = template_str, tmp_str2 = template_str;//1为节点所在行，2为其下一行
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                cur_loc = first_locations[node];
                std::string num_str = std::to_string(node->key) + " (lv" + std::to_string(node->level) + ")";
                //左边，如果存在左孩子，那么在第二行对应位置打印'/'，在第一行补上'_'
                if (node->left) {
                    q.push(node->left);
                    int first_loc = first_locations[node->left] + 1;
                    tmp_str2[first_loc++] = '/';
                    while (first_loc < cur_loc)tmp_str1[first_loc++] = '_';

                }
                //中间,对应位置打印节点值（有可能为多位数）
                for (int j = 0; j < num_str.length(); ++j, ++cur_loc) {
                    tmp_str1[cur_loc] = num_str[j];
                }
                //右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
                if (node->right) {
                    q.push(node->right);
                    int last_loc = first_locations[node->right] - 1;
                    tmp_str2[last_loc] = '\\';
                    while (cur_loc < last_loc) {
                        tmp_str1[cur_loc++] = '_';
                    }
                }
            }
            //打印两行
            std::cout << tmp_str1 << std::endl;
            std::cout << tmp_str2 << std::endl;
        }
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
