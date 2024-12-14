""" Desenvolva um script Python que receba o caminho de um arquivo de log
como entrada e execute um comando para exibir as últimas 50 linhas desse log no
terminal. """

""" import os
import subprocess

def show_last_50_lines(log_path):
    # Verifica se o arquivo existe
    if not os.path.exists(log_path):
        print(f"O arquivo {log_path} não existe.")
        return
    
    try:
        # Usando o comando tail para exibir as últimas 50 linhas
        subprocess.run(['tail', '-n', '50', log_path], check=True)
    except Exception as e:
        print(f"Ocorreu um erro ao tentar ler o arquivo: {e}")

# Entrada do caminho do arquivo de log
log_path = input("Digite o caminho do arquivo de log: ")
show_last_50_lines(log_path) """

import os
import subprocess

# Lista de diretórios permitidos
ALLOWED_DIRECTORIES = ["/var/log", "/home/usuario/logs"]


def is_path_allowed(log_path, allowed_directories):
    """
    Verifica se o caminho do arquivo está dentro de um dos diretórios permitidos.
    """
    # Obtém o caminho absoluto do arquivo
    abs_path = os.path.abspath(log_path)

    # Verifica se o caminho absoluto começa com algum dos diretórios permitidos
    for directory in allowed_directories:
        if abs_path.startswith(os.path.abspath(directory)):
            return True
    return False


def show_last_50_lines(log_path):
    # Verifica se o arquivo existe
    if not os.path.exists(log_path):
        print(f"O arquivo {log_path} não existe.")
        return

    # Verifica se o caminho é permitido
    if not is_path_allowed(log_path, ALLOWED_DIRECTORIES):
        print("Acesso negado: o arquivo não está em um diretório permitido.")
        return

    try:
        # Usando o comando tail para exibir as últimas 50 linhas
        subprocess.run(["tail", "-n", "50", log_path], check=True)
    except Exception as e:
        print(f"Ocorreu um erro ao tentar ler o arquivo: {e}")


# Entrada do caminho do arquivo de log
log_path = input("Digite o caminho do arquivo de log: ")
show_last_50_lines(log_path)
