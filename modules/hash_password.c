#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

#define SHA256_DIGEST_LENGTH 65

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

void print_hash(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    const char *password = "admin123";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    hash_password(password, hash);

    printf("Hashed password: ");
    print_hash(hash);

    return 0;
}