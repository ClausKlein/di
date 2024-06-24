
# Standard stuff

.SUFFIXES:
.SILENT:

MAKEFLAGS+= --no-builtin-rules          # Disable the built-in implicit rules.
#XXX MAKEFLAGS+= --warn-undefined-variables  # Warn when an undefined variable is referenced.

#XXX CXX:=g++-17
CPPFLAGS:=-I../include -isystem/usr/local/include -MD -MP # Write a depfile containing user headers only
CXXFLAGS:=-std=c++20 -Wextra -Wpedantic -Wunused -Wshadow

.PHONY: all clean
all: model_view

model_view: model_view.cpp
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	$(RM) model_view *.d *.o *~

model_view.cpp: model_view.hpp
#XXX -include *.d

# These rules keep make from trying to use the match-anything rule below to
# rebuild the makefiles--ouch!  Obviously, if you don't follow my convention
# of using a `.mk' suffix on all non-standard makefiles you'll need to change
# the pattern rule.
#
$(MAKEFILE) :: ;
%.mk :: ;
%.d :: ;
# Anything we don't know how to build will use this rule.
# The command is a do-nothing command.
#
% :: ;
