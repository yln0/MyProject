#include"ngx.h"
/*
小块内存chunk的头信息
*/
typedef struct {
	u_char               *last;
	u_char               *end;
	ngx_pool_t           *next;
	ngx_uint_t            failed;
} ngx_pool_data_t;

/*
表示nginx内存池的大类型
*/
struct ngx_pool_s {
	ngx_pool_data_t       d;
	size_t                max;
	ngx_pool_t           *current;
	ngx_pool_large_t     *large;
	//释放内存池的callback
	ngx_pool_cleanup_t	 *cleanup;
};

/*
nginx大块内存类型信息
*/
struct ngx_pool_large_s {
	ngx_pool_large_t     *next;
	//malloc申请出来的大内存的地址
	void                 *alloc;
};

/*
在内存池进行销毁时，循环调用这些回调函数对数据进行清理
回调函数结构体
*/
struct ngx_pool_cleanup_s {
	//handler 回调函数指针
	ngx_pool_cleanup_pt		handler;
	//回调时，将此数据传入回调函数
	void					*data;
	//指向下一个回调函数结构体
	ngx_pool_cleanup_t		*next;
};
class NgxMemPool
{
public:
	//创建ngx的内存池
	ngx_pool_t * ngx_create_pool(size_t size);
	//销毁ngx内存池
	void ngx_destroy_pool(ngx_pool_t *pool);
	//重置内存池
	void ngx_reset_pool(ngx_pool_t *pool);
	//开辟内存，对齐
	void* ngx_palloc(ngx_pool_t *pool,size_t size);
	//分配内存块
	void* ngx_palloc_block(ngx_pool_t *pool,size_t size);
	//分配大内存块
	void* ngx_palloc_large(ngx_pool_t *pool,size_t size);
	//开辟内存，不对齐
	void* ngx_pnalloc(ngx_pool_t *pool,size_t size);
	//把内存归还给内存池
	ngx_int_t ngx_pfree(ngx_pool_t *pool,void *p);
private:
	ngx_pool_t *_pool;
};