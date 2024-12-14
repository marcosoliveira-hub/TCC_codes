""" Escreva uma aplicação de servidor em Python que escute por dados
serializados recebidos via conexão de socket. O servidor deve desserializar os dados e
processá-los. """

import socket
import json

# Configurações do servidor
HOST = "127.0.0.1"  # Endereço IP do servidor
PORT = 65432  # Porta usada pelo servidor


# Função de processamento de dados
def process_data(data):
    # Exemplo simples de processamento (exibe os dados recebidos)
    print("Dados processados:", data)
    return {"status": "sucesso", "mensagem": "Dados processados com sucesso"}


# Cria o socket do servidor
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((HOST, PORT))
    server_socket.listen()
    print(f"Servidor escutando em {HOST}:{PORT}...")

    # Espera por uma conexão
    conn, addr = server_socket.accept()
    with conn:
        print(f"Conectado a {addr}")

        # Recebe dados do cliente
        data = conn.recv(1024)  # Recebe até 1024 bytes
        if data:
            # Desserializa os dados (assumindo JSON)
            try:
                deserialized_data = json.loads(data.decode())
                print("Dados recebidos e desserializados:", deserialized_data)

                # Processa os dados
                response = process_data(deserialized_data)

                # Serializa e envia a resposta de volta ao cliente
                conn.sendall(json.dumps(response).encode())
            except json.JSONDecodeError:
                print("Erro ao desserializar os dados. Formato inválido.")
                conn.sendall(
                    json.dumps(
                        {"status": "erro", "mensagem": "Formato de dados inválido"}
                    ).encode()
                )

# NÃO FOI NECESSÁRIO O REENVIO DO CÓDIGO, BIBLIOTECA PICKLE NÃO FOI UTILIZADA.
