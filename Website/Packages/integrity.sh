for package in $(ls *.tar.gz); do
    tar xf $package
    pushd $(basename $package .tar.gz) > /dev/null
    echo $package
    sha256sum --ignore-missing -c integrity.sha256
    popd > /dev/null
    rm -rf $(basename $package .tar.gz)
done
