#define ngx_pagesize 4096
#define NGX_MAX (ngx_pagesize-1) 
//内存地址取整
#define ngx_align_ptr(p,a) (u_char *)(((uintptr_t)(p)+((uintptr_t)a - 1)) & ~((uintptr_t)a -1))
#define NGX_ALIGN sizeof(unsigned long) //64位系统 8字节

#define NGX_OK 0
#define NGX_DEC -5
typedef unsigned char u_char;

//typedef int intptr_t;
//typedef unsigned int  uintptr_t;
typedef intptr_t ngx_int_t;
typedef uintptr_t ngx_uint_t;

typedef struct ngx_pool_cleanup_s ngx_pool_cleanup_t;
typedef void(*ngx_pool_cleanup_pt)(void * data);

typedef struct ngx_pool_s ngx_pool_t;
typedef struct ngx_pool_large_s  ngx_pool_large_t;