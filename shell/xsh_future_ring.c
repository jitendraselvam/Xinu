
#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <future.h>
/**
 *  * Test Futures
 *   */


uint future_ring(future *in, future *out) {
  int val;
  future_get(in, &val);
  printf("Process %d gets %d, puts %d\n", getpid(), val, val-1);
  val--;
  future_free(in);
  future_set(out, &val);
  return OK;
}



uint32 xsh_future_test(int nargs, char *args[])
{
  int ring = 0;
  int future_flags = 0;
  int ring_count = 10;
  int final_val;
  int i;

//#ifndef NFUTURE
//  printf("no support for futures (NFUTURES not defined.)\n");
//  return OK;
//#endif

  if (nargs == 3 && strncmp(args[2], "-r", 2) == 0) {
    ring = 1;
    printf("Producer/consumer process ring\n");
  }
  else {
    printf("No valid options\n");
    return(OK);
  }

  if (ring == 1) {
    future *first, *in, *out = NULL;
    first = future_alloc(future_flags);
    in = first;
    for (i=0; i < ring_count; i++) {
      out = future_alloc(future_flags);
      resume( create(future_ring, 1024, 20, "", 2, in, out) );
      in = out;
    }
    printf("master sets %d\n", ring_count);
    future_set(first, &ring_count);
    future_get(out, &final_val);
    printf("master gets %d\n", final_val);
    return(OK);
  }
  return(OK);
}
