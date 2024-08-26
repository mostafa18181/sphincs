#include <cstring>
#include "./avx2/sign.h" // Include the provided sign.h with your functions

class SPHINCSPlus {
public:
    SPHINCSPlus();
    ~SPHINCSPlus();

    bool sign(const unsigned char* message, size_t message_len, unsigned char* signature, size_t* signature_len);
    bool verify(const unsigned char* message, size_t message_len, const unsigned char* signature, size_t signature_len);
    bool generateKeyPair(unsigned char* publicKey, unsigned char* privateKey);

private:
    // Private variables and functions
};

// Implementing SPHINCSPlus functions

SPHINCSPlus::SPHINCSPlus() {
    // Constructor: Initialization code, if necessary
}

SPHINCSPlus::~SPHINCSPlus() {
    // Destructor: Cleanup code, if necessary
}

bool SPHINCSPlus::sign(const unsigned char* message, size_t message_len, unsigned char* signature, size_t* signature_len) {
    if (message == nullptr || signature == nullptr || message_len == 0) {
        return false; // Invalid input
    }

    unsigned long long sig_len;
    int result = crypto_sign(signature, &sig_len, message, message_len, nullptr); // Sign the message
    *signature_len = sig_len;
    return result == 0;
}

bool SPHINCSPlus::verify(const unsigned char* message, size_t message_len, const unsigned char* signature, size_t signature_len) {
    if (message == nullptr || signature == nullptr || message_len == 0) {
        return false; // Invalid input
    }

    int result = crypto_sign_verify(signature, signature_len, message, message_len, nullptr); // Verify the signature
    return result == 0;
}

bool SPHINCSPlus::generateKeyPair(unsigned char* publicKey, unsigned char* privateKey) {
    return crypto_sign_keypair(publicKey, privateKey) == 0; // Generate key pair
}
