#include "inet.h"
#define BUFSIZE 1024
#include <string.h>
#include <errno.h>

main()
{
	int sockfd, new_sockfd, clilen;
	char buffer[BUFSIZE+1];//create a valable pass to socket
	struct sockaddr_in serv_addr, cli_addr; // create server addr and client addr
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)//create a stream TCP socket
	{
		perror("Server: socket() error\n");
		exit(1);
	}

printf("\nEcho Application Demo\n");

bzero((char *) & serv_addr, sizeof(serv_addr));//
serv_addr.sin_family = AF_INET;//
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//
serv_addr.sin_port = htons(SERV_TCP_PORT);//

if(bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr))<0 )
{
	perror("Server: blind() error\n");
	exit(1);
}

/* Get Server's IP address */
	FILE *fp;
	char returnData[64];
	char *token;
	char a[1000];	
	fp = popen("/sbin/ifconfig eth0", "r");
	while (fgets(returnData, 64, fp) != NULL)
	{
		/* store the string in returnData into variable a */
		strcat(a, returnData);
	}

	/* get the first token and walk through other tokens 
	   until the IP address token */
	token = strtok(a, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " addr:");

	/* print the IP address token */
	printf("Server IP address: %s\n", token);

printf("\nWaiting for connection... [bind]\n");
listen(sockfd, 5);
for(;;){
clilen = sizeof(cli_addr);
new_sockfd = accept(sockfd,(struct sockaddr * ) &cli_addr, &clilen);

if(fork()==0){
	close(sockfd);

if(new_sockfd >0)
	printf("\nClient connected now.\n");


int count=0;
while(count==0)
{
	recv(new_sockfd, buffer, BUFSIZE, 0);
	int ch1;
	ch1 = atoi(buffer);
if(ch1 == 1)
{
 	/*Receive File from Client */
       
	recv(new_sockfd, buffer, BUFSIZE, 0);
	int option;
	option=atoi(buffer);
	//char* name = malloc(strlen(fr_name)+strlen(buffer) + 2);
    	//sprintf(name,"%s%s", fr_name, buffer);
	//fr_name = buffer;
	if(option==1)
	{
		char* fr_name = "/home/junjeck/server/aaa.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
		{
		//strcpy(buffer, "0");
		//send(new_sockfd, buffer, BUFSIZE, 0);
            		printf("File aaa.txt Cannot be opened file on server.\n");
		//return (0);
		}
       	 	else
        	{
            		bzero(buffer, BUFSIZE); 
            		int fr_block_sz = 0;
            		while((fr_block_sz = recv(new_sockfd, buffer, BUFSIZE, 0)) > 0) 
            	{
                	int write_sz = fwrite(buffer, sizeof(char), fr_block_sz, fr);
                	if(write_sz < fr_block_sz)
                	{
                    		error("File write failed on server.\n");
                	}
               	 	bzero(buffer, BUFSIZE);
                	if (fr_block_sz == 0 || fr_block_sz != 512) 
                	{
                    		break;
                	}
            	}//end while
            		
			if(fr_block_sz < 0)
            		{
                		if (errno == EAGAIN)
                		{
                    		printf("recv() timed out.\n");
                		}
                		else
                		{
                    		fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                    		exit(1);
               			}
            		}
           		 printf("Ok received from client!\n");
            		fclose(fr); 
        	}//end else
	
	count=0;
	}//end option 1
       	else if(option==2)
	{
		char* fr_name = "/home/junjeck/server/bbb.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
		{
		//strcpy(buffer, "0");
		//send(new_sockfd, buffer, BUFSIZE, 0);
            		printf("File aaa.txt Cannot be opened file on server.\n");
		//return (0);
		}
       	 	else
        	{
            		bzero(buffer, BUFSIZE); 
            		int fr_block_sz = 0;
            		while((fr_block_sz = recv(new_sockfd, buffer, BUFSIZE, 0)) > 0) 
            	{
                	int write_sz = fwrite(buffer, sizeof(char), fr_block_sz, fr);
                	if(write_sz < fr_block_sz)
                	{
                    		error("File write failed on server.\n");
                	}
               	 	bzero(buffer, BUFSIZE);
                	if (fr_block_sz == 0 || fr_block_sz != 512) 
                	{
                    		break;
                	}
            	}//end while
            		
			if(fr_block_sz < 0)
            		{
                		if (errno == EAGAIN)
                		{
                    		printf("recv() timed out.\n");
                		}
                		else
                		{
                    		fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                    		exit(1);
               			}
            		}
           		 printf("Ok received from client!\n");
            		fclose(fr); 
        	}//end else		
	count=0;
	}//end option 2
        else if(option==3)
	{
		char* fr_name = "/home/junjeck/server/ccc.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
		{
		//strcpy(buffer, "0");
		//send(new_sockfd, buffer, BUFSIZE, 0);
            	printf("File aaa.txt Cannot be opened file on server.\n");
		//return (0);
		}
       	 	else
        	{
            		bzero(buffer, BUFSIZE); 
            		int fr_block_sz = 0;
            		while((fr_block_sz = recv(new_sockfd, buffer, BUFSIZE, 0)) > 0) 
            	{
                	int write_sz = fwrite(buffer, sizeof(char), fr_block_sz, fr);
                	if(write_sz < fr_block_sz)
                	{
                    		error("File write failed on server.\n");
                	}
               	 	bzero(buffer, BUFSIZE);
                	if (fr_block_sz == 0 || fr_block_sz != 512) 
                	{
                    		break;
                	}
            	}//end while
            		
			if(fr_block_sz < 0)
            		{
                		if (errno == EAGAIN)
                		{
                    		printf("recv() timed out.\n");
                		}
                		else
                		{
                    		fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                    		exit(1);
               			}
            		}
           		printf("Ok received from client!\n");
            		fclose(fr); 
        	}//end else		
	count=0;	
	}//end option 3

        /* Call the Script */
        //system("cd ; chmod +x script.sh ; ./script.sh");
	count=0;
            close(new_sockfd);
            printf("[Server] Connection with Client closed. Server will wait now...\n");
}

else if (ch1 ==2)
{
	recv(new_sockfd, buffer, BUFSIZE,0);
	int option2;
	option2=atoi(buffer);
	/* Send File to Client */
	//char* location = "/home/chan/server/";

	if(option2==1)
	{
		char sdbuf[BUFSIZE]; 
	
		char* fs_name = "/home/junjeck/server/chan.txt";	
		//char* name = malloc(strlen(location)+strlen(buffer) + 2);
    		//sprintf(name,"%s%s", location, buffer);
        	FILE *fs = fopen(fs_name, "r");
		if(fs == NULL)
        	{
            		printf("ERROR: File %s not found.\n", fs_name);
        	}
		else{
        		bzero(sdbuf, BUFSIZE); 
        		int fs_block_sz; 
       			 while((fs_block_sz = fread(sdbuf, sizeof(char), BUFSIZE, fs)) > 0)
        		{
           		 if(send(new_sockfd, sdbuf, fs_block_sz, 0) < 0)
            			{
                		fprintf(stderr, "ERROR: Failed to send file %s. (errno = )\n", fs_name);
                		exit(1);
           		 	}
            			bzero(sdbuf, BUFSIZE);
        		}
			printf("[Server] Sending %s to the Client... \n", fs_name);
       		 	printf("Ok File %s was Sent!\n", fs_name);
			fclose(fs);
        		printf("[Server] Connection with Client closed. Server will wait now...\n");
		}
	count=0;
	}//end option1
        else if(option2==2)
	{
		char sdbuf[BUFSIZE]; 
	
		char* fs_name = "/home/junjeck/server/jun.txt";	
		//char* name = malloc(strlen(location)+strlen(buffer) + 2);
    		//sprintf(name,"%s%s", location, buffer);
        	FILE *fs = fopen(fs_name, "r");
		if(fs == NULL)
        	{
            		printf("ERROR: File %s not found.\n", fs_name);
        	}
		else{
        		bzero(sdbuf, BUFSIZE); 
        		int fs_block_sz; 
       			 while((fs_block_sz = fread(sdbuf, sizeof(char), BUFSIZE, fs)) > 0)
        		{
           		 if(send(new_sockfd, sdbuf, fs_block_sz, 0) < 0)
            			{
                		fprintf(stderr, "ERROR: Failed to send file %s. (errno = )\n", fs_name);
                		exit(1);
           		 	}
            			bzero(sdbuf, BUFSIZE);
        		}
			printf("[Server] Sending jun.txt to the Client... \n");
       		 	printf("Ok File jun.txt was Sent!\n");
			fclose(fs);
        		printf("[Server] Connection with Client closed. Server will wait now...\n");
		}
	count=0;
	}//end option2
}
else if (ch1 == 3)
{
	count=0;
}
else if(ch1 == 4)
{
	count = 0;
}
else if(ch1 == 5)
{
	count = 0;
}
else if(ch1==6)
{
	count = 0;
}
else if(ch1 == 7)
{
	count=1;
}
else 
{
	count=0;
}

}//while(strlen(buffer)!=2 && buffer[0]=='q');

exit(0);
}

close(new_sockfd);
}
close(sockfd);

}
