function centrality = KatzCentrality(records,loopStruct)
A = subGraph2AdjMat_SLOW(records, loopStruct);
alpha = 0.75/max(abs(eig(A)));
I = eye(size(A));
centrality = ((I-alpha*A')^(-1) - I)*ones(size(A,1),1);

end