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

    dsv_prependItem(&vtr, "Prepend0");
    dsv_prependItem(&vtr, "Prepend1");
    dsv_prependItem(&vtr, "Prepend2");
    
    dsv_debug_string_data(vtr, "=== TEST1 ===" );
    
    dsv_destroy(vtr); 
    

    printf("STEP MODE\n"); 
    vtr = dsv_createStepMode(10, 2);
    
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

    dsv_prependItem(&vtr, "Prepend0");
    dsv_prependItem(&vtr, "Prepend1");
    dsv_prependItem(&vtr, "Prepend2");
    
    dsv_debug_string_data(vtr, "=== TEST2 ===" );
    
    dsv_destroy(vtr); 
    
    
}
