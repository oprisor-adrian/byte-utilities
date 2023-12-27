
[![CTest](https://github.com/oprisor-adrian/byte-utilities/actions/workflows/ubuntu-unit-test.yml/badge.svg?branch=main)](https://github.com/oprisor-adrian/byte-utilities/actions/workflows/ubuntu-unit-test.yml)
![Linux Compatible](https://img.shields.io/badge/Linux-Compatible-brightgreen.svg)
![Windows Not Tested](https://img.shields.io/badge/Windows-Not%20Tested-lightgrey.svg)

## Byte utilities library
The `byte_utils` library is created for easy-to-use byte-level operations and manipulations. It's designed especially for use in cryptographic algorithms, and based on `std::bitset`.
> see [std::bitset](https://en.cppreference.com/w/cpp/utility/bitset)


## Disclaimer
This approach isn't meant for production use. Be aware of bugs and security risks.
> see [license](./LICENSE)

## Installation steps
### Install using the `.sh` script
1. Downloads the last version of the library
```bash
wget https://github.com/oprisor-adrian/byte-utilities.git
```
2. Installs the library using the `.sh` script
```bash
cd byte-utilities/
chmod +x install.sh
./install.sh
```
Make sure you run the script with `root` privileges.

### Install using precompiled binary
1. Downloads the library
```bash
wget https://github.com/oprisor-adrian/byte-utilities/releases/download/<version>/byte_utils.tar.gz
```
Replace `<version>` with the desired release version.
> see [releases](https://github.com/oprisor-adrian/byte-utilities/releases)
2. Extracts the files
```bash
tar -xzf byte_utils.tar.gz -C <path-to-dir>
```
Replace the `<path-to-dir>` with the desired path where the library can be found.

3. Adds the path to the `CMAKE_PREFIX_PATH` environment variable
```bash
export CMAKE_PREFIX_PATH="<path-to_dir>/cmake:$CMAKE_PREFIX_PATH"
```
Adding the path to the `CMAKE_PREFIX_PATH` ensures that the library can be imported using the `find_package`. To make the variable to be persistent, add the above line to your shell profile:
```bash
echo 'export CMAKE_PREFIX_PATH="<path-to-dir>/cmake:$CMAKE_PREFIX_PATH"' >> ~/.profile
```
The `~/.profile` file can be named differently depending on your system or shell.


## Usage
Adds to your `CMakeLists.txt` file the following:

1. Finds the library using `find_package`
```cmake
find_package(ByteUtils REQUIRED)
```

3. Links the library to your target
```cmake
target_link_libraries(`taget_name` ByteUtils)
```

## Testing
The repository contain the unit tests. To run the test make sure you have installed the `GTest` library.
In the cloned repository runs the following:
1. Builds the project
```bash
cmake -S . -B build/
```
2. Runs the unit tests
```bash
ctest --test-dir build/
```

## Notices
This project utilizes the Google Test (GTest) framework for testing purposes. Please refer to the [GTest documentation](https://google.github.io/googletest/) for more information on its usage and licensing terms.