#include <stack>
#include <queue>
#include <iostream>
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
    Tree(void);
    Tree(TreeNode<T>* rootNode);
    void inorder();
    void preorder();
    void postorder();
    void bfs();
private:
    TreeNode<T>* root;
};

template <class T>
class InorderIterator {
public:
    InorderIterator(TreeNode<T>* curNode, int count);
    T* next();
    bool hasNext();
private:
    TreeNode<T>* _curNode;
    std::stack<TreeNode<T>*> _s;
    int _count;
};

template <class T>
class PreorderIterator {
public:
    PreorderIterator(TreeNode<T>* curNode, int count);
    T* next();
    bool hasNext();
private:
    TreeNode<T>* _curNode;
    std::stack<TreeNode<T>*> _s;
    int _count;
};

template <class T>
class PostorderIterator {
public:
    PostorderIterator(TreeNode<T>* curNode, int count);
    T* next();
    bool hasNext();
private:
    TreeNode<T>* _curNode;
    std::stack<TreeNode<T>*> _s;
    int _count;
};

// implementation

template <class T>
TreeNode<T>::TreeNode(T data): _data(data), _traveled(false), _leftChild(nullptr), _rightChild(nullptr) {}

template <class T>
InorderIterator<T>::InorderIterator(TreeNode<T>* curNode, int count) : _curNode(curNode), _count(count) {}

template <class T>
PreorderIterator<T>::PreorderIterator(TreeNode<T>* curNode, int count) : _curNode(curNode), _count(count) {}

template <class T>
PostorderIterator<T>::PostorderIterator(TreeNode<T>* curNode, int count) : _curNode(curNode), _count(count) {}

template <class T>
Tree<T>::Tree(void) : root(nullptr) {}

template <class T>
Tree<T>::Tree(TreeNode<T>* rootNode) : root(rootNode) {}

template <class T>
void TreeNode<T>::visit() {
    _traveled = true;
    std::cout << " " << _data;
};

template <class T>
T* InorderIterator<T>::next() {
    while(_curNode) {
        _s.push(_curNode);
        _curNode = _curNode->_leftChild;
    }
    if (_s.empty()) return nullptr;
    _curNode = _s.top();
    _s.pop();
    T* returnVal = &_curNode->_data;
    _curNode = _curNode->_rightChild;
    --_count;
    return returnVal;
}

template <class T>
bool InorderIterator<T>::hasNext() {
    if(_count > 0) return true;
    else return false;
}

template <class T>
T* PreorderIterator<T>::next() {
    T* returnVal;
    while(1) {
        if (_curNode) {
            returnVal = &_curNode->_data;
            _s.push(_curNode);
            _curNode = _curNode->_leftChild;
            break;
        } else {
            if (_s.empty()) break;
            _curNode = _s.top();
            _s.pop();
            if (_curNode->_rightChild != nullptr) {
                _curNode = _curNode->_rightChild;
            } else {
                _curNode = nullptr;
            }
        }
    }
    --_count;
    return returnVal;
}

template <class T>
bool PreorderIterator<T>::hasNext() {
    if(_count > 0) return true;
    else return false;
}

template <class T>
T* PostorderIterator<T>::next() {
    T* returnVal;
    while(1) {
        while (_curNode) {
            _s.push(_curNode);
            _s.push(_curNode);
            _curNode = _curNode->_leftChild;
        }
        if (_s.empty()) break;
        _curNode = _s.top();
        _s.pop();
        if (!_s.empty() && _s.top() == _curNode) _curNode = _curNode->_rightChild;
        else {
            returnVal = &_curNode->_data;
            _curNode = nullptr;
            break;
        }
    }
    --_count;
    return returnVal;
}

template <class T>
bool PostorderIterator<T>::hasNext() {
    if(_count > 0) return true;
    else return false;
}

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

template <class T>
void Tree<T>::bfs() {
    std::queue<TreeNode<T>*> q;
    TreeNode<T>* curNode = root;
    std::cout << "BFS: [";
    while(curNode) {
        curNode->visit();
        if(curNode->_leftChild) q.push(curNode->_leftChild);
        if(curNode->_rightChild) q.push(curNode->_rightChild);
        if(q.empty()) break;
        curNode = q.front();
        q.pop();
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
    tree.bfs();
    InorderIterator<int> iit(root, 7);
    std::cout << "Inorder Iterator: [ ";
    while(iit.hasNext()) {
        std::cout << *iit.next() << " ";
    }
    std::cout << "]" << std::endl;

    PreorderIterator<int> preit(root, 7);
    std::cout << "Preorder Iterator: [ ";
    while(preit.hasNext()) {
        std::cout << *preit.next() << " ";
    }
    std::cout << "]" << std::endl;

    PostorderIterator<int> postit(root, 7);
    std::cout << "Postorder Iterator: [ ";
    while(postit.hasNext()) {
        std::cout << *postit.next() << " ";
    }
    std::cout << "]" << std::endl;
}