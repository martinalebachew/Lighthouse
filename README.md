# Lighthouse
Lighthouse is an open-source, well-written Windows & Office activation solution.
Behind the scenes, Lighthouse emulates a KMS (Key Management Services) host on the local network,
and grants all incoming requests.

## Limitations
- Lighthouse currently supports KMS 6.0 only.
- KMS activation is supported only on VL versions of Microsoft Office.

## Building Lighthouse
### Core
```
cd core
cmake -B build
cmake --build build
```
