# 1.Install iptables
```sh
#Ubuntu
apt-get install iptables

#Centos
yum install iptables
```

# 2.Add rules
```sh
iptables -A FORWARD -p tcp --dport 3389 -j ACCEPT
iptables -t nat -A PREROUTING -p tcp --dport 3389 -j DNAT --to-destination 
iptables -t nat -A PREROUTING -p tcp --dport 3389 -j DNAT --to-destination <WindowsIP>
iptables -t nat -A PREROUTING -p udp --dport 3389 -j DNAT --to-destination <WindowsIP>
iptables -t nat -A POSTROUTING -j MASQUERADE
```

# 3.Save
```sh
#Ubuntu
apt-get install iptables-persistent
iptables-save

#Centos
service iptables save

```
