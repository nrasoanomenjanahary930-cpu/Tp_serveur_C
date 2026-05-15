CC = gcc
CFLAGS = -Wall -Wextra -pthread -Iinclude
LDFLAGS = -pthread
SRCDIR = src
OBJDIR = obj
TARGET = myserverd

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS) | $(OBJDIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c include/server.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

distclean: clean
	rm -f $(TARGET)

# Tests
test1: $(TARGET)
	@echo "=== TEST PARTIE 1: Serveur itératif ==="
	./$(TARGET) iterative

test2: $(TARGET)
	@echo "=== TEST PARTIE 2: Serveur fork() ==="
	./$(TARGET) fork

test3: $(TARGET)
	@echo "=== TEST PARTIE 3: Serveur thread ==="
	./$(TARGET) thread

test4: $(TARGET)
	@echo "=== TEST PARTIE 4: Serveur select ==="
	./$(TARGET) select

test5: $(TARGET)
	@echo "=== TEST PARTIE 5: Daemon ==="
	sudo ./$(TARGET) daemon

stop:
	sudo pkill myserverd

status:
	ps aux | grep $(TARGET) | grep -v grep

logs:
	sudo tail -f /var/log/syslog | grep myserverd

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) iterative

help:
	@echo "Commandes disponibles:"
	@echo "  make          - Compiler le projet"
	@echo "  make clean    - Nettoyer les fichiers objets"
	@echo "  make distclean- Nettoyer tout"
	@echo "  make test1    - Tester partie 1 (itératif)"
	@echo "  make test2    - Tester partie 2 (fork)"
	@echo "  make test3    - Tester partie 3 (thread)"
	@echo "  make test4    - Tester partie 4 (select)"
	@echo "  make test5    - Tester partie 5 (daemon)"
	@echo "  make stop     - Arrêter le serveur"
	@echo "  make status   - Vérifier si le serveur tourne"
	@echo "  make logs     - Voir les logs en temps réel"
	@echo "  make valgrind - Vérifier les fuites mémoire"

.PHONY: all clean distclean test1 test2 test3 test4 test5 stop status logs valgrind help
