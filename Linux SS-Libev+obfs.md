# 12 SS-Libev+obfs
Centos
------

教程地址:

[https://www.junle.org/CentOS7%E7%BC%96%E8%AF%91%E5%AE%89%E8%A3%85shadowsocks-libev-simple-obfs%E6%B7%B7%E6%B7%86/](https://www.junle.org/CentOS7%E7%BC%96%E8%AF%91%E5%AE%89%E8%A3%85shadowsocks-libev-simple-obfs%E6%B7%B7%E6%B7%86/)

1.安装shadowsocks-libev
---------------------

git clone [https://github.com/shadowsocks/shadowsocks-libev.git](https://github.com/shadowsocks/shadowsocks-libev.git) cd shadowsocks-libev git submodule update –init –recursive

2.安装基本构建依赖
----------

yum install gettext gcc autoconf libtool automake make asciidoc xmlto c-ares-devel libev-devel pcre-devel

安装libsodium
-----------

wget [https://google.iplcn2.com/soft/linux/libsodium-1.0.18.tar.gz](https://google.iplcn2.com/soft/linux/libsodium-1.0.18.tar.gz) tar xvf libsodium-1.0.18.tar.gz ./configure –prefix=/usr && make sudo make install popd sudo ldconfig

安装MbedTLS
---------

wget [https://google.iplcn2.com/soft/linux/mbedtls.tar.gz](https://google.iplcn2.com/soft/linux/mbedtls.tar.gz) tar xvf mbedtls.tar.gz make SHARED=1 CFLAGS=-fPIC sudo make DESTDIR=/usr install popd sudo ldconfig

安装shadowsocks-libev
-------------------

./autogen.sh ./configure –with-sodium-include=/usr/include –with-sodium-lib=/usr/local/lib –with-mbedtls-include=/usr/include –with-mbedtls-lib=/usr/lib make && make install

安装simple-obfs
-------------

git clone [https://github.com/shadowsocks/simple-obfs.git](https://github.com/shadowsocks/simple-obfs.git) cd simple-obfs git submodule update –init –recursive

./autogen.sh ./configure make && make install

创建shadowsocks配置文件
-----------------

mkdir -p /etc/shadowsocks/ touch /etc/shadowsocks/config.json

vim /etc/shadowsocks/config.json

```
{
    "server":"0.0.0.0",
    "server_port":8388,
    "local_port":1080,
    "password":"password",
    "timeout":60,
    "method":"chacha20-ietf-poly1305",
    "user":"daemon",
    "plugin":"obfs-server",
    "plugin_opts":"obfs=http;failover=example.com"
}
```

创建shadowsocks启动脚本
-----------------

touch /etc/init.d/shadowsocks chmod +x /etc/init.d/shadowsocks vim /etc/init.d/shadowsocks

```markdown
#!/usr/bin/env bash
# chkconfig: 2345 90 10# description: A secure socks5 proxy, designed to protect your Internet traffic.### BEGIN INIT INFO# Provides:          Shadowsocks-libev# Required-Start:    $network $syslog# Required-Stop:     $network# Default-Start:     2 3 4 5# Default-Stop:      0 1 6# Short-Description: Fast tunnel proxy that helps you bypass firewalls# Description:       Start or stop the Shadowsocks-libev server### END INIT INFO# Author: Teddysun <i@teddysun.com>if [ -f /usr/local/bin/ss-server ]; then
    DAEMON=/usr/local/bin/ss-server
elif [ -f /usr/bin/ss-server ]; then
    DAEMON=/usr/bin/ss-server
fi
NAME=Shadowsocks-libev
CONF=/etc/shadowsocks/config.json
PID_DIR=/var/run
PID_FILE=$PID_DIR/shadowsocks.pid
RET_VAL=0
[ -x $DAEMON ] || exit 0
if [ ! -d $PID_DIR ]; then
    mkdir -p $PID_DIR
    if [ $? -ne 0 ]; then
        echo "Creating PID directory $PID_DIR failed"
        exit 1
    fi
fi
if [ ! -f $CONF ]; then
    echo "$NAME config file $CONF not found"
    exit 1
fi
check_running() {
    if [ -r $PID_FILE ]; then
        read PID < $PID_FILE
        if [ -d "/proc/$PID" ]; then
            return 0
        else
            rm -f $PID_FILE
            return 1
        fi
    else
        return 2
    fi
}
do_status() {
    check_running
    case $? in
        0)
        echo "$NAME (pid $PID) is running..."
        ;;
        1|2)
        echo "$NAME is stopped"
        RET_VAL=1
        ;;
    esac
}
do_start() {
    if check_running; then
        echo "$NAME (pid $PID) is already running..."
        return 0
    fi
    $DAEMON -uv -c $CONF -f $PID_FILE
    if check_running; then
        echo "Starting $NAME success"
    else
        echo "Starting $NAME failed"
        RET_VAL=1
    fi
}
do_stop() {
    if check_running; then
        kill -9 $PID
        rm -f $PID_FILE
        echo "Stopping $NAME success"
    else
        echo "$NAME is stopped"
        RET_VAL=1
    fi
}
do_restart() {
    do_stop
    do_start
}
case "$1" in
    start|stop|restart|status)
    do_$1
    ;;
    *)
    echo "Usage: $0 { start | stop | restart | status }"
    RET_VAL=1
    ;;
esac
exit $RET_VAL
```

配置shadowsocks开机启动
-----------------

chkconfig –add shadowsocks

启动shadowsocks
-------------

/etc/init.d/shadowsocks start

Ubuntu
------

教程地址:[https://blog.ahao.moe/posts/multi\_user\_of\_shadowsocks\_libev.html](https://blog.ahao.moe/posts/multi_user_of_shadowsocks_libev.html) apt update -y apt install shadowsocks-libev -y # 安装或升级 dpkg -l | grep shadowsocks # 查看版本号

1\. 添加单用户配置文件
-------------

vim /etc/shadowsocks-libev/config.json

```markdown
{
    "server":"0.0.0.0",
    "server_port":65510,
    "local_port":1080,
    "method": "aes-256-gcm",
    "password": "SABER@007a",
    "mode": "tcp_and_udp",
    "fast_open": false
}
```

2\. 启动服务端
---------

ss-server systemctl start shadowsocks-libev.service # 启动 systemctl enable shadowsocks-libev.service # 开机自启 systemctl status shadowsocks-libev.service # 查看状态 systemctl restart shadowsocks-libev.service # 重启

1\. 添加多用户配置文件
-------------

vim /etc/shadowsocks-libev/config.json

```
{
  "server":["::0","0.0.0.0"],
  "port_password": {
    "8452": "Zqx465gr5snppXlYWMEKZQ=="
  },
  "method": "chacha20-ietf-poly1305",
  "mode": "tcp_and_udp",
  "fast_open": false
}
```

2\. 启动服务端
---------

ss-manager -c /etc/shadowsocks-libev/config.json

1\. 从 Github 下载源码进行编译
---------------------

cd ~ apt-get install –no-install-recommends build-essential autoconf libtool libssl-dev libpcre3-dev libev-dev asciidoc xmlto automake -y

git clone [https://github.com/shadowsocks/simple-obfs.git](https://github.com/shadowsocks/simple-obfs.git) cd simple-obfs git submodule update –init –recursive ./autogen.sh && ./configure && make && make install

2\. 添加配置文件,
-----------

添加 plugin 和 plugin\_opts 参数

vim /etc/shadowsocks-libev/config.json { …省略其他配置 “plugin”:“obfs-server”, “plugin\_opts”:“obfs=http;failover=apps.bdimg.com” }

3\. 重启 shadowsocks-libev
------------------------

systemctl restart shadowsocks-libev.service # 重启