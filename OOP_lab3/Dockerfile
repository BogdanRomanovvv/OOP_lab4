# Use Ubuntu 24.04 as base image which has GCC 14 available
FROM ubuntu:24.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install GCC 14, CMake, Ninja, and other dependencies
RUN apt-get update && apt-get install -y \
    gcc-14 \
    g++-14 \
    cmake \
    ninja-build \
    git \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set GCC 14 as default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100

# Verify GCC version
RUN gcc --version && g++ --version

# Set working directory
WORKDIR /workspace

# Copy project files
COPY . /workspace

# Build the project
RUN mkdir -p build && cd build && \
    cmake -G Ninja .. && \
    cmake --build .

# Default command
CMD ["/bin/bash"]
