NAME = gnl

LIB = gnl.a

INCLUDES = get_next_line

SRCS = get_next_line \
	get_next_line_utils \

INCLUDES := $(patsubst %,srcs/%.h,${INCLUDES})
SRCS := $(patsubst %,srcs/%.c,${SRCS})

MAIN = main.c

CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
DFLAGS = -D BUFFER_SIZE=${ARGS}
COMP := ${CC} ${CFLAGS} -I ${INCLUDES} 

NO_COLOR = \x1b[0m
OK_COLOR = \x1b[32;01m
ERROR_COLOR = \x1b[31;01m
WARN_COLOR = \x1b[33;01m
_PURPLE = \x1b[35m

OBJ := ${SRCS:.c=.o}

all : ${OBJ} ${NAME} 
		@echo "$(OK_COLOR)\n>> Congrats. Your program $(NAME) has been created successfully.\n $(NO_COLOR)" 

$(LIB):${OBJ}
		ar rc ${LIB} ${OBJ}
		ranlib ${LIB}
		
${NAME}: ${OBJ} ${MAIN}
		 ${COMP} -o ${NAME} ${OBJ} ${MAIN} 

clean:
	rm -f ${OBJ}

run: ./${NAME}
	./${NAME} ${ARGS}

fclean: clean
	rm -f ${NAME} gnl.a Icon srcs/Icon srcs/get_next_line.h.gch
	@echo "$(_PURPLE)\n>> Folder cleaned.\n $(NO_COLOR)" 


norm:
	norminette ${SRCS} ${INCLUDES}

re: fclean all


.PHONY: norm all re fclean clean progs bonus