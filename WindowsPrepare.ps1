if($($env:ASHES_DIR | grep -c .) -ceq 0) {
    Set-Item -Path 'Env:\ASHES_DIR' -Value 'C:/Ashes'
    setx ASHES_DIR C:/Ashes
}

if(!(Test-Path -Path $($env:ASHES_DIR))) {
    mkdir $($env:ASHES_DIR)
}

Write-Host "VAR(ASHES_DIR) OK"



$BIN_DIR = $($env:ASHES_DIR) + "\bin"
$LIB_DIR = $($env:ASHES_DIR) + "\lib"
$INC_DIR = $($env:ASHES_DIR) + "\share"


if(!(Test-Path -Path $BIN_DIR)) {
    mkdir $BIN_DIR
}
Write-Host "BINDIR OK"


if(!(Test-Path -Path $LIB_DIR)) {
    mkdir $LIB_DIR
}
Write-Host "LIBDIR OK"


if(!(Test-Path -Path $INC_DIR)) {
    mkdir $INC_DIR
}
Write-Host "INCDIR OK"



# Set-Item -Path 'Env:\CP' -Value 'Copy-Item'
# Set-Item -Path 'Env:\RM' -Value 'Remove-Item'
Set-Item -Path 'Env:\A_SHLIB' -Value 'dll'
Set-Item -Path 'Env:\A_STLIB' -Value 'lib'

Set-Item -Path 'Env:\BINDIR' -Value $BIN_DIR
Set-Item -Path 'Env:\LIBDIR' -Value $LIB_DIR
Set-Item -Path 'Env:\INCDIR' -Value $INC_DIR