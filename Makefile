NAME = pipex

SRCS =  \
		main.c \
		srcs/pipex/new.c \
		srcs/pipex/delete.c \
		srcs/pipex/execute.c \

LIBS =	\
		-lft \

HEADERS = \
		includes \

LIB_NAMES	= $(subst -l,lib,$(LIBS))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(lib).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/)

OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
CC			= gcc
CCDBGFLGS	= -g3
CCFLAGS		= -Wall -Wextra
DEPSFLAGS	= -MMD -MP
RM			= rm -f
MAKE		= make -C
AR			= ar
AR_FLAGS	= rc

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) $(CCFLAGS) $(CCDBGFLGS) $(LIB_LD) $(LIBS) -o $@ $(OBJS)

$(LIB_PATHS) :
		$(MAKE) $(notdir $(basename $@))

all : $(NAME)

clean :
		-$(RM) $(OBJS) $(DEPS)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

-include $(DEPS)

%.o : %.c Makefile
		$(CC) $(CCFLAGS) $(DEPSFLAGS) $(CCDBGFLGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

.PHONY: all clean fclean re
