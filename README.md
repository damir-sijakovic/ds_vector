## DS_VECTOR v1.0


### About

'ds_vector' is a resizable array container with two resize modes. Resize modes are 'DS_VECTOR_MODE_DOUBLE' where 
memory needed for array doubles with each new step and 'DS_VECTOR_MODE_STEP' where array is resized in steps 
defined by step number. Library is developed and tested only on archlinux/openrc 4.3 kernel, gcc 5.3.0 and valgrind 3.11. 


### Usage

#### ds_vector.h

In header 'ds_vector.h' data type and vector size limit can be set.

    #define DS_VECTOR_DATATYPE void*
    #define DS_VECTOR_ITEM_LIMIT 10000


#### dsv_create()

To create a vector in step mode, call init function:

    DSVector *vector = dsv_create(10, DS_VECTOR_MODE_STEP, 1);

This creates container with 10 items. So there will be no resize untill index 
after 10 is requested. Resize mode is 'DS_VECTOR_MODE_STEP' with last argument
beeing 1. 1 means that in DS_VECTOR_MODE_STEP, in iteration, resize will 
happen per 1 step. In 'DS_VECTOR_MODE_DOUBLE' last argument is ignored.


#### dsv_destroy()

This function will destroy adt and free memory.

    dsv_destroy(vector);


#### dsv_set()

Inserts data in vector at specified index. If index is above allocated size,
resize will happen. For example, to add "Some text at index 9" data at index 9.

    dsv_set(&vector, 9, "Some text at index 9");


#### dsv_resize()

Increase/reduce capacity of vector. Size is limited by DS_VECTOR_ITEM_LIMIT 
constant. 


#### dsv_shrinkToFit()

Request container to reduce its capacity to fit its size.


#### dsv_forEach()

Pass all vector items through external function. If extrenal function returns 
FALSE bool, itreation stops. External function must be in this format:
    
    boolean pf_test(void **a){
        *a = "Overwrite with dsv_forEach";    
        return TRUE;
    }  

    dsv_forEach(&vector, pf_test);


#### dsv_getContainer()

Returns container item address in vector. Note that this address changes
is resize occurs. For example to get pointer to index 4:

    DS_VECTOR_DATATYPE* data_address = dsv_getContainer(&vtr, 4);
    *data_address = "Changed stuff at index 4.";

## Licence

MIT
