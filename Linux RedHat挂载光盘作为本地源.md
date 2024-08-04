
```bash
#1. 挂载光盘到指定目录
mount -t iso9660 /dev/cdrom /mnt/cdrom

#2. 挂载作为本地源
cd /etc/yum.repos.d
#如有repo文件，先备份为.bak文件，然后删除repo文件，否则会冲突
cp centos.repo centos.repo && rm centos.repo

#编辑本地源文件local.repovim 
/etc/yum.repos.d/local.repo

#3. 修改为以下内容

[local]
name=cdrom
baseurl=file:///mnt/cdrom
enabled=1
gpgcheck=0
#gpgkey=file:///mnt/cdrom/***

```

# 1 RedHat软件包相关操作

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

# 2 yum报错python

```
yum 报错的原因是安装了高版本的Python，而yum默认的是低版本的。
将/usr/bin/yum 和 /usr/libexec/urlgrabber-ext-down 两个文件的第一行
#!/usr/bin/python
改成 如下，保存退出就可以了
#!/usr/bin/python2.7
```

# 3 Centos安装certbot

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