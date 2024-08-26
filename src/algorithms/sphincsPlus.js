const addon = require('../../build/Release/myaddon');

console.log(addon)

class SphincsPlus {
    constructor(keyPair) {
        this.keyPair = keyPair;
    }

    /**
     * امضای پیام با استفاده از SPHINCS+
     * @param {Buffer|string} message - پیام برای امضا
     * @returns {Buffer} - امضای تولید شده
     */
    sign(message) {
        if (typeof message === 'string') {
            message = Buffer.from(message, 'utf8');
        }

        // استفاده از ماژول native برای امضا
        const signature = addon.signMessage(message, this.keyPair.privateKey);

        return signature;
    }

    /**
     * تأیید امضای پیام با استفاده از SPHINCS+
     * @param {Buffer|string} message - پیام اصلی
     * @param {Buffer} signature - امضا برای تأیید
     * @returns {boolean} - نتیجه تأیید
     */
    verify(message, signature) {
        if (typeof message === 'string') {
            message = Buffer.from(message, 'utf8');
        }


        console.log();
        const isValid = addon.verifySignature(message, signature, this.keyPair.publicKey);
        return isValid;
    }

    cleanUp() {
        // پاکسازی منابع حساس
        this.keyPair = null;
        console.log('Resources have been cleaned up.');
    }
}

module.exports = SphincsPlus;
