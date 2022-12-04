/*
 * mm-implicit.c - an empty malloc package
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 *
 * @id : 학번 
 * @name : 이름 
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#define DEBUG
#ifdef DEBUG
# define dbg_printf(...) printf(__VA_ARGS__)
#else
# define dbg_printf(...)
#endif


/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */


/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT-1)) & ~0x7)

/* Define Word Size(4bytes) */
#define WSIZE 4
/* Define Double Word Size(8bytes)*/ 
#define DSIZE 8
#define OVERHEAD 8
#define CHUNKSIZE (1<<12)

/* The PACK macro is a function that creates a 1-word bit string for size and allocation.*/
#define PACK(size,alloc) ((size)|(alloc))

/* Get a value as much as 1 word size from a specific address value */
#define GET(p) (*(unsigned int *)(p))

/* Assign a value to a specific address */
#define PUT(p,value) (*(unsigend int *)(p) = (value)) 

/* Get pointer of block's header */
#define HDRP(bp)    ((char *)(bp) - WSIZE)
/* Get pointer of block's footer */
#define FTRP(bp)    ((char *)(bp) + GET_SIZE(HDRP(bp))- DSIZE)

/* Get pointer of next or previous block */
#define NEXT_BLKP(bp)   (((char *)(bp) + GET_SIZE((char *)(bp) - WSIZE))) 
#define PREV_BLKP(bp)   (((char *)(bp) - GET_SIZE((char *)(bp) - DSIZE)))

/* A pointer to store the starting address of the heap */
static char *heap_listp = 0;


/*
 * Initialize: return -1 on error, 0 on success.
 */
int mm_init(void) {
     if((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1){
        return -1;
    };
    PUT(heap_listp, 0); // Padding                         
    PUT(heap_listp + WSIZE, PACK(OVERHEAD, 1)); // Prologue header 
    PUT(heap_listp + DSIZE, PACK(OVERHEAD, 1)); // Prologue footer
    PUT(heap_listp + WISZE + DSIZE, PACK(0, 1)); // Epilogue header
    heap_listp += (2*WSIZE);  
    
    if(extend_heap(CHUNKSIZE/WSIZE)==NULL)
        return -1; 
    return 0;
}
static void *extend_heap(size_t words)
{   
    /* Round the requested size to a multiple of a double word and expand the heap by that size */
    char *bp;
    size_t size;
    if(words%2)
        size = (words+1) * WSIZE;
    else
        size = words * WSIZE;
    
    if((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    // Put header of free block
    PUT(HDRP(bp), PACK(size, 0)); 
    
    // Put footer of free block
    PUT(FTRP(bp), PACK(size, 0));  //free 블록의 footer
    // Put epilogue header    
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); 

    return coalesce(bp);
};

static void *find_fit(size_t asize){

    void *bp;
    /* First Fit */
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)){
        /* If it is not an allocated block and the size of the block is greater than the size of the value to be allocated, the corresponding address (pointer) is returned. */
        if((GET_ALLOC(HDRP(bp))==0) && (asize <= GET_SIZE(HDRP(bp)))){
            return bp;
        }
    }
    return NULL;
}


/*
 * malloc
 */
void *malloc (size_t size) {
    return NULL;
}

/*
 * free
 */
void free (void *ptr) {
    if(!ptr) return;
}

/*
 * realloc - you may want to look at mm-naive.c
 */
void *realloc(void *oldptr, size_t size) {
    return NULL;
}

/*
 * calloc - you may want to look at mm-naive.c
 * This function is not tested by mdriver, but it is
 * needed to run the traces.
 */
void *calloc (size_t nmemb, size_t size) {
    return NULL;
}


/*
 * Return whether the pointer is in the heap.
 * May be useful for debugging.
 */
static int in_heap(const void *p) {
    return p < mem_heap_hi() && p >= mem_heap_lo();
}

/*
 * Return whether the pointer is aligned.
 * May be useful for debugging.
 */
static int aligned(const void *p) {
    return (size_t)ALIGN(p) == (size_t)p;
}

/*
 * mm_checkheap
 */
void mm_checkheap(int verbose) {
}
