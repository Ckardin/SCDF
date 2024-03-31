# Install Script // Version Windows

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


if($($env:ASHES_DIR | grep -c .) -ceq 0) {
    Set-Item -Path 'Env:\ASHES_DIR' -Value 'C:/Ashes'
    setx ASHES_DIR C:/Ashes
}

if(!(Test-Path -Path $($env:ASHES_DIR))) {
    mkdir $($env:ASHES_DIR)
}

Write-Host "VAR(ASHES_DIR) OK"



$INC_DIR = $($env:ASHES_DIR) + "\inc"
$LIB_DIR = $($env:ASHES_DIR) + "\lib"
$SHR_DIR = $($env:ASHES_DIR) + "\share"


if(!(Test-Path -Path $INC_DIR)) {
    mkdir $INC_DIR
}
Write-Host "INCDIR OK"


if(!(Test-Path -Path $LIB_DIR)) {
    mkdir $LIB_DIR
}
Write-Host "LIBDIR OK"


if(!(Test-Path -Path $SHR_DIR)) {
    mkdir $SHR_DIR
}
Write-Host "SHRDIR OK"



# Set-Item -Path 'Env:\CP' -Value 'Copy-Item'
# Set-Item -Path 'Env:\RM' -Value 'Remove-Item'
Set-Item -Path 'Env:\A_SHLIB' -Value 'dll'
Set-Item -Path 'Env:\A_STLIB' -Value 'lib'

Set-Item -Path 'Env:\INCDIR' -Value $INC_DIR
Set-Item -Path 'Env:\LIBDIR' -Value $LIB_DIR
Set-Item -Path 'Env:\SHRDIR' -Value $SHR_DIR