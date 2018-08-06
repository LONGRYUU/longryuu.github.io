#include<stack>
#include<queue>
#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

class Tree
{
public:
    char c;
    Tree *left;
    Tree *right;
    Tree(char x){
        c = x;
        left = NULL;
        right = NULL;
    }
};

int find_char(char *str, char c)
{
    for(int i = 0; i <strlen(str); i++)
    {
        if(str[i] == c) return i;
    }
    return -1;
}

Tree *buildTree(char *pre, char *mid, int& cur)
{
    if(strlen(mid) == 0 || cur == strlen(pre)) return NULL;
    Tree *root = new Tree(pre[cur]);
    int root_pos = find_char(mid, pre[cur]);
    cur++;
    char mid_left[27];
    char mid_right[27];
    strncpy(mid_left, mid, root_pos);
    mid_left[root_pos] = '\0';
    strncpy(mid_right, mid + root_pos + 1, strlen(mid) - root_pos - 1);
    mid_right[strlen(mid) - root_pos - 1] = '\0';
    root->left = buildTree(pre, mid_left, cur);
    root->right = buildTree(pre, mid_right, cur);
    return root;
}

void Past_Traverse(Tree *root)
{
    if(root == NULL) return;
    Past_Traverse(root->left);
    Past_Traverse(root->right);
    printf("%c", root->c);
}
int main()
{
    char pre[27];
    char mid[27];
    scanf("%s", pre);
    scanf("%s", mid);
    int start = 0;
    Tree* root = buildTree(pre, mid, start);
    Past_Traverse(root);
    return 0;
}
