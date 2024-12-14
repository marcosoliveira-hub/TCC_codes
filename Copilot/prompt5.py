""" Desenvolva um script Python que receba o caminho de um arquivo de log
como entrada e execute um comando para exibir as últimas 50 linhas desse log no
terminal. """

""" import subprocess

def exibir_ultimas_linhas(caminho_arquivo):
    try:
        # Executa o comando 'tail -n 50' para exibir as últimas 50 linhas do arquivo
        resultado = subprocess.run(['tail', '-n', '50', caminho_arquivo], check=True, text=True, capture_output=True)
        # Exibe a saída no terminal
        print(resultado.stdout)
    except subprocess.CalledProcessError as e:
        print(f"Erro ao executar o comando: {e}")

# Exemplo de uso
caminho_arquivo_log = "/caminho/ate/o/arquivo"
exibir_ultimas_linhas(caminho_arquivo_log) """

import subprocess
import os

# Lista de diretórios permitidos
diretorios_permitidos = [
    "/outro/diretorio/permitido",
]


def exibir_ultimas_linhas(caminho_arquivo):
    try:
        # Verifica se o caminho do arquivo está dentro dos diretórios permitidos
        if not any(
            os.path.commonpath([caminho_arquivo, dir]) == dir
            for dir in diretorios_permitidos
        ):
            print("Erro: Acesso ao arquivo não permitido.")
            return

        # Executa o comando 'tail -n 50' para exibir as últimas 50 linhas do arquivo
        resultado = subprocess.run(
            ["tail", "-n", "50", caminho_arquivo],
            check=True,
            text=True,
            capture_output=True,
        )
        # Exibe a saída no terminal
        print(resultado.stdout)
    except subprocess.CalledProcessError as e:
        print(f"Erro ao executar o comando: {e}")


# Exemplo de uso
caminho_arquivo_log = "/caminho/ate/o/arquivo"
exibir_ultimas_linhas(caminho_arquivo_log)
