#Name of the compiler to use
CC		= gcc 
#Compiler flags - optimisation and so on
CFLAGS	= -Wall -std=c99
#Libraries to include with compilation
LIBS	= -fopenmp
# Will install here
PREFIX	= /var/soft/
# Will build files into tmp
BUILDIR = /tmp/textgenbuild/

#Internal stuffs - do not modify
MKDIR_P := mkdir -p
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color
DISP_MSG := printf "${RED} $1 ${NC}\n"
COPY := cp
all:
	@printf "${YELLOW} Creating build directory ${NC}\n"
	${MKDIR_P} $(BUILDIR)
	@printf "${YELLOW} Creating build directory compiling program to build directory) ${NC}\n" 
	$(CC) practical1.c $(CFLAGS) $(LIBS) -o $(BUILDIR)textgen
	@printf "${GREEN}All done! ${NC}\n" 
clean:
	$(info )
	@printf "${RED} Deleting build directory... ${NC}\n" 
	-rm -rf $(BUILDIR)
	
install:
	@printf "${YELLOW} Creating installation directory ${NC}\n"
	${MKDIR_P} $(PREFIX)textgen
	@printf "${YELLOW} Installing program${NC}\n"
	${COPY} $(BUILDIR)textgen $(PREFIX)textgen/textgen
	@printf "${GREEN}All done! ${NC}\n" 

