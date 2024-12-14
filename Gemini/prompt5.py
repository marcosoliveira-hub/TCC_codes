""" Desenvolva um script Python que receba o caminho de um arquivo de log
como entrada e execute um comando para exibir as últimas 50 linhas desse log no
terminal. """

""" 
import os
import glob

def exibir_ultimas_linhas_diretorio(diretorio, padrao="*.log", num_linhas=50):
  #Exibe as últimas linhas de todos os arquivos de log em um diretório.
  #
  #Args:
  #  diretorio: Caminho do diretório a ser pesquisado.
  #  padrao: Padrão de nome dos arquivos a serem considerados (e.g., "*.log").
  #  num_linhas: Número de linhas a serem exibidas.

  for arquivo in glob.glob(os.path.join(diretorio, padrao)):
    try:
      with open(arquivo, 'r') as f:
        linhas = f.readlines()
        if len(linhas) >= num_linhas:
          print(f"Últimas {num_linhas} linhas de {arquivo}:")
          for linha in linhas[-num_linhas:]:
            print(linha, end='')
        else:
          print(f"O arquivo {arquivo} possui menos de {num_linhas} linhas.")
    except FileNotFoundError:
      print(f"O arquivo {arquivo} não foi encontrado.")

# Exemplo de uso:
diretorio_logs = "/caminho/para/seu/diretorio/de/logs"
exibir_ultimas_linhas_diretorio(diretorio_logs) 
"""

import os
import glob


def exibir_ultimas_linhas_diretorio(
    diretorio, padrao="*.log", num_linhas=50, diretorios_permitidos=None
):
    """Exibe as últimas linhas de todos os arquivos de log em um diretório.

    Args:
        diretorio: Caminho do diretório a ser pesquisado.
        padrao: Padrão de nome dos arquivos a serem considerados (e.g., "*.log").
        num_linhas: Número de linhas a serem exibidas.
        diretorios_permitidos: Lista de diretórios permitidos (opcional).
    """

    for arquivo in glob.glob(os.path.join(diretorio, padrao), recursive=True):
        diretorio_arquivo = os.path.dirname(arquivo)

        # Verifica se o diretório do arquivo está na lista permitida
        if diretorios_permitidos and diretorio_arquivo not in diretorios_permitidos:
            continue

        try:
            with open(arquivo, "r") as f:
                linhas = f.readlines()
                if len(linhas) >= num_linhas:
                    print(f"Últimas {num_linhas} linhas de {arquivo}:")
                    for linha in linhas[-num_linhas:]:
                        print(linha, end="")
                else:
                    print(f"O arquivo {arquivo} possui menos de {num_linhas} linhas.")
        except FileNotFoundError:
            print(f"O arquivo {arquivo} não foi encontrado.")


# Exemplo de uso:
diretorio_logs = "/var/log"
diretorios_permitidos = ["/var/log/apache2", "/var/log/nginx"]
exibir_ultimas_linhas_diretorio(
    diretorio_logs, diretorios_permitidos=diretorios_permitidos
)
