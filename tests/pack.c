#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "./../ds_vector.h"


void main(){
    
    printf("DOUBLE MODE\n"); 
    DSVector *vtr = dsv_createDoubleMode(30);
    
    dsv_set(&vtr, 0,  "0:set"); 
    dsv_set(&vtr, 2,  "2:set"); 
    dsv_set(&vtr, 4,  "4:set"); 
    dsv_set(&vtr, 12, "12:set"); 
    dsv_set(&vtr, 18, "18:set"); 
        
    dsv_pack(&vtr);
    
    dsv_debug_string_data(vtr, "=== TEST1 ===" );
    
    dsv_destroy(vtr); 
    

}
