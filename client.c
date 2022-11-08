#include "./connect.h"

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char server_message[2000], client_message[2000];
    int server_struct_length = sizeof(servaddr);

    
    // Create IPv4 UDP socket:
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        fprintf(stderr, "Socket creation failed!\n");
	    exit(1);
    } 
    
    // Set port and IP:
    cliaddr.sin_family = AF_INET; // IPv4
    cliaddr.sin_port = htons(CLIENTPORT);
    cliaddr.sin_addr.s_addr = INADDR_ANY;
    

    
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message)); 

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
    //set timeout for socket
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 1000; //avg 480ms for roundtime
    // level = only set timeout for sockfd
    // option_name = SO_RCVTIMEO : set timeout value output function blocks due flow control
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout)) < 0) {
        perror("Error");
    }

    if ( bind(sockfd, (const struct sockaddr *)&cliaddr, 
            sizeof(cliaddr)) < 0 ) 
    { 
        fprintf(stderr, "Bind failed!\n");
	    exit(1);
    } 
    
    while(recvfrom(sockfd, server_message, sizeof(server_message), 
            0,(struct sockaddr*)&servaddr, &server_struct_length)<0);

    while(sendto(sockfd, connected, strlen("connected"), 0,
         (struct sockaddr*)&servaddr, server_struct_length) < 0);

    
    while(recvfrom(sockfd, server_message, sizeof(server_message), 
            0,(struct sockaddr*)&servaddr, &server_struct_length)<0);

    printf("%s\n", server_message);
    
    if(strcmp(server_message,"yes")==0)
        printf("Torjan can start\n");
    else
        return 0;//restart
    
    
    // Get input from the user:
    while(1)
    {
        printf("Enter commands: ");
        fgets(client_message,2000,stdin);
        int change = strlen(client_message);
        client_message[change - 1] = '\0';
        
        
    }
    
    

    return 0;  

}