#ifndef	DS_VECTOR_H
#define	DS_VECTOR_H
    
/****************************************************************************\
 CONFIG
\****************************************************************************/

#define DS_VECTOR_DATATYPE void*
#define DS_VECTOR_ITEM_LIMIT 10000
#define DS_VECTOR_DEBUG_RESIZE 



/****************************************************************************\
 TYPES
\****************************************************************************/

#ifndef FALSE
 #define FALSE (0)
#endif
#ifndef TRUE
 #define TRUE (!FALSE)
#endif
#ifndef boolean
 #define boolean unsigned char
#endif

#define DSVectorMode long 
#define DS_VECTOR_MODE_DOUBLE 0xDB1E
#define DS_VECTOR_MODE_STEP 0x57E9

typedef struct DSVector{     
    size_t length;
    DSVectorMode mode;
    int step;
    DS_VECTOR_DATATYPE data[1];    
} DSVector;  

/****************************************************************************\
 PROTOS
\****************************************************************************/

DSVector *dsv_create(size_t size, DSVectorMode mode, int step);
void dsv_destroy(DSVector *handle);
void dsv_resize(DSVector **handle, size_t length);
boolean dsv_set(DSVector **handle, unsigned index, DS_VECTOR_DATATYPE data); 
DS_VECTOR_DATATYPE dsv_get(DSVector *handle, unsigned index);
int dsv_shrinkToFit(DSVector **handle);
boolean dsv_forEach(DSVector **handle, boolean (*fn_ptr)(void**));
DS_VECTOR_DATATYPE* dsv_getContainer(DSVector **handle, unsigned index);

    
#endif
