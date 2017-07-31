#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUF 50
//create out neccessary packet struct to send

typedef struct packet
{
    int I;
    char C;
    float F;
}packet;

void messageError(char *s, int sock);

int main(int argc, char *argv[])
{
    int x;
    int length;
    int socket1;
    int port_X;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUF];
    packet dataSend,dataBuffer ;
    //checks the port
    if (argc < 3)
    {
        fprintf(stderr,"Usage %s hostname port\n", argv[0]);
        exit(0);
    }
    
    port_X = atoi(argv[2]); //ascii to int
    socket1 = socket(AF_INET, SOCK_DGRAM, 0); //open new socket
    messageError("Cannot open the socket", socket1);
    
    server = gethostbyname(argv[1]);//connect to the server via quering
    
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host!\n"); //checks the server
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));//places value into pointer s
    
    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(port_X);
    
    length = sizeof(struct sockaddr_in);
    

    printf("\n Connection established to Server  <%s>\n",argv[1]); //only shows when we have actual connection
    printf("\n Please enter data:\n");
    printf(" Enter an integer: ");
    scanf("%d", &dataBuffer.I);
    printf(" Enter a character: ");
    scanf("\n%c", &dataBuffer.C);
    printf(" Enter a float number: ");
    scanf("%f", &dataBuffer.F);
    
    dataSend.I = htonl((uint32_t)dataBuffer.I); //send that the data into buffer to be sent
    dataSend.C = dataBuffer.C;
    dataSend.F = dataBuffer.F;
    
    bzero(buffer, BUF);
    sprintf(buffer,"%f",dataSend.F);
    //actually sends the data if no we display the error message
    x = sendto(socket1,&dataSend,sizeof(dataSend),0,(struct sockaddr *)&serv_addr,length);
    messageError("Cannot write to socket",x);
    
    x = sendto(socket1,buffer,sizeof(buffer),0,(struct sockaddr *)&serv_addr,length);
    messageError("Cannot write to socket",x);
    
    x = recvfrom(socket1,buffer,sizeof(buffer),0,(struct sockaddr *)&serv_addr,(socklen_t *)&length);
    messageError("Error reading from the Socket!",x);
    
    printf("\n Data was successfully sent to Server <%s>",argv[1]);
    printf("\n Message from Server: <%s>\n",buffer);
    printf("\nTerminating Client1 Connection\n");
    close(socket1); // Disconnect socket of c1
    
    return 0;
}
//error message if socket cannot send
void messageError(char *s, int sock)
{
    if (sock<0){
        perror(s);
        exit(1);
    }
}

