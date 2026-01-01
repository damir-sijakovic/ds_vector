/**********************************************************************\
 ________    ________  ___      ___  _______   ______  ___________  ______     _______   
|"      "\  /"       )|"  \    /"  |/"     "| /" _  "\("     _   ")/    " \   /"      \  
(.  ___  :)(:   \___/  \   \  //  /(: ______)(: ( \___))__/  \\__/// ____  \ |:        | 
|: \   ) || \___  \     \\  \/. ./  \/    |   \/ \        \\_ /  /  /    ) :)|_____/   ) 
(| (___\ ||  __/  \\     \.    //   // ___)_  //  \ _     |.  | (: (____/ //  //      /  
|:       :) /" \   :)     \\   /   (:      "|(:   _) \    \:  |  \        /  |:  __   \  
(________/ (_______/       \__/     \_______) \_______)    \__|   \"_____/   |__|  \___) 
DS_VECTOR v0.5, Damir Šijaković, (c) 2025. 

'ds_vector' is a resizable array container with two resize modes. 
Resize modes are 'DS_VECTOR_MODE_DOUBLE' where memory required for 
array doubles with each new step and 'DS_VECTOR_MODE_STEP' where array 
is resized in steps defined by step number. 

\**********************************************************************/

#ifndef	DS_VECTOR_H
#define	DS_VECTOR_H

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <assert.h> 

/**********************************************************************\
 CONFIG
\**********************************************************************/

#define DS_VECTOR_ITEM_LIMIT 10000
// #define DS_VECTOR_DEBUG_RESIZE 

/**********************************************************************\
 TYPES
\**********************************************************************/


typedef enum {
    DS_VECTOR_MODE_DOUBLE = 1000,
    DS_VECTOR_MODE_STEP   = 1001
} DSVectorMode;


typedef struct DSVector{     
    int length;
    DSVectorMode mode;
    int step;
    void* data[1];    
} DSVector;  

/**********************************************************************\
 PROTOS
\**********************************************************************/

DSVector *dsv_create(int size, DSVectorMode mode, int step);
void dsv_destroy(DSVector *handle);
void dsv_resize(DSVector **handle, int length);
bool dsv_set(DSVector **handle, unsigned index, void* data); 
void* dsv_get(DSVector *handle, unsigned index);
int dsv_shrinkToFit(DSVector **handle);                                 //cuts down unnecessary allocated slots to lowest possible
bool dsv_forEach(DSVector **handle, bool (*fn_ptr)(void**));
void** dsv_getContainer(DSVector **handle, unsigned index);
DSVector *dsv_createStepMode(int size, int step);
DSVector *dsv_createDoubleMode(int size);
int dsv_getNumberOfItems(DSVector *handle);
int dsv_getLastItem(DSVector *handle);
bool dsv_appendItem(DSVector **handle, void *data);
bool dsv_pack(DSVector **handle);                                       //remove empty slots between data -1-3--6 becomes 1,3,6

/**********************************************************************\
 PRIVATE
\**********************************************************************/

int _dsv_malloc_calc(unsigned base_size, unsigned item_size, unsigned item_num){
    if (base_size < item_size){
        fprintf(stderr, "DS_VECTOR/_dsv_malloc_calc: Wrong size for 'item_size' argument!  \n");
        return -1;
    }
    
    int ret_size = 0;
    
    if (item_num == 0)
        return base_size - item_size;
    else if (item_num > 0)
        ret_size = (base_size - item_size) + (item_size * item_num);
    
    return ret_size;
}


unsigned _dsv_double_calc(unsigned amount){

    int running = 1;
    int i = 1;
    
    while (running){
        if (i>amount-1){break;}        
        i = (i==1) ? 2 : i+i; 
    }    
        
    return i;
}


unsigned _dsv_step_calc(unsigned amount, unsigned step){        
    unsigned i=0;
    unsigned j=0;
    for (; j<(amount); i++){
        j += step;
    }
    
    return j;
}

/**********************************************************************\
 INTERFACE
\**********************************************************************/

DSVector *dsv_create(int size, DSVectorMode mode, int step){
    
    if (size < 0){
        fprintf(stderr, "DS_VECTOR/dsv_create: Wrong size for 'size' argument!  \n");
        return NULL;
    }
    
    if (size > DS_VECTOR_ITEM_LIMIT){
        fprintf(stderr, "DS_VECTOR/dsv_create: Wrong size for 'size' argument!  \n");
        return NULL;
    }
    
    if (mode == DS_VECTOR_MODE_STEP){
        if (step < 0){
            fprintf(stderr, "DS_VECTOR/dsv_create: Wrong size for 'size' argument!  \n");
            return NULL;
        }
    }
     
    int malloc_size = _dsv_malloc_calc(sizeof (DSVector), sizeof(void*), size);
    DSVector *t = malloc(malloc_size);
    if (!t){
        fprintf(stderr, "DS_VECTOR/dsv_create: Memory allocation error!  \n");
        abort();
    }
    memset(t, 0, malloc_size);
    t->length = size;
    t->mode = mode;
    t->step = step;
    return t;
}

DSVector *dsv_createStepMode(int size, int step){
    if (size < 0){
        fprintf(stderr, "DS_VECTOR/dsv_createStepMode: Wrong size for 'size' argument!  \n");
        return NULL;
    }
    
    if (size > DS_VECTOR_ITEM_LIMIT){
        fprintf(stderr, "DS_VECTOR/dsv_createStepMode: Wrong size for 'size' argument!  \n");
        return NULL;
    }
    
    int malloc_size = _dsv_malloc_calc(sizeof (DSVector), sizeof(void*), size);
    DSVector *t = malloc(malloc_size);
    if (!t){
        fprintf(stderr, "DS_VECTOR/dsv_createStepMode: Memory allocation error!  \n");
        abort();
    }
    memset(t, 0, malloc_size);
    t->length = size;
    t->mode = DS_VECTOR_MODE_STEP;
    t->step = step;
    return t;
}

DSVector *dsv_createDoubleMode(int size){
    if (size < 0){
        fprintf(stderr, "DS_VECTOR/dsv_createDoubleMode: Wrong size for 'size' argument! \n");
        return NULL;
    }  
    if (size > DS_VECTOR_ITEM_LIMIT){
        fprintf(stderr, "DS_VECTOR/dsv_createDoubleMode: Wrong size for 'size' argument! \n");
        return NULL;
    }
    
    int malloc_size = _dsv_malloc_calc(sizeof (DSVector), sizeof(void*), size);
    DSVector *t = malloc(malloc_size);
    if (!t){
        fprintf(stderr, "DS_VECTOR/dsv_createDoubleMode: Memory allocation error! \n");
        abort();
    }
    memset(t, 0, malloc_size);
    t->length = size;
    t->mode = DS_VECTOR_MODE_DOUBLE;
    t->step = -1; //unused
    return t;
}



void dsv_destroy(DSVector *handle){
    if (!handle){
        fprintf(stderr, "DS_VECTOR/dsv_destroy: Memory allocation error! \n");
        abort();
    }
    free(handle);
}

void dsv_resize(DSVector **handle, int length){
    if (!*handle){
        fprintf(stderr, "DS_VECTOR/dsv_resize: Argument 'handle' is null!");
        abort();
    }
    if (length < 0){
        fprintf(stderr, "DS_VECTOR/dsv_resize: Argument 'length' is less the 0!");
        abort();
    }

#ifdef DS_VECTOR_DEBUG_RESIZE
    printf("Debug: Resize to: %d \n", length);
#endif


    DSVector *old = *handle;
    int old_len = old->length;

    int malloc_size = _dsv_malloc_calc(sizeof(DSVector), sizeof(void*), length);
    DSVector *t = malloc(malloc_size);
    if (!t) abort();

    memset(t, 0, malloc_size);

    t->mode = old->mode;
    t->step = old->step;
    t->length = length;

    int copy_len = old_len < length ? old_len : length;
    memcpy(t->data, old->data, copy_len * sizeof(void*));

    *handle = t;
    free(old);
}


bool dsv_set(DSVector **handle, unsigned index, void *data){  

    if (!*handle){
        fprintf(stderr, "DS_VECTOR/dsv_set: Argument 'handle' is null! \n");
        abort();
        return false;
    }
    
    if (index > DS_VECTOR_ITEM_LIMIT){
        fprintf(stderr, "DS_VECTOR/dsv_set: Argument 'index' above limit set by 'DS_VECTOR_ITEM_LIMIT'! \n");
        abort();
        return false;
    }
    
    if (!data){
        fprintf(stderr, "DS_VECTOR/dsv_set: Argument 'data' is null! \n");
        abort();
        return false;
    }

    DSVectorMode mode = (*handle)->mode;
 
    if (index >= (*handle)->length){
        if (mode == DS_VECTOR_MODE_DOUBLE){
            dsv_resize(handle, _dsv_double_calc(index+1));          
        }         
        if (mode == DS_VECTOR_MODE_STEP){
            dsv_resize(handle, _dsv_step_calc(index+1, (*handle)->step));          
        }         
    }
    
    (*handle)->data[index] = data;
    
    return true;
}



void* dsv_get(DSVector *handle, unsigned index){
    if (!handle){
        fprintf(stderr, "DS_VECTOR/dsv_get: Argument 'handle' is null!");
        abort();
    }
    
    if (index > handle->length){
        fprintf(stderr, "DS_VECTOR/dsv_get: Argument 'index' is larger then set by 'handle->length'!");
        abort();
    }
    
    if (index > DS_VECTOR_ITEM_LIMIT){
        fprintf(stderr, "DS_VECTOR/dsv_get: Argument 'index' is larger then set by 'DS_VECTOR_ITEM_LIMIT'!");
        abort();
    }
    if (index >= (unsigned)handle->length) abort();
    if (index > DS_VECTOR_ITEM_LIMIT) abort();
    return handle->data[index];
}

void** dsv_getContainer(DSVector **handle, unsigned index){  
  
    if (!*handle){
        fprintf(stderr, "DS_VECTOR/dsv_getContainer: Argument 'handle' is null! \n");
        abort();
    }
    
    if (index > DS_VECTOR_ITEM_LIMIT){
        fprintf(stderr, "DS_VECTOR/dsv_getContainer: Argument 'index' is larger then set by 'DS_VECTOR_ITEM_LIMIT'! \n");
        abort();
    }
    
    return &((*handle)->data[index]);
}


int dsv_shrinkToFit(DSVector **handle){
    if (!handle || !*handle){
        fprintf(stderr, "DS_VECTOR/dsv_shrinkToFit: Argument 'handle' is null!");
        abort();
    }

    int i = (*handle)->length;
    while (i > 0 && (*handle)->data[i - 1] == NULL) i--;
    if (i == (*handle)->length) return -1;
    int removed = (*handle)->length - i;
    dsv_resize(handle, i);
    return removed;
}


bool dsv_forEach(DSVector **handle, bool (*fn_ptr)(void**)){
 
    if (!*handle){
        fprintf(stderr, "DS_VECTOR/dsv_forEach: Argument 'handle' is null! \n");
        abort();
    }
    
    if (!fn_ptr){
        fprintf(stderr, "DS_VECTOR/dsv_forEach: Argument 'fn_ptr' is null! \n");
        abort();
    }
    
    bool no_error = true;   
    unsigned i = 0;   
    for (; i<(*handle)->length; i++){
        if (no_error){
            no_error = fn_ptr(&(*handle)->data[i]);
        }
        else {
            return false;
        }
    }
    
    return no_error;    
}


int dsv_getNumberOfItems(DSVector *handle){ 
    if (!handle){
        fprintf(stderr, "DS_VECTOR/dsv_getNumberOfItems: Argument 'handle' is null!");
        abort();
    }

    int count = 0;
    int i = 0;
    for (; i<handle->length; i++){
        if (handle->data[i] == NULL){ //skip empty slots
            continue;
        }
        count++;
    }
    
    return count;

}

int dsv_getLastItem(DSVector *handle){ 
    if (!handle){
        fprintf(stderr, "DS_VECTOR/dsv_getLastItem: Argument 'handle' is null!");
        abort();
    }

    int lastItem = -1;
    int i = 0;
    for (; i<handle->length; i++){
        if (handle->data[i] != NULL){ //skip empty slots
            lastItem = i;
        }        
    }
    
    return lastItem;

}

bool dsv_appendItem(DSVector **handle, void *data){ 
    if (!handle){
        fprintf(stderr, "DS_VECTOR/dsv_appendItem: Argument 'handle' is null!");
        abort();
    }

    unsigned lastItem = dsv_getLastItem(*handle);
    lastItem++; 
    //printf("lastitem: %d \n",lastItem);
    return dsv_set(handle, lastItem, data);
}


bool dsv_pack(DSVector **handle){
    if (handle == NULL || *handle == NULL) {
        fprintf(stderr, "DS_VECTOR/dsv_pack: Argument 'handle' is null!");
        abort();
    }

    int length = (*handle)->length;
    DSVector *newVector = NULL;
    int step = 0; 
    int counter = 0;
    if ((*handle)->mode == DS_VECTOR_MODE_DOUBLE){
        newVector = dsv_createDoubleMode(length);
    } else if ((*handle)->mode == DS_VECTOR_MODE_STEP){
        step = (*handle)->step;
        newVector = dsv_createStepMode(length, step);
    }

    if (newVector == NULL) return false;
    
    for (int i = 0; i < length; ++i){
        if ((*handle)->data[i] == NULL) continue;

        if (!dsv_set(&newVector, counter, (*handle)->data[i])){
            return false;
        }
        counter++;
    }

    dsv_destroy(*handle); 
    *handle = newVector;
    return true;
}



/**********************************************************************\
 DEBUG
\**********************************************************************/


void dsv_debug_string_data(DSVector *handle, char *str){
    
    printf("%s\n", "========= DEBUG PRINT =========");
    printf("%s\n", str );
    int i = 0;
    for (; i<handle->length; i++){
        if (handle->data[i] == NULL){
            printf("%s\n", "-null-");
            continue;
        }
        printf("%s\n", (char*) handle->data[i]);
    }
    printf("Vector length is: %d\n", handle->length);
    printf("%s\n", "========= DEBUG END =========");
}







    
#endif
