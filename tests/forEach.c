#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "./../ds_vector.h"

typedef struct Pair{     
    char key[9];   
    long value; 
} Pair;  


bool forEachCallback(void **vectorItem){
    if (*vectorItem != NULL){
        Pair *pair = (Pair*) *vectorItem;
        printf("%s\n", pair->key);
        printf("%ld\n", pair->value);        
        return true; 
    }
}

void main(){
    
    DSVector *vtr = dsv_createDoubleMode(30);
    
    dsv_appendItem(&vtr, &(Pair){ .key = "example1", .value = 12345L }); 
    dsv_appendItem(&vtr, &(Pair){ .key = "example2", .value = 22345L }); 
    dsv_appendItem(&vtr, &(Pair){ .key = "example3", .value = 32345L }); 
    dsv_appendItem(&vtr, &(Pair){ .key = "example4", .value = 42345L }); 
    
    dsv_forEach(&vtr, forEachCallback); 
        
    dsv_destroy(vtr);   

}
