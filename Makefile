##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=shell
ConfigurationName      :=Debug
WorkspacePath          :="/media/tung/Hoc Tap/codelite/tung"
ProjectPath            :="/media/tung/Hoc Tap/codelite/tung/shell"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Tung
Date                   :=18/02/17
CodeLitePath           :=/home/tung/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="shell.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -std=c++11 -I include $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_token_parser.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_unix.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_unix_executor.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_cmd_token_parser.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/tung/Hoc Tap/codelite/tung/shell/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM src/main.cpp

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) src/main.cpp

$(IntermediateDirectory)/src_token_parser.cpp$(ObjectSuffix): src/token_parser.cpp $(IntermediateDirectory)/src_token_parser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/tung/Hoc Tap/codelite/tung/shell/src/token_parser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_token_parser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_token_parser.cpp$(DependSuffix): src/token_parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_token_parser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_token_parser.cpp$(DependSuffix) -MM src/token_parser.cpp

$(IntermediateDirectory)/src_token_parser.cpp$(PreprocessSuffix): src/token_parser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_token_parser.cpp$(PreprocessSuffix) src/token_parser.cpp

$(IntermediateDirectory)/src_unix.cpp$(ObjectSuffix): src/unix.cpp $(IntermediateDirectory)/src_unix.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/tung/Hoc Tap/codelite/tung/shell/src/unix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_unix.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_unix.cpp$(DependSuffix): src/unix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_unix.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_unix.cpp$(DependSuffix) -MM src/unix.cpp

$(IntermediateDirectory)/src_unix.cpp$(PreprocessSuffix): src/unix.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_unix.cpp$(PreprocessSuffix) src/unix.cpp

$(IntermediateDirectory)/src_unix_executor.cpp$(ObjectSuffix): src/unix_executor.cpp $(IntermediateDirectory)/src_unix_executor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/tung/Hoc Tap/codelite/tung/shell/src/unix_executor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_unix_executor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_unix_executor.cpp$(DependSuffix): src/unix_executor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_unix_executor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_unix_executor.cpp$(DependSuffix) -MM src/unix_executor.cpp

$(IntermediateDirectory)/src_unix_executor.cpp$(PreprocessSuffix): src/unix_executor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_unix_executor.cpp$(PreprocessSuffix) src/unix_executor.cpp

$(IntermediateDirectory)/src_cmd_token_parser.cpp$(ObjectSuffix): src/cmd_token_parser.cpp $(IntermediateDirectory)/src_cmd_token_parser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/tung/Hoc Tap/codelite/tung/shell/src/cmd_token_parser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_cmd_token_parser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_cmd_token_parser.cpp$(DependSuffix): src/cmd_token_parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_cmd_token_parser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_cmd_token_parser.cpp$(DependSuffix) -MM src/cmd_token_parser.cpp

$(IntermediateDirectory)/src_cmd_token_parser.cpp$(PreprocessSuffix): src/cmd_token_parser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_cmd_token_parser.cpp$(PreprocessSuffix) src/cmd_token_parser.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


