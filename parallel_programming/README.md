# MPI 实现埃拉托色尼素数筛选法

## 目录说明

### linux

本项目原本是在linux环境下使用clion基于mpich进行开发，环境配置见[我的博客](https://543877815.github.io/)，里面有详细的环境配置说明，项目运行说明及优化思路。相关目录及文件说明如下：

- main.cpp为原版代码
- main1.cpp为去掉偶数优化代码
- main2.cpp为去掉通信代码
- main3.cpp为初步提升cache命中率代码
- MPItest.cpp为起初测试linux下mpi环境代码
- base.cpp为原版代码副本
- cache.test.cpp为阅读[本文](http://www.360doc.com/content/14/1015/13/10249440_417146850.shtml)的测试代码
- output为输出结果（输出已在代码中注释需要手动取消）。

### windows

后来在windows上进行测试，使用VS对代码进行部分修改以兼容windows版本并进行了编译，其中

- srcForWindows为存放了windows下运行源码目录
- execForWindows为编译生成的可执行文件
  - 需要安装`msmpisetup.exe`
  - 执行命令为`mpiexec -n 8 main.exe 10000000`
  - main3.exe需要传入cache_size的参数 `mpiexec -n 8 main.exe 10000000  10240000`
  - 生成数据文件需要手动在该目录下创建名为output的文件夹

- 你可能需要的[文件](2019/04/25/ubuntu和windows下运行MPI做埃拉托色尼素数筛选法/msvcp120d +msvcr120d.rar)

