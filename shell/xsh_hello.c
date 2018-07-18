/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>


/*------------------------------------------------------------------------
 * xsh_hello - returns Hello <string>, Welcoe to the world of Xinu!!
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs, char *args[]){
	if(nargs != 2){
		fprintf(stderr,"%s: Too many or too less arguments\n",args[0]);
		fprintf(stderr,"TRY: xsh$ hello <string>\n");
		return 1;
	}
	printf("Hello %s ,Welcome to the world of Xinu!!\n",args[1]);
	return 0;
}

