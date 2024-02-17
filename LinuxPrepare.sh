if [ $(printenv | grep ASHES_DIR | grep -c .) -eq 0 ]; then
    Echo "The ASHES_DIR isn't defined." yellow default
    Echo "Don't compile SCDF project. If you do, many problems will occurs." red yellow
else
    export BUILDDIR="./Build"

    $INCDIR = $ASHES_DIR + "/inc/SCDF"
    $LIBDIR = $BUILDDIR + "/lib"
    $SHRDIR = $BUILDDIR + "/share"

    mkdir $INCDIR
    mkdir $LIBDIR
    mkdir $SHRDIR

    mv -i Makefile.linux Makefile
fi