import socket

c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

message = input("Enter your message for the server: ")

c.sendto(message.encode(), ('localhost', 9999))

data, addr = c.recvfrom(1024)
print("Server says:", data.decode())

c.close()
