#include <algorithm>
#include <cstring>
#include <stack>
#include "dictionary.hpp"

Dictionary::Node::~Node() {}

Dictionary::Node *Dictionary::INode::deleteFirstBranch() {
    if (first == nullptr) {
        return nullptr;
    }
    Node *subtree = first->subtree;
    Branch *next = first->next;
    delete first;
    first = next;
    return subtree;
};

Dictionary::Node * Dictionary::INode::findSubtree(char key) {
    Branch *node = first;
    while (node) {
        if (node->key == key) {
            return node->subtree;
        }
        node = node->next;
    }
    return nullptr;
}

void Dictionary::INode::addSubtree(char key, Dictionary::Node *node) {
    Branch *next = new Branch(key, node);
    if (!first) {
        first = next;
    } else {
        Branch *curr = first, *prev = nullptr;
        while (curr && curr->key < key) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == nullptr) {
            first = next;
        } else {
            prev->next = next;
        }
        next->next = curr;
    }
    numSubtrees++;
}

void Dictionary::INode::traverseSubtrees(std::queue<std::pair<Node *, std::string>> &prefixes, std::string &word) {
    Branch *node = first;
    while (node) {
        prefixes.push({node->subtree, word + node->key});
        node = node->next;
    }
}

Dictionary::~Dictionary() {
    std::stack<Node *> nodes;
    if (root == nullptr) {
        return;
    }
    nodes.push(root);
    while (!nodes.empty()) {
        Node *node = nodes.top();
        Node *next;
        nodes.pop();
        while ((next = node->deleteFirstBranch()) != nullptr) {
            nodes.push(next);
        }
        delete node;
    }
}

Dictionary::Node *Dictionary::findNode(std::string &key) {
    Node *curr = root;
    for (char c : key) {
        if (curr == nullptr) {
            return nullptr;
        }
        curr = curr->findSubtree(c);
    }
    if (curr != nullptr) {
        curr = curr->findSubtree(EOK);
    }
    return curr;
}

void Dictionary::insert(std::string &key) {
    if (!root) {
        root = new INode;
    }
    Node *curr = root;
    for (char c : key) {
        Node *next = curr->findSubtree(c);
        if (!next) {
            next = new INode;
            curr->addSubtree(c, next);
        }
        curr = next;
    }
    Node *subtree = curr->findSubtree(EOK);
    if (subtree == nullptr) {
        curr->addSubtree(EOK, new Leaf);
        numKeys++;
    } else {
        subtree->increaseFrequency();
    }
}

int Dictionary::find(std::string &key) {
    Node *list = findNode(key);
    if (list) {
        return list->frequency();
    }
    return 0;
}

std::vector<std::pair<std::string, int>> Dictionary::predict(std::string &word) {
    std::queue<std::tuple<Node *, const char *, std::string, int>> nodes;
    std::queue<std::pair<Node *, std::string>> prefixes;
    std::vector<std::pair<std::string, int>> words;
    nodes.push({root, word.c_str(), "", 3});
    while (!nodes.empty()) {
        auto tup = nodes.front();
        Node *node = std::get<0>(tup);
        const char *key = std::get<1>(tup);
        std::string currWord = std::get<2>(tup);
        int fixes = std::get<3>(tup);
        char keyPart = key[0];
        if (keyPart == '\0') {
            break;
        }
        nodes.pop();
        Node *subtree = node->findSubtree(keyPart);
        if (subtree != nullptr) {
            nodes.push({subtree, key + 1, currWord + keyPart, fixes});
        }
        if (fixes > 0) {
            for (char c : keyboard.getNeighbors(keyPart)) {
                Node *subtree = node->findSubtree(c);
                if (subtree != nullptr) {
                    nodes.push({subtree, key + 1, currWord + c, fixes - 1});
                }
            }
        }
    }
    if (std::get<2>(nodes.front()) == word) {
        auto tup = nodes.front();
        Node *node = std::get<0>(tup), *prev = node->findSubtree(EOK);
        std::string currWord = std::get<2>(tup);
        if (prev == nullptr) {
            while (node) {
                if (node->subtreeCount() <= 1) {
                    prev = node;
                    auto pair = node->firstSubtree();
                    node = pair.first;
                    currWord += pair.second;
                } else {
                    node = prev = nullptr;
                }
            }
        }
        if (prev != nullptr) {
            words.push_back({currWord, prev->frequency()});
            return words;
        }
    }
    while (!nodes.empty()) {
        auto tup = nodes.front();
        prefixes.push({std::get<0>(tup), std::get<2>(tup)});
        nodes.pop();
    }
    while (!prefixes.empty()) {
        auto pair = prefixes.front();
        Node *node = pair.first;
        std::string prefix = pair.second;
        prefixes.pop();
        int frequency = node->frequency();
        if (frequency == 0) {
            node->traverseSubtrees(prefixes, prefix);
        } else if (words.size() < 3) {
            words.push_back({prefix, frequency});
            // O(1)
            std::sort(words.begin(), words.end(), [](auto &pair1, auto &pair2) {
                return pair1.second > pair2.second;
            });
        } else {
            for (int i = 0; i < 3; ++i) {
                auto &pair = words[i];
                if (frequency > pair.second) {
                    for (int j = 2; j > i; --j) {
                        words[j] = words[j-1];
                    }
                    pair.first = prefix;
                    pair.second = frequency;
                    break;
                }
            }
        }
    }
    return words;
}
