//gcc 5.4.0

#include  <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;



Node* createNode(int value){
    Node* node = malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

Node** getLastNextPointer(Node* pHead){
    Node* current = pHead;
    while(current->next != NULL){
        current = current->next;
    }
    
    return &(current->next);
}


Node* appendNode(Node* pHead, int value){
    Node** ppNext = getLastNextPointer(pHead);
    *ppNext = createNode(value);
    return *ppNext;
}


Node* get(Node* pHead, int index){
    int i = 0;
    Node* current = pHead;
    while(i < index && current != NULL){
        current = current->next;
        i++;
    }
    
    return current;       
}

void printList(Node* pHead){
    Node* current = pHead;
    if (pHead == NULL){
       printf("empty\n");
    }
    do{
        printf("%d,", current->data);
        current = current->next;
    }while(current != NULL);
    printf("\n");
}

void delete(Node* pHead){
    if (pHead == NULL)  return;
    
    Node* current = pHead;
    Node* next = current->next;
    
    do{
        free(current);
        current = next;
        if (next != NULL){
            next = current->next;
        }
    }while(current != NULL);
    
}

int main(void)
{
    Node* pHead = createNode(0);
    appendNode(pHead, 1);
    Node* element = appendNode(pHead, 2);
    appendNode(pHead, 3);
    appendNode(pHead, 4);
    
    
    printList(pHead);
    
    for(int i=0; i<5; i++){
        printf("list[%d] = %d\n", i, get(pHead, i)->data);
    }
    
    delete(pHead);
    
}