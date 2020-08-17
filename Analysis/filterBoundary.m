function [filteredBoundaryProfile] = filterBoundary(loopStruct,filtParam)
%%cell geo port
y = loopStruct.boundaryDiff';
n = filtParam;
x = 1:length(y);
if length(loopStruct.boundaryDiff)<filtParam
    filteredBoundaryProfile=y';
    return;
end

if mod(filtParam,2)==0
    filtParam=filtParam+1;
end
ots=floor(filtParam/2);

gs=(x(n)-x(1))/6;
gx = linspace(-3*gs,3*gs,n);
gf = exp( -(gx.^2)/(2*gs^2) );
gf = gf / sum(gf);
yi=(y(1)+y(2))/2;
yf=(y(end-1)+y(end))/2;

    filteredBoundaryProfile=x;
    %yy=[yi*ones(1,ots) y yf*ones(1,ots)];
    yy=[y((end-ots+1):end) y y(1:ots)];
    
    for j=1:length(x)
        filteredBoundaryProfile(j)=sum(yy(j:(j+n-1)).*gf);
    end
filteredBoundaryProfile = filteredBoundaryProfile';
end

