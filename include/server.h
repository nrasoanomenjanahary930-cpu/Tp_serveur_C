#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/select.h>

#define PORT 9999
#define BUFFER_SIZE 1024
#define BACKLOG 10
#define MAX_THREADS 16
#define PIDFILE "/var/run/myserverd.pid"

/* Fonctions principales */
int create_server_socket(void);

/* Partie 1 - Iterative */
void run_iterative_server(void);

/* Partie 2 - Fork */
void run_fork_server(void);
void sigchld_handler(int signo);

/* Partie 3 - Thread */
void run_thread_server(void);
void* handle_client_thread(void* arg);

/* Partie 4 - Select */
void run_select_server(void);

/* Partie 5 - Daemon */
void run_daemon_server(void);
void daemonize(const char *pidfile);
void init_syslog(void);

/* Utilitaires */
int count_active_fds(int clients[], int size);

#endif
