/**
 * Pošto ni sam domaći nije najbolja programerska praksa, neće biti
 * ostavljani komentari kao na prošlim domaćim.
 */
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>
// #define DEBUG
// #define WINDOWS

using namespace std::rel_ops;

// Konstante za crtanje stabla u zavisnosti od mesta pokretanja.
#ifdef WINDOWS
    // http://www.asciitable.com/index/extend.gif
    const char *ARROW_RIGHT_DOWN = "\332"; // 218
    const char *ARROW_HORIZONTAL = "\304"; // 196
    const char *ARROW_HORIZONTAL_UP = "\301"; // 193
    const char *ARROW_LEFT_UP = "\331"; // 217
    const char *ARROW_RIGHT_UP = "\300"; // 192
    const char *ARROW_LEFT_DOWN = "\277"; // 191
    const char *ARROW_HORIZONTAL_DOWN = "\302"; // 194
#else
    const char *ARROW_RIGHT_DOWN = "\u250C";
    const char *ARROW_HORIZONTAL = "\u2500";
    const char *ARROW_HORIZONTAL_UP = "\u2534";
    const char *ARROW_LEFT_UP = "\u2518";
    const char *ARROW_RIGHT_UP = "\u2514";
    const char *ARROW_LEFT_DOWN = "\u2510";
    const char *ARROW_HORIZONTAL_DOWN = "\u252C";
#endif

void clear() {
    #ifndef DEBUG
    std::cout << "\033[2J\033[f";
    #endif
}

void spacetime(std::ostream &file, const char *space, int time) {
    for (int i = 0; i < time; ++i) {
        file << space;
    }
}

struct Job {
    int priority;
    std::string name;
    Job() = default;
    Job(int priority, std::string name) : priority(priority), name(name) {}
};

bool operator<(const Job &job1, const Job &job2) {
    return job1.priority < job2.priority || (
        job1.priority == job2.priority &&
        job1.name < job2.name
    );
}

bool operator==(const Job &job1, const Job &job2) {
    return job1.priority == job2.priority &&
           job1.name == job2.name;
}

std::ostream &operator<<(std::ostream &file, const Job &job) {
    file << std::setw(2) << job.priority << " "
         << std::setw(2) << job.name.substr(0, 2);
    return file;
}

struct Node {
    union {
        struct {
            Job *left, *center, *right;
        } named;
        Job *array[3];
    } keys;
    union {
        struct {
            Node *leftmost, *left, *right, *rightmost;
        } named;
        Node *array[4];
    } children;
    Node() : keys(), children() {}
    bool isFull() const;
    bool isEmpty() const;
    bool isMinimum() const;
    bool isLeaf() const;
    int insert(Job *job, int index);
    Job *remove(int index);
    int sibling(int index) const;
};

bool Node::isFull() const {
    return keys.named.left != nullptr && keys.named.right != nullptr;
}

bool Node::isEmpty() const {
    return keys.named.left == nullptr &&
           keys.named.center == nullptr &&
           keys.named.right == nullptr;
}

bool Node::isMinimum() const {
    return keys.named.left == nullptr &&
           keys.named.right == nullptr;
}

bool Node::isLeaf() const {
    return children.named.leftmost == nullptr &&
           children.named.left == nullptr &&
           children.named.right == nullptr &&
           children.named.rightmost == nullptr;
}

int Node::insert(Job *job, int index) {
    if (isFull()) {
        throw "Čvor je pun.";
    }
    switch (index) {
        case 0:
            // Unosi se levi ključ, svi ostali se guraju udesno.
            keys.named.right = keys.named.center;
            keys.named.center = keys.named.left;
            children.named.rightmost = children.named.right;
            children.named.right = children.named.left;
            children.named.left = children.named.leftmost;
            keys.named.left = job;
            return 0;
        case 1:
            if (keys.named.left == nullptr) {
                // Levo polje je slobodno, tamo umećemo.
                keys.named.left = job;
                return 0;
            }
            // Levo polje je zauzeto, pomeramo centar udesno.
            keys.named.right = keys.named.center;
            keys.named.center = job;
            children.named.rightmost = children.named.right;
            return 1;
        case 2:
            if (keys.named.right == nullptr) {
                // Desno polje je slobodno, tamo umećemo.
                keys.named.right = job;
                return 2;
            }
            // Desno polje je zauzeto, pomeramo centar ulevo.
            keys.named.left = keys.named.center;
            keys.named.center = job;
            children.named.leftmost = children.named.left;
            return 1;
        case 3:
            // Unosi se desni ključ, svi ostali se guraju ulevo.
            keys.named.left = keys.named.center;
            keys.named.center = keys.named.right;
            children.named.leftmost = children.named.left;
            children.named.left = children.named.right;
            children.named.right = children.named.rightmost;
            keys.named.right = job;
            return 2;
    }
    throw "Nepoznati indeks zadat za dodavanje.";
}

Job *Node::remove(int index) {
    if (!isLeaf()) {
        throw "Čvor nije list.";
    }
    Job *ret = keys.array[index];
    if (index == 0 || index == 2) {
        keys.array[index] = nullptr;
    } else if (keys.named.right != nullptr) {
        keys.named.center = keys.named.right;
        keys.named.right = nullptr;
    } else {
        keys.named.center = keys.named.left;
        keys.named.left = nullptr;
    }
    return ret;
}

int Node::sibling(int index) const {
    bool centeredSiblings = children.named.leftmost == nullptr &&
                            children.named.rightmost == nullptr;
    switch (index) {
        case 0: return 1;
        case 1: return centeredSiblings ? 2 : 0;
        case 2: return centeredSiblings ? 1 : 3;
        case 3: return 2;
    }
    throw "Nepoznati indeks zadat za određivanje brata.";
}

std::ostream &operator<<(std::ostream &file, const Node &node) {
    for (int i = 0; i < 3; ++i) {
        if (node.keys.array[i] == nullptr) {
            file << "     ";
        } else {
            if (file.rdbuf() == std::cout.rdbuf() && i % 2 == 0) {
                file << "\x1B[41m";
            }
            file << *(node.keys.array[i]);
            if (file.rdbuf() == std::cout.rdbuf() && i % 2 == 0) {
                file << "\x1B[0m";
            }
        }
    }
    return file;
}

struct RBNode {
    Node *node;
    int index;
    RBNode() : node(nullptr), index(1) {}
    RBNode(Node *node, int index) : node(node), index(index) {}
    RBNode(Node *node) : node(node), index(1) {}
    Job *key() const {
        return node->keys.array[index];
    }
    bool exists() const {
        return node != nullptr;
    }
    RBNode left();
    RBNode right();
    bool isRed() const;
};

RBNode RBNode::left() {
    if (index == 1) {
        if (node->keys.named.left == nullptr) {
            return node->children.named.left;
        } else {
            return {node, 0};
        }
    } else {
        return node->children.array[index];
    }
}

RBNode RBNode::right() {
    if (index == 1) {
        if (node->keys.named.right == nullptr) {
            return node->children.named.right;
        } else {
            return {node, 2};
        }
    } else {
        return node->children.array[index + 1];
    }
}

bool RBNode::isRed() const {
    return index % 2 == 0;
}

class Tree {
    public:
        Tree() : root(nullptr) {}
        Job *find(int priority) const;
        std::tuple<Node*, int, Node*, int> find(Job &job) const;
        void insert(Job *job);
        [[nodiscard]] Job *remove();
        [[nodiscard]] Job *remove(int priority, std::string &name);
        int count(int priority) const;
        void outputRB(std::ostream &file) const;
        ~Tree();
    private:
        Node *root;
        [[nodiscard]] Job* remove(std::stack<std::pair<Node*, int>> &nodes, int index);
    friend std::ostream &operator<<(std::ostream &output, const Tree &tree);
    friend std::istream &operator>>(std::istream &input, const Tree &tree);
};

Job *Tree::find(int priority) const {
    Node *curr = root;
    int index;
    while (curr != nullptr) {
        for (index = 0; index < 3; ++index) {
            Job *currJob = curr->keys.array[index];
            if (currJob == nullptr) {
                continue;
            }
            if (priority == currJob->priority) {
                return currJob;
            } else if (priority < currJob->priority) {
                curr = curr->children.array[index];
                break;
            }
        }
        if (index == 3) {
            if (curr->keys.named.right == nullptr) {
                index = 2;
            }
            curr = curr->children.array[index];
        }
    }
    return nullptr;
}

std::tuple<Node*, int, Node*, int> Tree::find(Job &job) const {
    Node *curr = root, *prev = nullptr;
    bool found = false;
    int index = -1, prevIndex = -1;
    while (curr != nullptr && !found) {
        prevIndex = index;
        for (index = 0; index < 3; ++index) {
            Job *currJob = curr->keys.array[index];
            if (currJob == nullptr) {
                continue;
            }
            if (job == (*currJob)) {
                found = true;
                break;
            } else if (job < (*currJob)) {
                prev = curr;
                curr = curr->children.array[index];
                break;
            }
        }
        if (index == 3 && !found) {
            if (curr->keys.named.right == nullptr) {
                index = 2;
            }
            prev = curr;
            curr = curr->children.array[index];
        }
    }
    return {prev, prevIndex, curr, index};
}

void Tree::insert(Job *job) {
    if (root == nullptr) {
        root = new Node;
        root->keys.named.center = job;
        return;
    }
    int index = -1;
    Node *curr = root;
    std::stack<std::pair<Node*, int>> nodes;
    while (curr != nullptr) {
        nodes.push(std::make_pair(curr, index));
        for (index = 0; index < 3; ++index) {
            Job *currJob = curr->keys.array[index];
            if (currJob != nullptr) {
                if ((*job) == (*currJob)) {
                    throw "Čvor već postoji u stablu.";
                } else if ((*job) < (*currJob)) {
                    curr = curr->children.array[index];
                    break;
                }
            }
        }
        if (index == 3) {
            if (curr->keys.named.right == nullptr) {
                index = 2;
            }
            curr = curr->children.array[index];
        }
    }
    bool prelomi = true;
    Node *leftPrevNode = nullptr, *rightPrevNode = nullptr,
         *leftNewNode, *rightNewNode;
    while (prelomi && !nodes.empty()) {
        prelomi = false;
        auto currPair = nodes.top();
        curr = currPair.first;
        if (curr->isFull()) {
            prelomi = true;
            Job *centerKey = curr->keys.named.center;
            leftNewNode = curr;
            leftNewNode->keys.named.center = curr->keys.named.left;
            rightNewNode = new Node;
            rightNewNode->keys.named.center = curr->keys.named.right;
            rightNewNode->children.named.left = leftNewNode->children.named.right;
            rightNewNode->children.named.right = leftNewNode->children.named.rightmost;
            leftNewNode->children.named.right = leftNewNode->children.named.left;
            leftNewNode->children.named.left = leftNewNode->children.named.leftmost;
            leftNewNode->children.named.leftmost = nullptr;
            leftNewNode->children.named.rightmost = nullptr;
            if ((*job) < (*centerKey)) {
                if ((*job) < *(leftNewNode->keys.named.center)) {
                    leftNewNode->children.named.leftmost = leftPrevNode;
                    leftNewNode->children.named.left = rightPrevNode;
                    leftNewNode->keys.named.left = job;
                    leftNewNode->keys.named.right = nullptr;
                } else {
                    leftNewNode->children.named.right = leftPrevNode;
                    leftNewNode->children.named.rightmost = rightPrevNode;
                    leftNewNode->keys.named.right = job;
                    leftNewNode->keys.named.left = nullptr;
                }
            } else {
                leftNewNode->keys.named.left = nullptr;
                leftNewNode->keys.named.right = nullptr;
                if ((*job) < *(rightNewNode->keys.named.center)) {
                    rightNewNode->children.named.leftmost = leftPrevNode;
                    rightNewNode->children.named.left = rightPrevNode;
                    rightNewNode->keys.named.left = job;
                } else {
                    rightNewNode->children.named.right = leftPrevNode;
                    rightNewNode->children.named.rightmost = rightPrevNode;
                    rightNewNode->keys.named.right = job;
                }
            }
            leftPrevNode = leftNewNode;
            rightPrevNode = rightNewNode;
            job = centerKey;
        } else {
            int newIndex = curr->insert(job, index);
            curr->children.array[newIndex] = leftPrevNode;
            curr->children.array[newIndex+1] = rightPrevNode;
        }
        index = currPair.second;
        nodes.pop();
    }
    if (prelomi) {
        root = new Node;
        root->keys.named.center = job;
        root->children.named.left = leftPrevNode;
        root->children.named.right = rightPrevNode;
    }
}

Job *Tree::remove() {
    if (root == nullptr) {
        throw "Stablo nema nijedan čvor.";
    }
    Node *curr = root;
    std::stack<std::pair<Node*, int>> nodes;
    int index = -1;
    while (curr != nullptr) {
        nodes.push(std::make_pair(curr, index));
        if (curr->children.named.leftmost == nullptr) {
            index = 1;
        } else {
            index = 0;
        }
        curr = curr->children.array[index];
    }
    return remove(nodes, index);
}

Job *Tree::remove(int priority, std::string &name) {
    if (root == nullptr) {
        throw "Stablo nema nijedan čvor.";
    }
    int index = -1;
    Node *curr = root;
    Job job(priority, name);
    std::stack<std::pair<Node*, int>> nodes;
    while (curr != nullptr) {
        nodes.push(std::make_pair(curr, index));
        for (index = 0; index < 3; ++index) {
            Job *currJob = curr->keys.array[index];
            if (currJob != nullptr) {
                if (job == (*currJob)) {
                    curr = nullptr;
                    break;
                } else if (job < (*currJob)) {
                    curr = curr->children.array[index];
                    break;
                }
            }
        }
        if (index == 3) {
            if (curr->keys.named.right == nullptr) {
                index = 2;
            }
            curr = curr->children.array[index];
        }
    }
    Node *parent = nodes.top().first;
    int parentIndex = index;
    if (*(parent->keys.array[index]) != job) {
        throw "Traženi čvor ne postoji.";
    }
    if (!parent->isLeaf()) {
        curr = parent->children.array[index + 1];
        while (curr != nullptr) {
            nodes.push(std::make_pair(curr, index));
            if (curr->children.named.leftmost != nullptr) {
                index = 0;
            } else {
                index = 1;
            }
            curr = curr->children.array[index];
        }
        curr = nodes.top().first;
        Job *temp = parent->keys.array[parentIndex];
        parent->keys.array[parentIndex] = curr->keys.array[index];
        curr->keys.array[index] = temp;
    }
    return remove(nodes, index);
}

Job *Tree::remove(std::stack<std::pair<Node*, int>> &nodes, int index) {
    auto currPair = nodes.top();
    Node *curr = currPair.first, *parent;
    Job *ret = curr->remove(index);
    index = currPair.second;
    nodes.pop();
    while (!nodes.empty() && curr->isEmpty()) {
        currPair = nodes.top();
        parent = currPair.first;
        nodes.pop();
        int siblingIndex = parent->sibling(index);
        Node *sibling = parent->children.array[siblingIndex],
             *fakeSibling = nullptr;
        if (sibling == nullptr && 0 < index && index < 3) {
            fakeSibling = parent->children.array[std::abs(3 - index)];
        }
        if (
            (sibling == nullptr || sibling->isMinimum()) &&
            (fakeSibling == nullptr || fakeSibling->isMinimum())
        ) {
            // Spajanje
            // 1. Spajanje brata i razdelnog ključa
            bool fakeMerge = false;
            int parentIndex;
            if (sibling == nullptr) {
                fakeMerge = true;
                sibling = fakeSibling;
                siblingIndex = std::abs(3 - index);
            }
            if (index < siblingIndex) {
                // Spajamo se sa desnim bratom
                sibling->keys.named.right = sibling->keys.named.center;
                sibling->keys.named.center = parent->keys.array[index];
                sibling->children.named.rightmost = sibling->children.named.right;
                sibling->children.named.right = sibling->children.named.left;
                sibling->children.named.left = curr->children.named.left;
                parentIndex = index;
            } else {
                // Spajamo se sa levim bratom
                sibling->keys.named.left = sibling->keys.named.center;
                sibling->keys.named.center = parent->keys.array[siblingIndex];
                sibling->children.named.leftmost = sibling->children.named.left;
                sibling->children.named.left = sibling->children.named.right;
                sibling->children.named.right = curr->children.named.left;
                parentIndex = siblingIndex;
            }
            delete curr;
            // 2. Prevezivanje roditelja
            switch (parentIndex) {
                case 0:
                    parent->children.named.leftmost = nullptr;
                    parent->children.named.left = sibling;
                    parent->keys.named.left = nullptr;
                    break;
                case 1:
                    if (fakeMerge && index == 2) {
                        parent->keys.named.center = parent->keys.named.left;
                        parent->keys.named.left = nullptr;
                        parent->children.named.left = parent->children.named.leftmost;
                        parent->children.named.leftmost = nullptr;
                        parent->children.named.right = sibling;
                    } else {
                        parent->keys.named.center = parent->keys.named.right;
                        parent->keys.named.right = nullptr;
                        parent->children.named.right = parent->children.named.rightmost;
                        parent->children.named.rightmost = nullptr;
                        parent->children.named.left = sibling;
                    }
                    break;
                case 2:
                    parent->children.named.rightmost = nullptr;
                    parent->children.named.right = sibling;
                    parent->keys.named.right = nullptr;
                    break;
            }
        } else {
            // Pozajmljivanje
            bool fakeBorrow = false;
            if (sibling == nullptr) {
                fakeBorrow = true;
                sibling = fakeSibling;
                siblingIndex = std::abs(3 - index);
            }
            if (index < siblingIndex) {
                curr->keys.named.center = parent->keys.array[index];
                // Pozajmljuje se od desnog brata
                if (sibling->isFull() || sibling->keys.named.left == nullptr) {
                    // Pozajmljuje se crni ključ
                    if (sibling->isFull()) {
                        // ali se takođe pozajmljuje crveni
                        curr->keys.named.right = sibling->keys.named.left;
                        sibling->keys.named.left = nullptr;
                        curr->children.named.rightmost = sibling->children.named.leftmost;
                        sibling->children.named.leftmost = nullptr;
                    }
                    if (fakeBorrow) {
                        // Pozajmljuje se od nepravog brata
                        parent->keys.named.center = parent->keys.named.right;
                        parent->keys.named.right = nullptr;
                        parent->keys.named.left = sibling->keys.named.center;
                        parent->children.named.leftmost = parent->children.named.left;
                        parent->children.named.left = parent->children.named.right;
                        parent->children.named.right = parent->children.named.rightmost;
                        parent->children.named.rightmost = nullptr;
                    } else {
                        parent->keys.array[index] = sibling->keys.named.center;
                    }
                    sibling->keys.named.center = sibling->keys.named.right;
                    sibling->keys.named.right = nullptr;
                    curr->children.named.right = sibling->children.named.left;
                    sibling->children.named.left = sibling->children.named.right;
                    sibling->children.named.right = sibling->children.named.rightmost;
                    sibling->children.named.rightmost = nullptr;
                } else {
                    // Pozajmljuje se crveni ključ
                    parent->keys.array[index] = sibling->keys.named.left;
                    sibling->keys.named.left = nullptr;
                    curr->children.named.right = sibling->children.named.leftmost;
                    sibling->children.named.leftmost = nullptr;
                }
            } else {
                // Pozajmljuje se od levog brata
                curr->keys.named.center = parent->keys.array[siblingIndex];
                if (sibling->isFull() || sibling->keys.named.right == nullptr) {
                    // Pozajmljuje se crni ključ
                    if (sibling->isFull()) {
                        // ali se takođe pozajmljuje crveni
                        curr->keys.named.left = sibling->keys.named.right;
                        sibling->keys.named.right = nullptr;
                        curr->children.named.leftmost = sibling->children.named.rightmost;
                        sibling->children.named.rightmost = nullptr;
                    }
                    if (fakeBorrow) {
                        // Pozajmljuje se od nepravog brata
                        parent->keys.named.center = parent->keys.named.left;
                        parent->keys.named.left = nullptr;
                        parent->keys.named.right = sibling->keys.named.center;
                        parent->children.named.rightmost = parent->children.named.right;
                        parent->children.named.right = parent->children.named.left;
                        parent->children.named.left = parent->children.named.leftmost;
                        parent->children.named.leftmost = nullptr;
                    } else {
                        parent->keys.array[siblingIndex] = sibling->keys.named.center;
                    }
                    sibling->keys.named.center = sibling->keys.named.left;
                    sibling->keys.named.left = nullptr;
                    curr->children.named.left = sibling->children.named.right;
                    sibling->children.named.right = sibling->children.named.left;
                    sibling->children.named.left = sibling->children.named.leftmost;
                    sibling->children.named.leftmost = nullptr;
                } else {
                    // Pozajmljuje se crveni ključ
                    parent->keys.array[siblingIndex] = sibling->keys.named.right;
                    sibling->keys.named.right = nullptr;
                    curr->children.named.left = sibling->children.named.rightmost;
                    sibling->children.named.rightmost = nullptr;
                }
            }
        }
        curr = parent;
        index = currPair.second;
    }
    if (curr->isEmpty()) {
        root = curr->children.named.left;
    }
    return ret;
}

int Tree::count(int priority) const {
    std::stack<RBNode> nodes;
    RBNode curr(root);
    int count = 0;
    while (curr.exists()) {
        nodes.push(curr);
        curr = curr.left();
    }
    while (!nodes.empty()) {
        curr = nodes.top();
        nodes.pop();
        int currPriority = curr.key()->priority;
        if (currPriority == priority) {
            ++count;
        } else if (currPriority > priority) {
            break;
        }
        curr = curr.right();
        while (curr.exists()) {
            nodes.push(curr);
            curr = curr.left();
        }
    }
    return count;
}

Tree::~Tree() {
    if (root == nullptr) {
        return;
    }
    Node* curr;
    std::stack<Node*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        curr = nodes.top();
        nodes.pop();
        for (int i = 0; i < 4; ++i) {
            if (i != 3) {
                delete curr->keys.array[i];
            }
            if (curr->children.array[i] != nullptr) {
                nodes.push(curr->children.array[i]);
            }
        }
        delete curr;
    }
    root = nullptr;
}

std::ostream &operator<<(std::ostream &file, const Tree &tree) {
    if (tree.root == nullptr) {
        return file;
    }
    // Level-order obilazak radi utvrđivanja dubine stabla.
    std::queue<std::pair<int, Node*>> levelOrderQueue;
    int maxLevel = 0, baseSpace, width = 15;
    levelOrderQueue.push(std::make_pair(1, tree.root));
    while (!levelOrderQueue.empty()) {
        auto indexNodePair = levelOrderQueue.front();
        int index = indexNodePair.first;
        Node *node = indexNodePair.second;
        levelOrderQueue.pop();
        if (index > maxLevel) {
            maxLevel = index;
            width = 4 * width + 3;
            baseSpace = (width - 15) / 2;
        }
        for (int i = 0; i < 4; ++i) {
            if (node->children.array[i] != nullptr) {
                levelOrderQueue.push(std::make_pair(
                    index + 1,
                    node->children.array[i]
                ));
            }
        }
    }
    // Formiranje punog stabla od trenutnog stabla.
    int fullTreeSize = std::pow(4, maxLevel + 1) - 1;
    Node **fullTree = new Node*[fullTreeSize];
    for (int i = 0; i < fullTreeSize; ++i) {
        fullTree[i] = nullptr;
    }
    levelOrderQueue.push(std::make_pair(0, tree.root));
    while (!levelOrderQueue.empty()) {
        auto indexNodePair = levelOrderQueue.front();
        int index = indexNodePair.first;
        Node *node = indexNodePair.second;
        levelOrderQueue.pop();
        fullTree[index] = node;
        for (int i = 0; i < 4; ++i) {
            if (node->children.array[i] != nullptr) {
                levelOrderQueue.push(std::make_pair(
                    index * 4 + i + 1,
                    node->children.array[i]
                ));
            }
        }
    }
    // Ispisivanje punog stabla.
    int currentLevelNodes = 1,
        index1 = 0,
        index2 = 0;
    for (int i = 0; i < maxLevel; ++i) {
        width = (width - 3) / 4;
        baseSpace = (width - 15) / 2;
        // Ispisivanje čvorova.
        for (int j = 0; j < currentLevelNodes; ++j) {
            if (j == 0) {
                spacetime(file, " ", baseSpace);
            } else {
                spacetime(file, " ", baseSpace * 2 + 1);
            }
            Node *currNode = fullTree[index1];
            if (currNode == nullptr) {
                spacetime(file, " ", 15);
            } else {
                file << (*currNode);
            }
            ++index1;
        }
        file << std::endl;
        // Ispisivanje strelica.
        if (i != maxLevel - 1) {
            int arrowSpace = (((width - 3) / 4) - 1) / 2;
            //spacetime(file, " ", arrowSpace + 1);
            for (int j = 0; j < currentLevelNodes; ++j) {
                bool exists = fullTree[index2] != nullptr,
                     childrenExist[4] = {false};
                if (exists) {
                    for (int i = 0; i < 4; ++i) {
                        childrenExist[i] = fullTree[index2]->children.array[i] != nullptr;
                    }
                    if (childrenExist[0]) {
                        spacetime(file, " ", arrowSpace);
                        file << ARROW_RIGHT_DOWN;
                        spacetime(file, ARROW_HORIZONTAL, arrowSpace * 2 + 1);
                        file << ARROW_HORIZONTAL_DOWN;
                    } else {
                        spacetime(file, " ", arrowSpace * 3 + 2);
                        file << ARROW_RIGHT_DOWN;
                    }
                    spacetime(file, ARROW_HORIZONTAL, arrowSpace);
                    file << ARROW_HORIZONTAL_UP;
                    spacetime(file, ARROW_HORIZONTAL, arrowSpace);
                    if (childrenExist[3]) {
                        file << ARROW_HORIZONTAL_DOWN;
                        spacetime(file, ARROW_HORIZONTAL, arrowSpace * 2 + 1);
                        file << ARROW_LEFT_DOWN;
                        spacetime(file, " ", arrowSpace);
                    } else {
                        file << ARROW_LEFT_DOWN;
                        spacetime(file, " ", arrowSpace * 3 + 2);
                    }
                } else {
                    spacetime(file, " ", width);
                }
                file << " ";
                ++index2;
            }
            file << std::endl;
        }
        currentLevelNodes *= 4;
    }
    delete[] fullTree;
    return file;
}

void Tree::outputRB(std::ostream &file) const {
    if (root == nullptr) {
        return;
    }
    // Level-order obilazak radi utvrđivanja dubine stabla.
    std::queue<std::pair<int, RBNode>> levelOrderQueue;
    int maxLevel = 0;
    levelOrderQueue.push(std::make_pair(1, root));
    while (!levelOrderQueue.empty()) {
        auto indexNodePair = levelOrderQueue.front();
        int index = indexNodePair.first;
        RBNode node = indexNodePair.second;
        levelOrderQueue.pop();
        if (index > maxLevel) {
            maxLevel = index;
        }
        if (node.left().exists()) {
            levelOrderQueue.push(std::make_pair(index + 1, node.left()));
        }
        if (node.right().exists()) {
            levelOrderQueue.push(std::make_pair(index + 1, node.right()));
        }
    }
    long long width = (1 << maxLevel) + 1;
    // Formiranje punog stabla od trenutnog stabla.
    long long fullTreeNodeNumber = width - 2;
    RBNode *fullTree = new RBNode[fullTreeNodeNumber];
    // Populacija punog stabla pokazivačima na čvorove level-order obilaskom.
    levelOrderQueue.push(std::make_pair(1, root));
    while (!levelOrderQueue.empty()) {
        auto indexNodePair = levelOrderQueue.front();
        int index = indexNodePair.first;
        RBNode node = indexNodePair.second;
        levelOrderQueue.pop();
        fullTree[index - 1] = node;
        if (node.left().exists()) {
            levelOrderQueue.push(std::make_pair(index * 2, node.left()));
        }
        if (node.right().exists()) {
            levelOrderQueue.push(std::make_pair(index * 2 + 1, node.right()));
        }
    }
    // Ispisivanje punog stabla.
    int currentLevelNodes = 1,
        index1 = 0,
        index2 = 0,
        baseSpace = std::pow(2, maxLevel) - 2;
    Job *currValue;
    for (int i = 0; i < maxLevel; ++i) {
        // Ispisivanje čvorova.
        for (int j = 0; j < currentLevelNodes; ++j) {
            if (j == 0) {
                spacetime(file, " ", baseSpace);
            } else {
                spacetime(file, " ", baseSpace * 2 + 1);
            }
            RBNode currNode = fullTree[index1];
            if (currNode.exists()) {
                currValue = currNode.key();
                if (file.rdbuf() == std::cout.rdbuf() && currNode.isRed()) {
                    file << "\x1B[41m";
                }
                if (currValue->name.size() == 1) {
                    file << ' ' << currValue->name << ' ';
                } else {
                    file << std::setw(3) << currValue->name.substr(0, 3);
                }
                if (file.rdbuf() == std::cout.rdbuf() && currNode.isRed()) {
                    file << "\x1B[0m";
                }
            } else {
                file << "   ";
            }
            ++index1;
        }
        file << std::endl;
        // Ispisivanje strelica.
        if (i != maxLevel - 1) {
            for (int j = 0; j < currentLevelNodes; ++j) {
                bool exists = fullTree[index2].exists(),
                     leftChildExists = false,
                     rightChildExists = false;
                if (exists) {
                    if (fullTree[index2].left().exists()) {
                        leftChildExists = true;
                    }
                    if (fullTree[index2].right().exists()) {
                        rightChildExists = true;
                    }
                }
                if (leftChildExists) {
                    spacetime(file, " ", baseSpace / 2);
                    file << ARROW_RIGHT_DOWN;
                    spacetime(file, ARROW_HORIZONTAL, baseSpace / 2);
                } else {
                    spacetime(file, " ", baseSpace + 1);
                }
                if (leftChildExists && rightChildExists) {
                    file << ARROW_HORIZONTAL_UP;
                } else if (leftChildExists) {
                    file << ARROW_LEFT_UP;
                } else if (rightChildExists) {
                    file << ARROW_RIGHT_UP;
                } else {
                    file << " ";
                }
                if (rightChildExists) {
                    spacetime(file, ARROW_HORIZONTAL, baseSpace / 2);
                    file << ARROW_LEFT_DOWN;
                    spacetime(file, " ", baseSpace / 2);
                } else {
                    spacetime(file, " ", baseSpace + 1);
                }
                file << " ";
                ++index2;
            }
            file << std::endl;
        }
        baseSpace = (baseSpace - 2) / 2;
        currentLevelNodes *= 2;
    }
    delete[] fullTree;
}

std::istream &operator>>(std::istream &input, Tree &tree) {
    std::string line;
    while (!input.eof()) {
        std::getline(input, line);
        if (line.size() == 0) {
            break;
        }
        auto pos = line.find_last_of(' ');
        if (pos == std::string::npos) {
            throw "Red datoteke nije validno formiran.";
        } else {
            Job *newJob = new Job(
                std::stoi(line.substr(pos + 1)),
                line.substr(0, pos)
            );
            tree.insert(newJob);
        }
    }
    return input;
}

void createTree(Tree *&tree) {
    delete tree;
    tree = new Tree;
}

void checkTreeExists(Tree *&tree) {
    if (tree == nullptr) {
        throw "Stablo nije napravljeno.";
    }
}

void inputTree(Tree *&tree) {
    if (tree == nullptr) {
        createTree(tree);
    }
    std::string filename;
    std::cout << "Unesite naziv datoteke: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::ifstream file(filename.c_str(), std::ios::in);
    if (!file.is_open()) {
        throw "Desila se greška prilikom otvaranja zadate datoteke.";
    }
    file >> (*tree);
    file.close();
}

void searchTree(Tree *&tree) {
    int priority;
    checkTreeExists(tree);
    std::cout << "Uneti prioritet akcije za traženje: ";
    std::cin >> priority;
    Job *foundJob = tree->find(priority);
    if (foundJob == nullptr) {
        std::cout << "Akcija sa zadatim prioritetom nije pronađena." << std::endl;
    } else {
        std::cout << "Pronađena akcija: " << foundJob->name << std::endl;
    }
}

void insertAction(Tree *&tree) {
    checkTreeExists(tree);
    Job *newJob = new Job;
    std::cout << "Unesite naziv akcije: ";
    std::cin.ignore();
    std::getline(std::cin, newJob->name);
    std::cout << "Unesite prioritet akcije: ";
    std::cin >> newJob->priority;
    tree->insert(newJob);
}

void deleteAction(Tree *&tree) {
    int priority;
    checkTreeExists(tree);
    std::cout << "Unesite prioritet akcije za brisanje (negativno za brisanje akcije najvišeg prioriteta): ";
    std::cin >> priority;
    Job *removedJob;
    if (priority < 0) {
        removedJob = tree->remove();
    } else {
        std::string name;
        std::cout << "Unesite naziv akcije za brisanje: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        removedJob = tree->remove(priority, name);
    }
    if (removedJob == nullptr) {
        std::cout << "Akcija nije pronađena." << std::endl;
    } else {
        delete removedJob;
    }
}

void outputTreeToFile(Tree *&tree, std::ostream &file) {
    file << "2-3-4 stablo:" << std::endl << (*tree) << std::endl
              << "Crveno-crno stablo:" << std::endl;
    tree->outputRB(file);
}

void outputTree(Tree *&tree) {
    checkTreeExists(tree);
    std::cout << "Unesite naziv datoteke za ispisivanje "
              << "(prazno za standardni izlaz): ";
    std::cin.ignore();
    std::string filename;
    std::getline(std::cin, filename);
    if (filename.size() == 0) {
        outputTreeToFile(tree, std::cout);
    } else {
        std::ofstream file(filename);
        outputTreeToFile(tree, file);
    }
}

void changePriority(Tree *&tree) {
    int oldPriority, newPriority;
    checkTreeExists(tree);
    std::cout << "Unesite stari prioritet: ";
    std::cin >> oldPriority;
    std::cout << "Unesite naziv: ";
    std::cin.ignore();
    std::string name;
    std::getline(std::cin, name);
    std::cout << "Unesite novi prioritet: ";
    std::cin >> newPriority;
    if (oldPriority == newPriority) {
        return;
    }
    Job oldJob(oldPriority, name);
    Job newJob(newPriority, name);
    auto foundData = tree->find(oldJob);
    Node *parentNode = std::get<0>(foundData);
    int parentIndex = std::get<1>(foundData);
    Node *node = std::get<2>(foundData);
    int index = std::get<3>(foundData);
    if (node == nullptr) {
        throw "Čvor nije pronađen.";
    }
    if (
        node->isLeaf() &&
        (
            parentNode == nullptr ||
            (
                (
                    parentIndex == 1 ||
                    parentIndex == 2
                ) &&
                parentNode->keys.array[parentIndex] != nullptr &&
                parentNode->keys.array[parentIndex-1] != nullptr &&
                newJob < *(parentNode->keys.array[parentIndex]) &&
                newJob > *(parentNode->keys.array[parentIndex-1])
            )
        )
    ) {
        Job *removedJob = node->remove(index);
        int newIndex;
        for (newIndex = 0; newIndex < 3; ++newIndex) {
            if (
                node->keys.array[newIndex] != nullptr &&
                newJob >= *(node->keys.array[newIndex])
            ) {
                break;
            }
        }
        if (node->keys.named.right == nullptr && newIndex == 3) {
            newIndex = 2;
        }
        removedJob->priority = newPriority;
        node->insert(removedJob, newIndex);
    } else {
        Job *job = tree->remove(oldPriority, name);
        job->priority = newPriority;
        tree->insert(job);
    }
}

void countPriorities(Tree *&tree) {
    int priority;
    checkTreeExists(tree);
    std::cout << "Unesite prioritet za koji akcije moraju da budu prebrojene: ";
    std::cin >> priority;
    std::cout << "Broj akcija sa zadatim prioritetom: "
              << tree->count(priority) << std::endl;
}

int main(void) {
    int option = 1;
    Tree *tree = nullptr;
    const int code[] = {
        27, 91, 65, 27, 91, 65, 27, 91, 66, 27, 91, 66, 27,
        91, 68, 27, 91, 67, 27, 91, 68, 27, 91, 67, 98, 97
    };
    const int codeLength = sizeof(code)/sizeof(int);
    void (*options[])(Tree *&) = {
        createTree,
        inputTree,
        searchTree,
        insertAction,
        deleteAction,
        outputTree,
        changePriority,
        countPriorities
    };
    clear();
    while (option) {
        char input;
        int currentCodePos = 0;
        std::cout
        <<  "╔══════════════════════════════════════════════════════════╗\n"
        <<  "║ Drugi domaći iz Algoritama i struktura podataka 2        ║\n"
        <<  "║ Student Luka Simić, broj indeksa 368, godina upisa 2019. ║\n"
        <<  "╟──────────────────────────────────────────────────────────╢\n"
        <<  "║ Izaberite opciju za svoju narednu operaciju.             ║\n"
        <<  "║ 1. Stvaranje stabla.                                     ║\n"
        <<  "║ 2. Unos stabla iz datoteke.                              ║\n"
        <<  "║ 3. Pretraživanje stabla.                                 ║\n"
        <<  "║ 4. Umetanje nove akcije.                                 ║\n"
        <<  "║ 5. Brisanje akcije.                                      ║\n"
        <<  "║ 6. Ispis stabla.                                         ║\n"
        <<  "║ 7. Izmena prioriteta akcije.                             ║\n"
        <<  "║ 8. Prebrojavanje akcija s prioritetom.                   ║\n"
        <<  "║ 0. Izlaz iz programa.                                    ║\n"
        <<  "╚══════════════════════════════════════════════════════════╝"
        << std::endl;
        std::cin >> input;
        option = input - '0';
        clear();
        if (option > 0 && option < 9) {
            try {
                options[option-1](tree);
            } catch (const char *message) {
                std::cout << message << std::endl;
            } catch (std::bad_alloc &exc) {
                std::cout << "Desila se greška prilikom alokacije memorije: "
                          << exc.what() << "." << std::endl;
            }
        } else if (option != 0) {
            while (
                currentCodePos < codeLength - 1 &&
                code[currentCodePos++] == int(input)
            ) {
                std::cin >> input;
            }
            if (
                currentCodePos == codeLength - 1 &&
                int(input) == code[currentCodePos]
            ) {
                std::ifstream milo("milo.ans");
                while (!milo.eof()) {
                    std::string line;
                    std::getline(milo, line);
                    std::cout << line << std::endl;
                }
            } else {
                std::cout << "Nije izabrana validna opcija." << std::endl;
            }
        }
    }
    delete tree;
    return EXIT_SUCCESS;
}
