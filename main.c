#include "unitExperiment.h"
#include "stdlib.h"     /* for atoi() and exit() */
#include "stdio.h"
#include "string.h"

int main(int argc, char *argv[]){
  char* x;
  if (argc != 1){    /* Test for correct number of arguments */
     exit(1);
  }
  int isSender = atoi(argv[0]);
  if(isSender==0){
    unitExperimentSender(1, 1,1, 1,x);
  }else if(isSender==1){
    unitExperimentReceiver();
  }else{
    exit(1);
  }
  return 0;
}
