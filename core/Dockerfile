# Dockerfile
# (C) Martin Alebachew, 2023

# Environment setup
FROM ubuntu:23.10
RUN apt update
RUN apt -y install build-essential git curl zip unzip tar cmake ninja-build pkg-config

# Install dependencies
RUN git clone https://github.com/Microsoft/vcpkg
RUN export VCPKG_FORCE_SYSTEM_BINARIES=1 && /vcpkg/bootstrap-vcpkg.sh
RUN export VCPKG_FORCE_SYSTEM_BINARIES=1 && /vcpkg/vcpkg install curl nlohmann-json boost-asio tinyxml2

# Compile Lighthouse
RUN git clone --depth=1 --branch=main https://github.com/martinalebachew/Lighthouse
RUN cd /Lighthouse/core && cmake -B build -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake
RUN cmake --build /Lighthouse/core/build

# Run Lighthouse
EXPOSE 1688/tcp
CMD /Lighthouse/core/bin/core
