# Lighthouse
Lighthouse is a KMS (Key Management Services) server for unix-like systems, consisted of three programs:

1. Server Core, written in C++. This program is an ABI (Application Binary Interface) that manages network communication between the server and its clients, including KMS messages.
2. Server GUI, written in TypeScript. This program connects an Electron GUI to the core.
3. Client Activator [Windows], written in TypeScript. This program is a small Electron GUI that acts as a frontend for underlying terminal commands.
