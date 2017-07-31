#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define BUF 50
//create the neccessary struct
typedef struct type
{
    int I;
    char C;
    float F;
}packet;
//decalre error message funct
void messageError(char *s, int sock);

int main(int argc, char *argv[]){
    
    int x = 0, y;
    int socket1;
    int port_X;
    int length;
    
    char buffer[BUF];
    
    struct sockaddr_in serv_addr, cli_addr;
    
    socklen_t clilen;
    
    packet dataReceived, NData;
    
    bzero(buffer, BUF);
    //check if port is good
    if (argc < 2)
    {
        fprintf(stderr,"ERROR port is establishing!\n");
        exit(1);
    }
    //opens up the port
    socket1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    messageError("Socket wont open", socket1);
    //get the buffer ready to send
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //this is where the client actually connects
    port_X = atoi(argv[1]); //ascii to int
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_X);
    //create error message if cant bind to socket
    if (bind(socket1, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        messageError("Unable to bind socket!", socket1);
    }
    
    clilen = sizeof(cli_addr);
    //retrieve the data that is being sent
    x = recvfrom(socket1,&dataReceived,sizeof(dataReceived),0,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);
    messageError("Socket writing error", x);
    //message of data being recieved
    //try to recieve data
    x = recvfrom(socket1,buffer,sizeof(buffer),0,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);
    printf("\nData has been received \n");
    printf("\nInteger = %d \nCharacter = %c \nFloat = %f\n", dataReceived.I, dataReceived.C, dataReceived.F);
    printf("\nFinishing client_2 Connection\n");
    close(socket1); // dis from sock
    return 0;
}
//error message prompt
void messageError(char *s, int sock)
{
    if (sock<0){
        perror(s);
        exit(1);
    }
}