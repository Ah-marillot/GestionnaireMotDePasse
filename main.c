#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <openssl/evp.h>

// Définir une longueur maximale et minimale pour le mot de passe
#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128
#define MASTER_PASSWORD_HASH "08ff61006d82fc76b019400054ff61000b1a4000b0194000d82fc60000000000"
#define SHA256_DIGEST_LENGTH 65
#define FILE_NAME "passwords.txt"

// Fonction pour hasher le mot de passe
void hash_password(const char *password, unsigned char *outputBuffer) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    // Create and initialize the context
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        // Handle error
        return;
    }

    // Initialize the digest
    md = EVP_sha256();
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        // Handle error
        EVP_MD_CTX_free(mdctx);
        return;
    }

    // Update the digest with the password
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) != 1) {
        // Handle error
        EVP_MD_CTX_free(mdctx);
        return;
    }

    // Finalize the digest
    if (EVP_DigestFinal_ex(mdctx, outputBuffer, &md_len) != 1) {
        // Handle error
        EVP_MD_CTX_free(mdctx);
        return;
    }

    // Clean up
    EVP_MD_CTX_free(mdctx);
}


// Fonction pour générer un mot de passe
int gen_mdp(char* mdp)
{
    const char *min, *maj, *chiffre, *c_sp;
    int nb_caracteres = 0;
    int nb_maj = 0;
    int nb_min = 0;
    int nb_c_sp = 0;
    int nb_chiffres = 0;
    int i = 0;
    int index = 0;

    // Initialisation du generateur de nombres aleatoires
    srand(time(NULL));

    maj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    min = "abcdefghijklmnopqrstuvwxyz";
    chiffre = "0123456789";
    c_sp = "@!*#%$:~";

    printf("**** BIENVENUE **** \n\n");
    printf("**** combien voulez-vous de carateres :  \n");
    scanf("%d", &nb_caracteres);

    if (nb_caracteres < 8 || nb_caracteres > 128)
    {
        printf("erreur, le nombre de caractere doit etre entre 8 et 128 ! \n");
        return 1;
    }
    else
    {
        // Demander combien de majuscules, minuscules, chiffres et caract�res sp�ciaux
        printf("Combien de majuscules (maximum %d) ? ", nb_caracteres - 2);
        scanf("%d", &nb_maj);

        if (nb_maj > nb_caracteres)
        {

            printf("Le nombre de majuscules ne peut pas depasser le total de caracteres.\n");
            return 1;
        }

        printf("Combien de minuscules (maximum %d) ? ", (nb_caracteres - 2) - nb_maj);
        scanf("%d", &nb_min);

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


          // Allocation de m�moire pour le mot de passe
        char mdp[nb_caracteres + 1];

        // Ajout des majuscules
        for (i = 0; i < nb_maj; i++)
        {
            mdp[index++] = maj[rand() % strlen(maj)]; // Selectionner un caratere dans la cha�ne maj, et le stocker dans le tableau mdp (avec la position index), et on incr�mente index pour avoir le ou les prochains caracteres

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

        // Ajout des caracteres speciaux
        for (i = 0; i < nb_c_sp; i++)
        {
            mdp[index++] = c_sp[rand() % strlen(c_sp)];
        }

        //Tant que la boucle n'a pas atteint la longueur totale, on complete le mdp avec les caracteres aleatoires
        for (i = 0; i < nb_restants; i++)
        {
            int type = rand() % 4; // L'entier type va prendre une valeur al�atoire entre 0 et 3 � chaque execution de ces lignes

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
            char temp = mdp[i]; //Concatener deux tableaux pour melanger les caracteres
            mdp[i] = mdp[j];
            mdp[j] = temp;
        }

    // Ajouter le caractere de fin de chaine
    mdp[nb_caracteres] = '\0';

    // affiche le mdp
    printf("Votre mot de passe est : %s\n", mdp);
    
    }
    return 0;
}


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
void registerPass(const char *login, char *password, const char *key) {
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

void viewPasswordModule() {
    char masterPass[MAX_PASSWORD_LENGTH];
    printf("\n=== Consultation des mots de passe ===\n");
    //Demander le mot de passe maitre et vérifier qu'il est correct avec 3 essais
                for(int i = 0; i < 3; i++)
                {
                    printf("Entrez le mot de passe maitre : ");
                    char masterPass[MAX_PASSWORD_LENGTH];
                    scanf("%s", masterPass);
                    unsigned char masterPassHash[SHA256_DIGEST_LENGTH];
                    hash_password(masterPass, masterPassHash);
                    if(*masterPassHash != MASTER_PASSWORD_HASH)
                    {
                        printf("Mot de passe maitre incorrect.\n");
                    }else{
                        break;
                    }
                }

    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Aucun mot de passe sauvegardé.\n");
        return;
    }

    char line[256];
    printf("\nIdentifiant | Type de Login | Service | Mot de Passe\n");
    printf("----------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        char identifier[MAX_PASSWORD_LENGTH], loginType[MAX_PASSWORD_LENGTH], serviceName[MAX_PASSWORD_LENGTH], password[MAX_PASSWORD_LENGTH];
        sscanf(line, "%[^,],%[^,],%[^,],%s", identifier, loginType, serviceName, password);

        // Décrypter le mot de passe
        decrypt(password, masterPass);
        printf("%s | %s | %s | %s\n", identifier, loginType, serviceName, password);
    }

    fclose(file);
}

//Appel des fonctions
void viewPasswordModule();

// Affiche le menu principal

int main() {

char menu;
char choix;
char sousmenu;

do{
   printf(" ________________________________________________________\n");
   printf("|                                                        |\n");
   printf("|                Gestionnaire de mot de passe            |\n");
   printf("|                            Menu                        |\n");
   printf("|                                                        |\n");
   printf("|________________________________________________________|\n\n");
   printf("Faites votre choix pour acceder a une fonction du menu (1/2/3/4).\n");
   printf("1 : Generer un nouveau mot de passe\n");
   printf("2 : Consulter un mot de passe deja crees\n");
   printf("3 : Exit\n");
   printf("Votre choix : ");

    scanf("%c=%c", &menu);
    getchar();

switch (menu)
        {
        case '1':
            printf("Vous entrez dans le module de dréation de mot de passe\n");
            char* mdp;
            gen_mdp(mdp);
            printf("Votre mot de passe est : %s\n", mdp);
            printf("Voulez-vous enregistrer ce mot de passe ? (O/N) : ");
            scanf("%c", &choix);
            if (choix == 'O' || choix == 'o')
            {
                //Demander le login à enregistrer et demander la confirmation à l'utilisateur que c'est le bon login
                char login[MAX_PASSWORD_LENGTH];
                {
                    printf("Entrez le login : ");
                    scanf("%s", login);
                    printf("Confirmez le login (O/N) : ");
                    scanf("%c", &choix);
                } while (choix != 'O' && choix != 'o');
                //Demander le mot de passe maitre et vérifier qu'il est correct avec 3 essais
                for(int i = 0; i < 3; i++)
                {
                    printf("Entrez le mot de passe maitre : ");
                    char masterPass[MAX_PASSWORD_LENGTH];
                    scanf("%s", masterPass);
                    unsigned char masterPassHash[SHA256_DIGEST_LENGTH];
                    hash_password(masterPass, masterPassHash);
                    if(*masterPassHash != MASTER_PASSWORD_HASH)
                    {
                        printf("Mot de passe maitre incorrect.\n");
                    }else{
                        registerPass(login, mdp, masterPass);
                        break;
                    }
                }
            }
            break;
        case '2':
            viewPasswordModule();
            break;
        case '3':
            printf("Au revoir !\n");
            exit(0);
            break;
        default:
            printf("Option invalide. Veuillez choisir une option valide.\n");
            break;
        }
}while(menu != '4');
}