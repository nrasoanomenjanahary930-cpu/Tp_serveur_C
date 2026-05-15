
---

## 📄 README.md

```markdown
# Serveur UNIX Complet - TP Final


---

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


### 4. Vérifier que la compilation a réussi
```bash
ls -la myserverd
```


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

##  EXÉCUTION - PARTIE 2 (Fork)

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

##  EXÉCUTION - PARTIE 3 (Thread)

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

##  EXÉCUTION - PARTIE 4 (Select)

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

##  EXÉCUTION - PARTIE 5 (Daemon)

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

