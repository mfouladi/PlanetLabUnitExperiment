#include "unitExperiment.h"
#include "stdio.h"      /* for printf() and fprintf() */
#include "sys/socket.h" /* for socket(), bind(), connect(), send(), recv() */
#include "arpa/inet.h"  /* for sockaddr_in, inet_addr(), inet_ntoa() */
#include "stdlib.h"     /* for atoi() and exit() */
#include "string.h"     /* for memset() */
#include "unistd.h"     /* for close() */

int unitExperimentReceiver(){
/*Initiate a TCP connection*/
  /*Variable Creation and Initializaiton*/
  int servSock;                      /* Socket descriptor for Server */
  int clntSock;                      /* Socket descriptor for Client */
  struct sockaddr_in servAddr;       /* Server address */
  struct sockaddr_in clntAddr;       /* Client address */
  unsigned short servPort = 16400;    /* Server port */
  char servIP[16]="127.0.0.1";       /* Server IP address (dotted quad) */
  char sendBuffer[12];               /* Buffer for sending packets */
  char *recBuffer;                   /* Buffer for receiving packets */
  unsigned int sendLen=12;           /* Length of send buffer */
  unsigned int recLen = 12;          /* Length of receive buffer */
  int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv() 
                                        and total bytes read */
  size_t clntLen;
  int count = 1;
printf("succes#%d\n",count++);
  /* Create a reliable, stream socket using TCP */
  if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return -1;
printf("succes#%d\n",count++);
  /* Construct the server address structure */
  memset(&servAddr, 0, sizeof(servAddr));         /* Zero out structure */
printf("succes#%d\n",count++);
  servAddr.sin_family      = AF_INET;             /* Internet address family*/
printf("succes#%d\n",count++);
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   /* Server IP address */
printf(" servAddr=%d\nsucces#%d\n",(INADDR_ANY),count++);
printf("succes#%d\n",count++);
  servAddr.sin_port        = htons(servPort);     /* Server port */
printf("succes#%d\n",count++);
  /* Bind to the local address */
  if (bind(servSock,(struct sockaddr *)&servAddr,sizeof(servAddr)) < 0)
    return -1;
printf("succes#%d\nwaiting...\n",count++);
  for(;;){
    /* Set the size of the in-out parameter */
    clntLen = sizeof(clntAddr);
    /* Wait for a client to connect */
    if ((clntSock = accept(servSock,(struct sockaddr*)&clntAddr,&clntLen)) < 0)
      continue;
    /* Receive ACK */
    if ((bytesRcvd = recv(clntSock, sendBuffer, recLen - 1, 0)) <= 0)
      return -1;
printf("succes#%d\n",count++);
    /* Send the data to the server */
    if (send(clntSock, sendBuffer, sendLen, 0) != sendLen)
      return -1;
printf("succes#%d\n",count++);
    break;
  }
  close(servSock);
  exit(0);
  return 0;
}
