#include<iostream>
#include"nginx.h"
using namespace std;

int main()
{
	ngx_pool_t *pool;
	NgxMemPool ngx;
	pool=ngx.ngx_create_pool(1024);
	ngx.ngx_palloc(pool,8);
	ngx.ngx_palloc(pool, 100);
	ngx.ngx_palloc(pool,900);//ngx_palloc_block
	ngx.ngx_palloc(pool, 1024);//ngx_palloc_large

	ngx.ngx_reset_pool(pool);
	ngx.ngx_destroy_pool(pool);

	return 0;
}
