// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    // -> AF_INET: é uma familia de protocolos, no caso o IPv4
    // -> SOCK_STREAM: o tipo do transporte que será usado
    // -> ULTIMO PARAMETRO: protocolo (no caso se for zero é o padrão)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    /*OPTIONAL*/ // Não entendi
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Permite o Servidor usar uma porta específica em quaisquer
    // dos endereços IP's do computador.
    address.sin_port = htons( PORT );

    /*Função Bind*/
    // Quando um socket é criado, ele não tem nem um endereço local
    // nem um endereço remoto. A função bind promove um numero de porta
    // de protocolo onde o servidor irá esperar pela requisição

    // Forcefully attaching socket to the port 8080
    // -> descritor do socket
    // -> address do tipo sockaddr: essa estrutua especifica o endereço local
    // a ser atribuido ao socket
    // -> Ultimo parametro: inteira que especifica o tamanho do endereço(depende do protocolo)
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    /*Função Listen*/
    // -> server_fd: descritor do socket que foi criado
    // queuesize (segundo parâmetro): tamanho da fila de requisições do servidor
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    /*Função Accept*/
    // Essa

    // -> server_fd: descritor do socket (no caso o original)
    // -> caddress(segundo parametro): endereço de uma estrutura do tipo sockaddr
    // -> caddresslen(terceiro parametro): ponteiro para um inteiro
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}
