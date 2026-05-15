#include "server.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s {iterative|fork|thread|select|daemon}\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "iterative") == 0) {
        run_iterative_server();
    } 
    else if (strcmp(argv[1], "fork") == 0) {
        run_fork_server();
    }
    else if (strcmp(argv[1], "thread") == 0) {
        run_thread_server();
    }
    else if (strcmp(argv[1], "select") == 0) {
        run_select_server();
    }
    else if (strcmp(argv[1], "daemon") == 0) {
        run_daemon_server();
    }
    else {
        printf("Mode inconnu: %s\n", argv[1]);
    }
    
    return 0;
}
