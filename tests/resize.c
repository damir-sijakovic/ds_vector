#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "./../ds_vector.h"


void main(){
    
    printf("DOUBLE MODE\n"); 
    DSVector *vtr = dsv_createDoubleMode(10);
    
    dsv_appendItem(&vtr, "Append 00");
    dsv_appendItem(&vtr, "Append 01");
    dsv_appendItem(&vtr, "Append 02");
    dsv_appendItem(&vtr, "Append 03");
    dsv_appendItem(&vtr, "Append 04");
    dsv_appendItem(&vtr, "Append 05");
    dsv_appendItem(&vtr, "Append 06");
    dsv_appendItem(&vtr, "Append 07");
    dsv_appendItem(&vtr, "Append 08");
    dsv_appendItem(&vtr, "Append 09");
    dsv_appendItem(&vtr, "Append 10");
    dsv_appendItem(&vtr, "Append 11");
    dsv_appendItem(&vtr, "Append 12");
    dsv_appendItem(&vtr, "Append 13");
        
    dsv_resize(&vtr, 6);  
    
    dsv_debug_string_data(vtr, "=== TEST1 ===" );
    
    dsv_destroy(vtr); 
    

}
