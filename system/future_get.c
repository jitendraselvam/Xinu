#include<future.h>

syscall future_get(future *f, int *value){

	if(f == NULL)
	{
		return SYSERR;	
	}
	if(f->state == FUTURE_EMPTY)
	{
		f->pid = getpid();
                       f->state = FUTURE_WAITING;
                       suspend(f->pid);
	}
	
	*value = *f->value;
	if(f->state == FUTURE_VALID)
	{	
		f->state = FUTURE_EMPTY;
	}
	return OK;

}
