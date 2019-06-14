//Damir Šijaković, (c) 2019 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "ds_vector.h"

/****************************************************************************\
 HELPERS
\****************************************************************************/

size_t dsv_malloc_calc(size_t base_size, size_t item_size, size_t item_num){
    assert(base_size > 0); assert(item_size > 0); assert(item_num >= 0); 
    assert(base_size > item_size);
    
    int ret_size = 0;
    
    if (item_num == 0)
        return base_size - item_size;
    else if (item_num > 0)
        ret_size = (base_size - item_size) + (item_size * item_num);
    
    return ret_size;
}


unsigned dsv_double_calc(unsigned amount){
    assert(amount > 0);
    
    int running = 1;
    int i = 1;
    
    while (running){
        if (i>amount-1){break;}        
        i = (i==1) ? 2 : i+i; 
    }    
        
    return i;
}


unsigned dsv_step_calc(unsigned amount, unsigned step){
    assert(amount > 0); assert(step > 0);
    
    unsigned i=0;
    unsigned j=0;
    for (; j<(amount); i++){
        j += step;
    }
    
    return j;
}

/****************************************************************************\
 INTERFACE
\****************************************************************************/

DSVector *dsv_create(size_t size, DSVectorMode mode, int step){
    assert(size > 0);    
    assert(size < DS_VECTOR_ITEM_LIMIT);
    if (mode == DS_VECTOR_MODE_STEP) assert(step > 0);
    
    size_t malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(DS_VECTOR_DATATYPE), size);
    DSVector *t = malloc(malloc_size);
    if (!t){
        printf("%s\n", "Memory allocation error!");
        abort();
    }
    memset(t, 0, malloc_size);
    t->length = size;
    t->mode = mode;
    t->step = step;
    return t;
}


void dsv_destroy(DSVector *handle){
    assert(handle);
    free(handle);
}


void dsv_resize(DSVector **handle, size_t length){
    assert(*handle); assert(length > 0); 
    
#ifdef DS_VECTOR_DEBUG_RESIZE
    printf("Debug: Resize to: %d \n", length);
#endif
    
    size_t old_length = (*handle)->length;    
    size_t malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(DS_VECTOR_DATATYPE), length);
    size_t old_malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(DS_VECTOR_DATATYPE), old_length);
    DSVector *t = dsv_create(length, (*handle)->mode, (*handle)->step);
        
    if (old_malloc_size < malloc_size){
        memcpy(t, *handle, old_malloc_size);
    }
    
    if (old_malloc_size > malloc_size){
        memcpy(t, *handle, malloc_size);
    }
        
    t->length = length;
    
    DSVector *f = *handle;
    *handle = t;
    free(f);
}


boolean dsv_set(DSVector **handle, unsigned index, void *data){  
    assert(*handle); assert(index < DS_VECTOR_ITEM_LIMIT); assert(data);
    
    DSVectorMode mode = (*handle)->mode;
 
    if (index >= (*handle)->length){
        if (mode == DS_VECTOR_MODE_DOUBLE){
            dsv_resize(handle, dsv_double_calc(index+1));          
        }         
        if (mode == DS_VECTOR_MODE_STEP){
            dsv_resize(handle, dsv_step_calc(index+1, (*handle)->step));          
        }         
    }
    
    (*handle)->data[index] = data;
}


DS_VECTOR_DATATYPE dsv_get(DSVector *handle, unsigned index){  
    assert(handle); assert(index < handle->length); assert(index < DS_VECTOR_ITEM_LIMIT); 
    
    return handle->data[index];
}


DS_VECTOR_DATATYPE* dsv_getContainer(DSVector **handle, unsigned index){  
    assert(*handle); assert(index < DS_VECTOR_ITEM_LIMIT); 
    
    return &((*handle)->data[index]);
}


int dsv_shrinkToFit(DSVector **handle){
    assert(*handle);
    
    if ((*handle)->data[(*handle)->length-1] == NULL){
        int j = 0;
        int i = (*handle)->length-1;
        for (; (*handle)->data[i] == NULL; --i, j++);
        dsv_resize(handle, (*handle)->length - j);
        return j;
    }
    return -1;    
}


boolean dsv_forEach(DSVector **handle, boolean (*fn_ptr)(void**)){
    assert(*handle); assert(fn_ptr);
    boolean no_error = TRUE;   
    unsigned i = 0;   
    for (; i<(*handle)->length; i++){
        if (no_error){
            no_error = fn_ptr(&(*handle)->data[i]);
        }
        else {
            return FALSE;
        }
    }
    
    return no_error;    
}
