#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>



struct data{
	unsigned char MsgID;
	unsigned char Flags;
};


int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[1000];
   int result;
   int port;
   char dateFormat[500];
   int strLength;
   struct data receivedInfo;
   time_t time_format;
   struct tm *t;

   
   if (argc < 2)
	{
		
		printf("You did not enter the correct number of parameters, you must specify a port! \n");
		printf("the number of args is only: %i \n", argc);
		return 0;
		//
	}
	
	
   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   if ( sockfd == -1 )
   {
       printf ("Could not create socket \n");
       return 0;
   }
   
   port = atoi(argv[1]);

   memset(&servaddr,0,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(port);
   result = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   
   
   if ( result == -1 )
   {
       printf ("Could not bind \n");
       return 0;
   }

   
   time(&time_format);
	  t = localtime(&time_format);
	  strftime(dateFormat, 500, "%c", t);
	  printf("time currently is: |%s|\n", dateFormat);
   
   for (;;)
   {
      len = sizeof(cliaddr);
      n = recvfrom(sockfd, &receivedInfo, sizeof(receivedInfo), 0, (struct sockaddr *)&cliaddr,&len);
	  //time(&time_format);
	  //time = localtime(&time_format);
	 // strftime(dateFormat, 500, "%c", time);
	 // printf("time currently is: |%s|\n", time);
	  //
	  if (receivedInfo.MsgID == 1){
		  if(receivedInfo.Flags == 1)
		  {
				time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%m", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf(" sent: month in decimal - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		 }
	  
		  else if(receivedInfo.Flags == 2)
		  {
				time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%B", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: month in english - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
	  
	  }
	  
	  else if (receivedInfo.MsgID == 2)
	  {
		  if (receivedInfo.Flags == 1)
		  {
				time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%d", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: day in numeric - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  else if (receivedInfo.Flags == 2)
		  {
				time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%A", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: day in english - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  
	  }
	  
	  else if (receivedInfo.MsgID == 3)
	  {
		  if (receivedInfo.Flags == 1)
		  {
			  time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%Y", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: year in 4 digits - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  else if (receivedInfo.Flags == 2)
		  {
			  time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%y", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: year in 2 digits - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  
	  }
	  
	  else if (receivedInfo.MsgID == 4)
	  {
		  if (receivedInfo.Flags == 1)
		  {
			  time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%I", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: 12 hour time - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  else if (receivedInfo.Flags == 2)
		  {
			  time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%H", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: 24 hr time - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  
	  }
	  
	  else if (receivedInfo.MsgID == 5)
	  {
		  if (receivedInfo.Flags == 1)
		  {
			  time(&time_format);
				t = localtime(&time_format);
				strftime(dateFormat, 500, "%M", t);
				strLength = strlen(dateFormat) + 1;
				char holder[strLength];
				strcpy(holder, dateFormat);
				result = sendto(sockfd,holder,sizeof(holder),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				printf("-------------------------------------------------------\n");
				printf("sent: minutes - %s  number of bytes - %i bytes \n", holder,result);
				printf("-------------------------------------------------------\n");
		  }
		  else if (receivedInfo.Flags == 2)
		  {
				
		  }
		  
	  }
      
   }
}

