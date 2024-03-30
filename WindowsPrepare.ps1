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