/**
 * @file       tests.c
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Testing functions for a binary tree.
 * **************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU. All rights reserved.
 */

/* Private includes -------------------------------------------------------- */
#include <inttypes.h>
#include <string.h>

#include "../src/mymalloc.h"
#include "../src/tree.h"
#include "minunit.h"

////////////////////////////// IMPORTANT //////////////////////////////////////
/////////// Source repository: https://github.com/siu/minunit /////////////////
/////////// For more info consult with this page //////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* Global variables -------------------------------------------------------- */
int gIndex = 0;
int gHeight[0x400];

/* Private function -------------------------------------------------------- */
void ProcessNode(TreeNode* node) {
  gHeight[gIndex] = node->data.height;
  gIndex++;
}

/* Test implementation ----------------------------------------------------- */
MU_TEST(test_tree_init) {
  Tree tree;
  mu_assert(Tree_Init(&tree),
            "Tree wasnt initialized. Expected true, got false.");
  mu_assert(tree.root == NULL, "The root should be NULL");
  mu_assert_int_eq(0, (int)tree.itemsCount);
}

MU_TEST(test_tree_init_nulls) {
  mu_assert(
      !Tree_Init(NULL),
      "Initialization with NULL pointer expected false, got true instead.");
}

MU_TEST(test_tree_insert) {
  Tree tree = {NULL, 0};

  {
    Data_t testingData = {.name = "John"};

    mu_assert(Tree_Insert(&tree, testingData),
              "Tree insert failed, expected true, got false.");
    mu_assert_int_eq(
        0, memcmp(&testingData, &tree.root->data, sizeof(testingData)));
  }
  {
    Data_t testingData = {.name = "Anna"};

    mu_assert(Tree_Insert(&tree, testingData),
              "Tree insert failed, expected true, got false.");
    mu_assert_int_eq(
        0, memcmp(&testingData, &tree.root->left->data, sizeof(testingData)));
  }
  {
    Data_t testingData = {.name = "Peter"};

    mu_assert(Tree_Insert(&tree, testingData),
              "Tree insert failed, expected true, got false.");
    mu_assert_int_eq(
        0, memcmp(&testingData, &tree.root->right->data, sizeof(testingData)));
  }

  mu_assert_int_eq(3, tree.itemsCount);
  myFree(tree.root->left);
  myFree(tree.root->right);
  myFree(tree.root);
}

MU_TEST(test_tree_insert_same_data) {
  Tree tree = {NULL, 0};
  {
    Data_t testingData = {.name = "John"};

    mu_assert(Tree_Insert(&tree, testingData),
              "Tree insert failed, expected true, got false.");
    mu_assert_int_eq(
        0, memcmp(&testingData, &tree.root->data, sizeof(testingData)));
  }
  {
    Data_t testingData = {.name = "John"};

    mu_assert(!Tree_Insert(&tree, testingData),
              "Tree insert failed, expected true, got false.");
  }
}

MU_TEST(test_tree_insert_nulls) {
  Data_t testData = {.name = "Franz"};
  mu_assert(!Tree_Insert(NULL, testData),
            "Tree_Insert with NULL pointer to tree expected false, got true "
            "instead.");
}

MU_TEST(test_tree_delete_nulls) {
  Data_t testingData = {.name = "John"};
  Tree_Delete(NULL, testingData);
}

MU_TEST(test_tree_delete_non_existing_node) {
  Tree tree = {NULL, 0};
  {
    Data_t testingData = {.name = "Luke"};
    Tree_Insert(&tree, testingData);
  }
  Data_t testingData = {.name = "Peter"};
  Tree_Delete(&tree, testingData);
  mu_assert_int_eq(1, tree.itemsCount);
}

MU_TEST(test_tree_delete_empty_tree) {
  Tree tree = {NULL, 0};
  Data_t testingData = {.name = "Peter"};
  Tree_Delete(&tree, testingData);
  mu_assert_int_eq(0, (int)tree.itemsCount);
}

MU_TEST(test_tree_delete) {
  Tree tree = {NULL, 0};
  Data_t data[8] = {{.name = "Franz", .height = 167}, {"Bianca", .height = 158},
                    {"Sally", .height = 174},         {"Aaron", .height = 179},
                    {"Daisy", .height = 164},         {"Luke", .height = 184},
                    {"Caroline", .height = 169},      {"Ethan", .height = 198}};

  for (unsigned int i = 0; i < 8; i++) {
    mu_assert(Tree_Insert(&tree, data[i]), "Tree insert failed");
  }

  /* Delete with 2 childrens ----------------------------------------------- */
  Tree_Delete(&tree, data[0]);
  mu_assert_string_eq(data[7].name, tree.root->data.name);
  mu_assert_int_eq(7, (int)tree.itemsCount);

  {
    gIndex = 0;
    Tree_Process(tree, ProcessNode, procINORDER);
    int inOrder[] = {179, 158, 169, 164, 198, 184, 174};
    mu_assert_int_eq(0, memcmp(inOrder, gHeight, sizeof(inOrder)));
  }
  /* Delete with 1 child --------------------------------------------------- */
  {
    gIndex = 0;
    Tree_Delete(&tree, data[4]);
    mu_assert_int_eq(6, (int)tree.itemsCount);
    Tree_Process(tree, ProcessNode, procINORDER);
    int inOrder[] = {179, 158, 169, 198, 184, 174};
    mu_assert_int_eq(0, memcmp(inOrder, gHeight, sizeof(inOrder)));
  }
  /* Delete with no child -------------------------------------------------- */
  {
    gIndex = 0;
    Tree_Delete(&tree, data[6]);
    mu_assert_int_eq(5, (int)tree.itemsCount);
    Tree_Process(tree, ProcessNode, procINORDER);
    int inOrder[] = {179, 158, 198, 184, 174};
    mu_assert_int_eq(0, memcmp(inOrder, gHeight, sizeof(inOrder)));
  }

  /* Delete first node ----------------------------------------------------- */
  {
    gIndex = 0;
    Tree_Delete(&tree, data[7]);
    mu_assert_int_eq(4, (int)tree.itemsCount);
    Tree_Process(tree, ProcessNode, procINORDER);
    int inOrder[] = {179, 158, 184, 174};
    mu_assert_int_eq(0, memcmp(inOrder, gHeight, sizeof(inOrder)));
  }
  /* Testing NULLs --------------------------------------------------------- */
  { Tree_Delete(NULL, data[0]); }

  Tree_Clear(&tree);
}

MU_TEST(test_tree_get_data) {
  Tree tree = {NULL, 0};
  {
    Data_t testingData = {.name = "John"};
    Tree_Insert(&tree, testingData);
  }

  Data_t testingData = {.name = "Luke"};
  Tree_Insert(&tree, testingData);

  mu_assert_int_eq(
      0, memcmp(&testingData, &tree.root->right->data, sizeof(testingData)));

  myFree(tree.root->left);
  myFree(tree.root);
}

MU_TEST(test_tree_get_data_nulls) {
  mu_assert(Tree_Get_Data(NULL) == NULL,
            "Tree_Get_Data should return NULL if NULL is passed as parameter.");
}

MU_TEST(test_tree_clear) {
  Tree tree = {NULL, 0};
  {
    Data_t testingData = {.name = "John"};
    Tree_Insert(&tree, testingData);
  }
  {
    Data_t testingData = {.name = "Luke"};
    Tree_Insert(&tree, testingData);
  }
  {
    Data_t testingData = {.name = "Sarah"};
    Tree_Insert(&tree, testingData);
  }
  {
    Data_t testingData = {.name = "Mike"};
    Tree_Insert(&tree, testingData);
  }

  Tree_Clear(&tree);

  mu_assert_int_eq(0, tree.itemsCount);
  mu_assert(tree.root == NULL, "Root should be NULL after Tree_Clear.");
}

MU_TEST(test_tree_clear_nulls) { Tree_Clear(NULL); }

MU_TEST(test_tree_find_node) {
  Tree tree = {NULL, 0};
  {
    Data_t testingData = {.name = "John"};
    Tree_Insert(&tree, testingData);
  }
  {
    Data_t testingData = {.name = "Luke"};
    Tree_Insert(&tree, testingData);
  }
  {
    Data_t testingData = {.name = "Sarah"};
    Tree_Insert(&tree, testingData);
  }
  {
    Data_t testingData = {.name = "Mike"};
    Tree_Insert(&tree, testingData);
  }

  {
    TreeNode* node;
    Data_t testingData = {.name = "John"};
    node = Tree_Find_Node(tree, testingData);
    mu_assert(node, "Value should be found in a tree but it was not.");
  }
  {
    TreeNode* node;
    Data_t testingData = {.name = "Kayle"};
    node = Tree_Find_Node(tree, testingData);
    mu_assert(!node, "Value should NOT be found in a tree but it was.");
  }

  Tree_Clear(&tree);
}

MU_TEST(test_tree_process) {
  Tree tree;
  Tree_Init(&tree);
  {
    Data_t data = {.name = "Petr", .height = 10};
    Tree_Insert(&tree, data);
  }
  {
    Data_t data = {.name = "Tomas", .height = 20};
    Tree_Insert(&tree, data);
  }
  {
    Data_t data = {.name = "Adam", .height = 30};
    Tree_Insert(&tree, data);
  }
  {
    Data_t data = {.name = "Jiri", .height = 40};
    Tree_Insert(&tree, data);
  }
  {
    Data_t data = {.name = "Roman", .height = 50};
    Tree_Insert(&tree, data);
  }
  {
    Data_t data = {.name = "Michal", .height = 60};
    Tree_Insert(&tree, data);
  }

  Tree_Process(tree, ProcessNode, procINORDER);
  int inOrder[] = {30, 40, 60, 10, 50, 20};
  mu_assert_int_eq(0, memcmp(inOrder, gHeight, sizeof(inOrder)));

  gIndex = 0;
  Tree_Process(tree, ProcessNode, procPOSTORDER);
  int postOrder[] = {60, 40, 30, 50, 20, 10};
  mu_assert_int_eq(0, memcmp(postOrder, gHeight, sizeof(postOrder)));

  gIndex = 0;
  Tree_Process(tree, ProcessNode, procPREORDER);
  int preOrder[] = {10, 30, 40, 60, 20, 50};
  mu_assert_int_eq(0, memcmp(preOrder, gHeight, sizeof(preOrder)));

  Tree_Clear(&tree);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_tree_init);
  MU_RUN_TEST(test_tree_init_nulls);
  MU_RUN_TEST(test_tree_insert);
  MU_RUN_TEST(test_tree_insert_same_data);
  MU_RUN_TEST(test_tree_insert_nulls);
  MU_RUN_TEST(test_tree_process);
  MU_RUN_TEST(test_tree_delete_nulls);
  MU_RUN_TEST(test_tree_delete_non_existing_node);
  MU_RUN_TEST(test_tree_delete_empty_tree);
  MU_RUN_TEST(test_tree_delete);
  MU_RUN_TEST(test_tree_get_data);
  MU_RUN_TEST(test_tree_get_data_nulls);
  MU_RUN_TEST(test_tree_clear);
  MU_RUN_TEST(test_tree_clear_nulls);
  MU_RUN_TEST(test_tree_find_node);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();

  return 0;
}
