template <class T> class Tree;

template <class T>
class TreeNode {
public:
    TreeNode(T data);
    void visit();
    friend class Tree<T>;
    T _data;
    bool _traveled;
    TreeNode<T>* _leftChild;
    TreeNode<T>* _rightChild;
};

template <class T>
class Tree {
public:
    Tree(void) : root(nullptr) {}
    Tree(TreeNode<T>* rootNode) : root(rootNode) {}
    void inorder();
    void preorder();
    void postorder();
private:
    TreeNode<T>* root;
};

#include <stack>
#include <iostream>
template <class T>
TreeNode<T>::TreeNode(T data): _data(data), _traveled(false), _leftChild(nullptr), _rightChild(nullptr) {}

template <class T>
void TreeNode<T>::visit() {
    _traveled = true;
    std::cout << " " << _data;
};

template <class T>
void Tree<T>::inorder() {
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* curNode = root;
    std::cout << "Inorder Traversal: [";
    while(1) {
        while(curNode) {
            s.push(curNode);
            curNode = curNode->_leftChild;
        }
        if (s.empty()) break;
        curNode = s.top();
        s.pop();
        curNode->visit();
        curNode = curNode->_rightChild;
    }
    std::cout << " ]" << std::endl;
}

template <class T>
void Tree<T>::postorder() {
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* curNode = root;
    std::cout << "Postorder Traversal: [";
    while(1) {
        while (curNode) {
            s.push(curNode);
            s.push(curNode);
            curNode = curNode->_leftChild;
        }
        if (s.empty()) break;
        curNode = s.top();
        s.pop();
        if (!s.empty() && s.top() == curNode) curNode = curNode->_rightChild;
        else {
            curNode->visit();
            curNode = nullptr;
        }
    }
    std::cout << " ]" << std::endl;
}

template <class T>
void Tree<T>::preorder() {
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* curNode = root;
    std::cout << "Preorder Traversal: [";
    while(1) {
        while (curNode) {
            curNode->visit();
            s.push(curNode);
            curNode = curNode->_leftChild;
        }
        if (s.empty()) break;
        curNode = s.top();
        s.pop();
        if (curNode->_rightChild != nullptr) {
            curNode = curNode->_rightChild;
        } else {
            curNode = nullptr;
        }
    }
    std::cout << " ]" << std::endl;
}

int main() {
    TreeNode<int>* root = new TreeNode<int>(4);
    TreeNode<int>* cur = root;
    cur->_leftChild = new TreeNode<int>(2);
    cur->_rightChild = new TreeNode<int>(5);
    cur = cur->_leftChild;
    cur->_leftChild = new TreeNode<int>(1);
    cur->_rightChild = new TreeNode<int>(3);
    cur = root->_rightChild;
    cur->_leftChild = new TreeNode<int>(6);
    cur = cur->_leftChild;
    cur->_rightChild = new TreeNode<int>(7);
    Tree<int> tree(root);
    tree.inorder();
    tree.preorder();
    tree.postorder();
}