#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "./../ds_vector.h"


void main(){
    
    printf("DOUBLE MODE\n"); 
    DSVector *vtr = dsv_createDoubleMode(10);
    
    dsv_set(&vtr, 0, "0:set"); 
    dsv_set(&vtr, 1, "1:set"); 
        
    dsv_appendItem(&vtr, "Append 00");
    dsv_appendItem(&vtr, "Append 01");
    dsv_appendItem(&vtr, "Append 02");
    
    dsv_set(&vtr, 6, "6:set"); 
    dsv_appendItem(&vtr, "Append 03");
    dsv_appendItem(&vtr, "Append 04");
    dsv_appendItem(&vtr, "Append 05");
    dsv_appendItem(&vtr, "Append 06");

    
    dsv_debug_string_data(vtr, "=== TEST1 ===" );
    
    dsv_destroy(vtr); 
    
    
    printf("STEP MODE\n"); 
    vtr = dsv_createStepMode(10, 2);
    
    dsv_set(&vtr, 0, "0:set"); 
    dsv_set(&vtr, 1, "1:set"); 
        
    dsv_appendItem(&vtr, "Append 00");
    dsv_appendItem(&vtr, "Append 01");
    dsv_appendItem(&vtr, "Append 02");
    
    dsv_set(&vtr, 6, "6:set"); 
    dsv_appendItem(&vtr, "Append 03");
    dsv_appendItem(&vtr, "Append 04");
    dsv_appendItem(&vtr, "Append 05");
    dsv_appendItem(&vtr, "Append 06");
    
    dsv_debug_string_data(vtr, "=== TEST2 ===" );
    
    dsv_destroy(vtr); 
    
    
    
    
    
/*
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
    
*/
}
