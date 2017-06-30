
//server program

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#define MAX 500
#define PORT 5563
#define SA struct sockaddr

int add1(int a,int b)
{
  return a+b;
}

float add2(float a,float b)
{
  return a+b;
}

int mul1(int a,int b)
{
  return a*b;
}

float mul2(float a,float b)
{
  return a*b;
}

void server_stub(int sockfd)
{
  char buff[MAX];
  int n,a,b,res1;
  char *temp[10],*temp1;
  int cnt=0,i;
  float res2;
  
  bzero(buff,MAX);
  
  read(sockfd,buff,sizeof(buff));
  printf("\nInput from client: %s\n",buff);
   
  temp[cnt++]=(char *)strtok(buff,","); 
  
  while(1)
    {
      temp1=(char *)strtok(NULL,",");
      if(temp1==NULL)
	break;
      temp[cnt++]=temp1;
    }
    
  if(strcmp(temp[0],"add")==0)
    if(atoi(temp[3])==1)		
      {
	res1=add1(atoi(temp[1]),atoi(temp[2]));
	sprintf(buff,"%d",res1);
      }
    else
      {
	res2=add2(atof(temp[1]),atof(temp[2]));
	sprintf(buff,"%f",res2);
      }
  else
    if(atoi(temp[3])==1)
      {
	res1=mul1(atoi(temp[1]),atoi(temp[2]));
	sprintf(buff,"%d",res1);
      }		
    else
      {
	res2=mul2(atof(temp[1]),atof(temp[2]));
	sprintf(buff,"%f",res2);
      }
  n=0;
  
  write(sockfd,buff,sizeof(buff));
  bzero(buff,MAX);  
}

int main()
{
  int sockfd,connfd,len1;
  struct sockaddr_in servaddr,cli;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd==-1)
    {
      printf("socket creation failed...\n");
      exit(0);
    }
  else
    printf("Socket successfully created..\n");
  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(PORT);
  if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
    {
      printf("socket bind failed...\n");
      exit(0);
    }
  else
    printf("Socket successfully binded..\n");
  if((listen(sockfd,5))!=0)
    {
      printf("Listen failed...\n");
      exit(0);
    }
  else
    printf("Server listening..\n");
  len1=sizeof(cli);
  connfd=accept(sockfd,(SA *)&cli,&len1);
  if(connfd<0)
    {
      printf("server acccept failed...\n");
      exit(0);
    }
  else
    printf("server acccept the client...\n");
  server_stub(connfd);
  close(sockfd);
}
