# Quick-Search

linux终端下文件搜索工具，设计思路参考mlcoate


## ISSUES

1. 写入文件有大小端问题  
同一块的数据必须用相同的方式读写。比如，一个int有4字节，写入时同时写入，读取时不可以分成4字节读，必须视为一个整体。