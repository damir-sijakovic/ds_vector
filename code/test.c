#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "ds_vector.h"

void dsv_debug_print(DSVector *handle, char *str){
    
    printf("%s\n", "========= DEBUG PRINT =========");
    printf("%s\n", str );
    int i = 0;
    for (; i<handle->length; i++){
        if (handle->data[i] == NULL){
            printf("%s\n", "-null-");
            continue;
        }
        printf("%s\n", handle->data[i]);
    }
    printf("Vector length is: %d\n", handle->length);
    printf("%s\n", "========= DEBUG END =========");
}


boolean pf_test(void **a){
   // printf("%s\n", *a);
    *a = "Overwrite with dsv_forEach.";  
    return TRUE;  
}

int main(){
    
    
    // TEST1: create vector and add items     
    DSVector *vtr = dsv_create(1, DS_VECTOR_MODE_STEP, 1);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
        
    printf("dsv_get: %s\n", dsv_get(vtr, 3 ));    
        
    dsv_debug_print(vtr, "=== TEST1 ===" );
    dsv_destroy(vtr);
    
        
    /*    
    // TEST2: resize vector   
    DSVector *vtr = dsv_create(2, DS_VECTOR_MODE_STEP, 2);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
    
    dsv_resize(&vtr, 3);
    
    dsv_debug_print(vtr, "=== TEST2: resize to 3 items ===" );
    
    dsv_resize(&vtr, 20);
    dsv_debug_print(vtr, "=== TEST2: resize to 20 items ===" );
    
    dsv_shrinkToFit(&vtr); 
    dsv_debug_print(vtr, "=== TEST2: dsv_shrinkToFit() ===" );
    
    dsv_destroy(vtr);
    */
    
    
    /*
    // TEST3: double resize mode, dsv_forEach() and dsv_getContainer()
    DSVector *vtr = dsv_create(1, DS_VECTOR_MODE_DOUBLE, 2);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
    
    DS_VECTOR_DATATYPE* data_address = dsv_getContainer(&vtr, 4);
    *data_address = "Changed stuff at index 4.";
    
    dsv_debug_print(vtr, "=== TEST3: dsv_getContainer() ===");
    
    dsv_forEach(&vtr, pf_test); 
    
    dsv_debug_print(vtr, "=== TEST3: dsv_forEach() ===");
    
    dsv_destroy(vtr);
    */

}
