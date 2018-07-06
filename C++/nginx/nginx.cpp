#include<iostream>
#include"nginx.h"
#include<assert.h>
using namespace std;

ngx_pool_t*  NgxMemPool::ngx_create_pool(size_t size)
{
	ngx_pool_t *p = (ngx_pool_t*)malloc(size);
	assert(p != NULL);

	p->d.last = (u_char *)p + sizeof(ngx_pool_t);//初始状态
	p->d.end = (u_char *)p + size;//指向分配的整个size大小的内存末尾
	p->d.next = NULL;
	p->d.failed = 0;

	size = size - sizeof(ngx_pool_t);
	p->max = (size < NGX_MAX) ? size : NGX_MAX;

	p->current = p;
	p->large = NULL;
	p->cleanup = NULL;
	return p;
}
//销毁ngx内存池
void NgxMemPool::ngx_destroy_pool(ngx_pool_t *pool)
{
	ngx_pool_cleanup_t *c=pool->cleanup;
	ngx_pool_large_t   *l = pool->large;
	ngx_pool_t		   *p, *n;
	//调用所有的数据清理函数（析构所有在小块内存上的对象）
	for (; c; c = c->next)
	{
		if (c->handler)
		{
			c->handler(c->data);
		}
	}
	//释放所有的大块内存
	for (; l; l = l->next)
	{
		if (l->alloc)
		{
			free(l->alloc);
		}
	}
	//释放所有内存池中的内存块
	for (p = pool, n = pool->d.next;; p = n, n = n->d.next)
	{
		free(p);
		if (n == NULL)
		{
			break;
		}
	}
}
//重置内存池
void NgxMemPool::ngx_reset_pool(ngx_pool_t *pool)
{
	ngx_pool_t       *p = pool;
	ngx_pool_large_t *l = pool->large;
	//释放所有大块内存
	for (; l; l = l->next)
	{
		if (l->alloc)
		{
			free(l->alloc);
		}
	}
	pool->large = NULL;
	//重置所有小块内存区
	for (; p; p = p->d.next)
	{
		//回到初始状态
		p->d.last = (u_char*)p + sizeof(ngx_pool_t);
		p->d.failed = 0;
	}
	pool->current = p;
}
//开辟内存，对齐
void * NgxMemPool::ngx_palloc(ngx_pool_t *pool,size_t size)
{
	u_char      *m;
	ngx_pool_t  *p;
	if (size <= pool->max)
	{
		p = pool->current;
		do
		{
			//内存地址对齐--没有调用malloc等函数申请内存，移动指针标记
			m = ngx_align_ptr(p->d.last, NGX_ALIGN);
			if ((size_t)(p->d.end - m) >= size)//容量够
			{
				p->d.last = m + size;
				return m;
			}
			p = p->d.next;
		} while (p);

		return ngx_palloc_block(pool,size);
	}
	return ngx_palloc_large(pool,size);
}
void* NgxMemPool::ngx_palloc_block(ngx_pool_t *pool,size_t size)
{
	u_char *m;
	size_t psize;
	ngx_pool_t *p, *newblock;
	//内存池第一个内存块的大小
	psize = (size_t)(pool->d.end - (u_char)pool);//计算内存池第一个内存块的大小

	//分配和第一个内存块大小相等的内存块
	m = (u_char*)malloc(psize);
	assert(m != NULL);

	newblock = (ngx_pool_t *)m;
	newblock->d.end = m + psize; //新内存的end
	newblock->d.next = NULL;
	newblock->d.failed = 0;

	//分配从数据块之后,作为起始位置
	m += sizeof(ngx_pool_data_t);
	m = ngx_align_ptr(m, NGX_ALIGN);//字节对齐
	newblock->d.last = m + size;//申请使用size大小的内存

	//failed 控制循环的长度，若分配次数达到5次，忽略，不需要每次从头找
	for (p = pool->current; p->d.next; p = p->d.next)
	{
		if (p->d.failed++ > 4)
		{
			p->current = p->d.next;
		}
	}
	p->d.next = newblock;
	return m;
}
void* NgxMemPool::ngx_palloc_large(ngx_pool_t *pool,size_t size)
{
	void             *p;
	ngx_uint_t        n;
	ngx_pool_large_t *large;

	p = malloc(size);
	assert(p != NULL);
	n = 0;
	//找到一个空large区，若有，分配的空间由它管理，否则创建一个
	for (large = pool->large; large; large = large->next)
	{
		if (large->alloc == NULL)
		{
			large->alloc = p;
			return p;
		}
		if (n++ > 3)
		{
			break;
		}
	}
	large = (ngx_pool_large_t *) ngx_palloc(pool,sizeof(ngx_pool_large_t));
	if (large == NULL)
	{
		free(p);
		return NULL;
	}
	//当前结构体插入到大块内存链   头插
	large->alloc = p;               
	large->next = pool->large;  
	pool->large = large;
	
	return p;
}
//开辟内存，不对齐
void* NgxMemPool::ngx_pnalloc(ngx_pool_t *pool,size_t size)
{
	u_char      *m;
	ngx_pool_t  *p;
	if (size <= pool->max)
	{
		p = pool->current;
		do
		{
			m = p->d.last;
			if ((size_t)(p->d.end - m) >= size)//容量够
			{
				p->d.last = m + size;
				return m;
			}
			p = p->d.next;
		} while (p);

		return ngx_palloc_block(pool,size);
	}
	return ngx_palloc_large(pool,size);
}

//把内存归还给内存池
ngx_int_t NgxMemPool::ngx_pfree(ngx_pool_t *pool,void *p)
{
	ngx_pool_large_t *l;
	//若是大块内存，释放free
	for (l = pool->large; l; l = l->next)
	{
		if (p == l->alloc)
		{
			free(l->alloc);
			l->alloc = NULL;
			return NGX_OK;
		}
	}
	return NGX_DEC;
}