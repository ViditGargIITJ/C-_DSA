// Code Goes Here
#include <iostream>
using namespace std;
#include <string>

class Node
{
public:
    int data;
    Node *right;
    Node *left;
    Node(int data)
    {
        this->data = data;
        right = NULL;
        left = NULL;
    }
};
class stack
{
public:
    int top;
    Node **inwitoutComma;
    stack()
    {
        top = -1;
        inwitoutComma = new Node *[100000];
    }
    void push(Node *n)
    {
        inwitoutComma[top + 1] = n;
        top++;
    }
    void pop()
    {
        if (top == -1)
        {
            // cout<<"stack is empty"<<endl;
            return;
        }
        top--;
    }
    Node *peek()
    {
        return inwitoutComma[top];
    }
    int size()
    {
        return top + 1;
    }
    int isEmpty()
    {
        if (top == -1)
        {
            return 1;
        }
        return 0;
    }
};
class BST
{
public:
    Node *root;
    BST()
    {
        root = NULL;
    }

private:
    Node *insertHelp(Node *root, int n)
    {
        if (root == NULL)
        {
            return new Node(n);
        }
        if (n > root->data)
        {
            root->right = insertHelp(root->right, n);
        }
        else
        {
            root->left = insertHelp(root->left, n);
        }
        return root;
    }
    void inorderPrint(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorderPrint(root->left);
        cout << root->data << " ";
        inorderPrint(root->right);
        return;
    }
    string pathTOxhelp(Node *root, int x, string s)
    {
        if (root == NULL)
            s = "";
        else if (root->data == x)
            s = " " + to_string(x);
        else if (x > root->data)
            s = to_string(root->data) + " " + pathTOxhelp(root->right, x, s);
        else
            s = to_string(root->data) + " " + pathTOxhelp(root->left, x, s);
        return s;
    }
    bool findhelp(Node *root, int x)
    {
        if (root == NULL)
            return false;
        else if (root->data == x)
            return true;
        else if (x > root->data)
            return findhelp(root->right, x);
        else
            return findhelp(root->left, x);
    }
    int sum(Node *root)
    {
        if (root == NULL || root->left == NULL)
            return 0;
        if (root->left->left == NULL && root->left->right == NULL)
            return root->left->data + sum(root->right);
        return sum(root->left) + sum(root->right);
        ;
    }
    int smallestGreater(Node *root, int x)
    {
        if (root == NULL)
            return 10000;
        if (x > root->data)
            return smallestGreater(root->right, x);
        else
            return min(root->data, smallestGreater(root->left, x));
    }
    int lowestCommonAncestor(Node *root, int x, int y)
    {
        if (x > root->data && y > root->data)
            return lowestCommonAncestor(root->right, x, y);
        else if (x < root->data && y < root->data)
            return lowestCommonAncestor(root->left, x, y);
        else
            return root->data;
    }
    void preorderIterative(Node *root)
    {
        stack s;
        s.push(root);
        cout << root->data << " ";
        while (s.size() != 0)
        {
            if (s.peek()->left != NULL)
            {
                Node *temp = s.peek();
                cout << s.peek()->left->data << " ";
                s.push(s.peek()->left);
                temp->left = NULL;
            }
            else
            {
                if (s.peek()->right == NULL)
                {
                    s.pop();
                }
                else
                {
                    Node *temp = s.peek();
                    s.pop();
                    s.push(temp->right);
                    cout << temp->right->data << " ";
                }
            }
        }
    }
    void preorderPrint(Node *root)
    {
        if (root == NULL)
            return;
        cout << root->data << " ";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
    bool isLeaf(Node *root)
    {
        if (root == NULL)
            return true;
        if (root->left == NULL && root->right == NULL)
            return true;
        return false;
    }
    Node *maximum(Node *root)
    {
        Node *it = root;
        while (it->right != NULL)
            it = it->right;
        return it;
    }
    Node *del(Node *root, int n)
    {
        if (n > root->data)
            root->right = del(root->right, n);
        else if (n < root->data)
            root->left = del(root->left, n);
        else if (root->data == n && root->left == NULL)
            return root->right;
        else if (root->data == n && isLeaf(root))
            return NULL;
        else
        {
            Node *temp = maximum(root->left);
            root->data = temp->data;
            temp->data = n;
        }
        return root;
    }

public:
    void insert(int n)
    {
        if (root == NULL)
        {
            root = new Node(n);
        }
        else
        {
            root = insertHelp(this->root, n);
        }
    }
    void inorder()
    {
        inorderPrint(this->root);
    }
    string pathTox(int x)
    {
        if (!find(x))
            return "-1";
        string s = "";
        s = pathTOxhelp(this->root, x, s);
        return s;
    }
    bool find(int x)
    {
        return findhelp(this->root, x);
    }
    void preorder()
    {
        preorderPrint(this->root);
    }
    void q2()
    {
        preorderIterative(this->root);
    }
    int q3()
    {
        return sum(this->root);
    }
    int q4(int n)
    {

        if (smallestGreater(this->root, n) == 10000)
            return -1;
        else
            return smallestGreater(this->root, n);
    }
    int q7(int x, int y)
    {
        return lowestCommonAncestor(this->root, x, y);
    }
    Node *remove(int n)
    {
        return del(this->root, n);
    }
};

int main()
{

    int n;
    int q;
    cin >> n;
    BST tree;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        tree.insert(x);
    }
    tree.q3();
}