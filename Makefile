
# =========================================================================
# CONFIGURATION DU COMPILATEUR
# =========================================================================
CC = gcc
CFLAGS = -Wall -Wextra -g	-I./cJSON

# =========================================================================
# NOM DE L'EXECUTABLE FINAL
# =========================================================================
EXEC = universite

# =========================================================================
# LISTE DES FICHIERS SOURCE ET OBJETS
# =========================================================================
SRC = main.c gestionAdministration.c gestionEtudiant.c	espace.c	sauvegarde.c	cJSON.c
OBJ = $(SRC:.c=.o)

# =========================================================================
# REGLES DE COMPILATION
# =========================================================================

# Règle principale (par défaut)
all: $(EXEC)

# Règle pour l'exécutable final
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS)	$(OBJ) -o $(EXEC)

cJSON.o:	cJSON/cJSON.c
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

# Règle pour transformer chaque fichier .c en fichier objet .o
%.o: %.c structures.h
	$(CC) $(CFLAGS) -c $< -o $@

# =========================================================================
# REGLES DE NETTOYAGE (Sécurisées avec .PHONY)
# =========================================================================
.PHONY: all clean mrproper

# Règle pour nettoyer les fichiers temporaires de compilation
clean:
	rm -f $(OBJ)

# Règle pour nettoyer tout (objets + exécutable)
mrproper: clean
	rm -f $(EXEC)