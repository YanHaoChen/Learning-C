#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>


#define Server_PortNumber 5555
#define Server_Address "127.0.0.1"

int main() {
    struct sockaddr_in server_addr;
    int sock, byte_sent, server_addr_length = sizeof(server_addr);
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)    printf("Error creating socket!\n");
    bzero(&server_addr, server_addr_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(Server_PortNumber);
    server_addr.sin_addr.s_addr = inet_addr(Server_Address);
    if (connect(sock, (struct sockaddr *)&server_addr,server_addr_length)==-1) {
        printf("connect failed!");
        close(sock);
    }
    char stop_buffer[1]="\0";
    char buffer[6]="hello\0";
    clock_t t1, t2;
    char buf[6];
    double sizeCount=0.0;
    int i = 0 ,outputpacket=0;
    t1 = clock();
    for(i=0;i < 59; i++) {
        outputpacket++;
        byte_sent = send(sock, buffer, sizeof(buffer),0);
        sizeCount +=6;
    }
    byte_sent = send(sock, stop_buffer, sizeof(stop_buffer), 0);
    t2 = clock();
    outputpacket++;
    sizeCount +=1;
    close(sock);
    printf("Server IP: %s\n", Server_Address);
    printf("Segment number: %d\n",outputpacket);
    printf("Time interval: %lf sec\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
    printf("Throughput: %lf Mbps\n",(sizeCount/((t2-t1)/(double)(CLOCKS_PER_SEC)))/1000);

    return 0;
}
