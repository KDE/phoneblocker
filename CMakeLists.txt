#################################################################################
# This file is part of the PhoneBlocker project
# Copyright (c) 2014 Laszlo Papp <lpapp@kde.org>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#/

cmake_minimum_required(VERSION 2.8.9)
project(PhoneBlocker)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")
option(BUILD_PHONEBLOCKER_BLACKBERRY "Build PhoneBlocker for Blackberry 10" ON)
add_subdirectory(frontends)
