#include "server.h"
#include <sys/wait.h>

static int client_counter = 0;

void sigchld_handler(int signo) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void handle_client_fork(int connfd, int num) {
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE+100];
    
    memset(buffer, 0, BUFFER_SIZE);
    read(connfd, buffer, BUFFER_SIZE-1);
    
    snprintf(response, sizeof(response), 
             "[Connexion #%d] Echo : %s", num, buffer);
    write(connfd, response, strlen(response));
    
    close(connfd);
    printf("Fils %d: Client #%d traité\n", getpid(), num);
    exit(0);
}

void run_fork_server(void) {
    int listenfd, connfd;
    struct sigaction sa;
    
    listenfd = create_server_socket();
    if (listenfd < 0) exit(1);
    
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);
    
    printf("Serveur FORK() démarré sur port %d\n", PORT);
    
    while (1) {
        connfd = accept(listenfd, NULL, NULL);
        if (connfd < 0) continue;
        
        client_counter++;
        printf("Connexion #%d - Création d'un fils\n", client_counter);
        
        pid_t pid = fork();
        
        if (pid == 0) {
            close(listenfd);
            handle_client_fork(connfd, client_counter);
        } else if (pid > 0) {
            close(connfd);
        }
    }
    
    close(listenfd);
}
