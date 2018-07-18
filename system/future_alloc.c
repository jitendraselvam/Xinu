#include<future.h>

future* future_alloc(int future_flag)
{
	future *f;
	f = (future*) getmem(sizeof(future));

	f->state = FUTURE_EMPTY;
	f->flag = future_flag;
	f->value = 0;
	f->pid = -1;

	return f;
}
