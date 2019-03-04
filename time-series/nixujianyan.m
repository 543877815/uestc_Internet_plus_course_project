function [A,B,u,r] = nixujianyan(ser,K) 
%NIXUJIANYAN Summary of this function goes here 
%   Detailed explanation goes here 
  y=cell(K,1); 
  length=size(ser')/K; 
  for k=1:K 
      y{k}=ser(1+(k-1)*length:k*length); 
  end 
  for k=1:K 
      yeve(k)=mean(y{k}); 
  end 
  for k=1:K 
      yvar(k)=var(y{k}); 
  end 
  a=zeros(K,K); 
  for j=1:K 
      for i=1:j 
          if yeve(i)<yeve(j); 
              a(i,j)=1; 
          end 
      end 
  end 
  b=zeros(K,K); 
  for j=1:K 
      for i=1:j 
          if yvar(i)<yvar(j); 
              b(i,j)=1; 
          end 
      end 
  end 
  [A,an]=size(find(a==1)); 
  [B,bn]=size(find(b==1)); 
  u=(A+0.5-K*(K-1)/4)/sqrt(K*(2*K*K+3*K-5)/72); 
  r=(B+0.5-K*(K-1)/4)/sqrt(K*(2*K*K+3*K-5)/72); 
end