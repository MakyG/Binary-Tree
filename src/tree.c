/**
 * @file       tree.c
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Source file for binary tree
 * **********************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

#include "tree.h"
#include "mymalloc.h"

/* Local functions declaration ---------------------------------------------- */
/**
 * @brief print_postorder   Recursive function that calls itself with the left
 * node and then right node and then processes node that is called with the
 * function that is passed in argument
 * @param node  Pointer at node
 * @param proc  function that is called by each node
 */
void print_postorder(TreeNode* node, TreeNodeProc proc);

/**
 * @brief print_inorder Recursive function that calls itself with the left node
 * first, then processes the current node with the function that is passed in
 * argument and then it calls itself with the right node
 * @param node  Pointer at node
 * @param proc  function that is called by each node
 */
void print_inorder(TreeNode* node, TreeNodeProc proc);

/**
 * @brief print_preorder    Recursive function that processes node first, then
 * it calls itself with the left and then right node
 * @param node  Pointer at node
 * @param proc  function that is called by each node
 */
void print_preorder(TreeNode* node, TreeNodeProc proc);

bool Tree_Init(Tree* const root) {
    if (!root)
        return false;

    root->root = NULL;
    root->itemsCount = 0;
    return true;
}

void Delete_Recursive(TreeNode* node){
    if (!node)
        return;

    if (node->left)
        Delete_Recursive(node->left);

    if (node->right)
        Delete_Recursive(node->right);

    myFree(node);
    node = NULL;
}

void Tree_Clear(Tree* const root) {
    if (!root)
        return;

    //Uvolni pamět pro všechny nodes
    Delete_Recursive(root->root);

    //nastav itemsCount & root na NULL
    root->root = NULL;
    root->itemsCount = 0;
}

bool Tree_Insert(Tree* const root, const Data_t data) {
    if (!root)
        return false;

    if (root->root) {//root již existuje
        //Najdi pozici pro vložení nového nodu
        TreeNode* node = root->root;
        TreeNode* parent = NULL;
        int result = 0;

        while (node) {
            result = Data_Cmp(&data, &node->data);
            parent = node;

            if (result < 0) {
                node = node->left;
            } else if (result > 0) {
                node = node->right;
            }
            else return false; //node již existuje
        }

        if (!parent)
            return false;//nemáme kde vložit node

        TreeNode* new_node = myMalloc(sizeof(TreeNode));
        if (!new_node)
            return false;//nepovedlo se vytvořit nový node/allocovat pro něj místo

        new_node->data = data;
        new_node->left = new_node->right = NULL;

        if (result < 0)
            parent->left = new_node;
        else if (result > 0)
            parent->right = new_node;
        else
            return false;

        root->itemsCount++;
    }
    else { //root ještě neexistuje
        TreeNode* new_node = myMalloc(sizeof(TreeNode));
        if (!new_node)
            return false;

        new_node->data = data;
        new_node->left = new_node->right = NULL;
        root->root = new_node;
        root->itemsCount++;
    }
    return true;
}

TreeNode* Find_And_Delete(TreeNode* node, const Data_t data) {
    if (!node)
        return NULL;

    int result =  Data_Cmp(&data, &node->data);
    if (result < 0)
        node->left = Find_And_Delete(node->left, data);
    else if (result > 0)
        node->right = Find_And_Delete(node->right, data);
    else {
        if (node->left && !node->right) {
            TreeNode* temp = node;
            node = node->left;
            myFree(temp);

            return node;
        }
        //existuje jen pravé dítě
        else if (node->right && !node->left) {
            TreeNode* temp = node;
            node = node->right;
            myFree(temp);

            return node;
        }
        //neexistuje žádné dítě
        else if (!node->left && !node->right){
            myFree(node);
            node = NULL;

            return node;
        }
    }
    return node;
}

void Tree_Delete(Tree* const root, const Data_t data) {
    if (!root)
        return;

    if (!root->root)
        return;

    TreeNode* findNode = root->root;
    TreeNode* node = NULL;
    TreeNode* PreviousNode = findNode;
    int left = 0;
    int result = 0;
    bool found = false;

    while (findNode) {
        result = Data_Cmp(&data, &findNode->data);
        node = findNode;
        if (result < 0) {
            left = 1;
            findNode = findNode->left;
        } else if (result > 0) {
            left = 0;
            findNode = findNode->right;
        }
        else if (result == 0){
            found = true;
            break;
        }

        if (findNode)
            PreviousNode = node;
    }

    if (!node || !found)
        return;

    //obě děti existují, přepiš rodiče největším dítětem z leva
    if (node->right && node->left) {
        //najdi největší dítě z levé strany
        TreeNode* max = node->left;

        while(max->right) {
            max = max->right;
        }

        //přepiš data z největšího dítěte z leva na toto místo
        node->data = max->data;
        //Vymaž největší dítě z levé strany
        node->left = Find_And_Delete(node->left, max->data);

        root->itemsCount--;
    }
    //existuje jen levé dítě
    else if (node->left && !node->right) {
        TreeNode* temp = node;
        node = node->left;
        myFree(temp);

        if (left)
            PreviousNode->left = node;
        else
            PreviousNode->right = node;

        root->itemsCount--;
    }
    //existuje jen pravé dítě
    else if (node->right && !node->left) {
        TreeNode* temp = node;
        node = node->right;
        myFree(temp);

        if (left)
            PreviousNode->left = node;
        else
            PreviousNode->right = node;

        root->itemsCount--;
    }
    //neexistuje žádné dítě
    else if (!node->left && !node->right){
        myFree(node);
        node = NULL;
        if (left)
            PreviousNode->left = node;
        else
            PreviousNode->right = node;

        root->itemsCount--;
    }

}

const Data_t* Tree_Get_Data(const TreeNode* const node) {
  return node ? &node->data : NULL;
}

TreeNode* Tree_Find_Node(Tree root, const Data_t data) {
    TreeNode* node = root.root;
    int result = 0;

    while (node) {
        result = Data_Cmp(&data, &node->data);

        if (result < 0) {
            node = node->left;
        } else if (result > 0) {
            node = node->right;
        }
        else return node;
    }
    return NULL;
}

size_t Tree_Get_Count(Tree root) {
  return root.itemsCount;
}

void Tree_Process(Tree root, TreeNodeProc proc, TreeProcessMode mode) {
    if (mode ==procPREORDER)
        print_preorder(root.root, proc);
    else if (mode == procINORDER)
        print_inorder(root.root, proc);
    else if (mode == procPOSTORDER)
        print_postorder(root.root, proc);
}

void print_preorder(TreeNode* node, TreeNodeProc proc) {
    if (!node)
        return;
    proc(node);
    print_preorder(node->left, proc);
    print_preorder(node->right, proc);
}

void print_inorder(TreeNode* node, TreeNodeProc proc) {
    if (!node)
        return;
    print_inorder(node->left, proc);
    proc(node);
    print_inorder(node->right, proc);
}

void print_postorder(TreeNode* node, TreeNodeProc proc) {
    if (!node)
        return;
    print_postorder(node->left, proc);
    print_postorder(node->right, proc);
    proc(node);
}

void Tree_Print(TreeNode* node, TreeNode* previous, int spaces) {
    // kontrola, zda byly přenány ukazatele
    if (node == NULL || previous == NULL) return;

    // rekurzivní výpis bin. stromu
    spaces += 6;
    Tree_Print(node->right, node, spaces);
    printf("\n");
    for (int i = 6; i < spaces; i++) printf(" ");
    if (previous == node) {
        printf("---%s", node->data.name);
    } else if (node == previous->left) {
        printf("|\n");
        for (int i = 6; i < spaces; i++) printf(" ");
        printf("---%s", node->data.name);
    } else {
        printf("---%s\n", node->data.name);
        for (int i = 6; i < spaces; i++) printf(" ");
        printf("|");
    }
    Tree_Print(node->left, node, spaces);
}
