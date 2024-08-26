const fs = require('fs');
const path = require('path');
const crypto = require('crypto');
const addon = require('../../build/Release/myaddon'); // بارگذاری ماژول native

class SPHINCSKeyManager {
    constructor(keysDir = './keys', encryptionKey = null) {
        this.keysDir = keysDir;
        this.encryptionKey = encryptionKey || crypto.randomBytes(32); // کلید رمزگذاری امن
        if (!fs.existsSync(this.keysDir)) {
            fs.mkdirSync(this.keysDir, {recursive: true});
        }
    }

    // روش بهبود یافته برای ذخیره‌سازی کلید با رمزنگاری
    saveEncryptedKey(filePath, key) {
        const cipher = crypto.createCipheriv('aes-256-cbc', this.encryptionKey, this.getIV());
        let encrypted = cipher.update(key, 'utf8', 'hex');
        encrypted += cipher.final('hex');
        fs.writeFileSync(filePath, encrypted);
    }

    // روش بهبود یافته برای بارگذاری کلید با رمزگشایی
    loadEncryptedKey(filePath) {
        const encrypted = fs.readFileSync(filePath, 'utf8');
        const decipher = crypto.createDecipheriv('aes-256-cbc', this.encryptionKey, this.getIV());
        let decrypted = decipher.update(encrypted, 'hex', 'utf8');
        decrypted += decipher.final('utf8');
        return decrypted;
    }

    generateSPHINCSKeypair() {


        const {publicKey, privateKey} = addon.generateKeypair(); // استفاده از ماژول native برای ایجاد جفت کلید


        this.saveEncryptedKey(path.join(this.keysDir, 'sphincs.public.pem'), publicKey);

        this.saveEncryptedKey(path.join(this.keysDir, 'sphincs.private.pem'), privateKey);

        return {publicKey, privateKey};
    }

    loadSPHINCSKeypair() {
        const publicKey = this.loadEncryptedKey(path.join(this.keysDir, 'sphincs.public.pem'));
        const privateKey = this.loadEncryptedKey(path.join(this.keysDir, 'sphincs.private.pem'));
        return {publicKey, privateKey};
    }

    getIV() {
        // تولید IV
        return crypto.randomBytes(16);
    }

    rotateSPHINCSKeypair() {
        const newKeyPair = this.generateSPHINCSKeypair();
        this.saveSPHINCSKeypair('sphincs', newKeyPair);
        return newKeyPair;
    }
}

module.exports = SPHINCSKeyManager;
