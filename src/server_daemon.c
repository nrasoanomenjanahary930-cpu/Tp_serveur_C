#include "server.h"

#define PIDFILE "/var/run/myserverd.pid"

void daemonize(const char *pidfile) {
    pid_t pid;
    
    pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);
    
    setsid();
    
    pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);
    
    chdir("/");
    umask(0);
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_WRONLY);
    
    FILE *f = fopen(pidfile, "w");
    if (f) {
        fprintf(f, "%d", getpid());
        fclose(f);
    }
}

void init_syslog(void) {
    openlog("myserverd", LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "Daemon démarré (PID: %d)", getpid());
}

void run_daemon_server(void) {
    daemonize(PIDFILE);
    init_syslog();
    syslog(LOG_INFO, "Serveur daemon en cours d'exécution");
    run_fork_server();
}
