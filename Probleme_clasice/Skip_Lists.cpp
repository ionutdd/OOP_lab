#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_LEVEL = 16;
const float P = 0.5;

struct SkipNode {
    int key;
    SkipNode** forward;
    SkipNode(int key, int level) {
        this->key = key;
        forward = new SkipNode*[level+1];
        memset(forward, 0, sizeof(SkipNode*)*(level+1));
    }
    ~SkipNode() {
        delete[] forward;
    }
};

class SkipList {
public:
    SkipList() {
        max_level_ = 1;
        level_ = 0;
        head_ = new SkipNode(0, MAX_LEVEL);
    }
    ~SkipList() {
        delete head_;
    }
    bool contains(int key) {
        SkipNode* node = find_node(key);
        return node != NULL && node->key == key;
    }
    void insert(int key) {
        SkipNode* update[MAX_LEVEL+1];
        SkipNode* node = head_;
        for (int i = level_; i >= 0; --i) {
            while (node->forward[i] != NULL && node->forward[i]->key < key) {
                node = node->forward[i];
            }
            update[i] = node;
        }
        node = node->forward[0];
        if (node == NULL || node->key != key) {
            int new_level = random_level();
            if (new_level > level_) {
                for (int i = level_+1; i <= new_level; ++i) {
                    update[i] = head_;
                }
                level_ = new_level;
            }
            node = new SkipNode(key, new_level);
            for (int i = 0; i <= new_level; ++i) {
                node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = node;
            }
        }
    }
    void remove(int key) {
        SkipNode* update[MAX_LEVEL+1];
        SkipNode* node = head_;
        for (int i = level_; i >= 0; --i) {
            while (node->forward[i] != NULL && node->forward[i]->key < key) {
                node = node->forward[i];
            }
            update[i] = node;
        }
        node = node->forward[0];
        if (node != NULL && node->key == key) {
            for (int i = 0; i <= level_; ++i) {
                if (update[i]->forward[i] != node) {
                    break;
                }
                update[i]->forward[i] = node->forward[i];
            }
            delete node;
            while (level_ > 0 && head_->forward[level_] == NULL) {
                --level_;
            }
        }
    }
    int lower_bound(int key) {
        SkipNode* node = head_;
        for (int i = level_; i >= 0; --i) {
            while (node->forward[i] != NULL && node->forward[i]->key <= key) {
                node = node->forward[i];
            }
        }
        return node->key;
    }
    int upper_bound(int key) {
        SkipNode* node = head_;
        for (int i = level_; i >= 0; --i) {
            while (node->forward[i] != NULL && node->forward[i]->key < key) {
                node = node->forward[i];
            }
       
