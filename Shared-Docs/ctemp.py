import socket
msg = b'20003ori'
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 8876)
sock.connect(server_address)
sock.sendall(msg)
server_msg = sock.recv(1024)
print (server_msg)
msg = b'i have i file txt'
sock.sendall(msg)
server_address = sock.recv(1024)

sock.close()	