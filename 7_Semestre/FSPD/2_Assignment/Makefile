# Variables
SVC_PAR = server.py
CLN_PAR = client.py
SVC_CEN = central_server.py
CLN_CEN = central_client.py

all:
	python -m grpc_tools.protoc -I. --python_out=. --pyi_out=. --grpc_python_out=. ./gRPC/part_1/serverProcedures.proto

# Rules
clean:
	rm -f $(SVC_PAR) $(CLN_PAR) $(SVC_CEN) $(CLN_CEN)

# executa o programa cliente da primeira parte
run_cli_pares:
	python3 $(CLN_PAR) $(arg)

# executa o programa servidor de pares com o comportamento da primeira parte (ativação não faz nada)
run_serv_pares_1:
	python3 $(SVC_PAR) $(arg)

# executa o programa servidor de pares com o comportamento da segunda parte 
# (ativação funciona com o servidor central identificado nos argumentos)
run_serv_pares_2:
	python3 $(SVC_PAR) $(arg) qqcoisa

# executa o programa servidor central da segunda parte
run_serv_central:
	python3 $(SVC_CEN) $(arg)

# executa o programa cliente da segunda parte
run_cli_central:
	python3 $(CLN_CEN) $(arg)




