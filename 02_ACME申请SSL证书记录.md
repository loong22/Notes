# 1.安装acme.sh

```
#替换为个人邮箱
curl https://get.acme.sh | sh -s email=example@example.com  
```

# 2.创建nginx配置文件

```
#在/etc/nginx/sites-available路径下创建example.com文件，文件内容见示例
vim /etc/nginx/sites-available/example.com
```

example.com内容示例如下：
```
server {
    listen 80;
    server_name example.com;

	#acme验证时使用的目录
  #确保目录/home/wwwroot/存在
	location /.well-known/acme-challenge/ {
        root /home/wwwroot/;
        try_files $uri =404;
    }

    location / {
        return 301 https://$host$request_uri;
    }
    #日志文件，可选是否开启
    #error_log /var/log/nginx/example.error.log;
    #access_log /var/log/nginx/example.access.log;
}

server {
    listen 443 ssl;
    ssl_certificate  /root/.acme.sh/example.com_ecc/fullchain.cer;
    ssl_certificate_key /root/.acme.sh/example.com_ecc/example.com.key;
    server_name example.com;
    charset utf-8;	
    location / {
        root /home/wwwroot/;
        autoindex on;   
        autoindex_exact_size off;               
        autoindex_localtime on;               
    }
    #日志文件，可选是否开启
    #error_log /var/log/nginx/example.error.log;
    #access_log /var/log/nginx/example.access.log;
}
```

把写好的配置文件链接到/etc/nginx/sites-enabled路径下

```
ln -s /etc/nginx/sites-available/example.com /etc/nginx/sites-enabled
```

# 3.申请SSL证书

```
#--force是强制更新，第一次申请可以不用添加
acme.sh  --issue  -d example.com  --webroot  /home/wwwroot/ --force
```

# 4.重启nginx
```
#测试配置文件是否通过
nginx -t

#重启nginx服务
nginx -s reload
```
