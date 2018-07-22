#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* next;
} Node;

typedef struct{
    Node *head;
} List;

void addNode(List *l, int key);
void createList1(List *l);
void createList2(List *l);
int chainLen(Node* node1, Node* node2);
void printList(Node* curNode);
List *findMaxSegment(List *l1, List *l2);

int main(){
    List l1, l2;
    l1.head = l2.head = NULL;
    
    createList1(&l1);
    createList2(&l2);

    printList(findMaxSegment(&l1,&l2)->head);

    return 0;
}
/*  copys n nodes starting at position pos and
 *  returns it as a new list
 * */
List *copyPartOfList(List *l, Node *pos, int n){
    List *l3 = (List*) malloc (sizeof(List));    
    int i;   
    
    for (i=0; i<n; i++){
        if (!pos){
            return NULL;
        }
        addNode(l3,pos->key);
        pos = pos->next;
    }
    
    return l3;
}


/*  returns longest chain of nodes that is a
 *  subset of l1 and of l2
 * */
List *findMaxSegment(List *l1, List *l2){
    int longestChainLen = 0;
    int currentChainLen;
    Node *curNode1;
    Node *curNode2;
    Node *chainStartPos = NULL;

    for (curNode1 = l1->head; curNode1 != NULL; curNode1 = curNode1->next){
        for (curNode2 = l2->head; curNode2 != NULL; curNode2 = curNode2->next){
            currentChainLen = chainLen(curNode1,curNode2);
            if (currentChainLen > longestChainLen){
                longestChainLen = currentChainLen;
                chainStartPos = curNode1;
            }
        }
    }
    
    return copyPartOfList(l1, chainStartPos, longestChainLen);
}

/*
 *  returns length of similar nodes starting from node1 and node2
 * */
int chainLen(Node* node1, Node* node2){
    int len = 0;
    
    while (node1 && node2 && node1->key == node2->key){
        len++;
        node1 = node1->next;
        node2 = node2->next;
    }
    
    return len;
}

/*
 *  compares two given lists
 * */
int listCompare(List *l1, List *l2, Node* pos1, Node* pos2, int n){
    int i;
    
    for (i=0; i<n; i++){
        if (!pos1 || !pos2|| pos1->key != pos2->key){
            return 0;
        }
        pos1 = pos1->next;
        pos2 = pos2->next;
    }
    
    return 1;
}

void createList2(List *l) {
    addNode(l,5);
    addNode(l,4);
    addNode(l,4);
    addNode(l,8);
    addNode(l,9);
    addNode(l,5);
    addNode(l,6);
    addNode(l,3);
    addNode(l,6);

}

void createList1(List *l) {
    addNode(l,1);
    addNode(l,5);
    addNode(l,6);
    addNode(l,3);
    addNode(l,4);
    addNode(l,8);
    addNode(l,9);
    addNode(l,5);
    addNode(l,4);
    addNode(l,3);
    addNode(l,6);
    addNode(l,7);
}

/*  adds node to end of list
 * */
void addNode(List *l, int key){
    Node *newNode = (Node*) malloc (sizeof(Node));
    Node *curNode = l->head;

    newNode->key = key;
    newNode->next = NULL;

    if (!curNode){
        l->head = newNode;
        return;
    }

    while (curNode->next){
        curNode = curNode->next;
    }
    curNode->next = newNode;
}

void printList(Node* curNode){
    if (!curNode){
        putchar('\n');
        return;
    }
    printf("%d\t",curNode->key);
    printList(curNode->next);
}