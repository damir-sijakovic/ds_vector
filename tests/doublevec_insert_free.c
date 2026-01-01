#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "./../ds_vector.h"


void main(){
    
    // TEST1: create vector and add items     
    DSVector *vtr = dsv_createDoubleMode(1);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
        
    printf("dsv_get at slot 3 : %s\n", (char *) dsv_get(vtr, 3 ));    
        
    dsv_debug_string_data(vtr, "=== TEST1 ===" );

    printf("dsv_getLastItem: %d\n", dsv_getLastItem(vtr));    
    printf("numberOfItems: %d\n", dsv_getNumberOfItems(vtr));    
    
    
    dsv_destroy(vtr); 
    
 

}
