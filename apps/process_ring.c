/********************************************************************************************
 *This file contains all the defintitons of the functions in the header file process_ring.h
 *by Jitendra Selvam
 ********************************************************************************************/


#include<process_ring.h>

//Method to perform polling synchronizaiton.
process poll( int32 rounds, int32 j, int32 nprocs)
{

	int32 lastIndex = nprocs -1;
	int32 rnd =0;
	
	while(rnd<rounds)
	{

		if(arr[j]!=-1)
		{
			printf("Ring Element %d : Round %d : value%d\n",j,rnd,arr[j]);	
		
			if(j == lastIndex) //check if j is the last index
			{	
				arr[0] = arr[j]-1;
				if(arr[j]-1 == -1)
				{
					signal(semexit);
				}
				else
				{
					arr[j]=-1;
				}
			}
			else
			{
				arr[j+1] = arr[j] -1;
				arr[j] = -1;
			}
			rnd++;
		}
	}
	return 0;
}


//Method to perform semaphore synchronization 
void sync(volatile int32 pid, volatile int32 pcount, volatile int32 round)
{
	volatile int32 rnds = 0;
	while(rnds < round)
	{
		wait(sem[pid]);
		printf("Ring Element %d : Round %d : value%d\n",pid,rnds,arr[pid]);
		arr[(pid+1)%pcount] = arr[pid]-1;
		signal(sem[(pid+1)%pcount]);
		rnds++;
	}
signal(semexit);
}
