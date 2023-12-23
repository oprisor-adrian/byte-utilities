
[![CTest](https://github.com/oprisor-adrian/byte-utilities/actions/workflows/ubuntu-unit-test.yml/badge.svg?branch=main)](https://github.com/oprisor-adrian/byte-utilities/actions/workflows/ubuntu-unit-test.yml)

## Byte utilities library
The `byte_utils` library is created for easy-to-use byte-level operations and manipulations. It's designed especially for use in cryptographic algorithms, and based on `std::bitset`.
> see [std::bitset](https://en.cppreference.com/w/cpp/utility/bitset)


## Disclaimer
This approach isn't meant for production use. Be aware of bugs and security risks.
> see [license](./LICENSE)

## Installation steps
### Install from source
This installation process will create a `lib` directory in the current folder where the binary file and headers will be included.
1. Clone the repository
```bash
git clone git@github.com:oprisor-adrian/byte-utilities.git
```
2. Build the library
```bash
mkdir build && cd build/
cmake ..
make
```
3. Install the library
```bash
make install
```

### Install using precompiled binary
1. Download the library
```bash
wget https://github.com/oprisor-adrian/byte-utilities/releases/download/v1.0-alpha/byte_utils.rar
```
2. Extract the files
```bash
unrar x byte_utils.rar /usr/local/byte_utils/
```
Change the `/usr/local/byte_utils/` path to the desired path.

## Usage
Add to your `CMakeLists.txt` file the following:

1. Add the path where the linker will look for the library
```cmake
link_directories(path/to/the/library/bytes_utils/)
```

2. Add the path to the library header files
```cmake
include_directories(path/to/the/library/bytes_utils/include)
```
or specify include directory for a specific target
```cmake
target_include_directories(
  `target_name' PRIVATE
  path/to/the/library/bytes_utils/include
)
```
3. Link  the library to your target
```cmake
target_link_libraries(`taget_name` _byte_utils)
```