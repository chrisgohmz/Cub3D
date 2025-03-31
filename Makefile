CFLAGS ?= -Wall -Wextra -Werror -MMD -MP -Ofast -pedantic
LDFLAGS = -Llibft -L$(MLXDIR) -L/usr/lib
LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm -lz 

SRCS_DIR = srcs/

SRCS = $(addprefix $(SRCS_DIR), main.c init.c events.c render_map.c\
		 render_map_cells.c drawing_grid_lines.c drawing_player.c drawing_rays.c\
		 ray_casting.c scene.c image.c parsing.c parsing_utils1.c parsing_utils2.c parsing_utils3.c parsing_utils4.c parsing_utils5.c sprite.c door.c free.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLXDIR = mlx-linux
MLX = $(MLXDIR)/libmlx_Linux.a
MLX_URL = https://github.com/42Paris/minilibx-linux.git
MLX_SUBMODULE = .git/modules/mlx-linux

-include $(LIBFT_DIR)/Makefile.variables

NAME = cub3D
RM = rm -rf

all: $(NAME)

debug: CFLAGS += -g -Og -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: all

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(MLX):
	@if [ ! -d $(MLXDIR) ] || [ ! -f $(MLX) ]; then \
		echo "MLX directory or library not found. Cloning and building..."; \
		rm -rf $(MLXDIR); \
		git submodule add $(MLX_URL) $(MLXDIR); \
		make -C $(MLXDIR); \
	else \
		echo "MLX library already exists. Skipping clone."; \
	fi

$(LIBFT): $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS) libft.h)
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(MLXDIR)
	git rm --cached $(MLXDIR)
	$(RM) $(OBJS) $(DEPS) $(MLX_SUBMODULE)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(MLXDIR)
	git rm --cached $(MLXDIR)
	$(RM) $(OBJS) $(NAME) $(MLX_SUBMODULE) $(DEPS)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug
