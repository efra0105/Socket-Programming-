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

typedef struct type //create the struct needed to pass info
{
    int I;
    char C;
    float F;
}packet;
//declare functions needed
//delcare error message if needed
packet modify(packet p);
void messageError(char *s, int sock);

int main(int argc, char *argv[]){
    
    int x = 0, y;
    int socket1,socket2;
    int port_X, cPort;
    int length;
    char buffer[BUF];
    struct sockaddr_in server_address, client1_address, client2_address;
    socklen_t clilen;
    packet dataReceived, NData;
    struct hostent *server;
    //make sure the buffer is 0
    bzero(buffer, BUF);
    
    if (argc < 2)
    {
        fprintf(stderr,"ERROR establishing port!\n"); // Checks for the port to make sure it works
        exit(1);
    }
    
    socket1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //opens the socket
    messageError("Socket cannot be opened", socket1);
    
    socket2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //opens second socket
    messageError("Cannot open the socket", socket2);
    
    port_X = atoi(argv[1]); //ascii to integer
    server = gethostbyname(argv[2]);//gets the hostname this way we don't have to hardcode ip in
    cPort =  atoi(argv[3]); //ascii to int
    
    bzero((char *) &server_address, sizeof(server_address));
    bzero((char *) &client2_address, sizeof(client2_address));
    //this is where the program will use the information from querying the dns to connect
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_X);
    //this will allow it to get information from the 2nd client
    client2_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&client2_address.sin_addr.s_addr,server->h_length); //copies the bytes from pointer 1 and 2
    client2_address.sin_port = htons(cPort);
    length = sizeof(struct sockaddr_in);
    
    if (bind(socket1, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        messageError("Unable to bind socket!", socket1);
    }
    
    if (bind(socket2, (struct sockaddr *) &client2_address, sizeof(client2_address)) < 0)
    {
        messageError("Unable to bind socket!", socket2);
    }
    
    clilen = sizeof(client1_address);
    x = recvfrom(socket1,&dataReceived,sizeof(dataReceived),0,(struct sockaddr *)&client1_address,(socklen_t *)&clilen);
    messageError("Error when writing to socket", x);
    //
    x = recvfrom(socket1,buffer,sizeof(buffer),0,(struct sockaddr *)&client1_address,(socklen_t *)&clilen);
    sscanf(buffer,"%f",&dataReceived.F);
    
    printf("\nData has been received \n");
    printf("\nInteger = %d \nCharacter = %c \nFloat = %f\n", dataReceived.I, dataReceived.C, dataReceived.F);
    
    NData = modify(dataReceived);
    
    printf("\nData modified \n");
    printf("\nInteger = %d \nCharacter = %c \nFloat = %f\n", NData.I, NData.C, NData.F);
    
    
    x = sendto(socket1,"Data successfully received\n",26, 0,(struct sockaddr *)&client1_address,(socklen_t)clilen); //write()
    x = sendto(socket2,&NData,sizeof(NData),0,(struct sockaddr *)&client2_address,length);
    messageError("Cannot write to socket",x);
    
    x = sendto(socket2,buffer,sizeof(buffer),0,(struct sockaddr *)&client2_address,length);
    messageError("Unable to write to socket",x);
    printf("\n Data was successfully sent to Server <%s>",argv[2]);
    printf("\nTerminating Server Connections\n");
    close(socket1); // Disconnects Server using close()
    close(socket2); // Disconnects Server using close()
    return 0;
}
//calls error message if failure
void messageError(char *s, int sock)
{
    if (sock<0){
        perror(s);
        exit(1);
    }
}
//modify our int, char, float according to the project description
packet modify (packet p)
{
    p.I =(p.I)*2;
    p.F =(p.F)+1;
    if(p.C == 122)
        p.C = 97;
    else if(p.C == 90)
        p.C = 65;
    else
        p.C = p.C+1;
    return p;
}
