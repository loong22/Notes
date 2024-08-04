### 1. nethogs

**nethogs(推荐)**

```bash
#可以查看端口速率
apt install nethogs

#使用命令
sudo nethogs
```

### 2. netstat

```bash
#查看tcp端口占用
netstat -tln

#如果您想查看端口 80 的状态，您可以使用以下命令：
netstat -tln | grep 80
```