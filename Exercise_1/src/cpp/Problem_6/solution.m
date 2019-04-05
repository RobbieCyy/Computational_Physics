A=zeros(n);
for i=1:n
    A(i,i)=3;
    A(i,n-i+1)=0.5;
end
for i=1:n-1
    A(i,i+1)=-1;
    A(i+1,i)=-1;
end
b=ones(n,1)*1.5;
b(1)=2.5;
b(n/2)=1;
b(n/2+1)=1;
b(n)=2.5;
max(abs(1-inv(A)*b))