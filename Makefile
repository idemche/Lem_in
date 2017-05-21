# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/03 14:05:14 by idemchen          #+#    #+#              #
#    Updated: 2017/05/19 22:27:53 by idemchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

LEM_NAME = lem_in
LEM_SRC	= lem_in.c
LEM_OBJ	= $(patsubst %.c, %.o, $(LEM_SRC))
TMP_DIR	= $TMPDIR

FLAGS = -Wall -Werror -Wextra -O3
DEBUG_EXE = lldb
DEBUG_EXT = .dSYM

LIB_PATH = ./libft
LIB_DYNAMIC = $(LIB_PATH)/libft.a

all: create

create:	libcreate $(LEM_NAME)

libcreate:
	@make -C $(LIB_PATH)

$(LEM_NAME):
	@echo "\t\t\t\t\033[0;34m\n\033[0m"
	@echo "\t\033[0;34m|  Welcome to Lem_in project	|\033[0m"
	@echo "\t\033[0;34m|  	Author: idemchen 	|\033[0m"
	@echo "\t\033[0;34m---------------------------------\033[0m"
	@echo "\t\033[0;34m---------------------------------\033[0m"
	@echo "\t\033[0;34m---------------------------------\033[0m"
	@echo "\t\033[0;34mFor makefile help use: [make help]\033[0m"
	@echo "\t\033[0;34m-------------Enjoy!---------------\033[0m"
	@echo "\033[0;34mlem_in\t\033[1;33mCompilation\t\033[0;32m	[In Progress]\033[0m"
	@clang $(FLAGS) -o $@ $(LEM_SRC) $(LIB_DYNAMIC)
	@echo "\033[0;34mlem_in\t\033[1;33mCompilation\t\033[0;32m	[Done]\033[0m"

$(TMP_DIR)/%.o: ./%.c
	@clang $(FLAGS) -o $(TMP_DIR)/$@ -c $<

remake:
	@echo "\033[0;34mlem_in\t\033[1;33mRemake\t\033[0;32m		[In Progress]\033[0m"

clean:
	@rm -f $(LEM_OBJ)
	@echo "\033[0;34mlem_in\t\033[1;33mCleaning obj\t\033[0;32m	[Done]\033[0m"

fclean: clean
	@rm -f $(LEM_NAME)
	@echo "\033[0;34mlem_in\t\033[1;33mCleaning executives\t\033[0;32m[Done]\033[0m"

libclean: fclean
	@make fclean -C $(LIB_PATH)
	@echo "\033[0;34mlem_in\t\033[1;33mCleaning libft\t\033[0;32m	[Done]\033[0m"

re: remake fclean all

norme:
	@echo "\033[1;34mlem_in\t\033[1;33mNorminette\t\033[0;32m[In process]\033[0m"
	@norminette $(LEM_SRC)
	@echo "\033[1;34mlem_in\t\033[1;33mNorminette\t\033[0;32m[Completed]\033[0m"

debug:
	@echo "\033[1;34mlem_in\t\033[1;33mDebug\t\033[0;32m		[Start]\033[0m"
	@clang -g -o $(LEM_NAME) $(LEM_SRC) $(LIB_DYNAMIC)
	@echo "\033[1;34mlem_in\t\033[1;33mDebug\t\033[0;32m		[In process]\033[0m"
	@lldb $(LEM_NAME)
	@echo "\033[1;34mlem_in\t\033[1;33mDebug\t\033[0;32m		[End]\033[0m"
	@rm -r $(LEM_NAME) $(LEM_NAME)$(DEBUG_EXT)

help:
	@echo "\033[0;33m[make clean] - cleans all object files           		 "
	@echo "\033[0;33m[make fclean] - cleans all object files and executable	 "
	@echo "\033[0;33m[make libclean] - makes complete cleanse including Lib_ft objects and library"
	@echo "\033[0;33m[make norme] - executes './norminette command'	and checks code according Norme"
	@echo "\033[0;33m[make debug] - Enters dubugging mode through lldb. On quit it removes lldb executables"
