%For major axis method.  Finds a local maximum head node.
function [radMax,radMaxID,headless] = getLocalRadMax(vec)
if(length(vec) > 3)
[~,pksID] = findpeaks(vec);
headless = isempty(pksID);
if(~headless)
    [radMax,pkID] = max(vec(pksID));
    radMaxID = pksID(pkID);
else
    [radMax,radMaxID] = max(vec);
end
else
    [radMax,radMaxID] = max(vec);
    headless = true;
end
end

