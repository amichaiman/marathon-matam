#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
int symmetricCount(Node *curNode, int *height);

int main(){
    List l;
    l.head = NULL;

    l.head = addNode(l.head, 50);
    l.head = addNode(l.head, 25);
    l.head = addNode(l.head, 75);
    l.head = addNode(l.head, 30);
    l.head = addNode(l.head, 15);
    l.head = addNode(l.head, 100);
//    l.head = addNode(l.head, 60);

    printf("symmetry count is %d\n", symmetricCount(l.head,NULL));

    printTree(l.head);

    return 0;
}

/*  input: tree
 *  output: number of nodes that the height of their right son's tree
 *                  is equal to the height of their left son's tree
 * */
int symmetricCount(Node *curNode, int *height){
    if (!curNode){
        return 0;
    }

    int kidsLeft=0, kidsRight=0;
    int symCount = 0;

    symCount = symmetricCount(curNode->right,&kidsRight);
    symCount += symmetricCount(curNode->left,&kidsLeft);


    if (height != NULL){
        *height = (kidsLeft > kidsRight ? kidsLeft : kidsRight) + 1;
    }

    return symCount + (kidsLeft==kidsRight);
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

