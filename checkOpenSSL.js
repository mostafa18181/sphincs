const os = require('os');
const fs = require('fs');
const path = require('path');
const {execSync} = require('child_process');


////////////////////////
function checkOpenSSL() {
    // if (handlePlatform === 'linux' && arch === 'x64') {
    //     binaryName = 'sphincs-v1.0.0-node-v64-linux-x64.tar.gz';
    // } else if (handlePlatform === 'linux' && arch === 'arm64') {
    //     binaryName = 'sphincs-v1.0.0-node-v64-linux-arm64.tar.gz';
    // } else if (handlePlatform === 'win32' && arch === 'x64') {
    //     binaryName = 'sphincs-v1.0.0-node-v64-win32-x64.tar.gz';
    // } else if (handlePlatform === 'darwin' && arch === 'x64') {
    //     binaryName = 'sphincs-v1.0.0-node-v64-darwin-x64.tar.gz';
    // } else if (handlePlatform === 'darwin' && arch === 'arm64') {
    //     binaryName = 'sphincs-v1.0.0-node-v64-darwin-arm64.tar.gz';
    // } else {
    //     console.error(`Unsupported platform: ${handlePlatform}, architecture: ${arch}`);
    //     process.exit(1);
    // }
    //
    // const binaryPath = path.join(__dirname, '..', 'prebuilt-binaries', binaryName);
    //
    // if (!fs.existsSync(binaryPath)) {
    //     console.error(`Binary not found: ${binaryPath}`);
    //     process.exit(1);
    // }
    //
    // // مسیر استخراج را به build/Release تغییر دهید
    // const extractPath = path.join(__dirname, '..', 'build', 'Release');
    //
    // if (!fs.existsSync(extractPath)) {
    //     fs.mkdirSync(extractPath, {recursive: true});
    // }
    //
    // execSync(`tar -xzf ${binaryPath} -C ${extractPath}`, {stdio: 'inherit'});
    try {
        execSync('openssl version', {stdio: 'ignore'});
        console.log('OpenSSL is already installed.');
    } catch (error) {
        console.log('OpenSSL is not installed. Installing...');
        const platform = os.platform();
        try {
            if (platform === 'linux') {
                execSync('sudo apt-get update && sudo apt-get install openssl -y', {stdio: 'inherit'});
            } else if (platform === 'darwin') {
                execSync('brew install openssl', {stdio: 'inherit'});
            } else if (platform === 'win32') {
                console.log('Please install OpenSSL manually for Windows from https://slproweb.com/products/Win32OpenSSL.html');
            } else {
                console.error('Unsupported platform:', platform);
            }
        } catch (installError) {
            console.error('Failed to install OpenSSL:', installError);
        }
    }
}


checkOpenSSL();
