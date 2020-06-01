# mono
pkg install wget perl python cmake clang
wget https://download.mono-project.com/sources/mono/mono-6.8.0.105.tar.xz

# It may show the following error but it's ok.
# tar: mono-6.8.0.105/external/bockbuild/bb: Cannot hard link to ‘mono-6.8.0.105/external/bockbuild/bockbuild.py’: Permission denied
tar xf mono-6.8.0.105.tar.xz
cd mono-6.8.0.105

./configure --prefix=/data/data/com.termux/files/usr/local --disable-mcs-build

sed -i 's|#define HAVE_PTHREAD_GETNAME_NP 1|/\* #undef HAVE_PTHREAD_GETNAME_NP \*/|g' config.h
sed -i 's|#define HAVE_GETPWENT 1|/\* #undef HAVE_GETPWENT \*/|g' config.h
sed -i 's|#define HAVE_SETPWENT 1|/\* #undef HAVE_SETPWENT \*/|g' config.h
sed -i 's|#define HAVE_LUTIMES 1|/\* #undef HAVE_LUTIMES \*/|g' config.h
sed -i 's|#define HAVE_FUTIMES 1|/\* #undef HAVE_FUTIMES \*/|g' config.h
sed -i 's|#define HAVE_GETDOMAINNAME 1|/\* #undef HAVE_GETDOMAINNAME \*/|g' config.h
sed -i 's|#define HAVE_SETDOMAINNAME 1|/\* #undef HAVE_SETDOMAINNAME \*/|g' config.h

sed -i 's|-lpthread|-lpthread -llog|g' mono/mini/Makefile
sed -i 's|-lpthread|-lpthread -llog|g' mono/dis/Makefile
sed -i 's|-lpthread|-lpthread -llog|g' tools/pedump/Makefile
sed -i 's|\tgint64       st_atime_nsec;|#undef st_atime_nsec\n#undef st_mtime_nsec\n#undef st_ctime_nsec\n\tgint64       st_atime_nsec;|g' support/map.h
sed -i 's|return L_cuserid;|return -1;|g' support/stdio.c

make
make install
cd ..
# msbuild
pkg install p7zip
wget http://download.mono-project.com/repo/ubuntu/pool/main/m/msbuild/msbuild_16.5+xamarinxplat.2020.01.10.05.36-0xamarin1+ubuntu1804b1_all.deb
7z x msbuild_16.5+xamarinxplat.2020.01.10.05.36-0xamarin1+ubuntu1804b1_all.deb
tar xf data.tar
cp -R usr/* /data/data/com.termux/files/usr/local/
rm -rf data.tar usr
#homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"