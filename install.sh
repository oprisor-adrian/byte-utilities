: ' 
  Copyright (C) 2023-2024 Oprișor Adrian-Ilie
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
   
  Contact: contact@dev-adrian.com
'
#!/bin/bash

checkLibrary() {
  local library="$1"
  if command -v "$library" > /dev/null 2>&1 ; then
    printf "%-14s %-18s %s\n" "$library" "✓ installed" "$($library --version | head -n 1)"
  else
    printf "%-14s %-18s %s\n" "$library" "✗ not found" "-"
    not_installed+=("$library")
  fi
}

# Checks if BASH is used as shell.
if [ ! -n "$BASH_VERSION" ]; then
    echo "Bash shell is not in use."
    exit
fi

# Checks for dependencies
printf "\nChecking for the necessary libraries\n\n"
printf "library name |    status    |               version\n"
printf "========================================================================\n"

not_installed=()
checkLibrary cmake
checkLibrary g++

if [ ${#not_installed[@]} -gt 0 ]; then
  read -p "Do you want to install missing library? [y/n]:" answer
  answer=${answer:y}
  if [[ $answer =~ [yY] ]]; then
    for lib in "${not_installed[@]}"; do
      apt-get install "$lib"
    done
  else 
    exit
  fi
fi
printf "\n"

# Prepare the library for building
if [ -d "build" ]; then
  rm -rf build
fi

mkdir build
cd build
cmake .. 
printf "\n"

# Build and install the library
make -j$(nproc) install 

# Adds the path to the environment variable
echo 'export CMAKE_PREFIX_PATH="/usr/local/byte_utils/cmake:$CMAKE_PREFIX_PATH"' >> ~/.profile