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
int isSameTree(Node* curNode1, Node* curNode2);

int main(){
    List l;
    l.head = NULL;

    l.head = addNode(l.head, 50);
    l.head = addNode(l.head, 25);
    l.head = addNode(l.head, 75);
    l.head = addNode(l.head, 30);
    l.head = addNode(l.head, 15);
    l.head = addNode(l.head, 100);
    l.head = addNode(l.head, 60);

    printf("the trees are%s the same\n", isSameTree(l.head,l.head) ? "" : " not");

//    printTree(l.head);

    return 0;
}

/*  input: 2 trees
 *  output: 1 if trees are identical. 0 otherwise.
 * */
int isSameTree(Node* curNode1, Node* curNode2){
    if (!curNode1 && !curNode2 || !curNode1 || !curNode2){
        return 1;
    }

    if (curNode1->key != curNode2->key){
        return 0;
    }

    return isSameTree(curNode1->left,curNode2->left) && isSameTree(curNode2->right, curNode2->right);
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

