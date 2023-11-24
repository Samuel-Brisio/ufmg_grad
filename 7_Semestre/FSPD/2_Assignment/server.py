from concurrent import futures
import argparse
import grpc
import threading
import socket

import serverProcedures_pb2
import serverProcedures_pb2_grpc

# Variavel utilizada para controlar o nível de detalhe do output
DEBUG = 0

# Armazena as chaves cadastradas no servidor
content = {}

def server(port, flag=None):
    stop_event = threading.Event()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    serverProcedures_pb2_grpc.add_ProceduresServicer_to_server(Procedures(stop_event, port), server)
    server.add_insecure_port(f"0.0.0.0:{port}")
    server.start()
    stop_event.wait()
    server.stop(grace=5)
    # server.wait_for_termination()


# Classe que implementa os funções definidas no arquivo proto
class Procedures(serverProcedures_pb2_grpc.ProceduresServicer):
    def __init__(self, stop_event, port, flag):
        self._stop_event = stop_event
        self.port = port
        self.flag = flag

    def insert(self, request, context):
        key = request.key
        description = request.description
        if (DEBUG): print(key, description)
        
        # if key is already inserted
        if key in content:
            return serverProcedures_pb2.insertOutput(retval=-1)
        
        # else
        # create the key
        content[key] = description
        return serverProcedures_pb2.insertOutput(retval=0)
            
    
    def search(self, request, context):
        key = request.key
        # if key exist, return its values
        if key in content:
            return serverProcedures_pb2.searchOutput(retval=content[key])
        # else return a empty string
        return serverProcedures_pb2.searchOutput(retval="")

    # Connect with central server to register its own keys
    def activation(self, request, context):
        if self.flag:
            # The client send the address of the central server
            centralServer = request.id
            # Connect with the central server
            channel = grpc.insecure_channel(centralServer)
            stub = serverProcedures_pb2_grpc.centralServerStub(channel)

            # Get server identification
            identification = socket.getfqdn()
            identification = f"{identification}:{self.port}"

            if(DEBUG): print(f"Server identification: {identification}")
            
            # register keys in the central server
            # Paramenters
            register_input = serverProcedures_pb2.registerInput()
            register_input.id = identification
            register_input.values.extend(list(content.keys()))

            # response from the central server
            response = stub.register(register_input)
            response = int(response.retval)
            
            # return the number of keys registred in the central server
            return serverProcedures_pb2.registerOutput(retval=response)

    # Send a command to end the server
    def termination(self, request, context):
        self._stop_event.set()
        return serverProcedures_pb2.terminationOutput(retval=0)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Start a server with optional flag")
    parser.add_argument('port', type=int,  help="Port number for the server")
    parser.add_argument('flag', nargs='?', help="Optional flag")

    args = parser.parse_args()
    server(args.port, args.flag)

