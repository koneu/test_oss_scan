#!/usr/bin/env bash
# Installs Conan dependencies, configures and builds the project.
# Usage: scripts/build.sh [Release|Debug]
set -euo pipefail

BUILD_TYPE="${1:-Release}"
PRESET="conan-$(echo "${BUILD_TYPE}" | tr '[:upper:]' '[:lower:]')"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "${ROOT_DIR}"

# Make sure a detected default profile exists; our profile includes it.
if ! conan profile path default >/dev/null 2>&1; then
    conan profile detect --force
fi

conan install . \
    --profile:all=extras/conan/profiles/default \
    --lockfile=conan.lock \
    --settings:all=build_type="${BUILD_TYPE}" \
    --build=missing

cmake --preset "${PRESET}"
cmake --build --preset "${PRESET}" --parallel
