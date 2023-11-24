from __future__ import print_function
import os
import grpc
import argparse

import serverProcedures_pb2
import serverProcedures_pb2_grpc

DEBUG = 0

def run(service):
    channel = grpc.insecure_channel(service)
    stub = serverProcedures_pb2_grpc.centralServerStub(channel)

    while True:
        try:
            command = input().strip().split(',', maxsplit=2)
        except EOFError:
            break

        # Search for a key using a central server
        if command[0] == 'C':
            # Get parameters
            key = int(command[1])

            # Call the central server searching for which server has the key
            response = stub.mapping(serverProcedures_pb2.mappingInput(key=key))
            response = response.retval

            if DEBUG: print(f"Servidor Central Resposta: {response}")

            # if a per to per server have the key
            if not (response == ""):
                s =  response + ":"
                server_par_channel = grpc.insecure_channel(response)
                server_par_stub = serverProcedures_pb2_grpc.ProceduresStub(server_par_channel)
        
                response = server_par_stub.search(serverProcedures_pb2.searchInput(key=key))
                response = response.retval
                
                s = s + response
                if DEBUG: print(f"Servidor Par-Par Resposta: {response}")
                else: print(s)  
            else:
                print("")

        
        elif command[0] == 'T':
            response = stub.termination(serverProcedures_pb2.terminationInput())
            response = response.retval
            
            print(response)
            break



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Start a client with a service identification")
    parser.add_argument("service", type=str, help="service identification")

    args = parser.parse_args()
    run(args.service)

