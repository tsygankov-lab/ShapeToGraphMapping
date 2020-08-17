@echo off
set MATLAB=A:\MATLAB~2
set MATLAB_ARCH=win64
set MATLAB_BIN="A:\MatlabR2017A\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=mexBetweenessCentrality_mex
set MEX_NAME=mexBetweenessCentrality_mex
set MEX_EXT=.mexw64
call "A:\MATLAB~2\sys\lcc64\lcc64\mex\lcc64opts.bat"
echo # Make settings for mexBetweenessCentrality > mexBetweenessCentrality_mex.mki
echo COMPILER=%COMPILER%>> mexBetweenessCentrality_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> mexBetweenessCentrality_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> mexBetweenessCentrality_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> mexBetweenessCentrality_mex.mki
echo LINKER=%LINKER%>> mexBetweenessCentrality_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> mexBetweenessCentrality_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> mexBetweenessCentrality_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> mexBetweenessCentrality_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> mexBetweenessCentrality_mex.mki
echo BORLAND=%BORLAND%>> mexBetweenessCentrality_mex.mki
echo OMPFLAGS= >> mexBetweenessCentrality_mex.mki
echo OMPLINKFLAGS= >> mexBetweenessCentrality_mex.mki
echo EMC_COMPILER=lcc64>> mexBetweenessCentrality_mex.mki
echo EMC_CONFIG=optim>> mexBetweenessCentrality_mex.mki
"A:\MatlabR2017A\bin\win64\gmake" -B -f mexBetweenessCentrality_mex.mk
