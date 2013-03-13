#include "unitExperiment.h"
#include "stdio.h"      /* for printf() and fprintf() */
#include "sys/socket.h" /* for socket(), connect(), send(), and recv() */
#include "arpa/inet.h"  /* for sockaddr_in and inet_addr() */
#include "stdlib.h"     /* for atoi() and exit() */
#include "string.h"     /* for memset() */
#include "unistd.h"     /* for close() */

int unitExperimentSender(int num_of_packets, int inter_packet_departure_spacing,
                     int probe_packet_length, int entropy, 
                     char* experiment_run_log_absolute_filename){
  /*Initiate a TCP connection*/
  /*Variable Creation and Initializaiton*/
  int sock;                          /* Socket descriptor */
  struct sockaddr_in servAddr;       /* Server address */
  unsigned short servPort = 16400;    /* Server port */
  char servIP[16]="127.0.0.1";       /* Server IP address (dotted quad) */
  char sendBuffer[12];               /* Buffer for sending packets */
  char *recBuffer;                   /* Buffer for receiving packets */
  unsigned int sendLen=12;           /* Length of send buffer */
  unsigned int recLen = 12;          /* Length of receive buffer */
  int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv() 
                                        and total bytes read */
  /*fill sendBuffer with data*/                                    
  size_t intSize=sizeof(int);
  memcpy((sendBuffer+intSize*0), &num_of_packets,                 intSize);
  memcpy((sendBuffer+intSize*1), &inter_packet_departure_spacing, intSize);
  memcpy((sendBuffer+intSize*2), &probe_packet_length,            intSize);
  /*TEST*/
  printf("BEFORE SEND: %d, %d, %d\n", *((int*)(sendBuffer+intSize*0)),
                       *((int*)(sendBuffer+intSize*1)), 
                       *((int*)(sendBuffer+intSize*2)));
  int count=1;
  /*TEST*/
  /* Create a reliable, stream socket using TCP */
printf("succes#%d\n",count++);
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return -1;
printf("succes#%d\n",count++);
  /* Construct the server address structure */
printf("succes#%d\n",count++);
  memset(&servAddr, 0, sizeof(servAddr));         /* Zero out structure */
printf("succes#%d\n",count++);
  servAddr.sin_family      = AF_INET;             /* Internet address family*/
printf("succes#%d\n",count++);
  servAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */

printf(" servAddr=%s\nsucces#%d\n",(servIP),count++);
  servAddr.sin_port        = htons(servPort);     /* Server port */
printf("succes#%d\n",count++);
  /* Establish the connection to the echo server */
  if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    return -1;
printf("succes#%d\n",count++);
  /* Send the data to the server */
  if (send(sock, sendBuffer, sendLen, 0) != sendLen)
    return -1;
printf("succes#%d\n",count++);
  /* Receive ACK */
  if ((bytesRcvd = recv(sock, recBuffer, recLen - 1, 0)) <= 0)
    return -1;
  /*TEST*/
  printf("AFTER REC: %d, %d, %d\n", *((int*)(recBuffer+intSize*0)),
                       *((int*)(recBuffer+intSize*1)), 
                       *((int*)(recBuffer+intSize*2)));
  /*TEST*/ 
  //recBuffer[bytesRcvd] = '\0';   /*terminate recBuffer */
  close(sock);
  exit(0);
  return 0;
}
