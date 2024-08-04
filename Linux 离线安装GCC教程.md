# 04 Linux离线安装GCC教程
1 下载相关依赖包
---------

官方离线包下载网站：

[https://ftp.gnu.org/gnu/](https://ftp.gnu.org/gnu/)

清华大学镜像站：

[https://mirrors.tuna.tsinghua.edu.cn/gnu/](https://mirrors.tuna.tsinghua.edu.cn/gnu/)

1.1 m4

[https://ftp.gnu.org/gnu/m4/m4-1.4.18.tar.gz](https://ftp.gnu.org/gnu/m4/m4-1.4.18.tar.gz)

1.2 gmp

[ftp://gcc.gnu.org/pub/gcc/infrastructure/gmp-6.1.0.tar.bz2](ftp://gcc.gnu.org/pub/gcc/infrastructure/gmp-6.1.0.tar.bz2)

1.3 mpfr

[ftp://gcc.gnu.org/pub/gcc/infrastructure/mpfr-3.1.4.tar.bz2](ftp://gcc.gnu.org/pub/gcc/infrastructure/mpfr-3.1.4.tar.bz2)

1.4 mpc

[ftp://gcc.gnu.org/pub/gcc/infrastructure/mpc-1.0.3.tar.gz](ftp://gcc.gnu.org/pub/gcc/infrastructure/mpc-1.0.3.tar.gz)

1.5 gcc

[https://ftp.gnu.org/gnu/gcc/gcc-9.5.0/gcc-9.5.0.tar.gz](https://ftp.gnu.org/gnu/gcc/gcc-9.5.0/gcc-9.5.0.tar.gz)

2 安装
----

2.1 安装m4
--------

```bash
tar zxvf m4-1.4.18.tar.gz
cd m4-1.4.18 && mkdir build
cd build && ../configure
make -j 8 && make install
```

2.2 安装gmp
---------

```bash
tar -jxvf gmp-6.1.0.tar.bz2
cd gmp-6.1.0 && mkdir build
cd build && ../configure --prefix=/opt/gcc-9.5.0/gmp-6.1.0
make -j 8 && make install
```

2.3 安装mpfr
----------

```bash
tar -jxvf mpfr-3.1.4.tar.bz2
cd mpfr-3.1.4 && mkdir build
cd build && ../configure --prefix=/opt/gcc-9.5.0/mpfr-3.1.4 --with-gmp=/opt/gcc-9.5.0/gmp-6.1.0
make -j 8 && make install
```

2.4 安装mpc
---------

```bash
tar -zxvf mpc-1.0.3.tar.gz
cd mpc-1.0.3 && mkdir build
cd build && ../configure --prefix=/opt/gcc-9.5.0/mpc-1.0.3 --with-gmp=/opt/gcc-9.5.0/gmp-6.1.0 --with-mpfr=/opt/gcc-9.5.0/mpfr-3.1.4
make -j 8 && make install
```

2.5 安装gcc
---------

```bash
tar -zxvf gcc-9.5.0.tar.gz
cd gcc-9.5.0 && mkdir build
cd build && ../configure --prefix=/opt/gcc-9.5.0 --with-gmp=/opt/gcc-9.5.0/gmp-6.1.0 --with-mpfr=/opt/gcc-9.5.0/mpfr-3.1.4 --with-mpc=/opt/gcc-9.5.0/mpc-1.0.3 --enable-language=c,c++,fortran --disable-multilib#构建32位命令#cd build && ../configure --prefix=/opt/gcc-9.5.0 --with-gmp=/opt/gcc-9.5.0/gmp-6.1.0 --with-mpfr=/opt/gcc-9.5.0/mpfr-3.1.4 --with-mpc=/opt/gcc-9.5.0/mpc-1.0.3 --enable-language=c,c++,fortran --with-multilib-list=m32#或#cd build && ../configure --prefix=/opt/gcc-9.5.0 --with-gmp=/opt/gcc-9.5.0/gmp-6.1.0 --with-mpfr=/opt/gcc-9.5.0/mpfr-3.1.4 --with-mpc=/opt/gcc-9.5.0/mpc-1.0.3 --enable-language=c,c++,fortran --enable-multilibmake -j 8 && make install
```

2.6 设置环境变量
----------

```bash
#永久vim /etc/profile
vim ~/.bashrc
export PATH=/opt/gcc-9.5.0/bin:$PATHexport LD_LIBRARY_PATH=/opt/gcc-9.5.0/lib64:/opt/gcc-9.5.0/gmp-6.1.0/lib:/opt/gcc-9.5.0/mpfr-3.1.4/lib:/opt/gcc-9.5.0/mpc-1.0.3/lib:$LD_LIBRARY_PATHexport C_INCLUDE_PATH=/opt/gcc-9.5.0/gmp-6.1.0/include:/opt/gcc-9.5.0/mpfr-3.1.4/include:/opt/gcc-9.5.0/mpc-1.0.3/include:/opt/gcc-9.5.0/include:$C_INCLUDE_PATHexport CPLUS_INCLUDE_PATH=/opt/gcc-9.5.0/gmp-6.1.0/include:/opt/gcc-9.5.0/mpfr-3.1.4/include:/opt/gcc-9.5.0/mpc-1.0.3/include:/opt/gcc-9.5.0/include:$C_INCLUDE_PATHexport LIBRARY_PATH=/opt/gcc-9.5.0/lib64:/opt/gcc-9.5.0/gmp-6.1.0/lib:/opt/gcc-9.5.0/mpfr-3.1.4/lib:/opt/gcc-9.5.0/mpc-1.0.3/lib:$LIBRARY_PATH
```

3 可能出现的报错
---------

```bash
离线安装gccA报错：configure: error: cannot compute suffix of object files: cannot compile
原因：未设置gmp\\mpfr\\mpc动态库路径解决方法：export LD_LIBRARY_PATH=/home/saber/gmp/lib:/home/saber/mpfr/lib:/home/saber/mpc/lib
source ~/.bashrc
export C_LINCLUDE_PATH=/home/saber/gmp/include:/home/saber/mpfr/include:/home/saber/mpc/include
source ~/.bashrc
使用环境变量可以通过设置环境变量来指定头文件搜索路径。在bash shell中，可以使用export命令来设置环境变量。例如，将头文件搜索路径设置为/path/to/header/files，可以执行以下命令：
export C_INCLUDE_PATH=/path/to/header/files:$C_INCLUDE_PATH这样就将/path/to/header/files目录添加到了头文件搜索路径中。需要注意的是，这种方式只对当前shell会话有效，如果需要永久生效，可以将export命令添加到~/.bashrc文件中。B报错：/usr/include/gnu/stubs.h:7:27: fatal error: gnu/stubs-32.h: No such file or directory
原因：缺少32位的嵌入式C库。在嵌入式开发环境配置时，也常遇到这个问题。各平台的解决办法：#Debian Linux:sudo apt-get install libc6-dev
#Ubuntu Linux:sudo apt-get install libc6-dev-i386
#OpenSUSE / Novell Suse Linux (SLES):zypper in glibc-devel-32bit
#RHEL / Fedora / CentOS / Scientific Linux:sudo yum install glibc-devel.i686
#进入gcc压缩包，使用下面这个命令自动下载依赖包./contrib/download_prerequisites# 更新make版本wget http://ftp.gnu.org/pub/gnu/make/make-4.3.tar.gz
```

4 在线安装
------

```
#快速安装/需联网或者配置本地源路径
yum -y install gcc
yum -y install gcc-c++
gcc --version
#安装旧版本GCC编译器（安装新版的基础）
yum install -y glibc-static libstdc++-static
yum install -y gcc gcc-c++
```

```bash
在线安装方式2自动下载，运行GCC源码目录内置脚本：wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.9.4/gcc-4.9.4.tar.gz
cd gcc-4.9.4
sh ./contrib/download_prerequisites
手动下载、解压，然后执行命令：cd gcc-4.9.4
ln -sf path/to/gmp-x.x.x gmp
ln -sf path/to/mpc-x.x.x mpc
ln -sf path/to/mpfr-x.x.x mpfr
这样，编译GCC同时自动构建上述3个库。注意要保证3个包的源码目录是干净的，否则可能报错，必要时可执行make distclean
版本要求参考脚本*./contrib/download_prerequisites*，以4.9.4为例# Necessary to build GCC.MPFR=mpfr-2.4.2
GMP=gmp-4.3.2
MPC=mpc-0.8.1
mkdir build-gcc-4.9.4
cd build-gcc-4.9.4
../gcc-4.9.4/configure --prefix=/usr/local/gcc-4.9.4/ --enable-checking=release --enable-languages=c,c++ --disable-multilib

make -j4
make install
```