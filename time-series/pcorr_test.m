clc,clear, close all;
randn('state',sum(clock));
%初始化随机数发生器
elps=randn(1,10000);
%产生10000个服从标准正态分布的随机数
x(1)=0;
%赋初始值
for j=2:10000
    x(j)=0.8*x(j-1)+elps(j)-0.4*elps(j-1);
    %产生样本点
end

y=(x-mean(x)); %把数据中心化
gama0=var(x); %求样本方差
L=20;
for j=1:L
    gama(j)=y(j+1:end)*y(1:end-j)'/10000;%求自协方差
end
rho=gama/gama0      %求自相关系数
f(1,1)=rho(1);
for k=2:L
    s1=rho(k);s2=1;    %式（90）中第二式计算的初始值
    for  j=1:k-1
        s1=s1-rho(k-j)*f(k-1,j);
        s2=s2-rho(j)*f(k-1,j);
    end
    f(k,k)=s1/s2;%式（90）中第二式的计算值
    for  j=1:k-1
        f(k,j)=f(k-1,j)-f(k,k)*f(k-1,k-j); %式（90）中第三式的计算值
    end
end
pcorr=diag(f)';      %提取偏相关函数
parcorr(x,L) %直接利用Matlab工具箱计算偏相关函数
figure;
plot(pcorr);
figure;
plot(pcorr2);