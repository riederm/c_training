//gcc 5.4.0

#include  <stdio.h>
#include <stdlib.h>

typedef struct Array{
    int* data;
    int length;
} Array;


Array* createArray(int length) {
    Array* a = malloc(sizeof(Array));
    a->data = malloc(sizeof(int) * length);
    a->length = length;
    return a;
}

void destroy(Array* array){
    free(array->data);
    array->data = NULL;
    free(array);
}

int* access(Array* pArray, int index){
    if (index >= 0 && index <pArray->length){
        return &(pArray->data[index]);
    }
    return NULL;
}

int main(void)
{
    Array* pArray = createArray(10);
    
     printf("WRITING\n");
    for(int i=-5; i<15; i++){
        int* element = access(pArray, i);
        if (element != NULL){
            *element = i;
        }else{
            printf("could not write index %d\n", i);
        }
    }
    
    printf("\n\nREADING\n");
    for(int i=-5; i<15; i++){
        int* element = access(pArray, i);
        if (element != NULL){
            printf("pArray[%d]\t= %d\n", i, *element);
        }else{
            printf("pArray[%d]\t= INDEX_OUT_OF_BOUNDS\n", i);
        }
    }
    
    destroy(pArray);
}