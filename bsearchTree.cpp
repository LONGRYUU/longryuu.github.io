#include<stack>
#include<queue>
#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

class Tree
{
public:
    int value;
    Tree *left;
    Tree *right;
    Tree *parent;
    Tree(int x)
    {
        value = x;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

void insert_node(Tree* &root, int x, Tree *parent)
{
    if(root == NULL)
    {
        root = new Tree(x);
        root->parent = parent;
        return;
    }
    if(x <= root->value)
    {
        insert_node(root->left, x, root);
    }
    else
    {
        insert_node(root->right, x, root);
    }
}

void midTraverse(Tree *root)
{
    if(root == NULL)return;
    midTraverse(root->left);
    printf("%d ", root->value);
    midTraverse(root->right);
}

Tree* buildTree(Tree *root, int x, Tree *parent)
{
    if(root == NULL)
    {
        Tree *node = new Tree(x);
        node->parent = parent;
        return node;
    }
    if(x <= root->value)
        root->left = buildTree(root->left, x, root);
    else root->right = buildTree(root->right, x, root);
    return root;
}

Tree* find_x(Tree *root, int x)
{
    if(root == NULL) return NULL;
    if(x == root->value) return root;
    if(x < root->value) return find_x(root->left, x);
    else return find_x(root->right, x);
}

void deleteNode(Tree* &root, int x)
{
    Tree* node = find_x(root, x);
    if(node == NULL) return;
    if(node->left == NULL && node->right == NULL)
    {
        if(node == root) root = NULL;
        else if(node == node->parent->left) node->parent->left = NULL;
        else node->parent->right = NULL;
    }
    else if(node->left == NULL)
    {
        if(node == root)
        {
            root = node->right;
            root->right = NULL;
        }
        else if(node == node->parent->left)
        {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        }
        else if(node == node->parent->right)
        {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
    }
    else if(node->right == NULL)
    {
        if(node == root)
        {
            root = node->left;
            root->parent = NULL;
        }
        else if(node == node->parent->left)
        {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        }
        else if(node == node->parent->right)
        {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        }
    }
    else
    {
        Tree *cur = node->right;
        Tree *next = NULL;
        while(true)
        {
            next = cur->left;
            if(next == NULL) break;
        }
        node->value = cur->value;
        cur->parent->left = NULL;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int num[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    Tree *root = NULL;
    for(int i = 0; i < n; i++)
        root = buildTree(root, num[i], NULL);
    for(int i = 0; i < n; i++)
    {
        deleteNode(root, num[(i + 1)%5]);
        midTraverse(root);
    }
    return 0;
}
