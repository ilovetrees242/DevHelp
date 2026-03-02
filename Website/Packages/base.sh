cat > MOONBUILD << "EOF"
#!/bin/bash
MOONPKGNAME="which"
MOONPKGVERSION="2.23"
MOONPKG="$MOONPKGNAME-$MOONPKGVERSION"
MOONPKGSRC="https://ftp.gnu.org/gnu/which"
DEPENDS="bash glibc"
BUILDSCRIPTPID=""
animation(){
    while true; do
        echo -ne "\r$1   ${NC}"; sleep 0.2
        echo -ne "\r$1.  ${NC}"; sleep 0.2
        echo -ne "\r$1.. ${NC}"; sleep 0.2
        echo -ne "\r$1...${NC}"; sleep 0.2
    done &
    BUILDSCRIPTPID="$!"
}
stop_animation(){
    if [ -n $BUILDSCRIPTPID ]; then kill $BUILDSCRIPTPID; fi &> /dev/null
}
trap 'stop_animation' INT TERM ERR
case $1 in
    chkdeps)
        for PACKAGE in $DEPENDS; do
            INSTALLED="$(grep -w "$PACKAGE" /var/db/Veiler/package.db | awk '{print $2}')"
            if [ $INSTALLED == "yes" ]; then
                echo -e "${YELLOW}Package ${WHITE}$PACKAGE${YELLOW} found!${NC}"
            elif [ $INSTALLED == "no" ]; then
                echo -e "${ORANGE}Package ${WHITE}$PACKAGE${ORANGE} not found!${NC}"
                exit 1
            else
                echo -e "${ORANGE}Incorrect structure of package database.${NC}"
                exit 1
            fi
        done
    ;;
    build)
        if [ $VEILERQUIET -eq 1 ]; then
            if [ ! -f "$MOONPKG.tar.gz" ]; then
                echo -e "${YELLOW}Downloading package source tarball...${NC}"
                wget -q --show-progress "$MOONPKGSRC/$MOONPKG.tar.gz"
                if [ $? -eq 0 ]; then
                    echo -e "${WHITE}Package downloaded successfully!${NC}"
                else
                    echo -e "${ORANGE}There was an error while downloading the package source tarball${NC}"; exit 1
                fi
            fi
            set -e
            if [ -d $MOONPKG ]; then rm -rf $MOONPKG; fi
            echo -e "${YELLOW}Verifiying package integrity${NC}"
            sha256sum --check integrity.sha
            if [ $? -ne 0 ]; then 
                    echo -e "${ORANGE}Package integrity was not verified!${NC}"
            fi
            echo -e "${WHITE}Package integrity verified!${NC}"
            animation "${YELLOW}Extracting the package source tarball${NC}"
            tar xf "$MOONPKG.tar.gz"
            if [ $? -ne 0 ]; then echo -e "${ORANGE}Could not extract the package source tarball${NC}"; fi
            stop_animation; echo
            pushd "$MOONPKG" &> /dev/null
                animation "${YELLOW}Configuring $MOONPKGNAME${NC}"
                ./configure --prefix=/usr > /dev/null
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Could not configure the package${NC}"; fi
                stop_animation; echo
                animation "${YELLOW}Building $MOONPKGNAME${NC}"
                make > /dev/null
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Could not build the package${NC}"; fi
                stop_animation; echo
            popd &> /dev/null
            set +e
        else
            if [ ! -f "$MOONPKG.tar.gz" ]; then
                echo -e "${YELLOW}Downloading package source tarball...${NC}"
                wget "$MOONPKGSRC/$MOONPKG.tar.gz"
                if [ $? -eq 0 ]; then
                    echo -e "${WHITE}Package downloaded successfully!${NC}"
                else
                    echo -e "${ORANGE}There was an error while downloading the package source tarball${NC}"; exit 1
                fi
            fi
            set -e
            echo -e "${YELLOW}Verifiying package integrity...${NC}"
            sha256sum --check integrity.sha
            if [ $? -ne 0 ]; then 
                    echo -e "${ORANGE}Package integrity was not verified!${NC}"
            fi
            echo -e "${WHITE}Package integrity verified!${NC}"
            if [ -d $MOONPKG ]; then rm -rf $MOONPKG; fi
            echo -e "${YELLOW}Extracting the package source tarball...${NC}"
            tar xvf "$MOONPKG.tar.gz"
            if [ $? -ne 0 ]; then echo -e "${ORANGE}Could not extract the package source tarball${NC}"; fi
            pushd "$MOONPKG"
                echo -e "${YELLOW}Configuring $MOONPKGNAME...${NC}"
                ./configure --prefix=/usr
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Could not configure the package${NC}"; fi
                echo -e "${YELLOW}Building $MOONPKGNAME...${NC}"
                make
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Could not build the package${NC}"; fi
            popd
            set +e
        fi
    ;;
    install)
        if [ $VEILERQUIET -eq 1 ]; then
            animation "${YELLOW}Installing $MOONPKGNAME${NC}"
            pushd $MOONPKG &> /dev/null
                make install > /dev/null
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Failed to install the package${NC}"; exit 1; fi
            popd &> /dev/null
            stop_animation; echo
            if [ $VEILERDOC -eq 0 ]; then
                rm -f /usr/share/info/which.info
                rm -f /usr/share/man/man1/which.1
            fi
        else
            echo -e "${YELLOW}Installing $MOONPKGNAME...${NC}" 
            pushd $MOONPKG
                make install
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Failed to install the package${NC}"; exit 1; fi
            popd
            if [ $VEILERDOC -eq 0 ]; then
                rm -vf /usr/share/info/which.info
                rm -vf /usr/share/man/man1/which.1
            fi
        fi
    ;;
    uninstall)
        echo -e "${YELLOW}Verifiying package integrity${NC}"
        sha256sum -c integrity.sha
        if [ $? -ne 0 ]; then echo -e "${ORANGE}Failed to verify the package integrity!${NC}"; exit 1; fi
        if [ $VEILERQUIET -eq 1 ]; then
            animation "${YELLOW}Unistalling $MOONPKGNAME${NC}"
            pushd $MOONPKG &> /dev/null
                make uninstall > /dev/null
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Failed to uninstall the package${NC}"; exit 1; fi
            popd &> /dev/null
            stop_animation; echo
        else
            echo -e "${YELLOW}Uninstalling $MOONPKGNAME...${NC}" 
            pushd $MOONPKG
                make uninstall
                if [ $? -ne 0 ]; then echo -e "${ORANGE}Failed to uninstall the package${NC}"; exit 1; fi
            popd
        fi
    ;;
    version)
        echo "$MOONPKGVERSION"
    ;;
esac
EOF
