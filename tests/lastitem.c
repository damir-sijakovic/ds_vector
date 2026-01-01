#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "./../ds_vector.h"


void main(){
    
    printf("DOUBLE MODE\n"); 
    DSVector *vtr = dsv_createDoubleMode(30);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert"); 
    dsv_set(&vtr, 9, "9:insert");

    dsv_debug_string_data(vtr, "=== TEST1 ===" );

    printf("dsv_getLastItem: %d\n", dsv_getLastItem(vtr));    
        
    dsv_destroy(vtr);   
    
    printf("\n\n"); 
    printf("STEP MODE\n"); 
    vtr = dsv_createStepMode(30, 100);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert"); 
    dsv_set(&vtr, 9, "9:insert");

    dsv_debug_string_data(vtr, "=== TEST2 ===" );

    printf("dsv_getLastItem: %d\n", dsv_getLastItem(vtr));    
        
    dsv_destroy(vtr);   
    

}
