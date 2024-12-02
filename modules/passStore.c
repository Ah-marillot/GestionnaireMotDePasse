#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "data.txt"

// Fonction pour chiffrer le mot de passe en assurant des caractères imprimables
void encrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] ^ key[i % key_len]) % 94) + 33; // Assure des caractères imprimables
    }
}

// Fonction pour déchiffrer le mot de passe
void decrypt(char *password, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < strlen(password); i++) {
        password[i] = ((password[i] - 33 + 94) % 94) ^ key[i % key_len]; // Reconvertit en caractères originaux
    }
}

// Fonction pour vérifier si le login existe déjà
int login_exists(const char *login) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    char line[256];
    char file_login[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s", file_login);
        if (strcmp(file_login, login) == 0) {
            fclose(file);
            return 1; // Login trouvé
        }
    }

    fclose(file);
    return 0; // Login non trouvé
}

// Fonction pour enregistrer le login et le mot de passe chiffré
void Enregistrer(const char *login, char *password, const char *key) {
    if (login_exists(login)) {
        printf("Le login already exist.\n");
        return;
    }

    printf("Enregistrement\n");
    // Chiffrer le mot de passe
    encrypt(password, key);

    // Ouvrir le fichier en mode append
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Écrire le login et le mot de passe chiffré dans le fichier
    fprintf(file, "%s\t%s\n", login, password);

    // Fermer le fichier
    fclose(file);
}

int main() {
    // Exemple d'utilisation de la fonction Enregistrer
    char password[] = "password123";
    Enregistrer("user1", password, "key");

    // Déchiffrer pour vérifier
    decrypt(password, "key");
    printf("Decrypted password: %s\n", password);

    return 0;
}
