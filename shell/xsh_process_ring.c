/******************************************************************************************
 *This file contains the code of the process_ring command to implement a count down based
 *on the number of processes and the number of rounds
 *By Jitendra Selvam
 ****************************************************************************************/
#include <process_ring.h>

volatile int arr[64];
sid32 sem[64];
sid32 semexit;

shellcmd xsh_process_ring(int argc, char *argv[])
{
	int32 nprocs= NPROCS;
	int32 rounds= NROUNDS;
	int32 i,j,k,synctype=0;
	int32 countdown;
	uint32 starttime,endtime;


	if(argc<1)
	{
		printf("Number of arguments is less");
		return SHELL_ERROR;
	}	
	else if(argc>1)
	{
		for(i=1;i<argc;i++)
		{
			if(strncmp(argv[i],"-p",3)==0)
			{
				nprocs=atoi(argv[++i]);
				if(nprocs <=0)
				{
					printf("\nInvalid arguments\n");
					return 1;
				}
				printf("Number of processes: %d\n",nprocs);
				
			}
			else if(strncmp(argv[i],"-r",3)==0)
			{
				rounds=atoi(argv[++i]);
				if(rounds <=0)
				{
					printf("\nInvalid arguments\n");
					return 1;
				}
				printf("Number of rounds %d\n",rounds);
			}
			else if(argc > 5)
			{
				if(strncmp(argv[i],"-i",3)==0)
				{
					if(strcmp(argv[++i],"poll")==0)
					{
						synctype = 1;
					}
					else
					{	
						synctype = 0;
					}
				}
			}
			else if (argc < 5)
			{
				synctype = 0;
			}
			else if(strncmp(argv[i],"--help",8)==0)
			{
				//display help options
				printf("Use:\n");
        			printf("\tprocess_ring [command]\n");
        			printf("Description:\n");
        			printf("\tPerforms a countdown based on the processes available\n");
        			printf("\thelp information for a specific command\n");
        			printf("Options:\n");
        			printf("\t-p\tnumber of processors\n");
        			printf("\t-r\tnumber of resources\n");
        			printf("\t-i\ttype of synchronization(poll or sync)\n");

			}
			else
			{
				printf("\n Invalid arguments \n");
			}	
		}
		
		//End of argument parsing
		
		countdown =(nprocs * rounds) -1;
				
		arr[0] = countdown;
		for(k=1;k<nprocs;k++)
		{
			 arr[k]=-1;
		}

		gettime(&starttime);
		semexit = semcreate(0);
		
		if(synctype == 1)
		{
			//creating the proceesses and calling the polling method
			for(j=0;j<nprocs;j++)
			{
				resume(create(poll,1024,20,"process",3,rounds,j,nprocs));
			}
			for(j=0;j<nprocs;j++)
			{
				wait(semexit);
				signal(semexit);
			}
		}
		else
		{
			//creating the proceesses and calling the semaphore method
			for(j=0;j<nprocs;j++)
			{
				sem[j]=semcreate(0);
			}
			
			for(j=0;j<nprocs;j++)
			{
				if(j==0)
					signal(sem[j]);
				resume(create(sync,1024,20,"process",3,j,nprocs,rounds));
			}
			
			for(j=0;j<nprocs;j++)
			{
				wait(semexit);
				semdelete(sem[j]);
			}
		}
		gettime(&endtime);
	}
	printf("Elapsed Seconds: %d\n",endtime - starttime);
	return SHELL_OK;
}