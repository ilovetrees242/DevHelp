cat > MOONBUILD << "EOF"
#!/bin/bash
source /var/db/Veiler/sync/(package)/info
trap 'echo -e "${BLUE}Interrupted. Goodbye!${NC}"; exit 1'
case $1 in
    getpkg)
        if [ ! -f "$MOONPKG.tar.gz" ]; then
            if [ "$VEILERQUIET" -eq 1 ]; then wget -q --show-progress ""$SRC"/"$MOONPKG".tar.gz"
            else wget ""$SRC"/"$MOONPKG".tar.gz"; fi
        fi
    ;;
    verifyintegrity)
        sha256sum --check --quiet integrity.sha
    ;;
    build)
        if [ -d "$MOONPKG" ]; then rm -rf "$MOONPKG"; fi
        if [ "$VEILERQUIET" -eq 1 ]; then
            tar xf "$MOONPKG.tar.gz"
            pushd "$MOONPKG" &> /dev/null
                # configure command goes here
                ./configure --prefix=/usr > /dev/null
                # build command goes here
                make --quiet 
            popd &> /dev/null
            set +e
        else
            tar xvf "$MOONPKG.tar.gz"
            if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: Could not extract the package source tarball${NC}"; fi
            pushd "$MOONPKG"
                # configure command goes here
                ./configure --prefix=/usr
                # build command goes here
                make
            popd
            set +e
        fi
    ;;
    install)
        pushd $MOONPKG &> /dev/null
        # install command goes here
            if [ $VEILERQUIET -eq 1 ]; then
                make install > /dev/null    
            else
                make install
            fi
            cp -r /var/db/Veiler/sync/"$MOONPKGNAME"/ /var/db/Veiler/local &> /dev/null
        popd &> /dev/null
        if [ "$VEILERDOC" -eq 0 ]; then
            while read file; do
            if [ $VEILERQUIET -eq 1 ]; then
                rm -f "$VEILERDEST$file"
            else
                rm -rfv "$VEILERDEST$file"
            fi
            done < /var/db/Veiler/sync/"$MOONPKGNAME"/docfiles
        fi
    ;;
    uninstall)
        if [ $VEILERQUIET -eq 1 ]; then
            while read name; do rm -f $name; done < "/var/db/Veiler/local/$MOONPKGNAME/files"
        else
            while read name; do rm -vf $name; done < "/var/db/Veiler/local/$MOONPKGNAME/files"
        fi
    ;;
esac
EOF
chmod +x MOONBUILD
