#[[ 
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
]]
add_library(ByteUtils INTERFACE IMPORTED)
set_target_properties(ByteUtils PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${ByteUtils_INCLUDE_DIRS}
)
set_target_properties(ByteUtils PROPERTIES
  INTERFACE_LINK_LIBRARIES ${ByteUtils_LIBRARIES}
)
set_property(TARGET ByteUtils PROPERTY
  INTERFACE_BYTEUTILS_VERSION ${ByteUtils_VERSION}
)