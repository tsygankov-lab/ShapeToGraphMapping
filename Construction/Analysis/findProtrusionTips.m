function [ tipID ] = findProtrusionTips(regionObj,param)
if(nargin == 1)
    param = 30;
end
%%This uses a built in matlab function to detect peaks
% [~,tipID] = findpeaks(boundaryProf); %
    originalProf = regionObj.boundaryDiff;
    boundaryProf = filterBoundary(regionObj,param);
    Py = boundaryProf';
    Pr = originalProf;
    Lb = length(boundaryProf);
    Px = 1:Lb;
    Pp=[Py(2:end), Py(1)];
    Pm=[Py(end), Py(1:(end-1))];
    Xdip=Px((Pp>Py) & (Pm>Py));
    if(Xdip > 0)
        tipID=zeros(size(Xdip));

        tt1=1:Xdip(1);
        tt2=Xdip(end):Lb;
        [vt1 it1]=max(Pr(tt1));
        [vt2 it2]=max(Pr(tt2));
        if vt1>=vt2
            tipID(1)=tt1(it1);
        else
            tipID(1)=tt2(it2);
        end
        for t=2:length(Xdip)
            tt=Xdip(t-1):Xdip(t);
            [vt it]=max(Pr(tt));        
            tipID(t)=tt(it);
        end
    else
        tipID = 1:length(Py);
    end

%     smPr=Py;
end

