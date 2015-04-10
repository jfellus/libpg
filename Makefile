
###### INSTALLATION GUIDE ######
# make external_libs
# make
# ./coeos++
################################


APT_GET_DEPENDENCIES:= 


REQUIRED_PACKAGES:= 
REQUIRED_LIBS:= 


INCLUDE_PATHS:= 

SRC_DIR:=./src

EXECUTABLE:=libpg.so







########################## DON'T EDIT BELOW THIS LINE (unless you are a gnu make's expert ##############

SRC := $(shell find $(SRC_DIR) -name '*.cpp') 
OBJS := $(addprefix bin/,$(SRC:.cpp=.o))

all: $(HOME)/.pgcc/includes/pg.h 

CXXFLAGS := -fPIC -g -rdynamic -Wall -MMD $(addprefix -I,$(INCLUDE_PATHS))
LDFLAGS := -fPIC -rdynamic 
DEPENDS = $(OBJS:.o=.d)    


$(HOME)/.pgcc/includes/pg.h: 
	@mkdir -p $(HOME)/.pgcc/includes/ 
	@for i in `ls src/*.h`; do ln -sf `readlink -f $$i` $(HOME)/.pgcc/includes/`basename $$i`; done
	@echo "Installed includes"

bin/%.o: %.cpp
	@mkdir -p `dirname $(@:.o=.d)`
	@touch $(@:.o=.d)
	@echo "Compilation : $< "
	@g++ $(CXXFLAGS) -MMD -c $< -o $@

bin: 
	@mkdir -p bin

clean:
	@rm -f $(EXECUTABLE)
	@rm -rf bin
	


external_libs:
	@echo "We need your password for this : "
	@sudo echo "thank you"
	@sudo apt-get install $(APT_GET_DEPENDENCIES)
	@echo "DONE"

.PHONY: $(HOME)/.pgcc/includes/pg.h

-include $(DEPENDS) 
