#!/bin/bash

# Install Script // Version Linux

<<"COMMENTS"
COMMENTS

# English version
# Copyright (C) 2023 BOUCARD NICOLLE Jody

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
# Copyright (C) 2023 BOUCARD NICOLLE Jody

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
    export ASHES_DIR="/Ashes"

    echo "export ASHES_DIR='/Ashes'" >> ~/.bashrc
fi

echo "VAR(ASHES_DIR) OK"

sudo mkdir $ASHES_DIR/inc   && echo "INCDIR OK"
sudo mkdir $ASHES_DIR/lib   && echo "LIBDIR OK"
sudo mkdir $ASHES_DIR/share && echo "SHRDIR OK"

# export CP=cp
# export RM=rm
export A_SHLIB=so
export A_STLIB=a

export BINDIR=$ASHES_DIR/inc
export LIBDIR=$ASHES_DIR/lib
export SHRDIR=$ASHES_DIR/share