const SPHINCSKeyManager = require('./keyManagement/keyManager');
const SphincsPlus = require('./algorithms/sphincsPlus');
const addon = require('../build/Release/myaddon');

const keyManager = new SPHINCSKeyManager();

// Lazy loading برای SPHINCS+ (در صورت نیاز)
function getSPHINCSPlusInstance() {
    const keyPair = keyManager.generateSPHINCSKeypair();
    return new SphincsPlus(keyPair);
}

// مدیریت خطا برای SPHINCS+
function signMessageWithSPHINCSPlus(message) {
    let sphincs;
    try {
        sphincs = getSPHINCSPlusInstance();
        return sphincs.sign(message);
    } catch (error) {
        console.error('Error signing message with SPHINCSPlus:', error);
        throw new Error('Signing failed. Please try again.');
    } finally {
        // پاک‌سازی منابع (در صورت نیاز)
        if (sphincs) {
            sphincs.cleanUp();
        }
    }
}

module.exports = {
    signMessageWithSPHINCSPlus,
};
