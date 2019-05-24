NAME		=	Optimisation

SRC_NAME	=	main.cpp		\
				collision.cpp 	\
				classfile/Car.cpp 		\
				classfile/Vecteur.cpp 	\
				classfile/Point.cpp		\
				classfile/World.cpp		\
				gerbeurs.cpp	\
				placing.cpp

OBJ_NAME	=	$(SRC:.c=.o)
SRC_PATH	=	./source
OBJ_PATH	=	.
SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC			=	g++ -std=c++11
CFLAGS		=	-Wall -Wextra #-Werror
CPPFLAGS	=	-I./inc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME)
	@printf "\n\e[38;5;82m##################################################\e[0m\n\n"
	@printf "\e[38;5;82m\t\tREADY FOR OPTIMISATION\e[0m\n"
	@printf "\n\e[38;5;82m##################################################\e[0m\n\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $^

clean:
	@$(RM) $(NAME)

fclean: clean


re: fclean all

.PHONY: clean, fclean, re, all
