cat > MOONBUILD << "EOF"
#!/bin/bash
BUILDSCRITPID="$!"
animation(){
    while true; do
        echo -ne "\r$1   ${NC}"; sleep 0.2
        echo -ne "\r$1.  ${NC}"; sleep 0.2
        echo -ne "\r$1.. ${NC}"; sleep 0.2
        echo -ne "\r$1...${NC}"; sleep 0.2
    done &
    BUILDSCRIPTPID="$!"
}
build_stop_animation(){
    if [ -n $BUILDSCRIPTPID ]; then kill $BUILDSCRIPTPID; fi &> /dev/null
}
trap 'build_stop_animation' INT TERM ERR
source /var/db/Veiler/sync/(package)/info
case $1 in
    getpkg)
        if [ ! -f "$MOONPKG.tar.gz" ]; then
            if [ "$VEILERQUIET" -eq 1 ]; then wget -q --show-progress ""$SRC"/"$MOONPKG".tar.gz"
            else wget ""$SRC"/"$MOONPKG".tar.gz"; fi
            if [ $? -ne 0 ]; then
                echo -e "${ORANGE}"$MOONPKGNAME": Error: ${WHITE}There was an error while downloading the package source tarball${NC}"; exit 1
            fi
        fi
    ;;
    verifyintegrity)
        sha256sum --check --quiet integrity.sha
        echo -ne ${NC}
        if [ $? -ne 0 ]; then 
            echo -e "\n${ORANGE}"$MOONPKGNAME": Error:${WHITE} Package integrity was not verified!${NC}"; exit 1
        fi
    ;;
    build)
        if [ -d "$MOONPKG" ]; then rm -rf "$MOONPKG"; fi
        if [ "$VEILERQUIET" -eq 1 ]; then
            animation "${YELLOW}"$MOONPKGNAME": ${WHITE}Extracting the package source tarball${NC}"
            tar xf "$MOONPKG.tar.gz"
            if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME" Error: ${WHITE}Could not extract the package source tarball${NC}"; fi
            build_stop_animation; echo
            pushd "$MOONPKG" &> /dev/null
                animation "${YELLOW}"$MOONPKGNAME": ${WHITE}Configuring the package${NC}"

                ./configure --prefix=/usr > /dev/null

                if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: ${NC}Could not configure the package${NC}"; fi
                build_stop_animation; echo
                animation "${YELLOW}"$MOONPKGNAME": ${WHITE}Building the package${NC}"

                make > /dev/null

                if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: ${WHITE}Could not build the package${NC}"; fi
                build_stop_animation; echo
            popd &> /dev/null
            set +e
        else
            echo -e "${YELLOW}"$MOONPKGNAME": Extracting the package source tarball...${NC}"
            tar xvf "$MOONPKG.tar.gz"
            if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: Could not extract the package source tarball${NC}"; fi
            pushd "$MOONPKG"
                echo -e "${YELLOW}"$MOONPKGNAME": ${WHITE}Configuring the package...${NC}"
                # configure command goes here

                ./configure --prefix=/usr

                if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: ${WHITE}Could not configure the package${NC}"; fi
                echo -e "${YELLOW}"$MOONPKGNAME": Building the package...${NC}"
                # build command goes here

                make

                if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error:Could not build the package${NC}"; fi
            popd
            set +e
        fi
    ;;
    install)
        if [ $VEILERQUIET -eq 1 ]; then
            animation "${YELLOW}$MOONPKGNAME: ${WHITE}Installing the package${NC}"
            pushd $MOONPKG &> /dev/null
                # install command goes here
                make install > /dev/null

                if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: ${WHITE}Failed to install the package${NC}"; exit 1; fi
                cp -r /var/db/Veiler/sync/"$MOONPKGNAME"/ /var/db/Veiler/local &> /dev/null
            popd &> /dev/null
            build_stop_animation; echo
            if [ "$VEILERDOC" -eq 0 ]; then
                while read file; do
                    rm -f "$file"
                done < /var/db/Veiler/sync/"$MOONPKGNAME"/docfiles
            fi
        else
            echo -e "${YELLOW}$MOONPKGNAME: ${WHITE}Installing the package...${NC}" 
            pushd $MOONPKG
                # install command goes here
                make install

                if [ $? -ne 0 ]; then echo -e "${ORANGE}"$MOONPKGNAME": Error: ${WHITE}Failed to install the package${NC}"; exit 1; fi
                cp -r /var/db/Veiler/sync/"$MOONPKGNAME"/ /var/db/Veiler/local &> /dev/null
            popd
            if [ "$VEILERDOC" -eq 0 ]; then
                while read file; do
                    rm -vf "$file"
                done < /var/db/Veiler/sync/"$MOONPKGNAME"/docfiles
            fi
        fi
    ;;
    uninstall)
        if [ $VEILERQUIET -eq 1 ]; then
            animation "${YELLOW}$MOONPKGNAME: ${WHITE}Uninstalling the package${NC}"
            while read name; do rm -f $name; done < "/var/db/Veiler/local/$MOONPKGNAME/files"
            build_stop_animation; echo
        else
            echo -e "${YELLOW}$MOONPKGNAME: ${WHITE}Uninstalling the package...${NC}" 
            while read name; do rm -vf $name; done < "/var/db/Veiler/local/$MOONPKGNAME/files"
        fi
    ;;
esac
EOF
chmod +x MOONBUILD
