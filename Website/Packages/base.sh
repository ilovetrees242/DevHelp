cat > MOONBUILD << "EOF"
#!/bin/bash
source "$VEILERDBPATH/sync/(package)/info"
trap 'echo -e "${BLUE}Interrupted. Goodbye!${NC}"; exit 1' INT
case $1 in
    getpkg)
        if [ ! -f "$MOONPKG.tar.gz" ]; then
            if [ "$VEILERQUIET" -eq 1 ]; then 
                wget -q --show-progress ""$SRC"/"$MOONPKG".tar.gz"
            else 
                wget -nv --show-progress ""$SRC"/"$MOONPKG".tar.gz"
            fi
        fi
    ;;
    build)
        CONFIGPARAMS=()
        for FLAG in ${USEFLAGS[@]}; do
            case $FLAG in
                *)
                    CONFIGPARAMS+=("DUMY")
                ;;
            esac
        done
        if [ -d "$MOONPKG" ]; then rm -rf "$MOONPKG"; fi
        if [ "$VEILERQUIET" -eq 1 ]; then
            tar xf "$MOONPKG.tar.gz"
            pushd "$MOONPKG" &> /dev/null
                # configure command goes here
                ./configure --prefix=/usr ${CONFIGPARAMS[@]} > /dev/null
                # build command goes here
                make --quiet 
            popd &> /dev/null
        else
            tar xvf "$MOONPKG.tar.gz"
            pushd "$MOONPKG"
                # configure command goes here
                ./configure --prefix=/usr ${CONFIGPARAMS[@]}
                # build command goes here
                make
            popd
        fi
    ;;
    install)
        pushd $MOONPKG &> /dev/null
        # install command goes here
            if [ $VEILERQUIET -eq 1 ]; then
                make DESTDIR=$PWD/DEST --quiet install 
            else
                make DESTDIR=$PWD/DEST install
            fi
        popd &> /dev/null
    ;;
esac
EOF
chmod +x MOONBUILD
touch integrity.sha256
