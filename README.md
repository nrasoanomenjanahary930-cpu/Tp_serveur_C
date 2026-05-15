
Voici un **README.md** complet pour guider la compilation et l'exécution du projet.

---

## 📄 README.md

```markdown
# Serveur UNIX Complet - TP Final

## Description
Ce projet implémente un serveur TCP complet avec 5 modèles architecturaux différents:
- **Partie 1** : Serveur itératif
- **Partie 2** : Serveur avec fork()
- **Partie 3** : Serveur multi-thread (pthread)
- **Partie 4** : Serveur avec select()
- **Partie 5** : Serveur en mode daemon

---

## 📁 Structure du projet

```
tp_final/
├── include/
│   └── server.h
├── src/
│   ├── main.c
│   ├── server_iterative.c
│   ├── server_fork.c
│   ├── server_thread.c
│   ├── server_select.c
│   └── server_daemon.c
├── Makefile
└── README.md
```

---

## 🔧 COMPILATION

### 1. Nettoyer les anciens fichiers
```bash
make clean
```

### 2. Compiler le projet
```bash
make
```

### 3. Compilation complète (nettoyer + compiler)
```bash
make clean && make
```

### 4. Vérifier que la compilation a réussi
```bash
ls -la myserverd
```

**Résultat attendu:** Un fichier `myserverd` (vert) doit apparaître.

---

## 🚀 EXÉCUTION - PARTIE 1 (Itératif)

### Lancer le serveur
```bash
./myserverd iterative
```

### Tester (dans un autre terminal)
```bash
echo "Bonjour" | nc localhost 9999
```

### Test 2 clients (comportement séquentiel)
```bash
(echo "Premier" | sleep 3 | nc localhost 9999) &
(echo "Deuxième" | nc localhost 9999) &
```

---

## 🚀 EXÉCUTION - PARTIE 2 (Fork)

### Lancer le serveur
```bash
./myserverd fork
```

### Tester avec 8 clients simultanés
```bash
for i in {1..8}; do (echo "Client $i" | nc -q 1 localhost 9999) & done
```

### Vérifier les processus
```bash
ps aux | grep myserverd | grep -v grep
```

---

## 🚀 EXÉCUTION - PARTIE 3 (Thread)

### Lancer le serveur
```bash
./myserverd thread
```

### Tester avec 20 clients (saturation du pool)
```bash
for i in {1..20}; do (echo "Thread $i" | nc -q 1 localhost 9999) & done
```

### Vérifier les threads
```bash
ps -eLf | grep myserverd | grep -v grep
```

---

## 🚀 EXÉCUTION - PARTIE 4 (Select)

### Lancer le serveur
```bash
./myserverd select
```

### Tester
```bash
echo "Test select" | nc localhost 9999
```

### Test avec plusieurs clients
```bash
for i in {1..5}; do (echo "Select $i" | nc -q 1 localhost 9999) & done
```

---

## 🚀 EXÉCUTION - PARTIE 5 (Daemon)

### Lancer le daemon (nécessite sudo)
```bash
sudo ./myserverd daemon
```

### Vérifier que le daemon tourne
```bash
ps aux | grep myserverd | grep -v grep
```

### Voir le PID
```bash
cat /var/run/myserverd.pid
```

### Tester le daemon
```bash
echo "Test daemon" | nc localhost 9999
```

### Voir les logs
```bash
sudo tail -f /var/log/syslog | grep myserverd
```

### Arrêter le daemon
```bash
sudo kill $(cat /var/run/myserverd.pid)
# ou
sudo pkill myserverd
```

---

## 📋 COMMANDES RAPIDES AVEC MAKEFILE

| Commande | Description |
|----------|-------------|
| `make` | Compiler le projet |
| `make clean` | Nettoyer les fichiers objets |
| `make distclean` | Nettoyer tout (objets + exécutable) |
| `make test1` | Lancer serveur itératif |
| `make test2` | Lancer serveur fork |
| `make test3` | Lancer serveur thread |
| `make test4` | Lancer serveur select |
| `make test5` | Lancer daemon (sudo) |
| `make stop` | Arrêter le serveur |
| `make status` | Vérifier si le serveur tourne |
| `make logs` | Voir les logs en temps réel |
| `make valgrind` | Vérifier les fuites mémoire |
| `make help` | Afficher l'aide |

---

## ⚠️ DÉPANNAGE

### Erreur: "Address already in use"
```bash
sudo fuser -k 9999/tcp
```

### Erreur: "nc: command not found"
```bash
sudo apt install netcat-openbsd
```

### Erreur: "Permission denied"
```bash
chmod +x myserverd
```

### Erreur: "make: command not found"
```bash
sudo apt install make
```

### Erreur: "gcc: command not found"
```bash
sudo apt install gcc
```

---

## 📝 VÉRIFICATION RAPIDE

```bash
# 1. Compiler
make clean && make

# 2. Tester partie 1
./myserverd iterative &  # serveur en arrière-plan
sleep 1
echo "Test" | nc localhost 9999
pkill myserverd

# 3. Tester partie 5 (daemon)
sudo ./myserverd daemon
sleep 2
ps aux | grep myserverd
echo "Test" | nc localhost 9999
sudo pkill myserverd
```

---

## ✅ RÉSUMÉ DES COMMANDES ESSENTIELLES

```bash
# Compilation
make clean && make

# Partie 1
./myserverd iterative

# Partie 2
./myserverd fork

# Partie 3
./myserverd thread

# Partie 4
./myserverd select

# Partie 5
sudo ./myserverd daemon

# Arrêter
pkill myserverd
```

---

**Bon test! 🚀**
```

---

## 💾 Sauvegarder le README

```bash
cd ~/tp_final
nano README.md
```

**Copier-coller** le contenu ci-dessus, puis:

```bash
Ctrl + O → Enter → Ctrl + X
```

---

## ✅ Vérifier que le README est bien créé

```bash
ls -la README.md
cat README.md | head -20
```

---

**Voilà! Tu as maintenant un README complet pour guider la compilation et l'exécution à chaque partie.** 🎯
