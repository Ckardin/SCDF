#!/usr/bin/zsh

# Install Script // Version Linux

<<"COMMENTS"
COMMENTS

# English version
# Copyright (C) 2025 BOUCARD NICOLLE Jody

# This file is part of LibSCDF.

# LibSCDF is free library: you can redistribute it and/or modify it under the terms of the GNU General 
# Public License as published by the Free Software Foundation, either version 3 of the License, or (at your 
# option) any later version.

# LibSCDF is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# General Public License for more details.

# You should have received a copy of the GNU General Public License along with LibSCDF. If not, see 
# <https://www.gnu.org/licenses/>.

# Version française
# Copyright (C) 2025 BOUCARD NICOLLE Jody

# Ce fichier fait partie de LibSCDF.

# LibSCDF est une bibliothèque libre; vous pouvez la redistribuer ou la modifier suivant les termes de la GNU General 
# Public License telle que publiée par la Free Software Foundation, soit la version 3 de la licence, soit (à votre 
# gré) toute version ultérieure.

# LibSCDF est distribuée dans l'espoir qu'elle sera utile, mais SANS AUCUNE GARANTIE; sans même la 
# garantie tacite de QUALITÉ MARCHANDE ou d'ADÉQUATION À UN BUT PARTICULIER. Consultez la GNU 
# General Public License pour plus de détails.

# Vous devez avoir reçu une copie de la GNU General Public License en même temps que LibSCDF. Si ce n'est pas le cas, consultez 
# <http://www.gnu.org/licenses>.

if [ $(printenv | grep ASHES_DIR | grep -c .) -eq 0 ]; then
    echo "export ASHES_DIR=$HOME/Ashes" >> ~/.bashrc
    source ~/.bashrc
fi

echo "VAR(ASHES_DIR) OK"

mkdir -p "$ASHES_DIR"/lib && echo "LIBDIR OK"
mkdir -p "$ASHES_DIR"/inc && echo "INCDIR OK"
mkdir -p "$ASHES_DIR"/share && echo "SHRDIR OK"

sed -i '9a A_SHLIB=so' Makefile
sed -i '10a A_STLIB=a' Makefile
sed -i '11a A_EXT=' Makefile
sed -i '12a SHRDIR=$(ASHES_DIR)/share' Makefile
sed -i '13a LIBDIR=$(ASHES_DIR)/lib' Makefile
sed -i '14a INCDIR=$(ASHES_DIR)/inc' Makefile