#include<future.h>

syscall future_set(future *f, int *value){
	
	if(f == NULL)
	{
		return SYSERR;
	}
	*f->value = *value;
	if(f->state == FUTURE_EMPTY ||f->state == FUTURE_WAITING)
	{
		f->state = FUTURE_VALID;
	}
	resume(f->pid);
	return OK;
	
}

