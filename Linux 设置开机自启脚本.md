
# 1. Ubuntu

## 1.1 写脚本内容test.sh

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

## 1.2 移动脚本文件

```bash
mv test.sh /etc/init.d/
chmod +750 test.sh
sudo update-rc.d test.sh defaults
#关闭自启命令# update-rc.d test.sh defaults-disabled
```

## 1.3 源码编译的nginx设置开机自启

### 1. 编辑/etc/systemd/system/nginx.service 文件, 写入如下内容

```
[Unit]
Description=nginx 
serviceAfter=network.target

[Service]
Type=forking
ExecStart=/opt/nginx-1.24.0/sbin/nginx
#执行文件位置, 需要绝对路径
ExecReload=/opt/nginx-1.24.0/sbin/nginx -s reload     
#执行文件位置
ExecStop=/opt/nginx-1.24.0/sbin/nginx -s quit   
#执行文件位置
PrivateTmp=true
[Install]
WantedBy=multi-user.target
```

### 2. 添加到开机自启 `systemctl enable nginx`

##### 2.1 概率报错
`error: nginx Default-Start contains no runlevels, aborting.`

##### 2.2 解决办法在/etc/init.d/nginx 文件头部添加以下内容
```
### BEGIN INIT INFO
# Provides:          nginx
# Required-Start:# Required-Stop:
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start nginx daemon at boot time
# Description:       Start nginx daemon at boot time
### END INIT INFO#
```


# 2. Centos

## 2.1 写脚本内容test.sh

```bash
#!/bin/sh
#chkconfig: 2345 80 90
#description:auto_run

#此处填写脚本位置(确保有执行权限)
cd /home/Desktop/
./test.sh
exit 0
```

## 2.2 移动脚本文件

```
mv test.sh /etc/init.d/

chmod +750 test.sh

#允许开机自启
systemctl enable autostart.sh

#关闭开机自启
systemctl disable autostart.sh
```