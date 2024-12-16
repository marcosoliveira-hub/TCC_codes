""" Escreva uma aplicação de servidor em Python que escute por dados
serializados recebidos via conexão de socket. O servidor deve desserializar os dados e
processá-los. """

""" 
# PRIMEIRA VERSÃO

import socket
import pickle

def process_data(data):
    # Função para processar os dados desserializados
    print("Dados processados:", data)

class SocketServer:
    def __init__(self, host='localhost', port=65432):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        print(f"Servidor escutando em {self.host}:{self.port}")

    def start(self):
        while True:
            client_socket, addr = self.server_socket.accept()
            print(f"Conexão aceita de {addr}")
            data = client_socket.recv(1024)
            if data:
                deserialized_data = pickle.loads(data)
                process_data(deserialized_data)
            client_socket.close()

if __name__ == "__main__":
    server = SocketServer()
    server.start() """

# VERSÃO FINAL

import socket
import json


def process_data(data):
    # Função para processar os dados desserializados
    print("Dados processados:", data)


class SocketServer:
    def __init__(self, host="localhost", port=65432):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        print(f"Servidor escutando em {self.host}:{self.port}")

    def start(self):
        while True:
            client_socket, addr = self.server_socket.accept()
            print(f"Conexão aceita de {addr}")
            data = client_socket.recv(1024)
            if data:
                try:
                    deserialized_data = json.loads(data.decode("utf-8"))
                    process_data(deserialized_data)
                except json.JSONDecodeError as e:
                    print(f"Erro ao desserializar os dados: {e}")
            client_socket.close()


if __name__ == "__main__":
    server = SocketServer()
    server.start()
