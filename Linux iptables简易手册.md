# 07 iptables简易手册
1.Install iptables
------------------

```sh
#Ubuntu
apt-get install iptables

#Centos
yum install iptables
```

2.Add rules
-----------

```sh
#forward Windows Remote desktop
iptables -A FORWARD -p tcp --dport 3389 -j ACCEPT
iptables -t nat -A PREROUTING -p tcp --dport 3389 -j DNAT --to-destination 
iptables -t nat -A PREROUTING -p tcp --dport 3389 -j DNAT --to-destination <WindowsIP>
iptables -t nat -A PREROUTING -p udp --dport 3389 -j DNAT --to-destination <WindowsIP>
iptables -t nat -A POSTROUTING -j MASQUERADE

#others
iptables -t nat -A PREROUTING -i eth0 -p tcp --dport [localPort] -j DNAT --to-destination [1.1.1.1:remotePort]

iptables -t nat -A POSTROUTING -d [1.1.1.1] -p tcp --dport [remotePort] -j SNAT --to-source [172.16.x.x Intranet ip]
```

3.Save
------

```sh
#Ubuntu
apt-get install iptables-persistent
iptables-save

#Centos
service iptables save
```