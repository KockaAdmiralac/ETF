#ifndef _dictionary_hpp
#define _dictionary_hpp
#include <string>
#include <queue>
#include <utility>
#include <vector>
#include "keyboard.hpp"

class Dictionary {
    struct Node {
        virtual Node *findSubtree(char) {
            return nullptr;
        }
        virtual void addSubtree(char, Node *) {};
        virtual int subtreeCount() const {
            return 0;
        }
        virtual void increaseFrequency() {}
        virtual int frequency() {
            return 0;
        }
        virtual Node *deleteFirstBranch() {
            return nullptr;
        }
        virtual void traverseSubtrees(std::queue<std::pair<Node *, std::string>> &, std::string &) {}
        virtual std::pair<Node *, char> firstSubtree() {
            return {nullptr, '\0'};
        }
        virtual ~Node() = 0;
    };
    struct INode : Node {
        struct Branch {
            char key;
            Node *subtree;
            Branch *next;
            Branch(char key, Node *subtree) :
                key(key), subtree(subtree), next(nullptr) {}
        };
        int numSubtrees = 0;
        Branch *first = nullptr;
        Node *findSubtree(char key) override;
        void addSubtree(char key, Node *node) override;
        int subtreeCount() const override {
            return numSubtrees;
        }
        void traverseSubtrees(std::queue<std::pair<Node *, std::string>> &prefixes, std::string &word) override;
        std::pair<Node *, char> firstSubtree() override {
            return {first->subtree, first->key};
        }
        Node *deleteFirstBranch() override;
    };
    struct Leaf : Node {
        int freq = 1;
        void increaseFrequency() override {
            ++freq;
        }
        int frequency() override {
            return freq;
        }
    };
    public:
        void insert(std::string &key);
        int find(std::string &key);
        std::vector<std::pair<std::string, int>> predict(std::string &word);
        int countKeys() {
            return numKeys;
        }
        ~Dictionary();
    private:
        static const char EOK = '\0';
        int numKeys = 0;
        Keyboard keyboard;
        INode *root = nullptr;
        Node *findNode(std::string &key);
};

#endif
