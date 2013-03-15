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
  char recBuffer[12];                   /* Buffer for receiving packets */
  unsigned int sendLen=12;           /* Length of send buffer */
  unsigned int recLen = 12;          /* Length of receive buffer */
  int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv() 
                                        and total bytes read */
  size_t clntLen;
  int count=1;//test
  /* Create a reliable, stream socket using TCP */
  if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return -1;
  printf("success #%d\n",count++);
  /* Construct the server address structure */
  memset(&servAddr, 0, sizeof(servAddr));         /* Zero out structure */
  servAddr.sin_family      = AF_INET;             /* Internet address family*/
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   /* Server IP address */
  servAddr.sin_port        = htons(servPort);     /* Server port */
  /* Bind to the local address */
   printf("success #%d\n",count++);
  if (bind(servSock,(struct sockaddr *)&servAddr,sizeof(servAddr)) < 0)
    return -1;
  printf("success #%d\n",count++);
  /* Mark the socket so it will listen for incoming connections */
  if (listen(servSock, 5) < 0)
    return -1;
  printf("success #%d\n",count++);
  /* Set the size of the in-out parameter */
  clntLen = sizeof(clntAddr);
  /* Wait for a client to connect */
  if ((clntSock = accept(servSock,(struct sockaddr*)&clntAddr,&clntLen)) < 0)
    return -1;
  printf("success #%d\n",count++);
  /* Receive Data */
  if ((bytesRcvd = recv(clntSock, sendBuffer, recLen , 0)) <= 0)
    return -1;
  printf("success #%d\n",count++);
  /* Send the data to the server */
  if (send(clntSock, sendBuffer, sendLen, 0) != sendLen)
    return -1;
  printf("success #%d\n",count++);
  close(servSock);
  printf("closed socket successfully\n");
  //exit(0);
  printf("exit successfully\n");
  return 0;
}
