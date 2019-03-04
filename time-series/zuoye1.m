% y = detrend(x) % 消除时间序列中的线性趋势项
% y = detrend(x,'constant') % 消除时间序列中的均值
% y = detrend(x,'linear',bp) % 分段消除时间序列中的线性趋势项,bp为分段点向量
clc, clear, close all  ;
data = xlsread('data.xlsx', 'Sheet1', 'A2:B732');
x=data(:,1);
y=data(:,2);
n = length(y);

% 原始图像
figure;
plot(y);title('原始图像')

L = 50;

% 原始相关性系数
figure;
autocorr(y, L);title('原始相关性系数')

% 去除线性趋势项
y1=detrend(y);
figure;
plot(y1);title('去除线性趋势项图像')

% 相关性系数
figure;
autocorr(y1, n-1);title('去除线性趋势项相关性系数')

% 二次函数拟合
p = polyfit(x,y,2);
y3 = polyval(p,x);

% 去除趋势项
y3 = y - y3;
figure;
plot(y3);title('去除二次趋势项图像')

% 相关性系数
figure;title('去除二次趋势项相关性系数')
autocorr(y3, n-1);

% 去除周期项
T = [1 32	61	92	122	153 183	214	245	275	306	336 367	398	426	457	487	518 548	579	610	640	671	701 732];
T_total = length(T)-1;
for i=1:T_total
    average(i) = mean(y3(T(i):T(i+1)-1));
    y4(T(i):T(i+1)-1) = y3(T(i):T(i+1)-1) - average(i);
end
figure;
plot(y4);title('差分去除周期项图像')

figure;
autocorr(y4, n-1);title('差分去除周期项图像')

save('data.mat', 'y4');

% 二阶差分
% y2 = diff(y,2);
% figure;
% plot(y2);
% n = length(y2);
% [acf,lags] = autocorr(y2, L);
% 
% y3 = diff(y2,31);
% figure;
% plot(y2);
% title('差分后')
% n = length(y3);
% autocorr(y3, L);
% y4 = y3';
% save('data.mat', 'y4');