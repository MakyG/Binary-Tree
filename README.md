# Binární strom #
Naprogramujte binární strom.

## Vizualizace ##
Pro lepší pochopení funkce binárního stromu navštivte [tento odkaz](https://www.cs.usfca.edu/~galles/visualization/BST.html). Je možné vidět, jak jsou jednotlivé operace binárního stromu vykonávány. Nejsložitějším úkolem je pravděpodobně mazání a na lepší pochopení zkuste zadat následující strom. `F-B-S-A-D-L`
![relative Tree](doc/tree.png)

Zkuste postupně zkusit smazat uzel `F`, `D`, `S` a `A`. Tyto čtyři možnosti mohou nastat, když budete mazat uzel ve vaší implementaci, takže je musíte vyřešit. 

Aby bylo lépe vidět, jak probíhá mazání uzlu, který má oba podstromy, zkuste si do původního stromu přidat ještě uzely `C` a `E`, a opět proveďte smazání uzlu `F` a poté `E`.
![relative Tree extended](doc/tree2.png)

## Vaším úkolem je implementace následujících funkcí: ##

Funkce lze řešit i rekurzivně za pomocí pomocných funkcí.

Pravidla pro vkládání/mazání ze stromu lze nalézt na přednáškách o seznamu.

- **Tree_Init** - Inicializuje první uzel stromu na NULL a nastaví počet uzlů na 0.

- **Tree_Clear** - Vymaže všechny uzly stromu a počet uzlů nastaví na 0.

- **Tree_Insert** - Vloží uzel do stromu dle pravidel, na porovnání uzlů použijte funkce Data_Cmp

- **Tree_Delete** - Smaže uzel ze stromu dle pravidel

- **Tree_Get_Data** - Vrátí data uzlu.

- **Tree_Find_Node** - Vrátí ukazatel na uzel, který drží daná data.

- **Tree_Get_Count** - Funkce, která vrací počet uzlů ve stromu

- **Tree_Process** - Zpracuje každý uzel stromu pomocí funkce specifikované ukazatelem "proc". Průchod stromem může být trojí: PREORDER, INORDER a POSTORDER.


# Binary Tree #
Implement functions listed below for binary tree.

## Visualisation ##
For better understanding of binary tree visit [this link](https://www.cs.usfca.edu/~galles/visualization/BST.html). You can see the animations how are the binary operations are done.
The most difficult operation in a tree is propably deleting for a better undestanding try to insert following nodes in tree `F`, `B`, `S`, `A`, `D`, `L`
![relative Tree](doc/tree.png)


Try to remove node `F`, `D`, `S` and `A`. Those are four possible scenarios that can happen, when you're going to delete node, so you have to make sure that those scenarios are working properly with your tree.

For better visualisation how is the node being deleted in a tree with both sub-trees, try to add to the original tree the following nodes `C` a `E` and delete node `F` and after that node `E`.
![relative Tree extended](doc/tree2.png)

## Implement those functions for binary tree: ##


Note: functions can be implemented recursively by using auxiliary functions.

The rules for insertion and deletions nodes from a tree can be found in lecture about list.

- **Tree_Init** - Initializes first node to NULL and sets the count of an items in a tree to 0.

- **Tree_Clear** - Deletes every node from a tree and sets the count of items in a tree to 0.

- **Tree_Insert** - Inserts node to a tree following the rules for binary tree insertion. For comparing the data from nodes use Data_Cmp

- **Tree_Delete** - Deletes node from a tree following the rules for binary tree node deletion.

- **Tree_Get_Data** - Returns the data from a node.

- **Tree_Find_Node** - Returns pointer at node, which is holding specific data

- **Tree_Get_Count** - Function, that returns the amount of items in a tree

- **Tree_Process** - Processes every node from a tree with function specified by pointer "proc". There are 3 ways of processing the tree: PREORDER, INORDER a POSTORDER

### Ukázka běhu programu/Example of program: ###

```
Tree v1.1
----------

1 - tree_init()
2 - tree_clear()
3 - tree_insert()
4 - tree_delete()
5 - tree_find_node()
6 - tree_get_node_count()
7 - tree_proces()
M - MENU
P - Print the tree
E - END
Your choice: Your choice: 7
Tree is NOT initialized!

Your choice: Your choice: 1
Tree initialized successfuly.

Your choice: Your choice: 7
Process:
1 - preorder
2 - inorder
3 - postorder
Your choice1


Your choice: Your choice: 3
Insert data to a node:
Please, enter a name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 296 bytes, memory allocated 296 bytes

Your choice: Your choice: 3
Insert data to a node:
Please, enter a name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 296 bytes, memory allocated 592 bytes

Your choice: Your choice: 3
Insert data to a node:
Please, enter a name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 296 bytes, memory allocated 888 bytes

Your choice: Your choice: 6
The number of nodes in a tree: 3

Your choice: Your choice: 7
Process:
1 - preorder
2 - inorder
3 - postorder
Your choice2

Name=Anna, age=30.0, weight=60.0, height=160.0
 | L -> NULL | R -> NULL
Name=Franta, age=50.0, weight=80.0, height=180.0
 | L -> Name=Anna, age=30.0, weight=60.0, height=160.0
 | R -> Name=Xaver, age=60.0, weight=70.0, height=175.0

Name=Xaver, age=60.0, weight=70.0, height=175.0
 | L -> NULL | R -> NULL

Your choice: Your choice: 4
Insert data to delete:
Please, enter a name: Enter age, weight and height (separated by Enter):
myFree: releasing 296 bytes, memory allocated 592 bytes

Your choice: Your choice: 7
Process:
1 - preorder
2 - inorder
3 - postorder
Your choice2

Name=Anna, age=30.0, weight=60.0, height=160.0
 | L -> NULL | R -> Name=Xaver, age=60.0, weight=70.0, height=175.0

Name=Xaver, age=60.0, weight=70.0, height=175.0
 | L -> NULL | R -> NULL

Your choice: Your choice: 5
Insert data to search:
Please, enter a name: Enter age, weight and height (separated by Enter):
Data were not found in a tree.

Your choice: Your choice: 5
Insert data to search:
Please, enter a name: Enter age, weight and height (separated by Enter):
Data were found in a tree.

Your choice: Your choice: 2
myFree: releasing 296 bytes, memory allocated 296 bytes
myFree: releasing 296 bytes, memory allocated 0 bytes
The nodes from a tree were deleted.

Your choice: Your choice: E
END.
```
