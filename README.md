# Quick-Search

linux终端下文件搜索工具，设计思路参考mlcoate

## 使用
使用cmake管理编译连接过程,最后生成可执行程序qs  

具体用法请参考代码
```shell
  mkdir build
  cd build
  cmake ..
  make
```

## QsDB
QsDB是本项目模拟出的数据库，用来存储系统目录信息，包括文件名、目录名、目录最后修改时间  

具体格式暂不说明。

## 实现细节的瑕疵

1. 写入文件有大小端问题  
同一块的数据必须用相同的方式读写。比如，一个int有4字节，写入时同时写入，读取时不可以分成4字节读，必须视为一个整体。

2. 对文件名有要求  
不允许出现文件名有空格的情况。涉及到文件读取问题，暂时不想修复。
