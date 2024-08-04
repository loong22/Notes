```bash
#!/bin/bash
# 进入目标文件夹
cd "$1" || exit 1

# 循环处理所有tar.gz文件
for file in *.tar.gz; 
do    # 提取文件名（不包含扩展名）   
        filename=$(basename "$file" .tar.gz)    # 解压缩tar.gz文件到临时目录    
        mkdir "$filename"    
        tar -xzf "$file" -C "$filename"    
        cd "$filename"    # 压缩临时目录为zip文件    
        zip -r "$filename.zip" ./*    
        mv "$filename.zip" ..
    cd ..
    rm -rf "$filename"    echo "已转换: $file -> $filename_no_ext.zip"doneecho "转换完成"
```