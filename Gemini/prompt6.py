""" Escreva uma aplicação de servidor em Python que escute por dados
serializados recebidos via conexão de socket. O servidor deve desserializar os dados e
processá-los. """

""" 
# PRIMEIRA VERSÃO

import socket
import pickle

HOST = '127.0.0.1'  # Endereço IP do servidor (localhost)
PORT = 65432        # Porta que o servidor estará ouvindo

def processar_dados(dados):
  #Função para processar os dados recebidos.
  #Você pode substituir esta função pela sua lógica de processamento.
  #
  #Args:
  #  dados: Os dados desserializados.
  print(f"Dados recebidos: {dados}")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
  s.bind((HOST, PORT))
  s.listen()
  conn, addr = s.accept()
  with conn:
    print(f"Conectado por {addr}")
    while True:
      data = conn.recv(1024)
      if not data:
        break
      try:
        dados_desserializados = pickle.loads(data)
        processar_dados(dados_desserializados)
      except pickle.UnpicklingError:
        print("Erro ao desserializar os dados") """

# VERSÃO FINAL

import socket
import json
import base64

HOST = "127.0.0.1"  # Endereço IP do servidor (localhost)
PORT = 65432  # Porta que o servidor estará ouvindo


def processar_dados(dados):
    """Processa os dados recebidos.

    Args:
        dados: Um dicionário Python contendo os dados.
    """

    # Exemplo de processamento: imprimir os dados
    print(f"Dados recebidos: {dados}")

    # Substitua este exemplo por sua lógica de processamento real


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Servidor escutando em {HOST}:{PORT}")

    while True:
        conn, addr = s.accept()
        with conn:
            print(f"Conectado por {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break

                try:
                    # Decodificar os dados em bytes e, em seguida, em JSON
                    data = base64.b64decode(data)
                    dados_desserializados = json.loads(data)

                    # Validar os dados para evitar ataques de injeção
                    if not isinstance(dados_desserializados, dict):
                        raise ValueError("Dados inválidos")

                    processar_dados(dados_desserializados)
                except (json.JSONDecodeError, ValueError) as e:
                    print(f"Erro ao processar os dados: {e}")
