#include "./connect.h" 
    
// Driver code 

//first send something to client, so that the client could get the address
//client get the address, send connect to server
//server begin to listen to port
//execute the command the client send and sned back the reply
int main(int argc, char *argv[]) {
    int sockfd; 
    char buffer[BUFSIZ]; 
    struct sockaddr_in servaddr, cliaddr;

    //set timeout for socket
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 1000; //avg 480ms for roundtime
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout)) < 0) {
        perror("Error");
    } 
        
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        fprintf(stderr, "Socket creation failed!\n");
	    exit(1);
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(SERVERPORT); 
    
    cliaddr.sin_family    = AF_INET; // IPv4 
    cliaddr.sin_addr.s_addr = inet_addr(CLIENTADDRESS);
    cliaddr.sin_port = htons(CLIENTPORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        fprintf(stderr, "Bind failed!\n");
	    exit(1);
    } 
        
    int len, n; 
    
    
    len = sizeof(cliaddr);  //len is value/result 
    
    while(sendto(sockfd, (const char *)connected, strlen(connected),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len)<0);

    while((n = recvfrom(sockfd, (char*)buffer, BUFSIZ,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len))<0);
    

    buffer[n] = '\0'; 
    printf("Server: Received message from %s: %s\n", inet_ntoa(cliaddr.sin_addr), buffer); 

    if (strcmp(buffer, connected) != 0)
    {
        sendto(sockfd, (const char *)no, strlen(no),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len);
        printf("Server: %s message sent.\n", no);
    } 

    else
    {
        sendto(sockfd, (const char *)yes, strlen(yes),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len);
        printf("Server: %s message sent.\n", yes);
    }
    
    while(1)
    {
        while((n = recvfrom(sockfd, (char*)buffer, BUFSIZ,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len))<0);
        buffer[n] = '\0';
        printf("%s\n", buffer);
        //execute the command here
    }
    return 0;
}



   