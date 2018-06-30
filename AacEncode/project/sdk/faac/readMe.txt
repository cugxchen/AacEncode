faac源码下载链接 http://www.audiocoding.com/downloads.html

1、解压
# tar -zxvf faac-1.29.9.2.tar.gz

2、编译
./configure
make

3、查看编译生成的库
find -name "libfaac*"

4、将动态库libfaac.so或静态库libfaac.a放入工程中，并引用头文件faac.h即可
