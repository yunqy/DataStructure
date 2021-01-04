#include "Tree.h"
#include <string>
#include <queue>
#include <iostream>

// Tree Constructor
template <class T>
Tree<T>::Tree(T val) : _root(new TreeNode(val)), _it(new InorderIterator(this, _root)), _size(1), _count(1) {}

template <class T>
Tree<T>::Tree(T val, std::string order) : _root(new Tree<T>::TreeNode(val)), _size(1), _count(1)
{
    if (order == "inorder")
        _it = new InorderIterator(this, _root);
    else if (order == "preorder")
        _it = new PreorderIterator(this, _root);
    else if (order == "postorder")
        _it = new PostorderIterator(this, _root);
}

// Tree Member Function
template <class T>
typename Tree<T>::Iterator* Tree<T>::getIterator()
{
    return _it;
}

template <class T>
void Tree<T>::changeIterator(std::string order)
{
    delete _it;
    _count = _size;
    if (order == "inorder")
        _it = new InorderIterator(this, _root);
    else if (order == "preorder")
        _it = new PreorderIterator(this, _root);
    else if (order == "postorder")
        _it = new PostorderIterator(this, _root);
}

template <class T>
void Tree<T>::insert(T val)
{
    TreeNode* curNode;
    std::queue<TreeNode*> q;
    q.push(_root);
    while (!q.empty())
    {
        curNode = q.front();
        q.pop();
        if (curNode->leftChild != nullptr)
        {
            q.push(curNode->leftChild);
        }
        else
        {
            curNode->leftChild = new TreeNode(val);
            break;
        }

        if (curNode->rightChild != nullptr)
        {
            q.push(curNode->rightChild);
        }
        else
        {
            curNode->rightChild = new TreeNode(val);
            break;
        }
    }
    ++_count;
    ++_size;
}

template <class T>
void Tree<T>::inorder()
{
    std::stack<TreeNode*> s;
    TreeNode *curNode = _root;
    std::cout << "Inorder Traversal: [";
    while (1)
    {
        while (curNode)
        {
            s.push(curNode);
            curNode = curNode->leftChild;
        }
        if (s.empty())
            break;
        curNode = s.top();
        s.pop();
        curNode->visit();
        curNode = curNode->rightChild;
    }
    std::cout << " ]" << std::endl;
}

template <class T>
void Tree<T>::postorder()
{
    std::stack<TreeNode*> s;
    TreeNode *curNode = _root;
    std::cout << "Postorder Traversal: [";
    while (1)
    {
        while (curNode)
        {
            s.push(curNode);
            s.push(curNode);
            curNode = curNode->leftChild;
        }
        if (s.empty())
            break;
        curNode = s.top();
        s.pop();
        if (!s.empty() && s.top() == curNode)
            curNode = curNode->rightChild;
        else
        {
            curNode->visit();
            curNode = nullptr;
        }
    }
    std::cout << " ]" << std::endl;
}


template <class T>
void Tree<T>::preorder()
{
    std::stack<TreeNode*> s;
    TreeNode *curNode = _root;
    std::cout << "Preorder Traversal: [";
    while (1)
    {
        while (curNode)
        {
            curNode->visit();
            s.push(curNode);
            curNode = curNode->leftChild;
        }
        if (s.empty())
            break;
        curNode = s.top();
        s.pop();
        if (curNode->rightChild != nullptr)
        {
            curNode = curNode->rightChild;
        }
        else
        {
            curNode = nullptr;
        }
    }
    std::cout << " ]" << std::endl;
}

template <class T>
void Tree<T>::bfs()
{
    std::queue<TreeNode*> q;
    TreeNode *curNode = _root;
    std::cout << "BFS: [";
    while (curNode)
    {
        curNode->visit();
        if (curNode->leftChild)
            q.push(curNode->leftChild);
        if (curNode->rightChild)
            q.push(curNode->rightChild);
        if (q.empty())
            break;
        curNode = q.front();
        q.pop();
    }
    std::cout << " ]" << std::endl;
}

// TreeNdoe Contructor
template <class T>
Tree<T>::TreeNode::TreeNode(T data) : data(data), traveled(false), leftChild(nullptr), rightChild(nullptr) {}

template <class T>
void Tree<T>::TreeNode::visit()
{
    traveled = true;
    std::cout << " " << data;
}

// Iterator Contructor
template <class T>
Tree<T>::Iterator::Iterator(Tree<T>* tree, Tree<T>::TreeNode *curNode) : _tree(tree), _curNode(curNode) {}

template <class T>
Tree<T>::InorderIterator::InorderIterator(Tree<T>* tree, Tree<T>::TreeNode *curNode) : SUPER(tree, curNode) {}

template <class T>
Tree<T>::PreorderIterator::PreorderIterator(Tree<T>* tree, Tree<T>::TreeNode *curNode) : SUPER(tree, curNode) {}

template <class T>
Tree<T>::PostorderIterator::PostorderIterator(Tree<T>* tree, Tree<T>::TreeNode *curNode) : SUPER(tree, curNode) {}

// Iterator Member Function
template <class T>
T *Tree<T>::InorderIterator::next()
{
    while (SUPER::_curNode)
    {
        SUPER::_s.push(SUPER::_curNode);
        SUPER::_curNode = SUPER::_curNode->leftChild;
    }
    if (SUPER::_s.empty())
        return nullptr;
    SUPER::_curNode = SUPER::_s.top();
    SUPER::_s.pop();
    T *returnVal = &SUPER::_curNode->data;
    SUPER::_curNode = SUPER::_curNode->rightChild;
    --SUPER::_tree->_count;
    return returnVal;
}

template <class T>
bool Tree<T>::InorderIterator::hasNext()
{
    if (SUPER::_tree->_count > 0)
        return true;
    else
        return false;
}

template <class T>
T *Tree<T>::PreorderIterator::next()
{
    T *returnVal;
    while (1)
    {
        if (SUPER::_curNode)
        {
            returnVal = &SUPER::_curNode->data;
            SUPER::_s.push(SUPER::_curNode);
            SUPER::_curNode = SUPER::_curNode->leftChild;
            break;
        }
        else
        {
            if (SUPER::_s.empty())
                break;
            SUPER::_curNode = SUPER::_s.top();
            SUPER::_s.pop();
            if (SUPER::_curNode->rightChild != nullptr)
            {
                SUPER::_curNode = SUPER::_curNode->rightChild;
            }
            else
            {
                SUPER::_curNode = nullptr;
            }
        }
    }
    --SUPER::_tree->_count;
    return returnVal;
}

template <class T>
bool Tree<T>::PreorderIterator::hasNext()
{
    if (SUPER::_tree->_count > 0)
        return true;
    else
        return false;
}

template <class T>
T *Tree<T>::PostorderIterator::next()
{
    T *returnVal;
    while (1)
    {
        while (SUPER::_curNode)
        {
            SUPER::_s.push(SUPER::_curNode);
            SUPER::_s.push(SUPER::_curNode);
            SUPER::_curNode = SUPER::_curNode->leftChild;
        }
        if (SUPER::_s.empty())
            break;
        SUPER::_curNode = SUPER::_s.top();
        SUPER::_s.pop();
        if (!SUPER::_s.empty() && SUPER::_s.top() == SUPER::_curNode)
            SUPER::_curNode = SUPER::_curNode->rightChild;
        else
        {
            returnVal = &SUPER::_curNode->data;
            SUPER::_curNode = nullptr;
            break;
        }
    }
    --SUPER::_tree->_count;
    return returnVal;
}

template <class T>
bool Tree<T>::PostorderIterator::hasNext()
{
    if (SUPER::_tree->_count > 0)
        return true;
    else
        return false;
}

int main()
{
    Tree<int> tree(4);
    tree.insert(2);
    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(6);
    tree.insert(7);
    tree.bfs();
    tree.inorder();
    Tree<int>::Iterator* it = tree.getIterator();
    std::cout << "Inorder Iterator: [ ";
    while (it->hasNext())
    {
        std::cout << *it->next() << " ";
    }
    std::cout << "]" << std::endl;
    Tree<int> tree2(4, "preorder");
    tree2.insert(2);
    tree2.insert(5);
    tree2.insert(1);
    tree2.insert(3);
    tree2.insert(6);
    tree2.insert(7);
    tree2.preorder();
    Tree<int>::Iterator* preit = tree2.getIterator();
    std::cout << "Preorder Iterator: [ ";
    while (preit->hasNext())
    {
        std::cout << *preit->next() << " ";
    }
    std::cout << "]" << std::endl;
    Tree<int> tree3(4, "postorder");
    tree3.insert(2);
    tree3.insert(5);
    tree3.insert(1);
    tree3.insert(3);
    tree3.insert(6);
    tree3.insert(7);
    tree3.postorder();
    Tree<int>::Iterator* postit = tree3.getIterator();
    std::cout << "Postorder Iterator: [ ";
    while (postit->hasNext())
    {
        std::cout << *postit->next() << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "=====Change Iterator from InorderIterator to PostorderIterator=====" << std::endl;
    tree.changeIterator("postorder");
    it = tree.getIterator();
    std::cout << "Postorder Iterator: [ ";
    while (it->hasNext())
    {
        std::cout << *it->next() << " ";
    }
    std::cout << "]" << std::endl;
}