# $Id$

#Set PROFILE to something to enable profiling
#PROFILE=1

#Set DEBUG to something to enable debug prints
DEBUG=1

OS := $(shell uname -s)
ARCH := $(shell uname -m)

GLXINFO = $(shell which glxinfo)
STD_GLDIR = /usr/X11R6
HP_GLDIR = /usr/GL/hp
BASE_LIBFLAGS = -lm -lz
TARGETS = torus cone dirac compare_curv lapl compute_curv
GSL_TARGETS = maps_lsq
ifeq ($(OS), Linux)
CC = gcc

ifeq ($(CC), gcc)
PROF_FLAGS = -pg
XTRA_CFLAGS = -g -pipe -ansi -Wall -DREAD_TIME -DSUBDIV_TIME -W -Winline \
	-Wmissing-prototypes -Wstrict-prototypes -Wnested-externs \
	-Wshadow -Waggregate-return  #-Wno-unused 
endif
ifeq ($(CC),icc)
PROF_FLAGS = -p
XTRA_CFLAGS = -g -inline_debug_info -ansi -DREAD_TIME -DSUBDIV_TIME
BASE_LIBFLAGS += -ipo 
endif


GL_VENDOR := $(shell $(GLXINFO)|grep "OpenGL vendor"|cut -d\: -f2|cut -d\  -f2)
ALL_TARGETS = $(TARGETS) rawview subdiv $(GSL_TARGETS)
ifeq ($(GL_VENDOR), Hewlett-Packard) # The HP visualize have special dirs.
GLDIR = $(HP_GLDIR)
STATIC_GLFLAGS =  -L$(GLDIR)/lib -lglut -lGLU -lGL -L$(STD_GLDIR)/lib -lX11 \
	-lXmu -lXext -lXi $(BASE_LIBFLAGS)
XTRA_CFLAGS += -Wno-unknown-pragmas # remove silly warnings of HP includes
else
GLDIR = $(STD_GLDIR)
STATIC_GLFLAGS = -L$(GLDIR)/lib -lglut -lGLU -lGL -lX11 \
	-lXmu -lXext -lXi $(BASE_LIBFLAGS)
endif # HP
endif #Linux

ifeq ($(OS), IRIX64)
CC = cc
PROF_FLAGS = -fbgen
XTRA_CFLAGS = -g3 -o32 -xansi -I/usr/freeware/include
STATIC_GLFLAGS =  -o32 -lglut -lGLU -lGL -lX11 -lXmu -lm \
	-L/usr/freeware/lib -lz
ALL_TARGETS = $(TARGETS) rawview subdiv
endif


#
# Output directories
#
BINDIR = ../bin
LIBDIR = ../lib
OBJDIR = ../obj

#
# Include flags
#
INCLFLAGS = -I../include
GLINCLFLAGS = -I$(GLDIR)/include

ifdef PROFILE
XTRA_CFLAGS += $(PROF_FLAGS)
BASE_LIBFLAGS += $(PROF_FLAGS)
endif

ifdef DEBUG
XTRA_CFLAGS += -DDEBUG #-DSUBDIV_DEBUG -DSUBDIV_SPH_DEBUG -DNORM_DEBUG -DNORM_DEBUG_BFS
else
XTRA_CFLAGS += -O2
ifeq ($(ARCH), i686)
ifeq ($(CC),gcc)
XTRA_CFLAGS += -pedantic -march=i686 -fstrict-aliasing -ffast-math #-fno-math-errno
endif
ifeq ($(CC),icc)
XTRA_CFLAGS += -tpp6 -rcd -march=pentiumiii -ipo #-parallel
endif
endif
endif

BASE_CFLAGS = $(INCLFLAGS) $(XTRA_CFLAGS) 
GL_CFLAGS = $(INCLFLAGS) $(GLINCLFLAGS) $(XTRA_CFLAGS) 

#
# Objects
#
BASE_OBJECTS = $(OBJDIR)/geomutils.o $(OBJDIR)/normals.o \
	$(OBJDIR)/3dmodel_io.o $(OBJDIR)/ring.o \
	$(OBJDIR)/model_in.o $(OBJDIR)/model_in_raw.o \
	$(OBJDIR)/model_in_smf.o $(OBJDIR)/block_list.o \
	$(OBJDIR)/model_in_ply.o $(OBJDIR)/model_in_vrml_iv.o \
	$(OBJDIR)/model_in_off.o $(OBJDIR)/curvature.o
SUBDIV_OBJECTS = $(OBJDIR)/subdiv.o $(OBJDIR)/subdiv_loop.o \
	$(OBJDIR)/subdiv_sph.o $(OBJDIR)/subdiv_butterfly.o \
	$(OBJDIR)/subdiv_sqrt3.o $(OBJDIR)/kobbelt_sqrt3.o
GL_OBJECTS = $(OBJDIR)/rawview.o $(OBJDIR)/gl2ps.o $(OBJDIR)/rawview_disp.o \
	$(OBJDIR)/rawview_utils.o $(OBJDIR)/rawview_grab.o
GSL_OBJECTS = $(OBJDIR)/maps_lsq.o


#
# Linking flags
#
GSL_LDFLAGS =  -g $(BASE_LIBFLAGS) -lgsl -lgslcblas

#
# Linking (only for the dynamic stuff)
#
GL_LIBFLAGS = -L$(LIBDIR) -L$(GLDIR)/lib -lglut -lGLU -lGL \
	-lXmu -lXext -lX11 -lXi -l3d -limage -lm 
BASE_LDFLAGS += -g $(BASE_LIBFLAGS)
GL_LDFLAGS += -g $(GL_LIBFLAGS) 


default : rawview

all: dirs $(ALL_TARGETS)

rawview : $(GL_OBJECTS) $(BASE_OBJECTS) $(SUBDIV_OBJECTS) $(OBJDIR)/image.o 
	$(CC) -g $^ -o $(BINDIR)/$@ $(STATIC_GLFLAGS)

$(TARGETS): % : $(OBJDIR)/%.o $(BASE_OBJECTS)
	$(CC) -o $(BINDIR)/$@ $^ $(BASE_LDFLAGS)

$(GSL_TARGETS): % : $(OBJDIR)/%.o $(BASE_OBJECTS)
	$(CC) -o $(BINDIR)/$@ $^ $(GSL_LDFLAGS)

isoca: $(OBJDIR)/isoca.o $(OBJDIR)/subdiv.o $(BASE_OBJECTS)
	$(CC) -o $(BINDIR)/$@ $^ $(BASE_LDFLAGS) 

subdiv : $(OBJDIR)/subdiv_main.o $(SUBDIV_OBJECTS) $(BASE_OBJECTS)
	$(CC) -o $(BINDIR)/$@ $^ $(BASE_LDFLAGS) 

rawview_d : $(GL_OBJECTS) lib3d libimage
	$(CC) $(GL_OBJECTS) -o $(BINDIR)/$@ $(GL_LDFLAGS)

libimage : $(OBJDIR)/image.o
	$(CC) -g -shared  -o $(LIBDIR)/$@.so $<

lib3d : $(BASE_OBJECTS)
	$(CC) -g -shared -o $(LIBDIR)/$@.so $^

$(GL_OBJECTS): $(OBJDIR)/%.o : %.c
	$(CC) $(GL_CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : %.c
	$(CC) $(BASE_CFLAGS) -c $< -o $@	


#
# Non-compile stuff below...
#
clean : 
	rm -f $(OBJDIR)/*.o $(BINDIR)/* $(LIBDIR)/*

dirs : libdir bindir objdir

libdir : 
	-[ -d $(LIBDIR) ] || mkdir $(LIBDIR)

bindir : 
	-[ -d $(BINDIR) ] || mkdir $(BINDIR)

objdir :
	-[ -d $(OBJDIR) ] || mkdir $(OBJDIR)

# Targets not being real files
.PHONY: default all dirs libdir bindir objdir

