# MPI 实现埃拉托色尼素数筛选法

## 目录说明

### linux

本项目原本是在linux环境下使用clion基于mpich进行开发，环境配置见[我的博客](https://543877815.github.io/)，里面有详细的环境配置说明，项目运行说明及优化思路。相关目录及文件说明如下：

- base.cpp为原版代码
- main1.cpp为去掉偶数优化代码
- main2.cpp为去掉通信代码
- main3.cpp为初步提升cache命中率代码

分别编译生成了base、main1、main2、main3

前三个执行命令如下
```
mpirun -np 16 ./main 100000000
```

最后一个执行命令如下，最后一个参数为cache的大小
```
mpirun -np 16 ./main3 100000000 26214400
```