#include "server.h"

int create_server_socket(void) {
    int listenfd, opt = 1;
    struct sockaddr_in srv;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        return -1;
    }
    
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        return -1;
    }
    
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = INADDR_ANY;
    srv.sin_port = htons(PORT);
    
    if (bind(listenfd, (struct sockaddr*)&srv, sizeof(srv)) < 0) {
        perror("bind");
        return -1;
    }
    
    if (listen(listenfd, 10) < 0) {
        perror("listen");
        return -1;
    }
    
    printf("Serveur démarré sur le port %d\n", PORT);
    return listenfd;
}

void run_iterative_server(void) {
    int listenfd, connfd;
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE + 100];
    int client_num = 0;
    ssize_t nread;
    
    listenfd = create_server_socket();
    if (listenfd < 0) {
        exit(EXIT_FAILURE);
    }
    
    printf("Serveur itératif en attente...\n");
    
    while (1) {
        connfd = accept(listenfd, NULL, NULL);
        if (connfd < 0) {
            perror("accept");
            continue;
        }
        
        client_num++;
        printf("Connexion #%d acceptée\n", client_num);
        
        memset(buffer, 0, BUFFER_SIZE);
        nread = read(connfd, buffer, BUFFER_SIZE - 1);
        
        if (nread > 0) {
            snprintf(response, sizeof(response), 
                     "[Connexion #%d] Echo : %s", client_num, buffer);
            write(connfd, response, strlen(response));
            printf("Client #%d traité\n", client_num);
        }
        
        close(connfd);
        printf("Connexion #%d fermée\n", client_num);
    }
    
    close(listenfd);
}
