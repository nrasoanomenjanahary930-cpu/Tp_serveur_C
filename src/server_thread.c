#include "server.h"

static int connexions_actives = 0;
static int client_counter = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define MAX_THREADS 16

void* handle_client_thread(void* arg) {
    int connfd = *(int*)arg;
    free(arg);
    
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE+100];
    int num;
    
    pthread_mutex_lock(&mutex);
    client_counter++;
    num = client_counter;
    connexions_actives++;
    printf("Thread %lu: Client #%d (actifs: %d/%d)\n", 
           pthread_self(), num, connexions_actives, MAX_THREADS);
    pthread_mutex_unlock(&mutex);
    
    memset(buffer, 0, BUFFER_SIZE);
    read(connfd, buffer, BUFFER_SIZE-1);
    
    snprintf(response, sizeof(response), 
             "[Connexion #%d] Echo : %s", num, buffer);
    write(connfd, response, strlen(response));
    
    close(connfd);
    
    pthread_mutex_lock(&mutex);
    connexions_actives--;
    printf("Thread %lu: Client #%d terminé (actifs: %d/%d)\n", 
           pthread_self(), num, connexions_actives, MAX_THREADS);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void run_thread_server(void) {
    int listenfd, connfd;
    pthread_t tid;
    int *fd_copy;
    
    listenfd = create_server_socket();
    if (listenfd < 0) exit(1);
    
    printf("Serveur THREAD démarré (max: %d threads)\n", MAX_THREADS);
    
    while (1) {
        connfd = accept(listenfd, NULL, NULL);
        if (connfd < 0) continue;
        
        pthread_mutex_lock(&mutex);
        int plein = (connexions_actives >= MAX_THREADS);
        pthread_mutex_unlock(&mutex);
        
        if (plein) {
            char *msg = "Serveur saturé! Réessayez plus tard.\n";
            write(connfd, msg, strlen(msg));
            close(connfd);
            printf("Connexion REFUSÉE (pool plein)\n");
            continue;
        }
        
        fd_copy = malloc(sizeof(int));
        *fd_copy = connfd;
        pthread_create(&tid, NULL, handle_client_thread, fd_copy);
        pthread_detach(tid);
    }
    
    close(listenfd);
}
