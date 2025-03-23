DIR_TO_REMOVE = build

all: clean mkdir build_dir 

install: clean mkdir build_dir

clean:
	@if [ -d $(DIR_TO_REMOVE) ]; then \
		echo "Удаление директории $(DIR_TO_REMOVE)..."; \
		rm -rf $(DIR_TO_REMOVE); \
	else \
		echo "Директория $(DIR_TO_REMOVE) не существует."; \
	fi

mkdir:
	mkdir -p $(DIR_TO_REMOVE)

build_dir: 
	@echo "Сборка проекта в директории $(DIR_TO_REMOVE)..."
	@cd $(DIR_TO_REMOVE) && cmake .. && make