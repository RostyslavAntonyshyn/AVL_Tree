// AVL-Tree Implementation //

#include <iostream>
#include <algorithm>

struct avl_node
{
    int data;
    struct avl_node *left;
    struct avl_node *right;
}*root;

class avlTree
{
    public:
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_rotation(avl_node *);
        avl_node *ll_rotation(avl_node *);
        avl_node *lr_rotation(avl_node *);
        avl_node *rl_rotation(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert(avl_node *, int );
        void print(avl_node *, int);
        void sum(avl_node *root, int &elem);
        avlTree()
        {
            root = 0;
        }
};

int main()
{
    int choice, item, sum;
    avlTree avl;
    while (1)
    {
        system("cls");
        std::cout << "\n---------------------" << std::endl;
        std::cout << "AVL Tree Implementation" << std::endl;
        std::cout << "\n---------------------" << std::endl;
        std::cout << "1.Insert Element into the tree" << std::endl;
        std::cout << "2.Display Balanced AVL Tree" << std::endl;
        std::cout << "3.Sum of elements" << std::endl;
        std::cout << "4.Exit" << std::endl;
        std::cout << "Enter your Choice: ";
        std::cin >> choice;
        switch(choice)
        {
        case 1:
            std::cout << "Enter value to be inserted: ";
            std::cin >> item;
            root = avl.insert(root, item);
            break;
        case 2:
            if (root == 0)
            {
                std::cout << "Tree is Empty" << std::endl;
                std::cin.get();
                std::cin.get();
                continue;
            }
            std::cout << "Balanced AVL Tree:" << std::endl;
            avl.print(root, 1);
            std::cin.get();
            std::cin.get();
            break;
        case 3:
            sum = 0;
            avl.sum(root, sum);
            std::cout << "Sum of elements: " << sum;
            std::cin.get();
            std::cin.get();
            break;
        case 4:
            exit(1);
            break;
        default:
            std::cout << "Wrong Choice" << std::endl;
        }
    }
    return 0;
}

// Height of AVL Tree

int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != 0)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = std::max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

// Height Difference

int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

// Right- Right Rotation

avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// Left- Left Rotation

avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

//Left - Right Rotation

avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}

// Right- Left Rotation

avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}

// Balancing AVL Tree

avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

// Insert Element into the tree

avl_node *avlTree::insert(avl_node *root, int value)
{
    if (root == 0)
    {
        root = new avl_node;
        root->data = value;
        root->left = 0;
        root->right = 0;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}

// Display AVL Tree

void avlTree::print(avl_node *ptr, int level)
{
    int i;
    if (ptr!=0)
    {
        print(ptr->right, level + 1);
        std::cout << std::endl;
        if (ptr == root)
        std::cout << "Tree: ";
        for (i = 0; i < level && ptr != root; i++)
            std::cout << "\t";
        std::cout << ptr->data;
        print(ptr->left, level + 1);
    }
}

void avlTree::sum(avl_node *root, int &elem)
{
    if (root != 0)
    {
        elem += root->data;
        sum(root->left, elem);
        sum(root->right, elem);
    }
}
