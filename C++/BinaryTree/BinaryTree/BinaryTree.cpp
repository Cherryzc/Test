// BinaryTree.cpp: 定义应用程序的入口点。
//

#include "BinaryTree.h"

#include <queue>
#include <stack>
#include <bitset>
using namespace std;


struct TreeNode
{
	int nData;
	TreeNode* left;
	TreeNode* right;

	TreeNode() : nData(0), left(nullptr), right(nullptr)
	{

	}
};

//前序 中序 后序 遍历 的递归方式
void PreOrder(const TreeNode* root)
{
    if (root == NULL)                 //若结点为空
    {
        return;
    }
    printf("%d ", root->nData);        //输出根节点的值
    PreOrder(root->left);             //前序访问左子树
    PreOrder(root->right);            //前序访问右子树
}

void InOrder(const TreeNode* root)
{
    if (root == NULL)              //判断节点是否为空
    {
        return;
    }
    InOrder(root->left);           //中序遍历左子树
    printf("%d ", root->nData);     //访问节点值
    InOrder(root->right);          //中序遍历右子树
}
void PostOrder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->nData);
}

// 层序遍历
// 层序遍历是比较接近人的思维方式的一种遍历方法，将二叉树的每一层分别遍历，直到最后的叶子节点被全部遍历完，这里要用到的辅助数据结构是队列，队列具有先进先出的性质。
void LevelOrder(TreeNode* root)
{
    std::queue<TreeNode*> q;
    TreeNode* front;

    if (root == NULL)return;

    q.push(root);

    while (!q.empty())
    {
        front = q.front();
        q.pop();

        if (front->left)
            q.push(front->left);

        if (front->right)
            q.push(front->right);

        printf("%d ", front->nData);
    }
}


// 递归方法求最大深度(其实就是求根节点高度的代码) 。非递归法可以用层序遍历，每遍历一层，就让maxdepth + 1，当遍历终止时，返回maxdepth即可。
// 1.递归函数的返回值和参数：返回值为当前节点的最大深度，参数为当前节点
// 2.递归函数的单层逻辑：当前节点的最大深度 = 1 + 左子树或右子树的最大深度
// 3.递归函数的终止条件：当前节点为空时，当前节点最大深度为0
int maxDepth(TreeNode* root) {

    //递归终止条件
    if (root == nullptr) return 0;

    //单层递归逻辑
    int leftdepth = maxDepth(root->left); 
    int rightdepth = maxDepth(root->right); 
    return 1 + max(leftdepth, rightdepth);
}



// 前序 中序 后序 遍历 的非递归方式

// 在理解非递归方法的时候要重点理解栈中保存的元素的共同点是什么，在前序访问中，栈中元素都是自己和自己的左孩子都访问过了，而右孩子还没有访问到的节点，
void PreOrderLoop(TreeNode* root)
{
    std::stack<TreeNode*> s;
    TreeNode* cur, * top;
    cur = root;
    while (cur != NULL || !s.empty())
    {
        while (cur != NULL)
        {
            printf("%d ", cur->nData);
            s.push(cur);
            cur = cur->left;
        }

        top = s.top();
        s.pop();

        cur = top->right;
    }
}

// 中序访问的非递归写法和前序一样，都要用到一个栈来辅助存储，不一样的地方在于前序访问时，栈中保存的元素是右子树还没有被访问到的节点的地址，而中序访问时栈中保存的元素是节点自身和它的右子树都没有被访问到的节点地址。
void InOrderLoop(TreeNode* root)
{
    std::stack<TreeNode*> s;
    TreeNode* cur;
    cur = root;
    while (cur != NULL || !s.empty())
    {
        while (cur != NULL)
        {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();
        printf("%d ", cur->nData);

        cur = cur->right;
    }
}

// 后序遍历的非递归同样要借助一个栈来保存元素，栈中保存的元素是它的右子树和自身都没有被遍历到的节点，与中序遍历不同的是先访问右子树，在回来的时候再输出根节点的值。
// 需要多一个last指针指向上一次访问到的节点，用来确认是从根节点的左子树返回的还是从右子树返回的。
void PostOrderLoop(TreeNode* root)
{
    std::stack<TreeNode*> s;
    TreeNode* cur, * top, * last = NULL;
    cur = root;
    while (cur != NULL || !s.empty())
    {
        while (cur != NULL)
        {
            s.push(cur);
            cur = cur->left;
        }

        top = s.top();

        if (top->right == NULL || top->right == last) 
        {
            s.pop();
            printf("%d ", top->nData);
            last = top;
        }
        else
        {
            cur = top->right;
        }
    }
}


int main()
{
    bitset<4> b1;
	cout << "Hello CMake." << endl;
	return 0;
}
