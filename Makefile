CXX=g++
CC=gcc
CXX_OBJS=
CC_OBJS=acpp/src/alloca acpp/src/cccp acpp/src/obstack acpp/src/version acpp/src/y.tab src/assigns src/derivs src/Excitation_Functions src/formain src/formain60
src/formain_ga src/ga_i src/gait_main src/GaussPattern src/gmc src/inits src/invert src/mathtools src/model_d src/model_s src/pipetools src/readmuscles src/readtools src/sdfor src/sdforWalk src/sdlib src/wrapping

CXX_OBJS=src/BiModalPattern src/CostFunc src/CostFunc_adjusted src/FileReadWrite src/ga_i src/ga_main src/ga_pop src/ModPattern src/SetExcPattern_Templates src/SetParamBounds src/SetPattern src/SetStructure src/Simann src/UpdatePattern

HEADERS=

all: $(CC_OBJS) $(CXX_OBJS)
	$(CXX) -o wsim $(CXX_OBJS) $(CC_OBJS)

$(CC_OBJS): $(HEADERS) $
