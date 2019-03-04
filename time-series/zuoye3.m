clear, clc, close all
data = load('data.mat');
data = data.y4;
data_length = length(data);

data = diff(data,2);

% 正态性检验
[A,B,u,r] = nixujianyan(data(1:720),20);

sk = skewness(data); % 偏度
ku = kurtosis(data); % 峰度

data = data - mean(data);

% for i = 0:10
%     for j = 0:10
%         %        2012b之前
%         %        spec = garchset('R',i,'M',j,'Display','off'); % 指定模型的结构
%         %        [coeffX,errorsX,LLFX]=garchfit(spec,x); % 拟合参数
%         %        num=garchcount(coeffX); % 计算拟合参数的个数
%         Mdl = arima(i,0,j);
%         [EstMdl,EstParamCov,LLFX] = estimate(Mdl, data');
%         num = sum(any(EstParamCov));
%         % 计算Akaike和bayesian信息准则
%         [aic,bic]=aicbic(LLFX, num, data_length);
%         fprintf('R=%d, M=%d, AIC=%f, BIC=%f\n',i,j,aic,bic); %显示计算结果
%         aics(i+1,j+1)=aic;
%         bics(i+1,j+1)=bic;
%     end
% end

Mdl = arima(7,0,4);
[EstMdl,EstParamCov,LLFX] = estimate(Mdl, data');
num = sum(any(EstParamCov));
e(1)=0;
for j=2:data_length
    e(j) = data(j) - cell2mat(EstMdl.AR)*e(j-1)-cell2mat(EstMdl.MA)*e(j-1); % 计算残差
end

%下面进行chi2检验，是否服从0均值的正态分布，nparam表示估计参数的个数
[h,p,stats] = chi2gof(e,'cdf',@(z)normcdf(z,0,std(e)),'nparams',1);

