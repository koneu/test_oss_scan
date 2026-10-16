#!/usr/bin/env bash
# Runs the unit tests of an already built tree (see scripts/build.sh).
# Usage: scripts/test.sh [Release|Debug]
set -euo pipefail

BUILD_TYPE="${1:-Release}"
PRESET="conan-$(echo "${BUILD_TYPE}" | tr '[:upper:]' '[:lower:]')"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "${ROOT_DIR}"

ctest --preset "${PRESET}" --output-on-failure "${@:2}"
