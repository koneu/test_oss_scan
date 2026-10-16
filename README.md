# test_oss_scan

Small C++17 sample project to try out the [OSS Review Toolkit (ORT)](https://oss-review-toolkit.org).

- **Build:** CMake + Conan 2 (`conanfile.py`, profile in `extras/conan/profiles/default`)
- **Dependencies:** `spdlog` (logging, pulls in `fmt`), `sqlitecpp` (SQL, pulls in `sqlite3`), `gtest` (test-only)
- **Layout:** `app/include`, `app/src` (library `app_core` + executable `app`), `tests/`

## Build & test

Open the repo in the devcontainer (VS Code: *Reopen in Container*), then:

```sh
scripts/build.sh Release   # conan install + cmake configure/build
scripts/test.sh Release    # ctest
build/Release/app/app
```

## CI

- `.github/workflows/build.yml` – builds and tests inside the devcontainer (`devcontainers/ci`).
- `.github/workflows/ort.yml` – runs ORT (analyzer, scanner, advisor, evaluator, reporter);
  reports are uploaded as workflow artifacts. Path/scope excludes live in `.ort.yml`.
