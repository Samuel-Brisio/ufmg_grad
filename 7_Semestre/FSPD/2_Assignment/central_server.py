from concurrent import futures
import argparse
import grpc
import threading

import serverProcedures_pb2
import serverProcedures_pb2_grpc

# Register the per to per server address connected
servers = []

# A dictory that save the content that each server have
# The key is content
# The value is the server that have this content
serversContent = {}

def server(port):
    stop_event = threading.Event()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    serverProcedures_pb2_grpc.add_centralServerServicer_to_server(Procedures(stop_event), server)
    server.add_insecure_port(f"0.0.0.0:{port}")
    server.start()
    stop_event.wait()
    server.stop(grace=5)
    # server.wait_for_termination()

class Procedures(serverProcedures_pb2_grpc.ProceduresServicer):
    def __init__(self, stop_event):
        self._stop_event = stop_event

    def register(self, request, context):
        identification = request.id
        keys = []

        for key in request.values:
            keys.append(key) 

        # if is the first time that per to per server connect
        if identification not in servers:
            servers.append(identification)

        # This step dont need a verification
        # Because with a server is trying to register key already registered
        # We can overwrite the old value
        for key in keys:
            serversContent[key] = identification

        # Return the number of keys registred
        return serverProcedures_pb2.terminationOutput(retval=len(keys))
        
    def mapping(self, request, context):
        key = request.key

        # if the key exist
        if key in serversContent:
            # return the server that contain that key
            return serverProcedures_pb2.searchOutput(retval=serversContent[key])
        
        # if the key not exist
        # return a empty string
        return serverProcedures_pb2.searchOutput(retval="")

    def termination(self, request, context):
        self._stop_event.set()
        return serverProcedures_pb2.terminationOutput(retval=len(serversContent))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Start a server with port number")
    parser.add_argument('port', type=int,  help="Port number for the server")

    args = parser.parse_args()
    server(args.port)

