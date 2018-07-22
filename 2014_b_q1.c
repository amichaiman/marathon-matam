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
void findPrevNext(Node* curNode, int a, int *closestFromBottom, int *closestFromTop);

int main(){
    List l;
    l.head = NULL;
    int prev=-1, next=-1;
    l.head = addNode(l.head, 50);
    l.head = addNode(l.head, 4);
    l.head = addNode(l.head, 2);
    l.head = addNode(l.head, 6);
    l.head = addNode(l.head, 100);
    l.head = addNode(l.head, 96);
    l.head = addNode(l.head, 202);

    findPrevNext(l.head, 1, &prev, &next);
    printf("prev: %d\tnext: %d",prev,next);
//    printTree(l.head);

    return 0;
}

/*  input: tree, number, and a pointer to a variable that will hold the
 *              closest value to the number from below and a variable
 *              that will hold the smallest number from above
 *  output: none
 *
 *  function assigns the closest to from below and from above
 * */
void findPrevNext(Node* curNode, int a, int *closestFromBottom, int *closestFromTop){
    if (!curNode){
        return;
    }

    /*  if the number in current node is smaller than a */
    if (curNode->key < a){
        /*  if no number smaller than a was found yet, or the our number is closer  */
        if (*closestFromBottom == -1 || curNode->key > *closestFromBottom){
            *closestFromBottom = curNode->key;
        }
    /*  if the number in current node is bigger than a */
    } else if (curNode->key > a){
        /*  if no number bigger than a was found yet, or the our number is closer  */
        if (*closestFromTop == -1 || curNode->key < *closestFromTop){
            *closestFromTop = curNode->key;
        }
    }
    /*  search rest of tree */
    findPrevNext(curNode->left, a, closestFromBottom, closestFromTop);
    findPrevNext(curNode->right, a, closestFromBottom, closestFromTop);
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
