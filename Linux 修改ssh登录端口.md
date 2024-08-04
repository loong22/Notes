
确保新端口在防火墙中放行

1. 关闭防火墙：
`/etc/init.d/iptables stop`
或者
`service iptables stop`

或者在防火墙过滤规则中上增加一条，允许对新增的端口的访问：
vi /etc/sysconfig/iptables

新增一条策略，放通新端口。
例如新端口为12022：
-A INPUT -m state --state NEW -m tcp -p tcp --dport 12022 -j ACCEPT

2. 编辑ssh配置文件
`vim /etc/ssh/sshd_config`

修改#Port 22，去掉#号，端口设置为新端口

3. 重启ssh服务

`systemctl restart sshd`
或者
`/etc/init.d/sshd restart`
