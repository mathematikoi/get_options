NAME = get_options.a

SOURCES =	get_options.c \
			parser.c \
			setters.c \
			utilities.c

OBJECTS = $(SOURCES:.c=.o)

SOURCES_DIR = sources
OBJECTS_DIR = build
INCLUDES = includes

SOURCES_PATH = $(addprefix $(SOURCES_DIR)/, $(SOURCES))
OBJECTS_PATH = $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJECTS_PATH)
	ar rc $(NAME) $(OBJECTS_PATH)
	ranlib $(NAME)

$(OBJECTS_PATH): $(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c | $(OBJECTS_DIR)
	gcc $(FLAGS) -I$(INCLUDES) -c $< -o $@

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean | all