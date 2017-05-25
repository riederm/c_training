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


void clearNode(Node* node){
    node->data = NULL;
    node->next = NULL;
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

Node* remove_beginning(List* list){
    if (list->size == 0){
        return NULL;
    }
    
    Node* toRemove = list->pHead;
    list->pHead = list->pHead->next;
    list->size--;
    
    if (list->size <= 1){
       list->pLast = list->pHead;   
    }
    
    clearNode(toRemove);
    return toRemove;
}


void remove_end(List* list){
    if (list->size == 0){
        return NULL;
    }else if (list->size == 1){
        return remove_beginning(list);
    }
    
    //find the node before the last node
    Node* pNode = list->pHead;
    while(pNode->next != list->pLast){
       pNode = pNode->next;
    }
    
    list->size--;
    clearNode(list->pLast);
    pNode->next = NULL;
    list->pLast = pNode;
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
        
char* get_key(List* list, int key){
    Node* pHead = list->pHead;
    while(pHead != NULL && pHead->key != key){
        pHead = pHead->next;
    }
    if (pHead != NULL){
        return pHead->data;
    }
    return NULL;
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
    insert_end(l3, 1, "end_one");
    insert_end(l3, 2, "end_two");
    insert_end(l3, 3, "end_three");   
    insert_beginning(l3, 3, "begin_three");
    insert_beginning(l3, 2, "begin_two");
    insert_beginning(l3, 1, "begin_one");
    printList(l3);
    
    printf("\nget_key...\n");
    printf("get_key(%d) = %s\n", 3, get_key(l3, 3));
    printf("get_key(%d) = %s\n", 2, get_key(l3, 2));
    printf("get_key(%d) = %s\n", 1, get_key(l3, 1));
    
    printf("\nremoving...\n");
    remove_beginning(l3);
    printList(l3);
    remove_beginning(l3);
    printList(l3);
    remove_beginning(l3);
    printList(l3);
    
    printf("\nget_key...\n");
    printf("get_key(%d) = %s\n", 3, get_key(l3, 3));
    printf("get_key(%d) = %s\n", 2, get_key(l3, 2));
    printf("get_key(%d) = %s\n", 1, get_key(l3, 1));
    
    
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
