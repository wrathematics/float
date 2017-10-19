#ifndef SPM_CDEFS_
#define SPM_CDEFS_


#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

#define FREE(ptr) if(ptr!=NULL) free(ptr)

#define THROW_MEMERR error("OOM")
#define CHECKMALLOC(ptr) if (ptr == NULL) THROW_MEMERR


#endif
