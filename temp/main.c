#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Définir une longueur maximale pour le mot de passe
#define MAX_PASSWORD_LENGTH 128
#define MASTER_PASSWORD "password123"
#define FILE_NAME "passwords.txt"

#define MYFILE "data.txt"

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
    FILE *file = fopen(MYFILE, "r");
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
        printf("Le login existe deja.\n");
        return;
    }

    printf("Enregistrement\n");
    // Chiffrer le mot de passe
    encrypt(password, key);

    // Ouvrir le fichier en mode append
    FILE *file = fopen(MYFILE, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Écrire le login et le mot de passe chiffré dans le fichier
    fprintf(file, "%s\t%s\n", login, password);

    // Fermer le fichier
    fclose(file);
}

void gen_mdp()
{
    const char *min,*maj,*chiffre,*c_sp;
    int nb_caracteres=0;
    int nb_maj=0;
    int nb_min=0;
    int nb_c_sp=0;
    int nb_chiffres=0;
    int i=0;
    int index = 0;

     // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    maj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    min = "abcdefghijklmnopqrstuvwxyz";
    chiffre = "0123456789";
    c_sp = "@!*#%$£:~";

     printf("*Bienvenue dans la gestion des mots de passe*\n");
    printf ("** combien voulez-vous de carateres :  \n");
    scanf ("%d", &nb_caracteres);

    if (nb_caracteres<8 || nb_caracteres>128)
    {
        printf ("erreur, le nombre de caractere doit etre entre 8 et 128 ! \n");
        return 1 ;
    }
    else
    {
             // Demander combien de majuscules, minuscules, chiffres et caractères spéciaux
        printf("Combien de majuscules (maximum %d) ? ", nb_caracteres - 2);
        scanf("%d", &nb_maj);

            if (nb_maj > nb_caracteres) {

                printf("Le nombre de majuscules ne peut pas depasser le total de caracteres.\n");
                return 1;
                                        }

        printf("Combien de minuscules (maximum %d) ? ", (nb_caracteres - 2) - nb_maj);
        scanf("%d", &nb_min );

    if (nb_min > nb_caracteres - nb_maj)
    {
        printf("Le nombre de minuscules ne peut pas depasser le total restant de caracteres.\n");
        return 1;
    }

        printf("Combien de chiffres (maximum %d) ? ", (nb_caracteres - 2) - nb_maj - nb_min);
        scanf("%d", &nb_chiffres);

    if (nb_chiffres > nb_caracteres - nb_maj - nb_min)
    {
        printf("Le nombre de chiffres ne peut pas depasser le total restant de caracteres.\n");
        return 1;
    }

        printf("Combien de caracteres speciaux (maximum %d) ? ", nb_caracteres - nb_maj - nb_min - nb_chiffres);
        scanf("%d", &nb_c_sp);

    if (nb_c_sp > nb_caracteres - nb_maj - nb_min - nb_chiffres)
    {
        printf("Le nombre de caracteres speciaux ne peut pas depasser le total restant de caracteres.\n");
        return 1;
    }
        int nb_restants = (nb_caracteres-2) - (nb_maj + nb_min + nb_chiffres + nb_c_sp); // ici on calcul le nombre de caractere

 if (nb_restants > 0)
    {
        printf("Le mot de passe sera complete avec %d caracteres aleatoires.\n", nb_restants);
        // que faire ???? a voir ...
    }
          // Allocation de mémoire pour le mot de passe
        char mdp[nb_caracteres + 1];

        // Ajout des majuscules
        for (i = 0; i < nb_maj; i++)
        {
            mdp[index++] = maj[rand() % strlen(maj)]; // Selectionner un caratere dans la chaîne maj, et le stocker dans le tableau mdp (avec la position index), et on incrémente index pour avoir le ou les prochains caracteres

        }

        // Ajout des minuscules
        for (i = 0; i < nb_min; i++)
        {
            mdp[index++] = min[rand() % strlen(min)];
        }

        // Ajout des chiffres
        for (i = 0; i < nb_chiffres; i++)
        {
            mdp[index++] = chiffre[rand() % strlen(chiffre)];
        }

        // Ajout des caractères spéciaux
        for (i = 0; i < nb_c_sp; i++)
        {
            mdp[index++] = c_sp[rand() % strlen(c_sp)];
        }

        //Tant que la boucle n'a pas atteint la longueur totale, on complete le mdp avec les caracteres aleatoires
        for (i = 0; i < nb_restants; i++)
        {
            int type = rand() % 4; // L'entier type va prendre une valeur aléatoire entre 0 et 3 à chaque execution de ces lignes

            if (type == 0)
            {
                mdp[index++] = maj[rand() % strlen(maj)];
            }

            else if (type == 1)
            {
                mdp[index++] = min[rand() % strlen(min)];
            }

            else if (type == 2)
            {
                mdp[index++] = chiffre[rand() % strlen(chiffre)];
            }

            else
            {
                mdp[index++] = c_sp[rand() % strlen(c_sp)];
            }
        }

        // melanger le mot de passe
        for (i = 0; i < nb_caracteres; i++) // on parcourt la ligne nb_caracteres
        {
            int j = rand() % nb_caracteres; // selectionner une position aleatoire entre et nb_caracteres -1
            char temp = mdp[i]; //Concatener deux tableaux pour mélanfer les caracteres
            mdp[i] = mdp[j];
            mdp[j] = temp;
        }

    // Ajouter le caractere de fin de chaîne
    mdp[nb_caracteres] = '\0';

    // affiche le mdp
    printf("Votre mot de passe est : %s\n", mdp);

}}

// Fonction : Consultation des mots de passe
void viewPasswords() {
    char masterPass[MAX_PASSWORD_LENGTH];
    char line[MAX_PASSWORD_LENGTH];

    printf("\n=== Consultation des Mots de Passe ===\n");
    printf("Entrez le mot de passe maitre : ");
    scanf("%s", masterPass);

    if (strcmp(masterPass, MASTER_PASSWORD) != 0) {
        printf("Mot de passe incorrect.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Aucun mot de passe sauvegarde.\n");
        return;
    }

    printf("\nIdentifiant | Type de Login | Service | Mot de Passe\n");
    printf("----------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char identifier[MAX_PASSWORD_LENGTH], loginType[MAX_PASSWORD_LENGTH], serviceName[MAX_PASSWORD_LENGTH], password[MAX_PASSWORD_LENGTH];
        if (sscanf(line, "%[^,],%[^,],%[^,],%s", identifier, loginType, serviceName, password) == 4) {
            encrypt(password, -3);
            decrypt(password, -3); // Décrypter le mot de passe
            printf("%-11s | %-13s | %-7s | %-12s\n", identifier, loginType, serviceName, password);
        }
    }

    fclose(file);
}

// Fonction : Suppression d'un mot de passe
void deletePassword() {
    char masterPass[MAX_PASSWORD_LENGTH];
    char line[MAX_PASSWORD_LENGTH];
    char lines[100][MAX_PASSWORD_LENGTH];
    int lineCount = 0;
    int targetLine, i;

    printf("\n=== Suppression d'un Mot de Passe ===\n");
    printf("Entrez le mot de passe maitre : ");
    scanf("%s", masterPass);

    if (strcmp(masterPass, MASTER_PASSWORD) != 0) {
        printf("Mot de passe incorrect.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Aucun mot de passe sauvegarde.\n");
        return;
    }

    // Lecture des lignes du fichier
    while (fgets(line, sizeof(line), file)) {
        strcpy(lines[lineCount], line);
        lineCount++;
    }
    fclose(file);

    // Affichage des mots de passe avec index
    printf("\nListe des mots de passe :\n");
    for (i = 0; i < lineCount; i++) {
        printf("%d: %s", i + 1, lines[i]);
    }

    printf("\nEntrez le numero de la ligne à supprimer (1-%d) : ", lineCount);
    if (scanf("%d", &targetLine) != 1 || targetLine < 1 || targetLine > lineCount) {
        flushInputBuffer();
        printf("Entree invalide. Annulation de l'operation.\n");
        return;
    }

    printf("Confirmez la suppression de la ligne %d ? (o/n) : ", targetLine);
    char confirm;
    scanf(" %c", &confirm);

    if (tolower(confirm) != 'o') {
        printf("Suppression annulee.\n");
        return;
    }

    // Réécriture des lignes dans le fichier sans celle à supprimer
    file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (i = 0; i < lineCount; i++) {
        if (i != targetLine - 1) {
            fprintf(file, "%s", lines[i]);
        }
    }
    fclose(file);
    printf("Ligne supprimee avec succes.\n");
}

// Fonction utilitaire : Vider le tampon d'entrée
void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void menuprincipal()
{
   printf("Faites votre choix pour acceder a une fonction du menu (1/2/3/4).\n");
   printf("1 : Generer un mot de passe\n");
   printf("2 : Consultation des mots de passe deja crees\n");
   printf("3 : Sauvegarde du mot de passe\n");
   printf("4 : Supprimer un mot de passe\n");
   printf("5 : Exit\n");
   printf("Votre choix : ");
}

//Appel des fonctions
void menuprincipal();
void viewPasswords();
void encrypt(char *password, const char *key);
void decrypt(char *password, const char *key);
void gen_mdp();
void Enregistrer();
void flushInputBuffer();

// Affiche le menu principal

int main() {

char menu;
char sousmenu;
char password[] = "password123";

   printf(" ________________________________________________________\n");
   printf("|                                                        |\n");
   printf("|                Gestionnaire de mot de passe            |\n");
   printf("|                            Menu                        |\n");
   printf("|                                                        |\n");
   printf("|________________________________________________________|\n\n");

   do {
        menuprincipal();
    if (scanf("%d", &menu) != 1) {
            flushInputBuffer();
            printf("Entrée invalide. Réessayez.\n");
        return 1;
    }
        switch (menu) {
        case 1:
            gen_mdp();
            break;
        case 2:
            viewPasswords();
            break;
        case 3:
            Enregistrer("user1", password, "key");
            decrypt(password, "key");
            printf("Mot de passe dechiffre : %s\n", password);
            break;
        case 4:
            deletePassword();
            break;
        case 5:
            printf("Au revoir !\n");
            break;
        default:
            printf("Option invalide.\n");
        }
    } while (menu != 5);

    return 0;
}