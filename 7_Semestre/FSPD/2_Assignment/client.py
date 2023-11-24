from __future__ import print_function
import os
import grpc
import argparse

import serverProcedures_pb2
import serverProcedures_pb2_grpc

# Variavel utilizada para controlar o nível de detalhe do output
DEBUG = 0

def run(service):
    channel = grpc.insecure_channel(service)
    stub = serverProcedures_pb2_grpc.ProceduresStub(channel)

    while True:
        try:
            command = input().strip().split(',', maxsplit=2)
        except EOFError:
            break

        # Insert the key in the server
        if command[0] == 'I':
            # Get the parameters
            key = int(command[1])
            description = command[2]

            # Call the function
            response = stub.insert(serverProcedures_pb2.insertInput(key=key, description=description))
            response = int(response.retval)

            if(DEBUG): print(f"Server response: {response}")
            else: print(response)
        
        # Search for a key in the server
        elif command[0] == 'C':
            # Get the parameters
            key = int(command[1])

            # Call the function
            response = stub.search(serverProcedures_pb2.searchInput(key=key))
            response = response.retval
            
            if(DEBUG): print(f"Server response: {response}")
            else: print(response)
        
        # Tell the server to register its keys
        elif command[0] == 'A':
            # Get the parameters
            id = command[1]

            # Call the function
            response = stub.activation(serverProcedures_pb2.activationInput(id=id))
            response = int(response.retval)
            
            if(DEBUG): print(f"Server Activation: {response}")
            else: print(response)
        
        # Tell the server to terminate
        elif command[0] == 'T':
            # Call the function
            response = stub.termination(serverProcedures_pb2.terminationInput())
            response = response.retval
            
            print(response)
            break



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Start a client with a service identification")
    parser.add_argument("service", type=str, help="service identification")

    args = parser.parse_args()
    run(args.service)

