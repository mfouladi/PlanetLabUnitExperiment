#include "unitExperiment.h"
#include "stdio.h"      /* for printf() and fprintf() */
#include "sys/socket.h" /* for socket(), connect(), send(), and recv() */
#include "arpa/inet.h"  /* for sockaddr_in and inet_addr() */
#include "stdlib.h"     /* for atoi() and exit() */
#include "string.h"     /* for memset() */
#include "unistd.h"     /* for close() */
#include "sys/time.h"       /*for clock_t, clock(), & CLOCK_PER_SEC*/

int unitExperimentSender(int num_of_packets, int inter_packet_departure_spacing,
                     int probe_packet_length, int entropy, 
                     char* experiment_run_log_absolute_filename){
  /*Initiate a TCP connection*/
  /*Variable Creation and Initializaiton*/
  int sock;                          /* Socket descriptor */
  struct sockaddr_in servAddr;       /* Server address */
  unsigned short servPort = 16400;   /* Server port */
  char servIP[16]="127.0.0.1";       /* Server IP address (dotted quad) */
  char sendBuffer[12];               /* Buffer for sending packets */
  char recBuffer[12];                /* Buffer for receiving packets */
  unsigned int sendLen=12;           /* Length of send buffer */
  unsigned int recLen = 12;          /* Length of receive buffer */
  int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv() 
                                        and total bytes read */
  clock_t begin, end;/*Time before send & Time after send*/
  unsigned int time_spent;/*Calculated RTT used for timout*/
  size_t intSize=sizeof(int);/*Length of integer*/
  /*fill sendBuffer with data*/                                    
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
  /*Record the Clock before Sending*/
  struct timeval start_time, end_time;
//gettimeofday(&start_time, NULL);
  /* Send the data to the server */
  if (send(sock, sendBuffer, sendLen, 0) != sendLen)
    return -1;
  /*Record the clock after Send completed Successfully*/
//gettimeofday(&end_time, NULL);
  /*Calculate time in ns of RTT*/
  //time_spent = 1000*((unsigned int)end_time.tv_usec-(unsigned int)start_time.tv_usec);
//printf("RTT is %d\n",time_spent);
  /* Receive ACK */
  if ((bytesRcvd = recv(sock, recBuffer, recLen, 0)) <= 0)
    return -1;
  close(sock);
  printf("closed socket successfully\n");
  //exit(0);
  printf("exit successfully\n");
  return 0;
}
