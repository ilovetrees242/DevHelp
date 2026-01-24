touch LFSBUILD
chmod +x LFSBUILD
cat > LFSBUILD << "EOF"
LFSPKGNAME=""
LFSPKGVERSION=""
LFSPKG="$LFSPKGNAME-$LFSPKGVERSION"
DEPENDS=""
cae $1 in
    chkdeps)
    ;;
    build)
    ;;
    uninstall)
    ;;
EOF


