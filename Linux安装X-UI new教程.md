# 1.连接VPS
```
(省略)
```

# 2.修改ssh登录端口

```
apt-get update

#确保新端口在防火墙中放行
（1）关闭防火墙：
/etc/init.d/iptables stop
或者
service iptables stop
或者在防火墙过滤规则中上增加一条，允许对新增的端口的访问：
vi /etc/sysconfig/iptables
新增一条策略，放通新端口。
例如新端口为12022：
-A INPUT -m state --state NEW -m tcp -p tcp --dport 12022 -j ACCEPT
（2）编辑ssh配置文件
vim /etc/ssh/sshd_config
修改#Port 22，去掉#号，端口设置为新端口
（3）重启ssh服务
systemctl restart sshd
或者
/etc/init.d/sshd restart
```

# 3.防止暴力破解

```
#防止暴力破解
（1）编写脚本定期将登录失败的IP添加进入黑名单中
touch ssh.sh
chmod +x ssh.sh
vim ssh.sh
（2）ssh.sh内容如下：
#!/bin/bash
#输入三次错误密码自动封禁ip
iplist=$(/bin/lastb |awk '{print $3}'|sort|uniq -c|awk '{if ($1>3) print $2}')
#追加到黑名单并清空登录日志
for ip in ${iplist}
do
echo ALL: ${ip} >> /etc/hosts.deny
echo > /var/log/btmp
done
（3）设置定时执行
#编辑crontab
crontab -e
#添加定时脚本命令，每分钟执行一次
0 */1 * * * sh /root/ssh.sh
```

# 4.启动TCP加速算法

```
#启动BBR加速算法
wget -N --no-check-certificate "https://raw.githubusercontent.com/chiakge/Linux-NetSpeed/master/tcp.sh" && chmod +x tcp.sh && ./tcp.sh
```

# 5.安装XUI

```
#安装X-UI For English Users,please use the following command to install English supported version:

bash <(curl -Ls https://raw.githubusercontent.com/FranzKafkaYu/x-ui/master/install_en.sh)
```

# 6.流媒体检测

```
bash <(curl -L -s check.unlock.media) -M 4
```
