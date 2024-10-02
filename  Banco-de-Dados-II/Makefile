# Makefile simplificado para o projeto investimentos-dashboard

# Variáveis
PYTHON = python3.11
VENV_DIR = .venv
REQ_FILE = requirements.txt
MAIN_FILE = main.py

# Executa o arquivo main.py (pipeline principal)
run: 
	@echo "Executando o pipeline (main.py)..."
	python $(MAIN_FILE)

# Inicializa o ambiente virtual e instala as dependências
init:
	@echo "Criando ambiente virtual..."
	$(PYTHON) -m venv $(VENV_DIR)

# Ativa o ambiente virtual (apenas para exibir uma mensagem)
activate:
	@echo "Para ativar o ambiente virtual, use o comando:"
	@echo "source $(VENV_DIR)/bin/activate"

install: 
	@echo "Instalando dependências..."
	pip install -r $(REQ_FILE)

# Limpa o ambiente virtual
clean-venv:
	@echo "Limpando o ambiente virtual..."
	rm -rf $(VENV_DIR)

# Reinstala o ambiente virtual e dependências
reinstall: clean-venv init
