clear;
clc;
N=10000;
A=zeros(N);

for i=1:N
    if i>2
        t=i-2;
    else
        t=1;
    end
    if i<N-1
        p=i+2;
    else
        p=N;
    end
    for j=t:p
        switch abs(i-j)
            case 0
                if i==1 || i==N
                    A(i,j)=5;
                else
                    A(i,j)=6;
                end
            case 1
                A(i,j)=4;
            case 2
                A(i,j)=1;
            otherwise
                A(i,j)=0;
        end
    end
end

b=ones(N,1);
b=b*120;
b(1)=60;
b(N)=60;

x=A\b

res=A*x-b