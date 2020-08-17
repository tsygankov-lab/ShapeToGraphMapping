%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%This code will check your OS and your current selected compiler, and will
%pass on the correct flags so that the code will compile correctly. Below
%is a description of various flags you can input which controls the code's
%behavior (along with a short technical explanation over what these do).  I
%have also included a list of compilers for each OS. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%Pre-Processor Flags
%%Flags that can be passed to the compiler to change the Voronoi Algorithm
%Behavior.  For more information, see below.
%_UNSAFE      -  Adds additional checks for potentially overlapping points.
%                Does not work with lines. 10-20% performance penalty
%_SKIP_CHECKS -  Internally validates every intersection and circle to
%                catch mathematical anomalies before the program finishes.
%                Defines an error as when two (or three) points differ in
%                distance from a common point by more than
%                (eps*10^8*maxVal(...)), allowing for some floating point
%                errors, but not large ones.  Can get false positives.
%                (Though this could be a symptom of an error in the
%                algorithm).
%_DEBUG       -  Program computes extra values in functions to make
%                debugging easier (alternative solutions to
%                intercept/circle center problems, character ID of all
%                elements, etc.
%_GCC_49_COMP -  Prior to 2017b (on windows) and 2018a (on linux), Matlab
%                only supported GCC 4.9 (mostly as it did not support
%                C++14).  This flag will implement the 'make_unique'
%                operator, so the code is C++11 compliant.  
%MATLAB_MEX_FILE Indicates to the included matlab libraries that this is to
%                be compiled as a stand alone library.  Should
%                automatically be defined by calling the mex function.
%_BUFFERED_VEC_OPT 
%             -  Uses a custom container class with an internal buffer
%                that then uses a normal vector if it overflows. Only 
%                your mileage may vary. Small speedup, more noticeable on
%                larger images.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%What are 'Pre-Processor Flags'
%For those not familiar with C/C++, prior to compilation, the code files
%are parsed with a pre-processor.  The pre-processor can insert or remove
%blocks of code based on what is 'defined' via a flag passed to cl, gcc, or
%llvm. In the C++ code, you will see:

% #ifdef _FLAG
%    ...
% #endif 

%This means that if _FLAG is defined, then that block will be
% included at compile time.  Else, it will be as if that chunk of code
% never existed. Additionally, there is... 

% #ifndef _FLAG
%   ...
% #endif 

% This means that if _FLAG is defined, that block will be removed at
% compile time. The Voronoi Diagram algorithm calls its internal functions
% *literally* hundreds of thousands to millions of times per second.
% Because of this, I decided to put some different code functionality as
% compile-time options rather than options passed to by the user to
% minimize the amount of branching in the code, and to allow some checks to
% be skipped if they are not needed for certain use cases.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%Suported Compilers (Search 'Supported Compilers' on Mathworks for more
%%Information)
%General notes:
%   The code uses the C++14 standard, or C++11 with _GCC_49_COMP defined.
%   Matlab 2018a has created a new mex API for C++ files.  Though this is a
%   C++ project, it currently uses the older C MEX API so it can be
%   compiled on earlier versions.
%Windows: 
%       Recommended: 
%               >2017b: Mingw-w64 (gcc) 5.3
%               >2015b & <2017b: Mingw-w64 (gcc) 4.9 w/ _GCC_49_COMP
%               MinGW Can be installed as an addon in MATLAB on versions
%               2015b and later.
%       Supported:
%               Visual Studio Compiler
%       Notes on r2015a and Earlier:
%               This is compatible with an older version of the visual
%               studio compiler.  I have not personally tested this, and to
%               compile it, you may need to define _GCC_49_COMP and
%               /std:c++11
%Apple/Mac:
%       Supported:
%               Xcode(7.0->9.0 on 2017b).
%       Notes on Xcode
%               Xcode is Apple's development tools for MacOS.  The Xcode
%               compiler is (I believe) gcc on 7.0, and clang on later
%               versions.  Clang and gcc use the same flags, so for now
%               this is not an issue.  I do not know the current state of
%               clang/gcc in xcode, so this code will build with the
%               -std=c++11 standard, and -D_GCC_49_COMP flag.
%Linux:
%       Supported:
%               >2018a: gcc 6.3 (c++17 compliant)
%               <2018a: gcc 4.9* (c++11 compliant)
%       Notes on gcc 4.9:
%               You will not find a version of gcc 4.9 on any repository,
%               it has completely disappeared.  However, later versions of
%               gcc will compile fine AS LONG AS you use -std=c++11 and
%               -D_GCC_49_COMP flags
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all
if(~exist('VoronoiDiagram.cpp','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end
if(~exist('VoronoiDiagram.cpp','file'))
    msgbox('Cannot locate VoronoiDiagram.cpp. Please select the directory with VoronoiDiagram.cpp.  This will add this folder to your path.');
    path2Code = uigetdir('','Select C++ Code Directory');
    if(path2Code == 0)
        error('No path provided');
    end
    addpath(genpath(path2Code));
end
[path,~,~] = fileparts(which('VoronoiDiagram.cpp'));
codeCopyDir = 'CppCopy'; %DO NOT CHANGE THIS
%%Copies the .cpp file to a common location, then compiles.
[a,b,c] = mkdir(codeCopyDir);
[a,b,c] = copyfile([path filesep '*.cpp'],codeCopyDir,'f');
[a,b,c] = copyfile([path filesep '*.hpp'],codeCopyDir,'f');
[a,b,c] = copyfile([path filesep '*.h'],codeCopyDir,'f');
[a,b,c] = copyfile([path filesep '*.c'],codeCopyDir,'f');
fprintf('\nCopying from: \n %s \n to: \n %s\n',path,codeCopyDir);
   
subDirNames = {'Containers','DataTypes','Math','Queue','Records','Search','Tree'};
for i = 1:length(subDirNames)
   location = fullfile(path,subDirNames{i});
   destination = [codeCopyDir filesep subDirNames{i}];
   fprintf('\nCopying from: \n %s \n to: \n %s\n',location,destination);
   [a,b,c] = mkdir(destination);
   [a,b,c] = copyfile([location filesep '*.cpp'],destination);
   [a,b,c] = copyfile([location filesep '*.hpp'],destination);
   [a,b,c] = copyfile([location filesep '*.c'],destination);
   [a,b,c] = copyfile([location filesep '*.h'],destination);
end

fprintf('Code is copied, compiling shortly...\n');
pause(3);
compilerInfo = mex.getCompilerConfigurations('C++');
%%Misc Notes
%Matlab will only compile with -O(1) by default, unless it is compiled with
%debug symbols (-g).
%%
if ismac
mex -v -g -output VoronoiMEX_DBG CXXFLAGS='$CXXFLAGS -D_DEBUG -D_GCC_49_COMP -std=c++11 -O0 -Wall' CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp
mex -v -g -output VoronoiMEX CXXFLAGS='$CXXFLAGS -D_GCC_49_COMP -D_UNSAFE -D_SKIP_CHECKS -std=c++11 -lm -O3 -Wall' CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp

elseif isunix
mex -v -g -output VoronoiMEX_DBG CXXFLAGS='$CXXFLAGS -D_DEBUG -D_GCC_49_COMP -std=c++11 -O0 -Wall' CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp
mex -v -g -output VoronoiMEX CXXFLAGS='$CXXFLAGS -D_GCC_49_COMP -D_UNSAFE -D_SKIP_CHECKS -std=c++11 -lm -O3 -Wall' CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp

elseif ispc
if(strcmp(compilerInfo.Manufacturer,'GNU'))
    disp('using GCC')
    mex -v -g -output VoronoiMEX_DBG CXXFLAGS='$CXXFLAGS -D_BUFFERED_VEC_OPT -D_DEBUG -D_UNSAFE -std=c++14 -pipe -lm -Og -g2 -ggdb -Wall' CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp
    mex -v -g -output VoronoiMEX CXXFLAGS='$CXXFLAGS -D_BUFFERED_VEC_OPT -D_UNSAFE -D_SKIP_CHECKS -std=c++14 -pipe -O3 -Wall' CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp
elseif(strcmp(compilerInfo.Manufacturer,'Microsoft'))
    disp('Using Microsoft Compiler')
%     warning('MinGW64 (g++) tends to have slightly better performance');
    mex -v -g -output VoronoiMEX_DBG COMPFLAGS="$COMPFLAGS /D"_BUFFERED_VEC_OPT" /D"_DEBUG" /D"_MBCS" /D"MATLAB_MEX_FILE" /ZI /Od /sdl /Zc:inline /Fd"vc141.pdb" /fp:precise /errorReport:prompt /WX- /Zc:forScope /Fp"VoronoiMEX_DBG.pch" /RTC1 /Gd /MDd /std:c++17 /EHsc" CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp
    mex -v -g -output VoronoiMEX COMPFLAGS="$COMPFLAGS /D"_BUFFERED_VEC_OPT" /D"_UNSAFE" /D"_SKIP_CHECKS" /Zi /Gm- /Ox /Ob2 /sdl /Zc:inline /fp:precise /errorReport:prompt /WX- /Zc:forScope /arch:AVX2 /Gd /Oi /std:c++17 /EHsc /Ot /diagnostics:classic " CppCopy/VoronoiDiagram.cpp CppCopy/DataTypes/lineEvent.cpp CppCopy/DataTypes/vertexEvent.cpp CppCopy/Math/basicMathAndGeometry.cpp CppCopy/Math/circleCalculator.cpp CppCopy/Math/interceptCalculators.cpp CppCopy/Queue/NodeSEQ.cpp CppCopy/Records/halfEdgeRecords.cpp  CppCopy/Tree/RBT_CircleEvents.cpp CppCopy/Tree/RBT_General.cpp CppCopy/Tree/RBT_Maintain.cpp CppCopy/Tree/RBT_SiteEvent_Processing.cpp
end
end

fprintf('\nDone! Removing the temporary CppCopy folder...\n');
rmdir(codeCopyDir,'s');

fprintf('\nCompiling done, running test image\n');
if(~exist('multiLayerBorder.m','file') || ~exist('plotVoronoiSkeleton_SingleRegion.m','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end
holeSizeFilt = 0;
records = testPerf_Def;
error_problem;
