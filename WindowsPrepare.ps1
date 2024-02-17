if($($env:ASHES_DIR | grep -c .) -ceq 0)
{
    Echo.ps1 "The ASHES_DIR isn't defined." yellow default
    Echo.ps1 "Don't compile SCDF project. If you do, many problems will occurs." red yellow
}
else
{
    $($env:BUILDDIR="./Build")

    $INCDIR = $($env:ASHES_DIR) + "\inc\SCDF"
    $LIBDIR = $($env:BUILDDIR) + "\lib"
    $SHRDIR = $($env:BUILDDIR) + "\share"

    if(Test-Path -Path $INCDIR)
    {
        Echo.ps1 "INCDIR... OK" green default
    }
    else {
        mkdir $INCDIR
        Echo.ps1 "INCDIR... CR" green default
    }

    if(Test-Path -Path $LIBDIR)
    {
        Echo.ps1 "LIBDIR... OK" green default
    }
    else {
        mkdir $LIBDIR
        Echo.ps1 "LIBDIR... CR" green default
    }

    if(Test-Path -Path $SHRDIR)
    {
        Echo.ps1 "SHRDIR... OK" green default
    }
    else {
        mkdir $SHRDIR
        Echo.ps1 "SHRDIR... CR" green default
    }

    Rename-Item Makefile.windows Makefile
}