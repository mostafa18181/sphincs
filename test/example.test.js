const {expect} = require('chai');
const {signMessageWithSPHINCSPlus} = require('../src/index'); // فرض کنید که کد اصلی در index.js است
const SPHINCSKeyManager = require('../src/keyManagement/keyManager');
const {logger} = require("node-gyp/lib/log");
const SphincsPlus = require('../src/algorithms/sphincsPlus');

describe('SPHINCS+ Signing and Verification', () => {
    it('should sign and verify a message correctly', () => {
        const message = "This is a test message";
        const keyManager = new SPHINCSKeyManager();

        // تولید کلیدهای SPHINCS+ فقط یک بار
        const keyPair = keyManager.generateSPHINCSKeypair();
        console.log("pu-----------");

        //const buffer = Buffer.from(keyPair.publicKey);
        // console.log("Signature (Hex):", buffer.toString('hex'));
        // console.log("pu-----------");

        // // حالا نیاز نیست که دوباره کلید جدید تولید کنیم
        const sphincs = new SphincsPlus(keyPair);

        const signature = sphincs.sign(message);
        //
        //
        // // تأیید امضا
        const isValid = sphincs.verify(message, signature);
        console.log("Is the signature valid?", isValid);

        expect(isValid).to.be.true;
    });

    it('should fail to verify a tampered message', () => {
        const message = "This is a test message";
        const tamperedMessage = "This is a tampered message";
        const keyManager = new SPHINCSKeyManager();

        // تولید کلیدهای SPHINCS+
        const keyPair = keyManager.generateSPHINCSKeypair();

        // امضای پیام اصلی
        const signature = signMessageWithSPHINCSPlus(message);

        // تلاش برای تأیید امضا با پیام دستکاری شده
        const sphincs = new SphincsPlus(keyPair);
        const isValid = sphincs.verify(tamperedMessage, signature);

        expect(isValid).to.be.false;
    });
});
