#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

struct data{
	unsigned char MsgID;
	unsigned char Flags;
};

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000];
   char recvline[1000];
   int result;
   int port;
   int msgID;
   int flag;
   struct data clientRequest;
   
   msgID = atoi(argv[3]);
   flag  = atoi(argv[4]);

   if (argc < 5)
   {
	  printf("You did not enter the correct number of parameters, arguments follow: IP PORT MSGNUM FLAG \n");
	  printf("the number of args is only: %i \n", argc);
      //printf("usage:  udpcli \n");
      return 0;
   }
   else if (msgID < 1 || msgID> 5)
   {
	   printf("message id is: %i\n", msgID);
	   printf("Invalid message id number, follow protocol \n");
	   return 0;
   }
   else if (flag < 1 || flag > 2)
   {
	   printf("flag is: %i\n", flag);
	   printf("Invalid flag number, follow protocol \n");
	   return 0;
   }
   else if (msgID == 5 && flag == 2)
   {
	   printf("This flag is not supported for minutes!\n");
	   return 0;
   }

   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   if ( sockfd == -1 )
   {
       printf ("Could not create socket \n");
       return 0;
   }
   
   port = atoi(argv[2]);

   memset(&servaddr,0,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(port);
   
   clientRequest.MsgID = msgID;
   clientRequest.Flags = flag;
   

    printf ("You have sent message id: %i, flag: %i to the server..\n", clientRequest.MsgID, clientRequest.Flags);	
    result = sendto(sockfd, &clientRequest, sizeof(clientRequest), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (result < 0)
	{
		printf("struct failed to send to server!\n");
	}
	
		n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
		fputs(recvline,stdout);
	
	
	
}

