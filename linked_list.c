// bachmann c_training - mathias rieder

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LEN 1024
#define MIN(a,b) (((a)<(b))?(a):(b))

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

/*
* creates an empty list, must be freed using free_list
*/
List* init_list(void){
    List* list = malloc(sizeof(List));
    list->pHead = NULL;
    list->pLast = NULL;
    list->size = 0;
    return list;
}

/*
* frees the node's data and the node itself
*/
void freeNode(Node* node){
    free(node->data);
    node->data = NULL;
    node->next = NULL;
    free(node);
}

/*
* creates a new Node and initializes it with the given key and the given data
* the data will be copied
* the node must be freed using freeNode(...)
*/
Node* createNode(int key, char* data){
    Node* node = malloc(sizeof(Node));
    node->key = key;
    
    int len = MIN(strlen(data), MAX_DATA_LEN);  
    node->data = malloc(sizeof(char)*(len+1));
    strncpy(node->data, data, len);
    node->data[len] = '\0';
  
    node->next = NULL;
    return node;
}

/*
* inserts a new node at the beginning of the list
*/
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

/*
* appends a new node at the end of the list
*/
Node* insert_end(List* list, int key, char* data){
    if (list->size == 0){
       return insert_beginning(list, key, data);
    }
    
    list->pLast->next = createNode(key, data);
    list->pLast = list->pLast->next;
    list->size++;
    return list->pLast;
}

/*
* removes the first node of the list
* does nothing if the list is empty
*/
void remove_beginning(List* list){
    if (list->size == 0){
        return;
    }
    
    Node* toRemove = list->pHead;
    list->pHead = list->pHead->next;
    list->size--;
    
    if (list->size <= 1){
       list->pLast = list->pHead;   
    }
    
    freeNode(toRemove);
}

/*
* remoes the last node of the list
* does notthing if the list is empty
*/
void remove_end(List* list){
    if (list->size == 0){
        return;
    }else if (list->size == 1){
        remove_beginning(list);
        return;
    }
    
    //find the node before the last node
    Node* pNode = list->pHead;
    while(pNode->next != list->pLast){
       pNode = pNode->next;
    }
    
    list->size--;
    freeNode(list->pLast);
    pNode->next = NULL;
    list->pLast = pNode;
}

/*
* prints all key-value pairs of the list
*/
void print_list(List* list){
    Node* current = list->pHead;
    printf("list Size: %d\n", list->size);
    if (current == NULL){
       printf("empty\n");
    }
    do{
        printf("\t%d\t->\t%s\n", current->key, current->data);
        current = current->next;
    }while(current != NULL);
}

/*
* frees all nodes of the list and the list itself
*/
void free_list(List* list){
    while(list->size > 0){
        remove_beginning(list);
    }
    list->pHead = NULL;
    list->pLast = NULL;
    free(list);
}

/*
* returns the first data associated to the given key
* returns NULL no data is associated to the given key
*/
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
    print_list(l1);
    free_list(l1);
    
    List* l2 = init_list();
    insert_end(l2, 1, "one");
    insert_end(l2, 2, "two");
    insert_end(l2, 3, "three");   
    print_list(l2);
    printf("removing_beginning 10 times\n");
    for(int i=0; i<10; i++){
        //remove_end(l2);
    }
    print_list(l2);
    free_list(l2);
    
    List* l3 = init_list();
    insert_end(l3, 1, "end_one");
    insert_end(l3, 2, "end_two");
    insert_end(l3, 3, "end_three");   
    insert_beginning(l3, 3, "begin_three");
    insert_beginning(l3, 2, "begin_two");
    insert_beginning(l3, 1, "begin_one");
    print_list(l3);
    
    printf("\nget_key...\n");
    printf("get_key(%d) = %s\n", 3, get_key(l3, 3));
    printf("get_key(%d) = %s\n", 2, get_key(l3, 2));
    printf("get_key(%d) = %s\n", 1, get_key(l3, 1));
    
    printf("\nremoving...\n");
    remove_beginning(l3);
    print_list(l3);
    remove_beginning(l3);
    print_list(l3);
    remove_beginning(l3);
    print_list(l3);
    
    printf("\nget_key...\n");
    printf("get_key(%d) = %s\n", 3, get_key(l3, 3));
    printf("get_key(%d) = %s\n", 2, get_key(l3, 2));
    printf("get_key(%d) = %s\n", 1, get_key(l3, 1));
    printf("get_key(%d) = %s\n", 777, get_key(l3, 777));
    
    free_list(l3);
    
    printf("\n\n*** original test code ***\n\n");

    List* l = init_list();
    printf("Size of list = %d\n",l->size);
    // Size of list = 0
    insert_end(l, 12, "Hello World");
    // Adds a node containing "Hello World" with key=12 at the end of
    // the list
    insert_beginning(l, 23, "Next Test String");
    // Adds a node containing "Next Test String" with key=23 at the
    // beginning of the list
    insert_end(l, 52, "Test String 3");
    insert_end(l, 45, "Test String 4");
    print_list(l);
    // 23 -> Next Test String
    // 12 -> Hello World
    // 52 -> Test String 3
    // 45 -> Test String 4
    remove_end(l);
    remove_beginning(l);
    print_list(l);
    // 12 -> Hello World
    // 52 -> Test String 3
    
    printf("String with key 52: %s", get_key(l, 52));
    // String with key 52: Test String 3
    free_list(l);
    // All memory on the heap is freed!


    
}
