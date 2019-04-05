function result=My_LagurerraL(n, alpha, x)
    result=1;
    bin=1;
    for i=n:-1:1
        bin = bin * (alpha + i) / (n+1-i);
        result=bin-result*x/i;
    end
end

