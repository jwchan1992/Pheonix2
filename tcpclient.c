#include "inet.h"
#define BUFSIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <dirent.h>


void deleteFile(int sockfd){	//Deleting file on client-site
	printf("Deleting a file...");
	
	//Setting directory
	char content[256];
	char dir[256] = "/home/";
	char hostname[256]="junjeck";
	char file[256] = "/client/";
	strcat(dir, hostname);
	strcat(dir, file);
	printf("\nPath: %s", dir);
	
	//Create directory if it does not exist	
	struct stat st = {0};
	if(stat(dir, &st) == -1){
	  mkdir(dir, 0700);
	}

	//Printing files that is available from the directory
	printf("\nAvailable file: \n");
	DIR *directory;
	struct dirent *ent;
	if((directory = opendir(dir)) != NULL){
	  while((ent = readdir(directory)) != NULL){
		printf("%s ", ent->d_name);
	  }
	  closedir(directory);
	}
	else{
	  perror("ERROR");
	  exit(0);
	}

	//Getting file name to be deleted
	char filename[256];
	printf("\nPlease enter the file name that you want to delete: ");
	scanf("%s", filename);	
	//fgets(filename, 256, stdin);

	
	if(filename != NULL){

		strcat(dir, filename);
		FILE *fp;
		
		//Check if file available
		fp = fopen(dir, "r");
		if(fp == NULL){
		  printf("\nERROR: File cannot be created");
		  perror("fopen");	
		  exit(0);	
		}
		else{	//Deleting file
		  int status = remove(dir);
		  if(status == 0){
			printf("\nFile deleted successfully!");
			fclose(fp);
		  }else{
			printf("\nERROR: unable to delete the file");
			exit(0);
		  }
		}
	}
}//end delete

void createFolder(int sockfd){
	char createname[20];
	printf("Enter directory name that you want to create: ");
	scanf("%s", createname);

	/* set the path/name of the directory that want to create */ 
	char createDirectory[30]; 
	strcpy(createDirectory, "/home/"); 
	strcat(createDirectory, "junjeck"); 
	strcat(createDirectory, "/"); 
	strcat(createDirectory, createname);

	/* Check the path exist or not, if not, create one */ 
	struct stat s; 
	if(stat(createDirectory, &s) == -1){ 
	mkdir(createDirectory, 0700); } 

}

void deleteFolder(sockfd){
	int valid2=0;	
	
	while(valid2==0)
	{
	char deletename[20];
	printf("\nEnter directory name that you want to delete: ");
	scanf("%s", deletename);

	/* set the path of the directory that want to delete */ 
	char deleteDirectory[30]; 
	strcpy(deleteDirectory, "/home/"); 
	strcat(deleteDirectory, "junjeck"); 
	strcat(deleteDirectory, "/"); 
	strcat(deleteDirectory, deletename);

	/* select all the files inside the directory that want to delete */
	char selectSubDirectory[50];
	strcpy(selectSubDirectory, "exec rm -r ");
	strcat(selectSubDirectory, "/home/"); 
	strcat(selectSubDirectory, "junjeck"); 
	strcat(selectSubDirectory, "/"); 
	strcat(selectSubDirectory, deletename);
	strcat(selectSubDirectory, "/*"); 

	/* Check the path exist or not, if exist, delete it */ 
	struct stat s; 
	if(stat(deleteDirectory, &s) != -1){
	system(selectSubDirectory);
	rmdir(deleteDirectory); 
	printf("\nfolder %s deleted successfully!",deletename);
	valid2=1;}
	else{
		printf("\nPlease enter valid folder name again");	 	
		valid2=0;
	}
	}//end while

}

void copyFolder(sockfd)
{
	int src_fd, dst_fd,n_chars,n, err;
	char copyname[20], buf[1024];/*Buffer to store files content*/
	printf("Enter directory name that you want to copy: ");
	scanf("%s", copyname);

	/* set the path/name of the directory that want to create */ 
	char copyDirectory[30]; 
	strcpy(copyDirectory, "/home/"); 
	strcat(copyDirectory, "junjeck"); 
	strcat(copyDirectory, "/"); 
	strcat(copyDirectory, copyname);

	/* set the source of the direcoty*/
	char sourceDirectory[30]; 
	strcpy(sourceDirectory, "/home/"); 
	strcat(sourceDirectory, "junjeck"); 
	strcat(sourceDirectory, "/client/"); 
	
	
	//copy all file in the directory
	  DIR* pnOpenDir = NULL;    /*DIR Pointer to open Dir*/
    	  DIR* pnReadDir = NULL;    /*DIR POinter to read directory*/

	struct    dirent* spnDirPtr;    /* struct dirent to store all files*/

	if((pnOpenDir = opendir(sourceDirectory)) != NULL){
            int nErrNo = 0;
	  while((spnDirPtr = readdir(pnOpenDir)) != NULL){
		if(nErrNo == 0)
                nErrNo = errno;
		printf("\n Now writing %s file...",spnDirPtr->d_name);
		
		printf("\n dest file name = %s/%s\n", copyDirectory, spnDirPtr->d_name);
		struct stat st_buf;
                stat(spnDirPtr->d_name, &st_buf);
                if (S_ISDIR (st_buf.st_mode))
                {
                   continue;
                 }
		else if (S_ISREG (st_buf.st_mode))
               {
                    FILE* pnReadFile = fopen(spnDirPtr->d_name,"r");

                   if(pnReadFile)
                   {
                    printf("\n Now reading %s file...",spnDirPtr->d_name);

                    char strDestFileName[1024] = {0};
                   sprintf(strDestFileName, "%s/%s", copyDirectory, spnDirPtr->d_name);
                   printf("\n dest file name = %s\n", strDestFileName);

                  FILE* pnWriteFile  = fopen(strDestFileName, "w");    /*File Pointer to write in file*/
                if(pnWriteFile)
                {
                     

                        while(fgets(buf, 1024, pnReadFile))
                        {
                            fputs(buf, pnWriteFile);
                        }
                    fclose(pnWriteFile);
                }
                 else
                {
                     printf("\n Unable to open file %s", strDestFileName);
               }
               fclose(pnReadFile);
           }// close file
	   else
           {
              printf ("\nERROR! File Could not be open for reading");
            }
        
	  }//end while
	  
	}
	closedir(pnOpenDir);
	}
	else{
	  perror("ERROR");
	  exit(0);
	}

    	

}

main(int argc, char * argv[])
{
	int sockfd;
	char buffer[BUFSIZE+1];
	char x [BUFSIZE+1];
	struct sockaddr_in serv_addr;

if(argc <=1)
{
	printf("How to use: %s remoteIPaddress [example./ client 127.0.0.1]\n", argv[0]);
	exit(1);
}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons (SERV_TCP_PORT);
inet_pton (AF_INET, argv[1], &serv_addr.sin_addr);

if((sockfd= socket(AF_INET, SOCK_STREAM,0))<0)
{
	perror("Client: socket() error\n");
	exit(1);
}

if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
perror("Client: connect() error\n");
exit(1);
}
int count=0;
while(count==0)
{
	
	printf("\n[ 1.Send file. 2.Download 3.delete file 4.create folder 5.delete folder 6.copy folder 7. exit]\n");
	fgets(buffer,1024,stdin);
	send (sockfd, buffer, BUFSIZE,0);
	int choose;
	choose = atoi(buffer);
	
if(choose == 1){
	/* Send File to Server */
        
	printf("[Client] Select the File you which to send to your directory.\n 1.aaa.txt  2.bbb.txt   3.ccc.txt\n");
	fgets(buffer,1024,stdin);
	send (sockfd, buffer, BUFSIZE,0);
	int option;
	option = atoi(buffer);
	if(option==1)
	{		
		char* fs_name ="/home/junjeck/client/aaa.txt";
        	char sdbuf[BUFSIZE]; 
		printf("[Client] Sending aaa.txt to the Server... \n");
		FILE *fs = fopen(fs_name, "r");
		bzero(sdbuf, BUFSIZE); 
        	int fs_block_sz; 
        	while((fs_block_sz = fread(sdbuf, sizeof(char), BUFSIZE, fs)) > 0)
        	{
            		if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
           		 {
                		fprintf(stderr, "ERROR: Failed to send file aaa.txt. (errno = )\n");
               			exit(1);
           		 }
            		bzero(sdbuf, BUFSIZE);
       		 }
		printf("[Client] Sending aaa.txt to the Server... \n");
        	printf("Ok File aaa.txt from Client was Sent!\n File are saved in Server\n");
		fclose(fs); 
		count=0;
	}//end option 1
	else if(option==2)
	{
		char* fs_name ="/home/junjeck/client/bbb.txt";
        	char sdbuf[BUFSIZE]; 
		printf("[Client] Sending aaa.txt to the Server... \n");
		FILE *fs = fopen(fs_name, "r");
		bzero(sdbuf, BUFSIZE); 
        	int fs_block_sz; 
        	while((fs_block_sz = fread(sdbuf, sizeof(char), BUFSIZE, fs)) > 0)
        	{
            		if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
           		 {
                		fprintf(stderr, "ERROR: Failed to send file aaa.txt. (errno = )\n");
               			exit(1);
           		 }
            		bzero(sdbuf, BUFSIZE);
       		 }
		printf("[Client] Sending bbb.txt to the Server... \n");
        	printf("Ok File bbb.txt from Client was Sent!\n File are saved in Server\n");
		fclose(fs); 
		count=0;
	}//end option 2
	else if(option==3)
	{
		char* fs_name ="/home/junjeck/client/ccc.txt";
        	char sdbuf[BUFSIZE]; 
		printf("[Client] Sending aaa.txt to the Server... \n");
		FILE *fs = fopen(fs_name, "r");
		bzero(sdbuf, BUFSIZE); 
        	int fs_block_sz; 
        	while((fs_block_sz = fread(sdbuf, sizeof(char), BUFSIZE, fs)) > 0)
        	{
            		if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
           		 {
                		fprintf(stderr, "ERROR: Failed to send file aaa.txt. (errno = )\n");
               			exit(1);
           		 }
            		bzero(sdbuf, BUFSIZE);
       		 }
		printf("[Client] Sending ccc.txt to the Server... \n");
        	printf("Ok File ccc.txt from Client was Sent!\n File are saved in Server\n");
		fclose(fs); 
		count=0;
	}//end option 3
	
	//fs_name =strtok(buffer,"");

	//char* name = malloc(strlen(fs_name)+strlen(filename) + 2);
    	//sprintf(name,"%s%s", fs_name, filename);
	count=0;
}//end  choose 1

else if (choose == 2)
{
	 /*Receive File from Server */
        
	printf("Please select the File need to Dowload.\n1.chan 2.jun\n");
	fgets(buffer,1024,stdin);
	send(sockfd, buffer, BUFSIZE,0);
	int option2;
	option2=atoi(buffer);
	//printf("Please Write the Filename to Store File:\n");
	//gets(buffer);
	//char* name = malloc(strlen(fr_name)+strlen(buffer) + 2);
    	//sprintf(name,"%s%s", fr_name, buffer);
        if(option2==1)
	{
		char* fr_name = "/home/junjeck/client/chan.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
		{
			//strcpy(buffer, "0");
			//send(new_sockfd, buffer, BUFSIZE, 0);
            		printf("File chan.txt Cannot be opened file on server.\n");
			return (0);
		}
		
	    bzero(buffer, BUFSIZE); 
            int fr_block_sz = 0;
            while((fr_block_sz = recv(sockfd, buffer, BUFSIZE, 0)) > 0) 
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
            }
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
            printf("Ok Received from Server!! File are stored in Folder clientFile!!\n");
            fclose(fr); 
	count=0;
	}//end option1
	else if(option2==2)
	{
		char* fr_name = "/home/junjeck/client/jun.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
		{
			//strcpy(buffer, "0");
			//send(new_sockfd, buffer, BUFSIZE, 0);
            		printf("File %s Cannot be opened file on server.\n", fr_name);
			return (0);
		}
		
	    bzero(buffer, BUFSIZE); 
            int fr_block_sz = 0;
            while((fr_block_sz = recv(sockfd, buffer, BUFSIZE, 0)) > 0) 
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
            }
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
            printf("Ok Received from Server!! File are stored in Folder clientFile!!\n");
            fclose(fr); 
		count=0;
	}//end option2

	count=0;
}//end if choose 2
else if(choose == 3)
{
	deleteFile(sockfd);	
	count = 0;
}else if(choose == 4)
{
	createFolder(sockfd);
	count=0;
}
else if(choose == 5)
{
	deleteFolder(sockfd);
	count=0;
}
else if(choose==6)
{
	copyFolder(sockfd);
	count=0;
}
else if(choose == 7){
	count=1;
}	
else
{
	printf("Make Sure You are Enter Valid Number");
	count=0;
	//recv(sockfd, buffer, BUFSIZE,0);//receive meassage from server
	//printf("Message received from server: %s\n", buffer);
}

}//while (strlen(buffer)!=2 && buffer[0]!='q');
close (sockfd);

}



