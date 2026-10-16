FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

ARG CONAN_VERSION=2.15.1

RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
        ninja-build \
        python3-pip \
        python3-venv \
        pipx \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Conan system-wide into its own venv so every user can call it.
RUN PIPX_HOME=/opt/pipx PIPX_BIN_DIR=/usr/local/bin pipx install "conan==${CONAN_VERSION}"
