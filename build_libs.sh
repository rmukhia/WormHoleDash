rm -rf bullet-build
mkdir bullet-build
pushd bullet-build
cmake ../bullet3 -G "Unix Makefiles" -DINSTALL_LIBS=ON 
make -j4
make DESTDIR=$(dirname $(pwd))/extra install
rm -rf bullet-build
