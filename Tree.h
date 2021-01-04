#ifndef _TREE_H_
#define _TREE_H_

#include <stack>
#include <string>

template <class T>
class Tree
{
public:
    class TreeNode
    {
    public:
        TreeNode(T data);
        void visit();
        T data;
        bool traveled;
        TreeNode *leftChild;
        TreeNode *rightChild;
    };

    class Iterator
    {
    public:
        Iterator(Tree<T>* tree, TreeNode *curNode);
        virtual T *next() = 0;
        virtual bool hasNext() = 0;
    protected:
        Tree<T>* _tree;
        TreeNode *_curNode;
        std::stack<TreeNode*> _s;
    };

    class InorderIterator : public Iterator
    {
        typedef Iterator SUPER;
    public:
        InorderIterator(Tree<T>* tree, TreeNode *curNode);
        T *next() override;
        bool hasNext() override;
    };

    class PreorderIterator : public Iterator
    {
        typedef Iterator SUPER;
    public:
        PreorderIterator(Tree<T>* tree, TreeNode *curNode);
        T *next() override;
        bool hasNext() override;

    private:
        Tree<T>::TreeNode *_curNode;
        std::stack<Tree<T>::TreeNode*> _s;
    };

    class PostorderIterator : public Iterator
    {
        typedef Iterator SUPER;
    public:
        PostorderIterator(Tree<T>* tree, TreeNode *curNode);
        T *next() override;
        bool hasNext() override;

    private:
        TreeNode *_curNode;
        std::stack<TreeNode*> _s;
    };

    Tree(T val);
    Tree(T val, std::string order);
    virtual void insert(T val);
    Iterator* getIterator();
    void changeIterator(std::string order);
    void inorder();
    void preorder();
    void postorder();
    void bfs();

private:
    TreeNode *_root;
    Iterator *_it;
    int _size;
    int _count;
};

#endif