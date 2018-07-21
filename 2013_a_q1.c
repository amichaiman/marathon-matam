#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
} Node;

typedef struct{
    Node *head;
} List;

Node *addNode(Node *curNode, int key);
void printTree(Node *curNode);
int isOrderTree(Node *curNode);

int main(){
    List l;
    l.head = NULL;
    Node n1 = {75, NULL, NULL};
    Node n2 = {80, NULL, NULL};
    Node n3 = {196, NULL, NULL};
    Node n4 = {202, NULL, NULL};
    Node n5 = {70, &n1, &n2};
    Node n6 = {100, &n3, &n4};
    Node n7 = {10, &n5, &n6};
    l.head = &n7;

    printf("the tree is%s an ordered tree\n", isOrderTree(l.head) ? "" : " not");

    return 0;
}

/* input: tree
 * output: 1 if the following rules apply to all nodes:
 *          1) either 2 kids or none
 *          2) if node has kids:
 *              i) right node's key is bigger than left node's key
 *              ii) the node's key is smaller than the left node's key
 *        0 otherwise
 * */
int isOrderTree(Node *curNode){
    if (!curNode || (!curNode->left && !curNode->right)){
        return 1;
    }

    /*  if node has only one son or left son is bigger than right, or current node's key is smaller than
     *  the left node's key*/
    if (!curNode->left || !curNode->right
            || curNode->left->key > curNode->right->key // right son must be bigger
            || curNode->key > curNode->left->key){
        return 0;
    }

    /*  check if both kid trees are also ordered  */
    return isOrderTree(curNode->left) && isOrderTree(curNode->right);
}

Node *addNode(Node *curNode, int key) {
    if (!curNode){
        Node* newNode = (Node*) malloc (sizeof(Node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (key > curNode->key){
        curNode->right = addNode(curNode->right, key);
    } else {
        curNode->left = addNode(curNode->left, key);
    }
    return curNode;
}

void printTree(Node *curNode){
    if (!curNode){
        return;
    }
    printTree(curNode->left);
    printf("%d\t",curNode->key);
    printTree(curNode->right);
}