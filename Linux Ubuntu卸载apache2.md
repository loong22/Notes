
```
sudo apt-get autoremove apache2 -y
sudo apt-get remove apache* -y
sudo apt-get --purge remove apache-common -y
sudo apt-get --purge remove apache -y
sudo find /etc -name "*apache*" |xargs  rm -rf 
sudo rm -rf /var/www
sudo rm -rf /etc/libapache2-mod-jk
dpkg -l |grep apache2|awk '{print $2}'|xargs dpkg -P

```