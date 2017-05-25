//gcc 5.4.0

#include  <stdio.h>
#include <stdlib.h>

#define MAX_DATA_LEN = 1024;

typedef struct Node{
    int key;
    char* data;
    struct Node* next;
} Node;

typedef struct List{
    Node* pHead;
    Node* pLast;
    int size;
} List;

List* init_list(void){
    List* list = malloc(sizeof(List));
    list->pHead = NULL;
    list->pLast = NULL;
    list->size = 0;
    return list;
}


Node* createNode(int key, char* data){
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->data = data;
    node->next = NULL;
    return node;
}

Node* insert_beginning(List* list, int key, char* data){
    Node* oldpHead = list->pHead;
    list->pHead = createNode(key, data);
    list->pHead->next = oldpHead;
    list->size++;
    
    if (list->size == 1){
        list->pLast = list->pHead;
    }
    return list->pHead;
}

Node* insert_end(List* list, int key, char* data){
    if (list->size == 0){
       return insert_beginning(list, key, data);
    }
    
    list->pLast->next = createNode(key, data);
    list->pLast = list->pLast->next;
    list->size++;
    return list->pLast;
}

Node** getLastNextPointer(Node* pHead){
    Node* current = pHead;
    while(current->next != NULL){
        current = current->next;
    }
    
    return &(current->next);
}


Node* appendNode(Node* pHead, int value, char* data){
    Node** ppNext = getLastNextPointer(pHead);
    *ppNext = createNode(value, data);
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

void printList(List* list){
    Node* current = list->pHead;
    printf("list Size: %d\n", list->size);
    if (current == NULL){
       printf("empty\n");
    }
    do{
        printf("{%d,%s},", current->key, current->data);
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
    List* l1 = init_list();
    insert_beginning(l1, 3, "three");
    insert_beginning(l1, 2, "two");
    insert_beginning(l1, 1, "one");
    printList(l1);
    
    
    List* l2 = init_list();
    insert_end(l2, 1, "one");
    insert_end(l2, 2, "two");
    insert_end(l2, 3, "three");   
    printList(l2);
    
    
    List* l3 = init_list();
    insert_end(l3, 1, "e_one");
    insert_end(l3, 2, "e_two");
    insert_end(l3, 3, "e_three");   
    insert_beginning(l3, 3, "b_three");
    insert_beginning(l3, 2, "b_two");
    insert_beginning(l3, 1, "b_one");
    printList(l3);
    
    /*Node* pHead = createNode(0, "");
    appendNode(pHead, 1, "");
    Node* element = appendNode(pHead, 2, "");
    appendNode(pHead, 3, "");
    appendNode(pHead, 4, "");
    
    
    printList(pHead);
    
    for(int i=0; i<5; i++){
        printf("list[%d] = %d\n", i, get(pHead, i)->key);
    }
    
    delete(pHead);*/
    
}
