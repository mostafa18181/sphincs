

# SPHINCS+ Post-Quantum Cryptography Project

This project implements the SPHINCS+ post-quantum cryptographic algorithm using Node.js. It includes a native addon written in C/C++ for high-performance cryptographic operations across various platforms, ensuring security against quantum computer attacks.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Building and Testing](#building-and-testing)
- [Rebuilding Prebuilt Binaries](#rebuilding-prebuilt-binaries)
- [Platform Support](#platform-support)
- [Contributing](#contributing)
- [License](#license)

## Installation

To install the necessary dependencies for this project, run:

```bash
npm install
```

This command installs all required Node.js packages, including development dependencies.

## Usage

Here is a basic example of how to use this library:

```javascript
const sphincs = require('path_to_your_module');

// Example of signing a message
const message = "Hello, Quantum World!";
const privateKey = "your_private_key"; // Load or generate your SPHINCS+ private key
const signature = sphincs.signMessage(message, privateKey);

// Example of verifying a signature
const publicKey = "your_public_key"; // Load or generate your SPHINCS+ public key
const isValid = sphincs.verifySignature(message, signature, publicKey);
console.log(`Signature valid: ${isValid}`);
```

## Building and Testing

To build the project and run tests, follow these steps:

```bash
# Clean up previous builds and node_modules
rm -rf build
rm -rf node_modules
node-gyp clean

# Configure and build the project
node-gyp configure
node-gyp build

# Install dependencies
npm install

# Run tests
npm test
```

These commands ensure that your build environment is clean and that tests are executed using a fresh build.

## Rebuilding Prebuilt Binaries

This project uses `prebuild` to create prebuilt binaries for various Node.js versions and platforms. To generate these binaries, use the following commands:

### Linux and macOS:
```bash
npx prebuild --napi --target 10.0.0 --target 10.6.0 --target 12.11.0 --target 14.0.0 --target 16.0.0 --arch x64 --arch arm64 --strip --verbose
```

### Windows:
```bash
npx prebuild --napi --target 10.0.0 --target 10.6.0 --target 12.11.0 --target 14.0.0 --target 16.0.0 --arch x64 --arch arm64 --platform win32 --strip --verbose
```

### macOS:
```bash
npx prebuild --napi --target 10.0.0 --target 10.6.0 --target 12.11.0 --target 14.0.0 --target 16.0.0 --arch x64 --arch arm64 --platform darwin --strip --verbose
```

These commands will create prebuilt binaries compatible with multiple Node.js versions and platforms.

## Platform Support

This project supports multiple platforms, including:

- **Linux (x64, ARM64)**
- **macOS (x64, ARM64)**
- **Windows (x64, ARM64)**

The prebuilt binaries are optimized for different environments to ensure performance and compatibility.

## Contributing

We welcome contributions from the community! If you would like to contribute, please follow these steps:

1. **Fork the repository.**
2. **Create a new branch:**
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes.**
4. **Commit your changes:**
   ```bash
   git commit -m 'Add some feature'
   ```
5. **Push to the branch:**
   ```bash
   git push origin feature/your-feature-name
   ```
6. **Open a pull request.**

## License

This project is licensed under the MIT License. See the LICENSE file for more information.

## Resources

- **GitHub Repository**: [SPHINCS+ Project](https://github.com/your-repository-url)

---



