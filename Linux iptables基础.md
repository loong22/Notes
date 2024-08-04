
# 1. 放行所有端口
```
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT
```

# 2. 保存iptables规则
```
#安装iptables-persistent组件
apt-get install iptables-persistent
#执行下面的命令自动保存当前的规则，重启自动生效
sudo dpkg-reconfigure iptables-persistent
#保险起见，执行下列2条命令，覆盖rules.v4文件iptables-save > iptables.conf#保存规则到文件
cp iptables.conf /etc/iptables/rules.v4#覆盖文件，重启自动生效
#恢复保存的iptables.conf文件iptables-restore < iptables.conf
```

# 3. iptables设置端口仅允许指定ip访问
```
#先丢弃所有包——如果是ssh端口则必须在VNC界面执行，否则ssh连接会直接断开
iptables -I INPUT -p TCP --dport 40000 -j DROP
#允许指定ip访问特定端口
iptables -I INPUT -s 202.81.229.55 -p TCP --dport 40000 -j ACCEPT
```

# 4. iptables常见命令
```
iptables -L -n --line-number #查看到每个规则chain的序列号。
iptables -D INPUT 3 #删除INPUT的第三条已添加规则，这里3代表第几行规则#iptables防火墙
service iptables status #查看iptables防火墙状态
service iptables start #开启防火墙
service iptables stop #停止防火墙#firewall防火墙
systemctl status firewalld #查看firewall防火墙服务状态
service firewalld start #开启防火墙
service firewalld stop #关闭防火墙
```

# 5. iptables限制指定端口网速#hashlimit-name必须是唯一的。
```
#限速
iptables -A INPUT -p tcp --dport 10000:65500 -m hashlimit --hashlimit-name conn_limitA --hashlimit-htable-expire 30000 --hashlimit-upto 3500kb/s --hashlimit-mode srcip --hashlimit-burst 3575kb -j ACCEPT
iptables -A INPUT -p tcp --dport 10000:65500 -j DROP
iptables -A OUTPUT -p tcp --sport 10000:65500 -m hashlimit --hashlimit-name conn_limitB --hashlimit-htable-expire 30000 --hashlimit-upto 3500kb/s --hashlimit-mode dstip --hashlimit-burst 3575kb -j ACCEPT
iptables -A OUTPUT -p tcp --sport 10000:65500 -j DROP

#限速
iptables -A INPUT -p tcp --dport 10000:65500 -m hashlimit --hashlimit-name conn_limitA --hashlimit-htable-expire 30000 --hashlimit-upto 15000kb/s --hashlimit-mode srcip --hashlimit-burst 15010kb -j ACCEPT
iptables -A INPUT -p tcp --dport 10000:65500 -j DROP
iptables -A OUTPUT -p tcp --sport 10000:65500 -m hashlimit --hashlimit-name conn_limitB --hashlimit-htable-expire 30000 --hashlimit-upto 15000kb/s --hashlimit-mode dstip --hashlimit-burst 15010kb -j ACCEPT
iptables -A OUTPUT -p tcp --sport 10000:65500 -j DROP
```

# 6. iptables禁icmp&ping
```
iptables -A INPUT -p icmp --icmp-type echo-request -j DROP
iptables -A OUTPUT -p icmp --icmp-type echo-request -j DROP

```