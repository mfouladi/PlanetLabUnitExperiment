#include "unitExperiment.h"
#include "stdio.h"      /* for printf() and fprintf() */
#include "sys/socket.h" /* for socket(), connect(), send(), and recv() */
#include "arpa/inet.h"  /* for sockaddr_in and inet_addr() */
#include "stdlib.h"     /* for atoi() and exit() */
#include "string.h"     /* for memset() */
#include "unistd.h"     /* for close() */

int unitExperimentReceiver(){
/*Initiate a TCP connection*/
  /*Variable Creation and Initializaiton*/
  int sock;                          /* Socket descriptor */
  struct sockaddr_in servAddr;       /* Server address */
  unsigned short servPort = 9999;    /* Server port */
  char servIP[16]="255.255.255.255"; /* Server IP address (dotted quad) */
  char sendBuffer[12];               /* Buffer for sending packets */
  char *recBuffer;                   /* Buffer for receiving packets */
  unsigned int sendLen=12;           /* Length of send buffer */
  unsigned int recLen = 32;          /* Length of receive buffer */
  int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv() 
                                        and total bytes read */
  /* Create a reliable, stream socket using TCP */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return -1;
  /* Construct the server address structure */
  memset(&servAddr, 0, sizeof(servAddr));         /* Zero out structure */
  servAddr.sin_family      = AF_INET;             /* Internet address family*/
  servAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
  servAddr.sin_port        = htons(servPort);     /* Server port */
  /* Bind to the local address */
  if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    return -1;
  /* Set the size of the in-out parameter */
  clntLen = sizeof(echoClntAddr);

  /* Wait for a client to connect */
  if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
      DieWithError("accept() failed");
  close(sock);
  exit(0);
  return 0;
}
