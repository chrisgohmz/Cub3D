CFLAGS = -g -Wall -Wextra -Werror -MMD -MP -Ofast -pedantic
LDFLAGS = -Llibft -L$(MLXDIR) -L/usr/lib
LDLIBS = -lft -lmlx_Linux -lXext -lX11 -lm -lz 

SRCS_DIR = srcs/
PARSING_DIR = $(SRCS_DIR)parsing/
RENDERING_DIR = $(SRCS_DIR)rendering/

SRCS = $(addprefix $(SRCS_DIR), main.c events.c free.c game_loop.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

PARSING_SRCS = $(addprefix $(PARSING_DIR), elements_utils.c elements.c parsing.c load_doors_enemies.c\
		floor_ceiling.c map_utils.c map.c load_textures.c)
PARSING_DEPS = $(PARSING_SRCS:.c=.d)
PARSING_OBJS = $(PARSING_SRCS:.c=.o)

RENDERING_SRCS = $(addprefix $(RENDERING_DIR), render_map.c render_map_cells.c drawing_grid_lines.c drawing_player.c drawing_rays.c door.c\
		 ray_casting.c scene.c scene_utils1.c scene_utils2.c scene_utils3.c image.c sprite.c sprite_utils1.c sprite_utils2.c sprite_utils3.c)
RENDERING_DEPS = $(RENDERING_SRCS:.c=.d)
RENDERING_OBJS = $(RENDERING_SRCS:.c=.o)

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

debug: CFLAGS += -g -Og
debug: all

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(PARSING_OBJS) $(RENDERING_OBJS)
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
	$(RM) $(OBJS) $(DEPS) $(MLX_SUBMODULE) $(PARSING_OBJS) $(PARSING_DEPS) $(RENDERING_OBJS) $(RENDERING_DEPS)

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(MLXDIR)
	git rm --cached $(MLXDIR)
	$(RM) $(OBJS) $(NAME) $(MLX_SUBMODULE) $(DEPS) $(PARSING_OBJS) $(PARSING_DEPS) $(RENDERING_OBJS) $(RENDERING_DEPS)

re: fclean all

-include $(DEPS) $(PARSING_DEPS) $(RENDERING_DEPS)

.PHONY: all clean fclean re debug
