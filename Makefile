CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIBS = -lncursesw
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
EXEC = $(BUILD_DIR)/scp

#===LISTA DE ARQUIVOS===
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

#====================================================
#====REGRAS PRINCIPAIS====
#=====================================================

#Regra padrão (Executada quando rodamos apenas o "make")
all: dirs $(EXEC)
	@echo "Compilação concluida com sucesso!"

#Cria o driretorio build caso ele não exista
dirs:
	@mkdir -p $(BUILD_DIR)

#Como gerar o executavel apartir dos objetos
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LIBS)

#Como  gerar cada arquivo .o (objeto) a partir de um .c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#Limpa arquivos compilados
clean:
	rm -rf $(BUILD_DIR)
	@echo "Limpeza feita com sucesso"

#Executa o programa (depois de compilar)
run: all
	@echo "Executando o Sistema de Controle de Pedidos..."
	@$(EXEC)

#Mostra ajuda
help:
	@echo "Comandos disponíveis:"
	@echo " make 		→ compila o projeto"
	@echo " make run → compila e executa"
	@echo " make clean → remove arquivos compilados"
	@echo " make help → mostra esta ajuda"
.PHONY: all clean run help dirs


