# Others
some notes
## 1 Linux安装 v 2
### 1.1 安装命令
```bash

// 安裝執行檔和 .dat 資料檔  安裝和更新 V2Ray
bash <(curl -L https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh)

// 只更新 .dat 資料檔  安裝最新發行的 geoip.dat 和 geosite.dat
bash <(curl -L https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-dat-release.sh)

// 移除 V2Ray
bash <(curl -L https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh) --remove
```
### 1.2 安装后设置开机自启
```cpp
# /etc/systemd/system/v2ray.service.d/10-donot_touch_single_conf.conf
# In case you have a good reason to do so, duplicate this file in the same directory and make your customizes there.
# Or all changes you made will be lost!  # Refer: https://www.freedesktop.org/software/systemd/man/systemd.unit.html
[Service]
ExecStart=
ExecStart=/usr/local/bin/v2ray run -config /usr/local/etc/v2ray/config.json

installed: /usr/local/bin/v2ray
installed: /usr/local/share/v2ray/geoip.dat
installed: /usr/local/share/v2ray/geosite.dat
installed: /usr/local/etc/v2ray/config.json
installed: /var/log/v2ray/
installed: /var/log/v2ray/access.log
installed: /var/log/v2ray/error.log
installed: /etc/systemd/system/v2ray.service
installed: /etc/systemd/system/v2ray@.service
removed: /tmp/tmp.e0xidWJcNm
info: V2Ray v5.14.1 is installed.
You may need to execute a command to remove dependent software: apt purge curl unzip
Please execute the command: systemctl enable v2ray; systemctl start v2ray

// 命令
systemctl enable v2ray
systemctl start v2ray
```
### 1.3 设置vmess http配置
```bash
# 文件位置/usr/local/etc/v2ray/config.json
{
    "log": {
        "loglevel": "warning"
    },
    "routing": {
        "domainStrategy": "AsIs",
        "rules": [
            {
                "type": "field",
                "ip": [
                    "geoip:private"
                ],
                "outboundTag": "block"
            }
        ]
    },
    "inbounds": [
        {
            "listen": "0.0.0.0",
            "port": 25566, #自己配置
            "protocol": "vmess",
            "settings": {
                "clients": [
                    {
                        "id": ""  #自己生成
                    }
                ]
            },
            "streamSettings": {
                "network": "tcp",
                "tcpSettings": {
                    "header": {
                        "type": "http",
                        "response": {
                            "version": "1.1",
                            "status": "200",
                            "reason": "OK",
                            "headers": {
                                "Content-Type": [
                                    "application/octet-stream",
                                    "video/mpeg",
                                    "application/x-msdownload",
                                    "text/html",
                                    "application/x-shockwave-flash"
                                ],
                                "Transfer-Encoding": [
                                    "chunked"
                                ],
                                "Connection": [
                                    "keep-alive"
                                ],
                                "Pragma": "no-cache"
                            }
                        }
                    }
                },
                "security": "none"
            }
        }
    ],
    "outbounds": [
        {
            "protocol": "freedom",
            "tag": "direct"
        },
        {
            "protocol": "blackhole",
            "tag": "block"
        }
    ]
}
```

## 2 UnixBench跑分
```bash
wget https://github.com/kdlucas/byte-unixbench/archive/v5.1.3.tar.gz
tar -zxvf v5.1.3.tar.gz
cd byte-unixbench-5.1.3/UnixBench
make./Run
```
### 测试项简单说明

**Dhrystone 2 using register variables**

此项用于测试 string
handling，因为没有浮点操作，所以受软件和硬件设计、编译和链接、代码优化、对内存的缓存、等待状态、整数数据类型的影响。

**Double-Precision Whetstone**

这一项测试浮点数操作的速度和效率。这一测试包括几个模块，每个模块都包括一组用于科学计算的操作。覆盖面很广的一系列
c 函数：sin，cos，sqrt，exp，log
被用于整数和浮点数的数学运算、数组访问、条件分支和程序调用。此测试同时测试了整数和浮点数算术运算。

**Execl Throughput**

测试每秒钟可以执行的execl系统调用的次数。
execl系统调用是exec函数族的一员。它和其他一些与之相似的命令一样是execve()函数的前端。

**File copy**

测试从一个文件向另外一个文件传输数据的速率。每次测试使用不同大小的缓冲区。这一针对文件
read、write、copy 操作的测试统计规定时间（默认是 10s）内的文件
read、write、copy 操作次数。

**Pipe Throughput**

管道是进程间交流的最简单方式，这里的 Pipe throughtput
指的是一秒钟内一个进程可以向一个管道写 512
字节数据然后再读回的次数。需要注意的是，pipe throughtput
在实际编程中没有对应的真实存在。

**Pipe-based Context Switching**

这个测试两个进程（每秒钟）通过一个管道交换一个不断增长的整数的次数。这一点很向现实编程中的一些应用，这个测试程序首先创建一个子进程，再和这个子进程进行双向的管道传输。

**Process Creation**

测试每秒钟一个进程可以创建子进程然后收回子进程的次数（子进程一定立即退出）。一般说来，这个测试被用于对操作系统进程创建这一系统调用的不同实现的比较。

**Shell Scripts**

测试一秒钟内一个进程可以并发地开始一个 shell 脚本的 n 个拷贝的次数，n
一般取值 1，2，4，8。这个脚本对一个数据文件进行一系列的变形操作。

**System Call Overhead**

测试进入和离开操作系统内核的代价，即一次系统调用的代价。它利用一个反复地调用
getpid 函数的小程序达到此目的。

**Graphical Tests**

提供2D和3D图形性能测试，但是目前对3D性能测试还非常有限，并且测试的结果只是大致的。测试的结果不仅取决于硬件，还取决于您的系统是否安装了适当的驱动程序。

## 3 Bash小脚本
### 3.1 tar.gz压缩包转zip
```bash
#!/bin/bash# 进入目标文件夹cd "$1" || exit 1
# 循环处理所有tar.gz文件
for file in *.tar.gz; 
do    # 提取文件名（不包含扩展名）   
		filename=$(basename "$file" .tar.gz)    # 解压缩tar.gz文件到临时目录    
		mkdir "$filename"    
		tar -xzf "$file" -C "$filename"    
		cd "$filename"    # 压缩临时目录为zip文件    
		zip -r "$filename.zip" ./*    
		mv "$filename.zip" ..
    cd ..
    rm -rf "$filename"    echo "已转换: $file -> $filename_no_ext.zip"doneecho "转换完成"
```

## 4 Linux网络，端口信息查看
### 4.1 网络信息
**nethogs(推荐)**
```bash
#//////////////////////////apt install nethogs
nethogs#//////////////////////////apt install iftop
iftop#//////////////////////////#命令：每隔一秒高亮显示网络链接数的变化情况
watch -n 1 -d netstat -ant#//////////////////////////watch -n 1 ss -4twatch是一个非常实用的命令，基本所有的Linux发行版都带有这个小工具，如同名字一样，watch可以帮你监测一个命令的运行结果，省得你一遍遍的手动运行。在Linux下，watch是周期性的执行下个程序，并全屏显示执行结果。你可以拿他来监测你想要的一切命令的结果变化，比如 tail 一个 log 文件，ls 监测某个文件的大小变化，看你的想象力了！1．命令格式：watch[参数][命令]2．命令功能：可以将命令的输出结果输出到标准输出设备，多用于周期性执行命令/定时执行命令3．命令参数：-n或--interval  watch缺省每2秒运行一下程序，可以用-n或-interval来指定间隔的时间。-d或--differences  用-d或--differences 选项watch 会高亮显示变化的区域。 而-d=cumulative选项会把变动过的地方(不管最近的那次有没有变动)都高亮显示出来。-t 或-no-title  会关闭watch命令在顶部的时间间隔,命令，当前时间的输出。  -h, --help 查看帮助文档4．使用实例：实例1：命令：每隔一秒高亮显示网络链接数的变化情况watch -n 1 -d netstat -ant
说明：其它操作：
切换终端： Ctrl+x
退出watch：Ctrl+g
实例2：每隔一秒高亮显示http链接数的变化情况命令：watch -n 1 -d 'pstree|grep http'说明：每隔一秒高亮显示http链接数的变化情况。 后面接的命令若带有管道符，需要加''将命令区域归整。
实例3：实时查看模拟攻击客户机建立起来的连接数命令：watch 'netstat -an | grep:21 | \ grep<模拟攻击客户机的IP>| wc -l'说明：
实例4：监测当前目录中 scf' 的文件的变化命令：watch -d 'ls -l|grep scf'实例5：10秒一次输出系统的平均负载命令：watch -n 10 'cat /proc/loadavg'#//////////////////////////
```

### 4.2 端口开放或正在使用信息
```bash
#//////////////////////////netstat -tln#如果您想查看端口 80 的状态，您可以使用以下命令：
netstat -tln | grep 80
#//////////////////////////
```
## 5 Linux生成指定大小的文件

```bash
#一、生成文件大小和实际占空间大小一样的文件

dd if=/dev/zero of=50M.file bs=1M count=50

dd if=/dev/zero of=20G.file bs=1G count=20

bs=1M表示每一次读写1M数据，count=50表示读写
50次，这样就指定了生成文件的大小为50M。bs参数还可以进一步细分为ibs和obs两种，为读操作与写操作分别指定不同的Buffer大小。

#二、生成文件大小固定，但实际不占空间命令

dd if=/dev/zero of=1G.img bs=1M seek=1000 count=0

这里用了一个新的命令seek，表示略过1000个Block不写（这里Block按照bs的定义是1M），count=0表示写入0个Block。用ls(查看文件大小)命令看新生成的文件，大小可以看出是1000M。但是再用du（查看文件占用空间）一看，实际占用硬盘大小只有0M。

#三、命令详解

dd命令用法：

dd [选项]

if =输入文件（或设备名称）。

of =输出文件（或设备名称）。

ibs = bytes 一次读取bytes字节，即读入缓冲区的字节数。

skip = blocks 跳过读入缓冲区开头的ibs*blocks块。

obs = bytes 一次写入bytes字节，即写入缓冲区的字节数。

bs = bytes 同时设置读/写缓冲区的字节数（等于设置ibs和obs）。

cbs = byte 一次转换bytes字节。

count=blocks 只拷贝输入的blocks块。

conv = ASCII 把EBCDIC码转换为ASCIl码。

conv = ebcdic 把ASCIl码转换为EBCDIC码。

conv = ibm 把ASCIl码转换为alternate EBCDIC码。

conv = block 把变动位转换成固定字符。

conv = ublock 把固定位转换成变动位。

conv = ucase 把字母由小写转换为大写。

conv = lcase 把字母由大写转换为小写。

conv = notrunc 不截短输出文件。

conv = swab 交换每一对输入字节。

conv = noerror 出错时不停止处理。

conv = sync 把每个输入记录的大小都调到ibs的大小（用NUL填充）。

iconv命令用法：

iconv [选项…] [文件…]

输入/输出格式规范：

-f, –from-code=原始文本编码

-t, –to-code=输出文本编码

信息：

-l, –list 列举所有已知的字符集

输出控制：

-c 从输出中忽略无效的字符

-o, –output=FILE 输出文件

-s, –silent 关闭警告

–verbose 打印进度信息

-?, –help 给出该系统求助列表

–usage 给出简要的用法信息

-V, –version 打印程序版本号
```

## 6 互联网网页文件互传（基于Blaze）
```bash

Github地址：https://github.com/blenderskool/blaze

拉取镜像docker pull akashhamirwasia/blaze:latest
启动容器(12345为服务器暴露端口，访问网页地址为 IP:12345 )docker run -p 12345:80 -p 3030:3030 -e PORT=80 akashhamirwasia/blaze:latest
关闭容器docker stop CONTAINER_ID[使用 docker container ls -a 查看CONTAINER_ID]
```

## 7 Linux设置开机自启脚本
### 7.1 Ubuntu

#### 7.1.1 写脚本内容test.sh

```
#!/bin/bash
### BEGIN INIT INFO
# Provides: test
# Required-Start: $remote_fs $syslog
# Required-Stop: $remote_fs $syslog
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: start test
# Description: start test
### END INIT INFO

#此处编写脚本内容
cd /home/Desktop/
./test.sh
exit 0
```

#### 7.1.2 移动脚本文件

```bash
mv test.sh /etc/init.d/
chmod +750 test.sh
sudo update-rc.d test.sh defaults
#关闭自启命令# update-rc.d test.sh defaults-disabled
```

#### 7.1.3 源码编译的nginx设置开机自启

```bash
# 1.编辑/etc/systemd/system/nginx.service 文件, 写入如下内容#---开始---[Unit]Description=nginx serviceAfter=network.target
[Service]
Type=forking
ExecStart=/opt/nginx-1.24.0/sbin/nginx     #执行文件位置, 需要绝对路径ExecReload=/opt/nginx-1.24.0/sbin/nginx -s reload     #执行文件位置ExecStop=/opt/nginx-1.24.0/sbin/nginx -s quit   #执行文件位置PrivateTmp=true
[Install]
WantedBy=multi-user.target
#---终止---# 2.添加到开机自启systemctl enable nginx
# 2.1 概率报错error: nginx Default-Start contains no runlevels, aborting.# 2.2 解决办法在/etc/init.d/nginx 文件头部添加以下内容#---开始---### BEGIN INIT INFO# Provides:          nginx# Required-Start:# Required-Stop:# Default-Start:     2 3 4 5# Default-Stop:      0 1 6# Short-Description: Start nginx daemon at boot time# Description:       Start nginx daemon at boot time### END INIT INFO#---终止---
```

### 7.2 Centos

#### 7.2.1 写脚本内容test.sh

```bash
#!/bin/sh#chkconfig: 2345 80 90#description:auto_run#此处编写脚本内容cd /home/Desktop/
./test.sh
exit 0
```

#### 7.2.2 移动脚本文件

```
mv test.sh /etc/init.d/

chmod +750 test.sh

systemctl enable autostart.sh

#关闭自启
#systemctl disable autostart.sh
```

## 8 Linux SVN教程

### 8.1 安装

```
apt-get install subversion

yum install subversion

```

### 8.2 建立文件夹

```
#建立库位置
mkdir /home/csxj/svn

#建立版本库
svnadmin create /home/csxj/svn/repos

```

### 8.3 修改鉴权文件

```
#打开版本库文件夹
cd /home/csxj/svn/repos/conf
#authz : 权限控制文件， passwd : 账号密码文件， svnserve.conf : 服务器配置文件

vim passwd
///////////////////添加内容(用户名 = 密码)
[users]
admin = admin
user1 = user1
user2 = user2
///////////////////

vim authz
#方式1
///////////////////添加内容[/]表示仓库下所有文件，*= r 表示任何用户都有读取权限
[/]
admin = rw
user1 = rw
* = r
///////////////////
#方式2 分组形式
///////////////////
group1 = admin
group2 = user1,user2

[/]
@group1 = rw
@group2 = r
* = r
///////////////////

vim svnserve.conf
///////////////////取消注释并修改
anon-access = read
auth-access = write
password-db = /home/csxj/svn/repos/conf/passwd
authz-db = /home/csxj/svn/repos/conf/authz
realm = /home/csxj/svn/
///////////////////

```

### 8.4 启动/终止命令

```
#启动命令(默认端口3690)
svnserve -d -r /home/csxj/svn/repos --listen-port 3691

#终止命令
killall svnserve

#查看是否启动
lsof -i:3691

#查看svn进程
ps -ef | grep svn
```

### 8.5 本地添加文件到本地的svn服务器

```
#导入test目录下的所有文件到svn://127.0.0.1:3691
svn import /home/csxj/test/ svn://127.0.0.1:3691 -m "upload files"

#myproj 是一个目录
svn import -m "New import" myproj  http://svn.red-bean.com/repos/trunk/misc/myproj

#导入单个文件需要指定svn路径下的文件名
svn import -m "Adding just a file" file_name http://path/to/svn/repo/file_name

#登录svn本地库更新文件到最新
svn update
```

### 8.6 其他

```
svn list svn://127.0.0.1:3691
# 导出到本地
svn co svn://localhost/测试工具 /home/testtools --username wzhnsc
svn co http://localhost/test/testapp --username wzhnsc
svn checkout svn://localhost/测试工具 /home/testtools --username wzhnsc
svn checkouthttp://localhost/test/testapp --username wzhnsc

```

```

# [SVN命令使用详解](https://www.cnblogs.com/hk315523748/p/6178273.html)

1、检出
svn co http://路径(目录或文件的全路径)　[本地目录全路径] --username 用户名 --password 密码
svn co svn://路径(目录或文件的全路径)　[本地目录全路径] --username 用户名 --password 密码
svn checkout http://路径(目录或文件的全路径)　[本地目录全路径] --username　用户名
svn checkout svn://路径(目录或文件的全路径)　[本地目录全路径] --username　用户名
注：如果不带--password 参数传输密码的话，会提示输入密码，建议不要用明文的--password 选项。
　　其中 username 与 password前是两个短线，不是一个。
　　不指定本地目录全路径，则检出到当前目录下。
例子：
svn co svn://localhost/测试工具 /home/testtools --username wzhnsc
svn co http://localhost/test/testapp --username wzhnsc
svn checkout svn://localhost/测试工具 /home/testtools --username wzhnsc
svn checkouthttp://localhost/test/testapp --username wzhnsc

2、导出(导出一个干净的不带.svn文件夹的目录树)
svn export [-r 版本号] http://路径(目录或文件的全路径) [本地目录全路径]　--username　用户名
svn export [-r 版本号] svn://路径(目录或文件的全路径) [本地目录全路径]　--username　用户名
svn export 本地检出的(即带有.svn文件夹的)目录全路径 要导出的本地目录全路径
注：第一种从版本库导出干净工作目录树的形式是指定URL，
　　　如果指定了修订版本号，会导出相应的版本，
　　　如果没有指定修订版本，则会导出最新的，导出到指定位置。
　　　如果省略 本地目录全路径，URL的最后一部分会作为本地目录的名字。
　　第二种形式是指定 本地检出的目录全路径 到 要导出的本地目录全路径，所有的本地修改将会保留，
　　　但是不在版本控制下(即没提交的新文件，因为.svn文件夹里没有与之相关的信息记录)的文件不会拷贝。
例子：
svn export svn://localhost/测试工具 /home/testtools --username wzhnsc
svn export svn://localhost/test/testapp --username wzhnsc
svn export /home/testapp /home/testtools

3、添加新文件
svn　add　文件名
注：告诉SVN服务器要添加文件了，还要用svn commint -m真实的上传上去！
例子：
svn add test.php ＜－ 添加test.php
svn commit -m “添加我的测试用test.php“ test.php
svn add *.php ＜－ 添加当前目录下所有的php文件
svn commit -m “添加我的测试用全部php文件“ *.php

4、提交
svn　commit　-m　“提交备注信息文本“　[-N]　[--no-unlock]　文件名
svn　ci　-m　“提交备注信息文本“　[-N]　[--no-unlock]　文件名
必须带上-m参数，参数可以为空，但是必须写上-m
例子：
svn commit -m “提交当前目录下的全部在版本控制下的文件“ * ＜－ 注意这个*表示全部文件
svn commit -m “提交我的测试用test.php“ test.php
svn commit -m “提交我的测试用test.php“ -N --no-unlock test.php ＜－ 保持锁就用–no-unlock开关
svn ci -m “提交当前目录下的全部在版本控制下的文件“ * ＜－ 注意这个*表示全部文件
svn ci -m “提交我的测试用test.php“ test.php
svn ci -m “提交我的测试用test.php“ -N --no-unlock test.php ＜－ 保持锁就用–no-unlock开关

5、更新文件
svn　update
svn　update　-r　修正版本　文件名
svn　update　文件名
例子：
svn update ＜－ 后面没有目录，默认将当前目录以及子目录下的所有文件都更新到最新版本
svn update -r 200 test.cpp ＜－ 将版本库中的文件 test.cpp 还原到修正版本（revision）200
svn update test.php ＜－ 更新与版本库同步。
　　　　　　　　　　　 提交的时候提示过期冲突，需要先 update 修改文件，
　　　　　　　　　　　 然后清除svn resolved，最后再提交commit。

6、删除文件
svn　delete　svn://路径(目录或文件的全路径) -m “删除备注信息文本”
推荐如下操作：
svn　delete　文件名
svn　ci　-m　“删除备注信息文本”
例子：
svn delete svn://localhost/testapp/test.php -m “删除测试文件test.php”
推荐如下操作：
svn delete test.php
svn ci -m “删除测试文件test.php”

７、加锁/解锁
svn　lock　-m　“加锁备注信息文本“　[--force]　文件名
svn　unlock　文件名
例子：
svn lock -m “锁信测试用test.php文件“ test.php
svn unlock test.php

8、比较差异
svn　diff　文件名
svn　diff　-r　修正版本号m:修正版本号n　文件名
例子：
svn diff test.php＜－ 将修改的文件与基础版本比较
svn diff -r 200:201 test.php＜－ 对 修正版本号200 和 修正版本号201 比较差异

9、查看文件或者目录状态
svn st 目录路径/名
svn status 目录路径/名＜－ 目录下的文件和子目录的状态，正常状态不显示
　　　　　　　　　　　　　【?：不在svn的控制中； M：内容被修改；C：发生冲突；
　　　　　　　　　　　　　　A：预定加入到版本库；K：被锁定】
svn -v 目录路径/名
svn status -v 目录路径/名＜－ 显示文件和子目录状态
　　　　　　　　　　　　　　【第一列保持相同，第二列显示工作版本号，
　　　　　　　　　　　　　　　第三和第四列显示最后一次修改的版本号和修改人】
注：svn status、svn diff和 svn revert这三条命令在没有网络的情况下也可以执行的，
　　原因是svn在本地的.svn中保留了本地版本的原始拷贝。

10、查看日志
svn　log　文件名
例子：
svn log test.php＜－ 显示这个文件的所有修改记录，及其版本号的变化

11、查看文件详细信息
svn　info　文件名
例子：
svn info test.php

12、SVN 帮助
svn　help ＜－ 全部功能选项
svn　help　ci ＜－ 具体功能的说明

13、查看版本库下的文件和目录列表
svn　list　svn://路径(目录或文件的全路径)
svn　ls　svn://路径(目录或文件的全路径)
例子：
svn list svn://localhost/test
svn ls svn://localhost/test ＜－ 显示svn://localhost/test目录下的所有属于版本库的文件和目录

14、创建纳入版本控制下的新目录
svn　mkdir　目录名
svn　mkdir　-m　"新增目录备注文本"　http://目录全路径
例子：
svn mkdir newdir
svn mkdir -m "Making a new dir." svn://localhost/test/newdir
注：添加完子目录后，一定要回到根目录更新一下，不然在该目录下提交文件会提示“提交失败”
svn update
注：如果手工在checkout出来的目录里创建了一个新文件夹newsubdir，
　　再用svn mkdir newsubdir命令后，SVN会提示：
　　svn: 尝试用 “svn add”或 “svn add --non-recursive”代替？
　　svn: 无法创建目录“hello”: 文件已经存在
　　此时，用如下命令解决：
　　svn add --non-recursive newsubdir
　　在进入这个newsubdir文件夹，用ls -a查看它下面的全部目录与文件，会发现多了：.svn目录
　　再用 svn mkdir -m "添hello功能模块文件" svn://localhost/test/newdir/newsubdir 命令，
　　SVN提示：
　　svn: File already exists: filesystem '/data/svnroot/test/db', transaction '4541-1',
　　path '/newdir/newsubdir '

15、恢复本地修改
svn　revert　[--recursive]　文件名
注意: 本子命令不会存取网络，并且会解除冲突的状况。但是它不会恢复被删除的目录。
例子：
svn revert foo.c ＜－ 丢弃对一个文件的修改
svn revert --recursive . ＜－恢复一整个目录的文件，. 为当前目录

16、把工作拷贝更新到别的URL
svn　switch　http://目录全路径　本地目录全路径
例子：
svn switch http://localhost/test/456 . ＜－ (原为123的分支)当前所在目录分支到localhost/test/456

17、解决冲突
svn　resolved　[本地目录全路径]
例子：
$ svn update
C foo.c
Updated to revision 31.
如果你在更新时得到冲突，你的工作拷贝会产生三个新的文件：
$ ls
foo.c
foo.c.mine
foo.c.r30
foo.c.r31
当你解决了foo.c的冲突，并且准备提交，运行svn resolved让你的工作拷贝知道你已经完成了所有事情。
你可以仅仅删除冲突的文件并且提交，但是svn resolved除了删除冲突文件，还修正了一些记录在工作拷贝管理区域的记录数据，所以我们推荐你使用这个命令。

18、不checkout而查看输出特定文件或URL的内容
svn　cat　http://文件全路径
例子：
svn cat http://localhost/test/readme.txt
19、新建一个分支copy
svn copy branchA branchB -m "make B branch" // 从branchA拷贝出一个新分支branchB
20、合并内容到分支merge
svn merge branchA branchB // 把对branchA的修改合并到分支branchB

原文详情：[http://www.roncoo.com/article/detail/124725](http://www.roncoo.com/article/detail/124725)
```

### 8.7 部署apache2
http方式访问svn库

```
# 安装apache2
apt-get install apache2
apt-get install libapache2-mod-svn

# 修改svn所在文件夹所有者
chown -R www-data:www-data /root/svn/

# 修改/etc/apache/mods-enabled/dav_svn.load文件
# 添加mod_dav_svn.so动态库
# LoadModule dav_svn_module /usr/lib/apache2/modules/mod_dav_svn.so

```

/etc/apache2/ports.conf

```
root@u22:~/svn# more /etc/apache2/ports.conf
# If you just change the port or add more ports here, you will likely also
# have to change the VirtualHost statement in
# /etc/apache2/sites-enabled/000-default.conf

Listen 80

<IfModule ssl_module>
    Listen 443
</IfModule>

<IfModule mod_gnutls.c>
    Listen 443
</IfModule>

# vim: syntax=apache ts=4 sw=4 sts=4 sr noet

```

/etc/apache2/mods-enabled/dav_svn.conf

```

<Location /svn>

  DAV svn
  SVNPath /root/svn/repos
  AuthType Basic
  AuthName "Subversion Repository"
  AuthUserFile /etc/apache2/dav_svn.passwd
  AuthzSVNAccessFile /root/svn/repos/conf/authz
  Require valid-user
  Satisfy ALL
  SVNAutoversioning on
  ModMimeUsePathInfo on
</Location>

```

/etc/apache2/mods-enabled/dav_svn.load

```
# Depends: dav
<IfModule !mod_dav_svn.c>
    <IfModule !mod_dav.c>
        Include mods-enabled/dav.load
    </IfModule>
    LoadModule dav_svn_module /usr/lib/apache2/modules/mod_dav_svn.so
    LoadModule authz_svn_module /usr/lib/apache2/modules/mod_authz_svn.so
    LoadModule dav_module /usr/lib/apache2/modules/mod_dav.so
    LoadModule dav_fs_module /usr/lib/apache2/modules/mod_dav_fs.so
</IfModule>

```

添加密文的passwd

```

htpasswd -c /etc/apache2/dav_svn.passwd saber
htpasswd -m /etc/apache2/dav_svn.passwd user1

#输入两次密码
sudo chmod 644 /etc/apache2/dav_svn.passwd

```

## 9 Linux给普通用户赋予sudo权限

```bash
Linux中普通用户用sudo执行命令时报”xxx is not in the sudoers file.This
incident will be
reported”错误，解决方法就是在/etc/sudoers文件里给该用户添加权限。如下：
1.切换到root用户下
方法为直接在命令行输入：`su`，然后输入密码（即你的登录密码，且密码默认不可见）。
2./etc/sudoers文件默认是只读的，对root来说也是，因此需先添加sudoers文件的写权限,命令是:即执行操作：`chmod u+w /etc/sudoers`
3.编辑sudoers文件 即执行：`vi /etc/sudoers` 找到这行 root
ALL=(ALL) ALL,在他下面添加xxx ALL=(ALL) ALL (这里的xxx是你的用户名)
ps:这里说下你可以sudoers添加下面四行中任意一条

youuser ALL=(ALL) ALL
%youuser ALL=(ALL) ALL
youuser ALL=(ALL) NOPASSWD: ALL
%youuser ALL=(ALL) NOPASSWD: ALL

第一行:允许用户youuser执行sudo命令(需要输入密码).
第二行:允许用户组youuser里面的用户执行sudo命令(需要输入密码).
第三行:允许用户youuser执行sudo命令,并且在执行的时候不输入密码.
第四行:允许用户组youuser里面的用户执行sudo命令,并且在执行的时候不输入密码.
4.撤销sudoers文件写权限,命令: `chmod u-w /etc/sudoers`

```

## 10 VMware虚拟机Centos扩容

https://juejin.cn/post/6916366875685289991

先进入虚拟机设置里增大磁盘空间

1.VMware中关闭CentOS 2.打开VMware CentOS设置
3.到硬盘(SCSI)选项中-磁盘实用工具-扩展 4.扩展完成，重新开启CentOS

### 10.1 查看分区

一般情况下是/dev/sda1 和 /dev/sda2

```
fdisk -l
```

### 10.2 增加一个分区

```
fdisk /dev/sda

命令操作 m > n > p > 3(默认) > 起始扇区(默认) > Last扇区(默认) > w

```

```bash
fdisk -l#会看到三个扇区：sda1,sda2,sda3
```

### 10.3 重启配置磁盘

```bash
#创建物理卷pvcreate /dev/sda3
#使用 vgscan 查询物理卷,可以查到本机物理卷名称为 centosvgscan#使用新增物理卷扩展 centos 命令：vgextend centos /dev/sda3vgextend centos /dev/sda3
#命令lvextend -L +24G /dev/mapper/centos-root :使用 lvextend 命令为逻辑卷 /dev/mapper/centos-root 增加24G空间lvextend -L +24G /dev/mapper/centos-root
#lvextend -L +24G /dev/mapper/centos-home  #给用户增加空间#xfs_growfs 加上要扩展的分区名 或者 resize2fs – f 加 上要扩展的分区名xfs_growfs /dev/mapper/centos-root
# df-h 磁盘增加成功
```

## 11 将linux虚拟机做成docker镜像

https://blog.csdn.net/wangzh92429/article/details/114357383 ##
### 11.1 将linux虚拟机做成docker镜像

```bash
tar --numeric-owner --exclude=/proc --exclude=/sys -zcvpf centos7-12.tar /
```

–numeric-owner 执行所属 –exclude 排除目录或文件 -zcvpf 打包压缩
p保持文件内绝对路径

### 11.2 导入镜像

```bash
docker import centos7-12.tar <image-name>
```

### 11.3 运行镜像

```bash
docker run -ti <image-name> /bin/bash
```

## 12 Docker常用操作(使用MDO)
### 12.1 Install

```bash
docker pull mdolab/public:u20-gcc-ompi-latest
docker image ls
docker run -it --name <NAME给容器起名字> --mount "type=bind,src=<HOST_DIR:当前对绝对目录>,target=<MOUNT_DIR:/home/mdolabuser/mount/>" <IMAGE-id使用image的ID> /bin/bash
exitdocker start <NAME>docker exec -it <NAME> /bin/bash
```

### 12.2 docker操作

```markdown
在windows系统上docker占用大量空间
1、停止docker
2、备份当前docker数据
打开Windows powershell
wsl --export docker-desktop-dat "E:\docker\data.tar"
dir E:\docker\
3、删除原来的数据
wsl --unregister docker-desktop-data
wsl --list -v
(会输出version信息，导入时要用到)
4、将刚才备份的数据导入
wsl --import docker-desktop-data "E:\docker\image\" "E:\docker\data.tar" --version 2
wsl --list -v
5、启动docker
```

以管理员方式进入docker

```bash
sudo docker exec -ti -u root MACHaero /bin/bash
```

以用户身份进入docker

```bash
sudo docker exec -it MACHaero /bin/bash
```

```python
# built-insimport unittest
import os
import copy
# MACH testing classfrom adflow import ADFLOW
# import the testing utilitiesimport reg_test_utils as utils
from reg_default_options import adflowDefOpts
from reg_aeroproblems import ap_naca0012_time_acc
import reg_test_classes
baseDir = os.path.dirname(os.path.abspath(__file__))
class TestSolve(reg_test_classes.RegTest):
    """    Tests that ADflow can converge the wing from the mdo tutorial using the euler    equation to the required accuracy as meassure by the norm of the residuals,    and states, and the accuracy of the functions    based on the old regression test 15    """    N_PROCS = 2    ref_file = "solve_rans_time_acc_naca0012.json"    def setUp(self):
        super().setUp()
        gridFile = os.path.join(baseDir, "../../input_files/naca0012_rans-L2.cgns")
        f = 10.0  # [Hz] Forcing frequency of the flow        period = 1.0 / f  # [sec]        nStepPerPeriod = 8        nPeriods = 1        nfineSteps = nStepPerPeriod * nPeriods
        dt = period / nStepPerPeriod  # [s] The actual timestep        options = copy.copy(adflowDefOpts)
        options.update(
            {
                "gridfile": gridFile,
                "outputdirectory": os.path.join(baseDir, "../output_files"),
                "writevolumesolution": False,
                "vis4": 0.025,
                "vis2": 0.5,
                "restrictionrelaxation": 0.5,
                "smoother": "DADI",
                "equationtype": "RANS",
                "equationmode": "unsteady",
                "timeIntegrationscheme": "BDF",
                "ntimestepsfine": nfineSteps,
                "deltat": dt,
                "nsubiterturb": 10,
                "nsubiter": 5,
                "useale": False,
                "usegridmotion": True,
                "cfl": 2.5,
                "cflcoarse": 1.2,
                "ncycles": 2000,
                "mgcycle": "3w",
                "mgstartlevel": 1,
                "monitorvariables": ["cpu", "resrho", "cl", "cd", "cmz"],
                "usenksolver": False,
                "useanksolver": False,
                "l2convergence": 1e-6,
                "l2convergencecoarse": 1e-4,
                "qmode": True,
                "alphafollowing": False,
                "blockSplitting": True,
                "useblockettes": False,
            }
        )
        # Setup aeroproblem        self.ap = copy.copy(ap_naca0012_time_acc)
        # Create the solver        self.CFDSolver = ADFLOW(options=options, debug=False)
        self.CFDSolver.addSlices("z", [0.5])
    def test_solve(self):
        # do the solve        self.CFDSolver(self.ap)
        # check if the solution failed        self.assert_solution_failure()
        # check its accuracy        utils.assert_functions_allclose(self.handler, self.CFDSolver, self.ap, tol=1e-8)
if __name__ == "__main__":
    unittest.main()

```

### 12.3 u20-gcc-ompi-stable镜像解决办法：进入容器后重新编译adflow组件。

```markdown
1、修改/home/mdolabuser/repos/adflow/config/config.mk文件，把make j 4改成make j 2
2、执行 make clean
3、执行 make
4、执行 pip install .
5、OK
```

## 13 Python pip使用清华源
### 13.1 本次指定源

```bash
#升级pip3, -i后面是镜像站地址,目前使用清华镜像pip3 install --upgrade pip -i https://pypi.tuna.tsinghua.edu.cn/simple
pip3 install ansys-fluent-core -i https://pypi.tuna.tsinghua.edu.cn/simple
pip3 install ansys-fluent-parametric -i https://pypi.tuna.tsinghua.edu.cn/simple
pip3 install ansys-fluent-visualization -i https://pypi.tuna.tsinghua.edu.cn/simple
```

### 13.2 更新系统pip源

```bash
# LinuxLinux/Mac os 环境中，配置文件位置在 ~/.pip/pip.conf（如果不存在创建该目录和文件）：
mkdir ~/.pip
打开配置文件 ~/.pip/pip.conf，修改如下：[global]index-url = https://pypi.tuna.tsinghua.edu.cn/simple
[install]trusted-host = https://pypi.tuna.tsinghua.edu.cn
查看 镜像地址：
$ pip3 config list
global.index-url='https://pypi.tuna.tsinghua.edu.cn/simple'install.trusted-host='https://pypi.tuna.tsinghua.edu.cn'可以看到已经成功修改了镜像。# WindowsWindows下，你需要在当前对用户目录下（C:\Users\xx\pip，xx 表示当前使用对用户，比如张三）创建一个 pip.ini在pip.ini文件中输入以下内容：
[global]index-url = https://pypi.tuna.tsinghua.edu.cn/simple
[install]trusted-host = pypi.tuna.tsinghua.edu.cn
# 其他国内镜像源- 中国科学技术大学 : https://pypi.mirrors.ustc.edu.cn/simple
- 豆瓣：http://pypi.douban.com/simple/
- 阿里云：http://mirrors.aliyun.com/pypi/simple/
```

## 14 Ubuntu更换清华源(apt-get)

### 14.1 备份

```
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak
```

### 14.2 阿里源

```
sudo vim /etc/apt/sources.list

#将source.list文件内容替换成下面的(阿里源)
deb http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
```

### 14.3 清华源

https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/

```
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-backports main restricted universe multiverse

# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-security main restricted universe multiverse

deb http://security.ubuntu.com/ubuntu/ focal-security main restricted universe multiverse
# deb-src http://security.ubuntu.com/ubuntu/ focal-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-proposed main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ focal-proposed main restricted universe multiverse

```

### 14.4 更新

```
sudo apt-get update
```

## 15 Linux修改ssh登录端口
```bash
#确保新端口在防火墙中放行（1）关闭防火墙：/etc/init.d/iptables stop
或者service iptables stop
或者在防火墙过滤规则中上增加一条，允许对新增的端口的访问：vi /etc/sysconfig/iptables
新增一条策略，放通新端口。例如新端口为12022：-A INPUT -m state --state NEW -m tcp -p tcp --dport 12022 -j ACCEPT
（2）编辑ssh配置文件vim /etc/ssh/sshd_config
修改#Port 22，去掉#号，端口设置为新端口
（3）重启ssh服务systemctl restart sshd
或者/etc/init.d/sshd restart
```

## 16 Linux自动封禁ssh登录失败的ip(防止暴力破解)
```bash
#防止暴力破解（1）编写脚本定期将登录失败的IP添加进入黑名单中touch ssh.sh
chmod +x ssh.sh
vim ssh.sh
（2）ssh.sh内容如下：#!/bin/bash#输入三次错误密码自动封禁ipiplist=$(/bin/lastb |awk '{print $3}'|sort|uniq -c|awk '{if ($1>3) print $2}')#追加到黑名单并清空登录日志for ip in ${iplist}doecho ALL: ${ip} >> /etc/hosts.deny
echo > /var/log/btmp
done（3）设置定时执行#编辑crontabcrontab -e#添加定时脚本命令，每分钟执行一次0 */1 * * * sh /root/ssh.sh
```

## 17 Linux修改网络配置
```bash
#(1)debian系统配置文件位置为：/etc/network/interfaces修改后保存配置后，运行/etc/init.d/networking restart
网络配置就改变了
#(2)redhat系统配置文件位置为：/etc/sysconfig/network-scripts/ifcfg-eth0TYPE=Ethernet
PROXY_METHOD=none
BROWSER_ONLY=no
BOOTPROTO=dhcp
DEFROUTE=yes
IPV4_FAILURE_FATAL=no
IPV6INIT=yes
IPV6_AUTOCONF=yes
IPV6_DEFROUTE=yes
IPV6_FAILURE_FATAL=no
IPV6_ADDR_GEN_MODE=stable-privacy
NAME=eth0
UUID=e5f4078b-ebf0-46bb-9545-1ab724d541bc
DEVICE=eth0
ONBOOT=no
DNS1=8.8.8.8
DNS2=8.8.4.4
修改后保存配置后，运行/etc/init.d/network restart
或者service network restart
网络配置就改变了默认DNS的文件的位置为：/etc/resolv.confcat /etc/resolv.conf
search test.com.cn
nameserver 192.168.1.11
```

## 18 Linux修改DNS地址
```bash
（1）HOST 本地DNS解析
vi /etc/hosts
添加规则 例如:
223.231.234.33 www.baidu.com
（2）网卡配置文件DNS服务地址vi /etc/sysconfig/network-scripts/ifcfg-eth0
添加规则 例如:
DSN1=’114.114.114.114’
（3）系统默认DNS配置vi /etc/resolv.conf
添加规则 例如:
nameserver 114.114.114.114
#系统解析的优先级1>2>3
```

## 19 Linux 禁用 ping,icmp
```bash
#永久修改文件 /etc/sysctl.conf，在文件末尾增加一行：
net.ipv4.icmp_echo_ignore_all = 1
如果已经有 net.ipv4.icmp_echo_ignore_all 这一行了，直接修改 = 号后面的值即可的 0 表示允许，1 表示禁止。
修改完成后执行 sysctl -p 使新配置生效（重要）
```

## 20 Linux iptables基础

```bash
（1）放行所有端口iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT
（2）保存iptables规则#安装iptables-persistent组件apt-get install iptables-persistent
#执行下面的命令自动保存当前的规则，重启自动生效sudo dpkg-reconfigure iptables-persistent
#保险起见，执行下列2条命令，覆盖rules.v4文件iptables-save > iptables.conf#保存规则到文件
cp iptables.conf /etc/iptables/rules.v4#覆盖文件，重启自动生效
#恢复保存的iptables.conf文件iptables-restore < iptables.conf
（3）iptables设置端口仅允许指定ip访问#先丢弃所有包——如果是ssh端口则必须在VNC界面执行，否则ssh连接会直接断开iptables -I INPUT -p TCP --dport 40000 -j DROP
#允许指定ip访问特定端口iptables -I INPUT -s 202.81.229.55 -p TCP --dport 40000 -j ACCEPT
（4）iptables常见命令iptables -L -n --line-number #查看到每个规则chain的序列号。iptables -D INPUT 3 #删除INPUT的第三条已添加规则，这里3代表第几行规则#iptables防火墙service iptables status #查看iptables防火墙状态service iptables start #开启防火墙service iptables stop #停止防火墙#firewall防火墙systemctl status firewalld #查看firewall防火墙服务状态service firewalld start #开启防火墙service firewalld stop #关闭防火墙（5）iptables限制指定端口网速#hashlimit-name必须是唯一的。#HKIX限速iptables -A INPUT -p tcp --dport 10000:65500 -m hashlimit --hashlimit-name conn_limitA --hashlimit-htable-expire 30000 --hashlimit-upto 3500kb/s --hashlimit-mode srcip --hashlimit-burst 3575kb -j ACCEPT
iptables -A INPUT -p tcp --dport 10000:65500 -j DROP
iptables -A OUTPUT -p tcp --sport 10000:65500 -m hashlimit --hashlimit-name conn_limitB --hashlimit-htable-expire 30000 --hashlimit-upto 3500kb/s --hashlimit-mode dstip --hashlimit-burst 3575kb -j ACCEPT
iptables -A OUTPUT -p tcp --sport 10000:65500 -j DROP
#US限速iptables -A INPUT -p tcp --dport 10000:65500 -m hashlimit --hashlimit-name conn_limitA --hashlimit-htable-expire 30000 --hashlimit-upto 15000kb/s --hashlimit-mode srcip --hashlimit-burst 15010kb -j ACCEPT
iptables -A INPUT -p tcp --dport 10000:65500 -j DROP
iptables -A OUTPUT -p tcp --sport 10000:65500 -m hashlimit --hashlimit-name conn_limitB --hashlimit-htable-expire 30000 --hashlimit-upto 15000kb/s --hashlimit-mode dstip --hashlimit-burst 15010kb -j ACCEPT
iptables -A OUTPUT -p tcp --sport 10000:65500 -j DROP
（6）iptables禁icmp\\pingiptables -A INPUT -p icmp --icmp-type echo-request -j DROP
iptables -A OUTPUT -p icmp --icmp-type echo-request -j DROP
```

## 21 RedHat 挂载光盘作为本地源

```bash
（1）挂载光盘到指定目录mount -t iso9660 /dev/cdrom /mnt/cdrom
（2）挂载作为本地源cd /etc/yum.repos.d
#如有repo文件，先备份为.bak文件，然后删除repo文件，否则会冲突#例如：#cp centos.repo centos.repo && rm centos.repo编辑本地源文件local.repovim /etc/yum.repos.d/local.repo
（3）修改为以下内容
[local]
name=cdrom
baseurl=file:///mnt/cdrom
enabled=1
gpgcheck=0
#gpgkey=file:///mnt/cdrom/***
```

### 21.1 RedHat软件包相关操作

```bash
列出所有可更新的软件清单命令：yum check-update
更新所有软件命令：yum update
仅安装指定的软件命令：yum install <package_name>仅更新指定的软件命令：yum update <package_name>列出所有可安裝的软件清单命令：yum list
删除软件包命令：yum remove <package_name>查找软件包命令：yum search keyword
清除缓存命令:yum clean packages: 清除缓存目录下的软件包
yum clean headers: 清除缓存目录下的 headers
yum clean oldheaders: 清除缓存目录下旧的 headers
yum clean, yum clean all (= yum clean packages; yum clean oldheaders) :清除缓存目录下的软件包及旧的 headers
#Centos设置国内源（1）备份/etc/yum.repos.d/CentOS-Base.repomv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup（2）下载对应版本 repo 文件, 放入 /etc/yum.repos.d/ (操作前请做好相应备份)例如：<http://mirrors.163.com/.help/CentOS7-Base-163.repo><https://lug.ustc.edu.cn/wiki/mirrors/help/centos>
```

### 21.2 yum报错python

```
yum 报错的原因是安装了高版本的Python，而yum默认的是低版本的。
将/usr/bin/yum 和 /usr/libexec/urlgrabber-ext-down 两个文件的第一行
#!/usr/bin/python
改成 如下，保存退出就可以了
#!/usr/bin/python2.7
```

### 21.3 Centos安装certbot

```
#先安装 snapd，使用 snap 安装 certbot 可以隔离环境影响
yum install snapd
# 设置为开机启动并立即启动
sudo systemctl enable --now snapd
# 建立软链接
sudo ln -s /var/lib/snapd/snap /snap
# 安装内核
sudo snap install core
# 安装certbot
sudo snap install --classic certbot
# 添加软链接
sudo ln -s /snap/bin/certbot /usr/bin/certbot
```

```bash
（1）挂载光盘到指定目录mount -t iso9660 /dev/cdrom /mnt/cdrom
（2）挂载作为本地源cd /etc/yum.repos.d
#如有repo文件，先备份为.bak文件，然后删除repo文件，否则会冲突#例如：#cp centos.repo centos.repo && rm centos.repo编辑本地源文件local.repovim /etc/yum.repos.d/local.repo
（3）修改为以下内容[local]name=cdrom
baseurl=file:///mnt/cdrom
enabled=1
gpgcheck=0
#gpgkey=file:///mnt/cdrom/***
```

## 22 Ubuntu 设置iso文件作为本地源

```bash
#创建挂载目录sudo mkdir /mnt/cdrom
#进行挂载sudo mount -t iso9660 -o loop /dev/sr0 /mnt/cdrom
#or mount -t auto /dev/sr0 /mnt/cdrom#添加本地目录到软件源sudo apt-cdrom -m -d=/mnt/cdrom add
#检测apt源cat /etc/apt/sources.list
#出现下面这个字段表示已经挂载完成deb cdrom:[Ubuntu 22.04.1 LTS _Jammy Jellyfish_ - Release amd64 (20220809.1)]/ jammy main restricted
#进行本地库依赖更新apt-get update
#升级软件包apt-get upgrade
#常用依赖安装apt-get install build-essential
#对于libc6-i386#把原来的版本删除后，再进行安装dpkg -l | grep libc6-i386
dpkg -r libc6-i386
dpkg -l | grep libgo
dpkg -r libgompl
#执行完成后再进行libc-i386安装apt-get install libc6-i386
#安装完成后再安装build-essentialapt-get install essential
#成功执行后，说明一些必要的依赖都已经安装完成gcc -v
```

### 22.1 Ubuntu/Debian软件包相关操作

```bash
sudo apt-get update: 升级安装包相关的命令,刷新可安装的软件列表(但是不做任何实际的安装动作)sudo apt-get upgrade: 进行安装包的更新(软件版本的升级)sudo apt-get dist-upgrade: 进行系统版本的升级(Ubuntu版本的升级)sudo do-release-upgrade: Ubuntu官方推荐的系统升级方式,若加参数-d还可以升级到开发版本,但会不稳定
sudo apt-get autoclean: 清理旧版本的软件缓存
sudo apt-get clean: 清理所有软件缓存
sudo apt-get autoremove: 删除系统不再使用的孤立软件
apt（Advanced Packaging Tool）是一个在 Debian 和 Ubuntu 中的 Shell 前端软件包管理器。 apt 命令提供了查找、安装、升级、删除某一个、一组甚至全部软件包的命令，而且命令简洁而又好记。 apt 命令执行需要超级管理员权限(root)。apt 常用命令
列出所有可更新的软件清单命令：sudo apt update
升级软件包：sudo apt upgrade
列出可更新的软件包及版本信息：apt list --upgradeable升级软件包，升级前先删除需要更新软件包：sudo apt full-upgrade
安装指定的软件命令：sudo apt install <package_name>安装多个软件包：sudo apt install <package_1> <package_2> <package_3>更新指定的软件命令：sudo apt update <package_name>显示软件包具体信息,例如：版本号，安装大小，依赖关系等等：sudo apt show <package_name>删除软件包命令：sudo apt remove <package_name>清理不再使用的依赖和库文件: sudo apt autoremove
移除软件包及配置文件: sudo apt purge <package_name>查找软件包命令： sudo apt search keyword
列出所有已安装的包：apt list --installed列出所有已安装的包的版本信息：apt list --all-versions#实例查看一些可更新的包：sudo apt update
升级安装包：sudo apt upgrade
#在以上交互式输入字母 Y 即可开始升级，可以将以下两个命令组合起来，一键升级：sudo apt update && sudo apt upgrade -y
```

### 22.2 Debian/Ubuntu系统命令终端提示
sudo: gedit：找不到命令 解决方法

```
原因：gedit文件损坏导致。
解决方法：重新安装 gedit 即可
sudo apt-get install gedit
如果无法安装，可先卸载gedit
sudo apt-get remove gedit

```

#### Ubuntu install libc-dev

```
sudo apt install libc6-dev

Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Some packages could not be installed. This may mean that you have
requested an impossible situation or if you are using the unstable
distribution that some required packages have not yet been created
or been moved out of Incoming.
The following information may help to resolve the situation:

The following packages have unmet dependencies:
libc6-dev : Depends: libc6 (= 2.35-0ubuntu3) but 2.35-0ubuntu3.1 is to be installed
E: Unable to correct problems, you have held broken packages.

sudo apt install libc6=2.35-0ubuntu3

```

#### Ubuntu install
python3-lib2to3

```
The following packages have unmet dependencies: python3-distutils : Depends: python3-lib2to3 (= 3.10.4-0ubuntu1) but 3.10.6-1~22.04 is to be installed

sudo apt --fix-missing purge $(dpkg -l | grep 'python3\\.1[01]' | awk '{print $2}')

```

#### Ubuntu查看crontab运行日志

```
#安装日志服务
apt-get install rsyslog
#修改配置文件
vim /etc/rsyslog.d/50-default.conf
#取消 cron 行的注释 重启 系统日志服务
sudo service rsyslog restart

#crontab定时任务

*    *     *     *     *  Run
min  hour data month week Run

```



