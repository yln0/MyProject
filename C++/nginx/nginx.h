#include"ngx.h"
/*
С���ڴ�chunk��ͷ��Ϣ
*/
typedef struct {
	u_char               *last;
	u_char               *end;
	ngx_pool_t           *next;
	ngx_uint_t            failed;
} ngx_pool_data_t;

/*
��ʾnginx�ڴ�صĴ�����
*/
struct ngx_pool_s {
	ngx_pool_data_t       d;
	size_t                max;
	ngx_pool_t           *current;
	ngx_pool_large_t     *large;
	//�ͷ��ڴ�ص�callback
	ngx_pool_cleanup_t	 *cleanup;
};

/*
nginx����ڴ�������Ϣ
*/
struct ngx_pool_large_s {
	ngx_pool_large_t     *next;
	//malloc��������Ĵ��ڴ�ĵ�ַ
	void                 *alloc;
};

/*
���ڴ�ؽ�������ʱ��ѭ��������Щ�ص����������ݽ�������
�ص������ṹ��
*/
struct ngx_pool_cleanup_s {
	//handler �ص�����ָ��
	ngx_pool_cleanup_pt		handler;
	//�ص�ʱ���������ݴ���ص�����
	void					*data;
	//ָ����һ���ص������ṹ��
	ngx_pool_cleanup_t		*next;
};
class NgxMemPool
{
public:
	//����ngx���ڴ��
	ngx_pool_t * ngx_create_pool(size_t size);
	//����ngx�ڴ��
	void ngx_destroy_pool(ngx_pool_t *pool);
	//�����ڴ��
	void ngx_reset_pool(ngx_pool_t *pool);
	//�����ڴ棬����
	void* ngx_palloc(ngx_pool_t *pool,size_t size);
	//�����ڴ��
	void* ngx_palloc_block(ngx_pool_t *pool,size_t size);
	//������ڴ��
	void* ngx_palloc_large(ngx_pool_t *pool,size_t size);
	//�����ڴ棬������
	void* ngx_pnalloc(ngx_pool_t *pool,size_t size);
	//���ڴ�黹���ڴ��
	ngx_int_t ngx_pfree(ngx_pool_t *pool,void *p);
private:
	ngx_pool_t *_pool;
};