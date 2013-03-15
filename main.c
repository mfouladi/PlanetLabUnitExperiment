#include "unitExperiment.h"
#include "stdlib.h"     /* for atoi() and exit() */
#include "stdio.h"
#include "string.h"

int main(int argc, char *argv[]){
  char* x;
  printf("%d\n", argc);
  if (argc != 2){    /* Test for correct number of arguments */
     exit(1);
  }
  int isSender = atoi(argv[1]);
  printf("isSender=%d\n", isSender);
  if(isSender==0){
    printf("RUNNING unitExperimentSender\n");
    unitExperimentSender(100,-20,30,0,x);
  }else if(isSender==1){
    printf("RUNNING unitExperimentReceiver\n");
    unitExperimentReceiver();
  }else{
    printf("error\n");
    exit(1);
  }
  exit(0);
  printf("program terminated\n");
  return 0;
}
