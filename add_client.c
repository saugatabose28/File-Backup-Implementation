
//client program

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#define MAX 500
#define PORT 5563
#define SA struct sockaddr
#include<time.h>

void client_stub(int sockfd,char fun[50],void *a1,void *b1,int t)
{
  char buff[MAX],buff1[MAX];
  int n,*a,*b;
  float *f1,*f2,f3,f4;
  char sep=',';
	time_t start,end;
	double time_required;
		

	start=clock();

  if(t==1)
    {
      a=(int *)a1;
      b=(int *)b1;
      
      sprintf(buff1,"%s%c%d%c%d%c%d",fun,sep,*a,sep,*b,sep,t);

    }
  else if(t==2)
    {
      f1=(float *)a1;
      f2=(float *)b1;
      sprintf(buff1,"%s%c%f%c%f%c%d",fun,sep,*f1,sep,*f2,sep,t);
      
      printf("\n%s\n",buff1);	
    }
  write(sockfd,buff1,sizeof(buff1));
  
  bzero(buff,sizeof(buff));
  read(sockfd,buff,sizeof(buff));
  printf("\nResult is: %s\n",buff);

	end=clock();

	time_required=(double)end-start/1000000;

	printf("\nTime required=%f",time_required);
}

int main()
{
  int sockfd,connfd,a,b,c,type1,type2;
  int ch,t1,t2,flag;
  float f1,f2;
  void *v1,*v2;
  
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
  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  servaddr.sin_port=htons(PORT);
  if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0)
    {
      printf("connection with the server failed...\n");
      exit(0);
    }
  else
    printf("connected to the server..\n");
  
  printf("\nMenu:\n1)ADD\n2)Mul\n\n");
  printf("\nEnter the choice: ");
  scanf("%d",&ch);
  
  switch(ch)
    {
    case 1:
      
      
      printf("\nEnter the nos to add:\n");
      printf("\nEnter the type of numbers:\n1)Int\n2)Float:\n");		
      scanf("%d",&type1);
      
      switch(type1)
	{
	case 1:
	  printf("\nEnter the numbers:\n");
	  scanf("%d%d",&t1,&t2);		
	  
	  client_stub(sockfd,"add",&t1,&t2,1);			
	  break;
	  
	  
	case 2:
	  printf("\nEnter the numbers:\n");
	  scanf("%f%f",&f1,&f2);		
	  
	  client_stub(sockfd,"add",&f1,&f2,2);			
	  break;
	  
	default:
	  printf("\nWrong choice.\n");
	  
	}
      
      
      break;
      
    case 2:
      
      printf("\nEnter the nos to multiply:\n");
      printf("\nEnter the type of numbers:\n1)Int\n2)Float:\n");		
      scanf("%d",&type1);
      
      switch(type1)
	{
	case 1:
	  printf("\nEnter the numbers:\n");
	  scanf("%d%d",&t1,&t2);		
	  
	  client_stub(sockfd,"mul",&t1,&t2,1);
	  
	  break;
	  
	  
	case 2:
	  printf("\nEnter the numbers:\n");
	  scanf("%f%f",&f1,&f2);		
	  
	  client_stub(sockfd,"mul",&f1,&f2,2);			
	  break;
	  
	default:
	  printf("\nWrong choice.\n");
	  
	}
      
      break;
    default:
      printf("\nWrong choice.\n");
      
    }
  close(sockfd);
}
