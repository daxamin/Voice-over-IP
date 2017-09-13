#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

//void filesend(char filesend);

#define MAXRCVLEN 1024
#define PORTNUM 5555

int main(int argc, char *argv[])
{
    char* msg;
    msg = malloc(256);
    
    int len;
    char buff[MAXRCVLEN + 1];
    int opt;
  
    struct sockaddr_in dest; /* socket info about the machine connecting to us */
    struct sockaddr_in serv; /* socket info about our server */
    int server_socket;            /* socket used to listen for incoming connections */
    socklen_t socksize = sizeof(struct sockaddr_in);
    
    //------------server code starts here
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(buff, 0, sizeof(buff)); 
    memset(&serv, 0, sizeof(serv));    /* zero the struct before filling the fields */
    
    serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    serv.sin_addr.s_addr = INADDR_ANY;//htonl((in_addr_t)0xc0a889fd); /* set our address to any interface */
    serv.sin_port = htons(PORTNUM);           /* set the server port number */    

    printf("server add:%s\n", inet_ntoa(serv.sin_addr));
    
    //------------end of server code

    //------------connection initialisation

    /* bind serv information to mysocket */

    bind(server_socket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
    if (listen(server_socket, 1) == -1)
    {
        printf("Failed to listen");
        return -1;
    }
    /* start listening, allowing a queue of up to 10 pending connection */
    

    int consocket = accept(server_socket, (struct sockaddr *)&dest, &socksize);
    printf("Client/destination add:%s\n", inet_ntoa(dest.sin_addr));
    
    //-------------end of connection
    
    //\\\\\\\\\\\\\\\\\\\\\\creating client-like on server---
    
    
    printf("Press\t 1 - VOIP\n\t 2 - CHAT\n");
    scanf("%d", &opt);
  
    if (opt == 1)
    {
    while(1)
    {
        

        printf("\n:");
        scanf("%s",msg);
        send(consocket, msg, strlen(msg), 0); 
        

        if (recv(server_socket, buff, MAXRCVLEN, 0))
        {
            len = recv(consocket, buff, MAXRCVLEN, 0);            
           
        
            buff[len] = '\0';
            printf("::: %s\n", buff);
        }
        else{
            printf("error recieving msg");
        }
        
        

        //-------------receiving code
        
        
        
    }
    }
    else{
        while(1){
            printf("Sending Requested File....\nSample.txt...\n");
            filesend("sample_text.txt", consocket);
            wait(500);
        }
    }

    close(server_socket);
    return EXIT_SUCCESS;
}

int filesend(filesend, consocket){
    FILE *fp = fopen("sample_text.txt","rb");
        if(fp==NULL)
        {
            printf("File NULL error");
            return 1;   
        }   

        
        while(1)
        {
        
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(consocket, buff, nread);
            }

            
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }
        return 0;

}

