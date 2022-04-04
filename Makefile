NAME = webserv

CC = c++

CFLAGS = --std=c++98 -Wall -Wextra -Werror -g3

HEADER =	include/ClassParsingClientRequest.hpp \
			include/p_conf.hpp \
			include/server_data.hpp \
			include/w_defines.hpp \
			include/w_library.hpp \
			include/P_server.hpp \
			include/Parser.hpp

SRC = 	main.cpp \
		server.cpp \
		server_read.cpp \
		fill_request.cpp \
		response.cpp \
		p_conf.cpp \
		ClassParsingClientRequest.cpp \
		_post_parsing.cpp \
		server_data.cpp \
		entity.cpp	\
		post_response.cpp \
		get_response.cpp \
		time.cpp	\
		utils.cpp	\
		setup.cpp	\
		set.cpp		\
		send_response.cpp \
		cgi.cpp \
		Parser.cpp \
		P_server.cpp


SRCS_DIR = ./srcs/
OBJS_DIR = ./objects/
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
			@mkdir -p $(@D)
			@$(ECHO)
			@echo "\033[0;32mCompiling... \033[0m"  $<
			$(CC) $(CFLAGS) -c -o $@ $<	
			@echo "\033[A\033[A"

all: $(NAME)

$(NAME): ${OBJS} ${HEADER}
		@echo "\n\n\033[0;33mLinking...\033[0m\n"
		$(CC) ${CFLAGS} $(OBJS) -o $(NAME)
		@echo "\n\033[0;32mDONE\033[0m"

install: sudo apt-get install php-cgi

test: re && ./${NAME}

clean:
		@echo "\033[0;31mWipeout..."
		rm -rf $(OBJS)
		@echo "\033[0m"

fclean: clean
		@echo "\033[0;31mRemoving executable..."
		rm -f $(NAME)
		@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
