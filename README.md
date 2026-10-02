<h1 align="center">Fukiyomi</h1>

<p align="center">A manga reader with a portable C++ core that runs entirely on your device.</p>

###

<div align="center">
  <img src="https://skillicons.dev/icons?i=cpp" height="40" alt="C++ logo" />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=cmake" height="40" alt="CMake logo" />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=qt" height="40" alt="Qt logo" />
  <img width="12" />
  <img src="https://skillicons.dev/icons?i=opencv" height="40" alt="OpenCV logo" />
</div>

###

<p align="center"><b>English</b> · <a href="README.ru.md">Русский</a></p>

The long-term goal is to detect speech bubbles on a page, recognize their text, and translate or voice it, all without a server.

> **Status:** early development. Version 0.1 is in progress. A console prototype already opens a folder of images and reads every page; the Qt window comes next.

## Architecture

The core is a C++23 library with no UI and no platform dependencies. Each platform gets its own native UI on top of it.

```
Desktop (Qt 6)   Android (Kotlin)   iOS (Swift)   Web (JS)
      │                └───────────────┼──────────────┘
      │                        bindings layer
      └────────────────┬───────────────┘
                   C++ core
```

The desktop app comes first. Mobile and web clients will follow once the core has real features.

## Roadmap

| Version | Goal |
|---|---|
| 0.1 | Open a folder of images and page through it in a desktop window |
| 0.2 | Detect speech bubbles with classic computer vision (OpenCV) |
| 0.3 | Recognize text inside the bubbles (OCR) |
| 0.4 | Translate or voice the recognized text |

## Tech stack

- C++23, CMake
- Qt 6 for the desktop UI
- OpenCV for image processing (from 0.2)
- ONNX Runtime for local ML inference (when needed)
- GoogleTest for unit tests

## Building

You need CMake 3.20 or newer and a compiler with C++23 support, including `std::expected`: Clang 16+, GCC 12+, or Apple Clang from Xcode 15+.

```sh
./build.sh
```

The script configures the project into `build/` and compiles it. You can also run the same two steps by hand:

```sh
cmake -S . -B build
cmake --build build
```

## Running

The current version is a console prototype. Pass it a folder with manga pages:

```sh
./build/apps/desktop/fukiyomi path/to/chapter
```

It lists the images in the folder (PNG, JPEG, WebP, sorted by file name), reads each one, and prints its size:

```
version 0.1.0
Page count: 2
	Size page 0: 217572 bytes
	Size page 1: 277086 bytes
```

Exit codes: `0` if every page was read, `1` if the folder could not be opened, `2` if some pages failed to read.

## License

Licensed under the [Apache License 2.0](LICENSE).

Third-party libraries and ML models keep their own licenses.
