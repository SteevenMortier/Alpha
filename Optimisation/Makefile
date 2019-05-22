NAME		=	Optimisation

SRC_NAME	=	main.cpp		\
				collision.cpp 	\
				Car.cpp 		\
				Vecteur.cpp 	\
				Point.cpp

OBJ_NAME	=	$(SRC:.c=.o)
SRC_PATH	=	./source
OBJ_PATH	=	.
SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC			=	g++ -std=c++11
CFLAGS		=	-Wall -Werror -Wextra
CPPFLAGS	=	-I./inc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $^

clean:


fclean: clean
	

re: fclean all

.PHONY: clean, fclean, re, all
