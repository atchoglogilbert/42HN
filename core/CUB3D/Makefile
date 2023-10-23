# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 03:34:56 by rrajaobe          #+#    #+#              #
#    Updated: 2023/03/03 22:19:11 by katchogl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=		gcc

NAME		=		cub3D

GLFW_DIR	=		$(shell brew --prefix glfw)

CFLAGS		=		-Wall -Wextra -Werror \
						-I./include -I./$(MLX_REPO)/include/MLX42 -I./libft \
						-I$(GLFW_DIR)/include -I./$(GNL_REPO) -g \

HEADERS		=		./include/cub3D.h ./include/containers.h

LIBFT_REPO	=		libft

LIBFT		=		$(LIBFT_REPO)/libft.a

MLX_REPO	=		MLX42

MLX			=		$(MLX_REPO)/build/libmlx42.a

GNL_REPO	=		gnl

GNL			=		$(GNL_REPO)/get_next_line.a

SRC			=		main init destroy utils \
					./parsing/ft_parse ./parsing/parsing_utils  \
					./parsing/rgb ./parsing/type ./parsing/ft_parse_map \
					./runtime/ft_translator ./runtime/ft_rotator \
					./runtime/handlers \
					./rendering/ft_raycaster ./rendering/ft_raycaster_utils

OBJ			=		$(patsubst %.c, src/%.o, $(SRC:=.c))

all: $(NAME)

$(GNL):
	@if [[ ! -d $(GNL_REPO) ]] ; \
	then \
		git clone https://github.com/atchoglogilbert/gnl.git $(GNL_REPO); \
	fi ;
	make -C $(GNL_REPO)
 
$(LIBFT):
	@if [[ ! -d $(LIBFT_REPO) ]] ; \
	then \
		git clone https://github.com/atchoglogilbert/libft.git $(LIBFT_REPO); \
	fi ;
	make -C $(LIBFT_REPO)

$(MLX):
	@if [[ ! -d $(MLX_REPO) ]] ; \
	then \
		git clone https://github.com/codam-coding-college/MLX42.git ; \
	fi ; \
	cd $(MLX_REPO) && cmake -B build && cmake --build build -j4

$(GLFW_DIR)/lib:
	brew install glfw

%.o: %.c $(CDEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(GLFW_DIR)/lib $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(GNL) -L$(GLFW_DIR)/lib -lglfw $(MLX) $(OBJ) -o $(NAME)
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

purge: fclean
	@if [[ -d $(LIBFT_REPO) ]] ; \
	then \
		rm -rf $(LIBFT_REPO) ; \
	fi ;

	@if [[ -d $(MLX_REPO) ]] ; \
	then \
		rm -rf $(MLX_REPO) ; \
	fi ;

	@if [[ -d .vscode ]] ; \
	then \
		rm -rf .vscode ; \
	fi ; \

	@if [[ -d $(NAME).dSYM ]] ; \
	then \
		rm -rf $(NAME).dSYM ; \
	fi ; \

	@if [[ -d $(NAME).log ]] ; \
	then \
		rm -rf $(NAME).log ; \
	fi ; \
	
	@if [[ -d $(GNL_REPO) ]] ; \
	then \
		rm -rf $(GNL_REPO) ; \
	fi ; \
	

.PHONY: all clean fclean all purge test-leaks log-leaks
