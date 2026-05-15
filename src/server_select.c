#include "server.h"

void run_select_server(void) {
    int listenfd, connfd, maxfd;
    int clients[FD_SETSIZE];
    fd_set readfds;
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE+100];
    int i;
    
    listenfd = create_server_socket();
    if (listenfd < 0) exit(1);
    
    for (i = 0; i < FD_SETSIZE; i++) {
        clients[i] = -1;
    }
    
    printf("Serveur SELECT() démarré\n");
    printf("FD_SETSIZE = %d\n", FD_SETSIZE);
    
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(listenfd, &readfds);
        maxfd = listenfd;
        
        for (i = 0; i < FD_SETSIZE; i++) {
            if (clients[i] != -1) {
                FD_SET(clients[i], &readfds);
                if (clients[i] > maxfd) maxfd = clients[i];
            }
        }
        
        struct timeval tv = {5, 0};
        int activity = select(maxfd + 1, &readfds, NULL, NULL, &tv);
        
        if (activity < 0) continue;
        
        if (activity == 0) {
            printf("Timeout - %d clients actifs\n", 
                   count_active_fds(clients, FD_SETSIZE));
            continue;
        }
        
        if (FD_ISSET(listenfd, &readfds)) {
            connfd = accept(listenfd, NULL, NULL);
            if (connfd >= 0) {
                for (i = 0; i < FD_SETSIZE; i++) {
                    if (clients[i] == -1) {
                        clients[i] = connfd;
                        printf("Client connecté (fd=%d) - Total: %d\n", 
                               connfd, count_active_fds(clients, FD_SETSIZE));
                        break;
                    }
                }
            }
        }
        
        for (i = 0; i < FD_SETSIZE; i++) {
            if (clients[i] != -1 && FD_ISSET(clients[i], &readfds)) {
                memset(buffer, 0, BUFFER_SIZE);
                int nread = read(clients[i], buffer, BUFFER_SIZE-1);
                
                if (nread <= 0) {
                    printf("Client fd=%d déconnecté\n", clients[i]);
                    close(clients[i]);
                    clients[i] = -1;
                } else {
                    snprintf(response, sizeof(response), "Echo: %s", buffer);
                    write(clients[i], response, strlen(response));
                }
            }
        }
    }
    
    close(listenfd);
}

int count_active_fds(int clients[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (clients[i] != -1) count++;
    }
    return count;
}
