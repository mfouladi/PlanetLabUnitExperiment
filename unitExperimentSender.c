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
  unsigned short servPort = 9999;    /* Server port */
  char servIP[16]="255.255.255.255"; /* Server IP address (dotted quad) */
  char sendBuffer[12];               /* Buffer for sending packets */
  char *recBuffer;                   /* Buffer for receiving packets */
  unsigned int sendLen=12;           /* Length of send buffer */
  unsigned int recLen = 32;          /* Length of receive buffer */
  int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv() 
                                        and total bytes read */
  /*fill sendBuffer with data*/                                    
  size_t intSize=sizeof(int);
  memcpy((sendBuffer+intSize*0), &num_of_packets,                 intSize);
  memcpy((sendBuffer+intSize*1), &inter_packet_departure_spacing, intSize);
  memcpy((sendBuffer+intSize*2), &probe_packet_length,            intSize);
  /* Create a reliable, stream socket using TCP */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return -1;
  /* Construct the server address structure */
  memset(&servAddr, 0, sizeof(servAddr));         /* Zero out structure */
  servAddr.sin_family      = AF_INET;             /* Internet address family*/
  servAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
  servAddr.sin_port        = htons(servPort);     /* Server port */
  /* Establish the connection to the echo server */
  if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    return -1;
  /* Send the data to the server */
  if (send(sock, sendBuffer, sendLen, 0) != sendLen)
    return -1;
  /* Receive ACK */
  if ((bytesRcvd = recv(sock, recBuffer, recLen - 1, 0)) <= 0)
    return -1;
  recBuffer[bytesRcvd] = '\0';   /*terminate recBuffer */
  close(sock);
  exit(0);
  return 0;
}
