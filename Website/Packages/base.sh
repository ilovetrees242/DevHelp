cat > MOONBUILD << "EOF"
#!/bin/bash
MOONPKGNAME="which"
MOONPKGVERSION="2.23"
MOONPKG="$MOONPKGNAME-$MOONPKGVERSION"
SRC="https://ftp.gnu.org/gnu/which/"
DEPENDS="bash glibc"
BUILDSCRIPTPID=""
clean() {
   echo -e "${YELLOW}Interrupted.${NC}"
   rm -rfv "$MOONPKG.tar.gz" "$MOONPKG.tar.gz.*" "$MOONPKG" 
}
trap clean INT
case $1 in
	chkdeps)
        echo -e "${YELLOW}Checking for dependencies...${NC}"
        set -e; trap 'echo "$PKG not found!"' ERR
        for PKG in $DEPENDS; do
            if [ "$PKG" == "glibc" ]; then
                ldd --version &> /dev/null
                echo -e "${WHITE}Package ${YELLOW}$PKG${WHITE} found!${NC}"
            else
                $PKG --version $> /dev/null
                echo -e "${WHITE}Package ${YELLOW}$PKG${WHITE} found!${NC}"
            fi
        done
        set +e
        echo -e "${YELLOW}Dependencies met!${NC}"
	;;
	build)
        if [ "$VEILERQUIET" -eq 0 ]; then
            wget "$SRC/$MOONPKG.tar.gz"
            if [ "$?" -eq 0 ]; then echo -e "${YELLOW}Package downloaded successfuly.${NC}"; echo -e "${YELLOW}Now verifying package integrity.${NC}" 
            else
                echo -e "${ORANGE}An error was encountered while downloading the package.${NC}"
                exit 1
            fi
            md5sum -c integrity.md5
            if [ "$?" -eq 0 ]; then echo -e "${YELLOW}Package integrity verified!${NC}"
            else
                echo -e "${ORANGE}Integrity not verified. Not building the package.${NC}"
                rm -f "$MOONPKG.tar.gz"
                exit 1 
            fi
            set -e 
            echo -e "${YELLOW}Extracting the package source tarball...${NC}"; sleep 0.2
		    tar xvf $MOONPKG.tar.?z && echo -e "${WHITE}->Done!${NC}"
            trap 'echo -e "${ORANGE}Failed to extract the tarball.${NC}"' 
            echo -e "${YELLOW}Entering build enviroment...${NC}"; sleep 0.2
		    pushd $MOONPKG && echo -e "${WHITE}->Done!${NC}"
                echo -e "${YELLOW}Configuring the package...${NC}"; sleep 0.2
			    ./configure --prefix=/usr && echo -e "${WHITE}->Done!${NC}"
                trap 'echo -e "${ORANGE}Failed to configure the package.${NC}"' ERR
                echo -e "${YELLOW}Building the package...${NC}"; sleep 0.2
                make && echo -e "${WHITE}->Done!${NC}"
                trap 'echo -e "${ORANGE}Failed to build the package.${NC}"' ERR
            popd 
            set +e; trap - ERR
        else
            set -e 
            while true; do
                echo -ne "\r${ORANGE}Downloading the package source tarball   ${NC}"; sleep 0.2
                echo -ne "\r${ORANGE}Downloading the package source tarball.  ${NC}"; sleep 0.2
                echo -ne "\r${ORANGE}Downloading the package source tarball.. ${NC}"; sleep 0.2
                echo -ne "\r${ORANGE}Downloading the package source tarball...${NC}"; sleep 0.2
            done &
            BUILDSCRIPTPID="$!"
            wget "$SRC/$MOONPKG.tar.gz" &> /dev/null
            trap 'echo "${ORANGE}An error was encountered while downloading the package.${NC}; kill $BUILDSCRIPTPID"' ERR; set +e
            trap - ERR
            kill $BUILDSCRIPTPID; echo -e "\n${WHITE}->Done!, now verifying package integrity."
            md5sum -c integrity.md5 
            if [ "$?" -eq 0 ]; then echo -e "${WHITE}Package integrity verified!${NC}"
            else
                echo -e "${ORANGE}Integrity not verified. Not building the package.${NC}"
                rm -f "$MOONPKG.tar.gz"
                exit 1 
            fi
            set -e
            while true; do
                echo -ne "\r${YELLOW}Extracting the package source tarball   ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Extracting the package source tarball.  ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Extracting the package source tarball.. ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Extracting the package source tarball...${NC}"; sleep 0.2
            done &
            BUILDSCRIPTPID="$!"
            tar xf $MOONPKG.tar.?z 
            trap 'echo -e "${YELLOW}Failed to extract the package.${NC}"' ERR
            kill $BUILDSCRIPTPID; echo -e "\n${WHITE}->Done!"
            echo -e "${YELLOW}Entering build enviroment...${NC}"; sleep 0.2
		    pushd $MOONPKG &> /dev/null && echo -e "${WHITE}->Done!${NC}"
                while true; do
                    echo -ne "\r${YELLOW}Configuring ${WHITE}$MOONPKGNAME   ${NC}"; sleep 0.2
                    echo -ne "\r${YELLOW}Configuring ${WHITE}$MOONPKGNAME.  ${NC}"; sleep 0.2
                    echo -ne "\r${YELLOW}Configuring ${WHITE}$MOONPKGNAME.. ${NC}"; sleep 0.2
                    echo -ne "\r${YELLOW}Configuring ${WHITE}$MOONPKGNAME...${NC}"; sleep 0.2
                done &
                BUILDSCRIPTPID="$!"
                ./configure --prefix=/usr &> /dev/null 
                trap 'echo -e "${YELLOW}Failed to configure the package.${NC}"' ERR
                kill $BUILDSCRIPTPID; echo -e "\n${WHITE}->Done!${NC}"
                while true; do
                    echo -ne "\r${YELLOW}Compiling ${WHITE}$MOONPKGNAME${YELLOW}   ${NC}"; sleep 0.2
                    echo -ne "\r${YELLOW}Compiling ${WHITE}$MOONPKGNAME${YELLOW}.  ${NC}"; sleep 0.2
                    echo -ne "\r${YELLOW}Compiling ${WHITE}$MOONPKGNAME${YELLOW}.. ${NC}"; sleep 0.2
                    echo -ne "\r${YELLOW}Compiling ${WHITE}$MOONPKGNAME${YELLOW}...${NC}"; sleep 0.2
                done &
                BUILDSCRIPTPID="$!"
                make &> /dev/null 
                trap 'echo -e "${YELLOW}Failed to build the package.${NC}"' ERR
                kill $BUILDSCRIPTPID; echo -e "\n${WHITE}"
                echo -e "\n${WHITE}Done!"
            popd &> /dev/null
            set +e
            echo -e "${WHITE}Successfuly built ${YELLOW}$PKGNAME${NC}"
        fi
	;;
    install)
        if [ $VEILERQUIET -eq 0 ]; then
            set -e
            trap 'echo -e "${ORANGE}An error was encountered while installing the package."' ERR
            echo -e "${YELLOW}Installing ${WHITE}${MOONPKGNAME}...${NC}"; sleep 0.2
            pushd $MOONPKG
                make install && echo -e "${WHITE}->Done!${NC}"
            popd
            echo -e "${YELLOW}Cleaning up...${NC}"; sleep 0.2
            clean 
            trap 'echo -e "${YELLOW}Failed to clean up.${NC}; kill $BUILDSCRIPTPID; exit 1"'
            set +e
        else
            while true; do
                echo -ne "\r${YELLOW}Installing ${WHITE}$MOONPKGNAME   ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Installing ${WHITE}$MOONPKGNAME.  ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Installing ${WHITE}$MOONPKGNAME.. ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Installing ${WHITE}$MOONPKGNAME...${NC}"; sleep 0.2
            done &
            BUILDSCRIPTPID="$!"
            pushd $MOONPKG &> /dev/null
            make install &> /dev/null
            if [ "$?" -ne 0 ]; then echo -e "${YELLOW}Could not install the package.${NC}"; exit 1; kill $BUILDSCRIPTPID; 
            else
                kill $BUILDSCRIPTPID
                echo -e "${WHITE}Done!${NC}"
            fi
            while true; do
                echo -ne "\r${YELLOW}Cleaning up   ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Cleaning up.  ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Cleaning up.. ${NC}"; sleep 0.2
                echo -ne "\r${YELLOW}Cleaning up...${NC}"; sleep 0.2
            done &
            BUILDSCRIPTPID="$!"
            popd &> /dev/null
            clean &> /dev/null
            trap 'echo -e "${YELLOW}Failed to clean up.${NC}; kill $BUILDSCRIPTPID; exit 1"' ERR
            kill $BUILDSCRIPTPID
        fi
        trap - ERR
    ;;
	uninstall)
        if [ $VEILERQUIET -eq 1 ]; then
            set -e 
            trap 'echo -e "${ORANGE}An error was encountered while uninstalling! Manual intervention required.${NC}"' ERR
            while true; do
                echo -ne "\r${YELLOW}Uninstalling ${WHITE}${MOONPKGNAME}${YELLOW}   "; sleep 0.2
                echo -ne "\r${YELLOW}Uninstalling ${WHITE}${MOONPKGNAME}${YELLOW}.  "; sleep 0.2
                echo -ne "\r${YELLOW}Uninstalling ${WHITE}${MOONPKGNAME}${YELLOW}.. "; sleep 0.2
                echo -ne "\r${YELLOW}Uninstalling ${WHITE}${MOONPKGNAME}${YELLOW}..."; sleep 0.2
            done &
            BUILDSCRIPTPID=$!
		    rm /usr/bin/which
		    rm -rf /usr/share/man/man1/which.1 && kill "$BUILDSCRIPTPID" && echo -e "\n${WHITE}->Done!${NC}"
            set +e 
            trap - ERR
        else
            echo -ne "${YELLOW}Uninstalling ${WHITE}${MOONPKGNAME}${YELLOW}..."
            rm /usr/bin/which
            rm -rf /usr/share/man/man1/which.1 && echo -e "\n${WHITE}->Done!${NC}"
        fi
	;;
esac
EOF
echo "Successfuly installed a MOONBUILD build script"
