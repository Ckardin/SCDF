if [ $(printenv | grep ASHES_DIR | grep -c .) -eq 0 ]; then
    export ASHES_DIR="/Ashes"

    echo "export ASHES_DIR='/Ashes'" >> ~/.bashrc
fi

echo "VAR(ASHES_DIR) OK"

sudo mkdir $ASHES_DIR/bin   && echo "BINDIR OK"
sudo mkdir $ASHES_DIR/lib   && echo "LIBDIR OK"
sudo mkdir $ASHES_DIR/share && echo "SHRDIR OK"

# export CP=cp
# export RM=rm
export A_SHLIB=so
export A_STLIB=a

export BINDIR=$ASHES_DIR/bin
export LIBDIR=$ASHES_DIR/lib
export INCDIR=$ASHES_DIR/share