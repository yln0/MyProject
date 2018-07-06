#include<iostream>
#include"nginx.h"
#include<assert.h>
using namespace std;

ngx_pool_t*  NgxMemPool::ngx_create_pool(size_t size)
{
	ngx_pool_t *p = (ngx_pool_t*)malloc(size);
	assert(p != NULL);

	p->d.last = (u_char *)p + sizeof(ngx_pool_t);//��ʼ״̬
	p->d.end = (u_char *)p + size;//ָ����������size��С���ڴ�ĩβ
	p->d.next = NULL;
	p->d.failed = 0;

	size = size - sizeof(ngx_pool_t);
	p->max = (size < NGX_MAX) ? size : NGX_MAX;

	p->current = p;
	p->large = NULL;
	p->cleanup = NULL;
	return p;
}
//����ngx�ڴ��
void NgxMemPool::ngx_destroy_pool(ngx_pool_t *pool)
{
	ngx_pool_cleanup_t *c=pool->cleanup;
	ngx_pool_large_t   *l = pool->large;
	ngx_pool_t		   *p, *n;
	//�������е�����������������������С���ڴ��ϵĶ���
	for (; c; c = c->next)
	{
		if (c->handler)
		{
			c->handler(c->data);
		}
	}
	//�ͷ����еĴ���ڴ�
	for (; l; l = l->next)
	{
		if (l->alloc)
		{
			free(l->alloc);
		}
	}
	//�ͷ������ڴ���е��ڴ��
	for (p = pool, n = pool->d.next;; p = n, n = n->d.next)
	{
		free(p);
		if (n == NULL)
		{
			break;
		}
	}
}
//�����ڴ��
void NgxMemPool::ngx_reset_pool(ngx_pool_t *pool)
{
	ngx_pool_t       *p = pool;
	ngx_pool_large_t *l = pool->large;
	//�ͷ����д���ڴ�
	for (; l; l = l->next)
	{
		if (l->alloc)
		{
			free(l->alloc);
		}
	}
	pool->large = NULL;
	//��������С���ڴ���
	for (; p; p = p->d.next)
	{
		//�ص���ʼ״̬
		p->d.last = (u_char*)p + sizeof(ngx_pool_t);
		p->d.failed = 0;
	}
	pool->current = p;
}
//�����ڴ棬����
void * NgxMemPool::ngx_palloc(ngx_pool_t *pool,size_t size)
{
	u_char      *m;
	ngx_pool_t  *p;
	if (size <= pool->max)
	{
		p = pool->current;
		do
		{
			//�ڴ��ַ����--û�е���malloc�Ⱥ��������ڴ棬�ƶ�ָ����
			m = ngx_align_ptr(p->d.last, NGX_ALIGN);
			if ((size_t)(p->d.end - m) >= size)//������
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
	//�ڴ�ص�һ���ڴ��Ĵ�С
	psize = (size_t)(pool->d.end - (u_char)pool);//�����ڴ�ص�һ���ڴ��Ĵ�С

	//����͵�һ���ڴ���С��ȵ��ڴ��
	m = (u_char*)malloc(psize);
	assert(m != NULL);

	newblock = (ngx_pool_t *)m;
	newblock->d.end = m + psize; //���ڴ��end
	newblock->d.next = NULL;
	newblock->d.failed = 0;

	//��������ݿ�֮��,��Ϊ��ʼλ��
	m += sizeof(ngx_pool_data_t);
	m = ngx_align_ptr(m, NGX_ALIGN);//�ֽڶ���
	newblock->d.last = m + size;//����ʹ��size��С���ڴ�

	//failed ����ѭ���ĳ��ȣ�����������ﵽ5�Σ����ԣ�����Ҫÿ�δ�ͷ��
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
	//�ҵ�һ����large�������У�����Ŀռ������������򴴽�һ��
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
	//��ǰ�ṹ����뵽����ڴ���   ͷ��
	large->alloc = p;               
	large->next = pool->large;  
	pool->large = large;
	
	return p;
}
//�����ڴ棬������
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
			if ((size_t)(p->d.end - m) >= size)//������
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

//���ڴ�黹���ڴ��
ngx_int_t NgxMemPool::ngx_pfree(ngx_pool_t *pool,void *p)
{
	ngx_pool_large_t *l;
	//���Ǵ���ڴ棬�ͷ�free
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