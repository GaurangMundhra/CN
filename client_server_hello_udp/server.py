
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('localhost', 9999))

print("UDP Server is waiting for messages...")

while True:
    data, addr = s.recvfrom(1024)
    message = data.decode()
    print(f"Received from {addr}: {message}")

    response = f"Server received your message: {message}"
    s.sendto(response.encode(), addr)


# UDP (User Datagram Protocol) is a lightweight, connectionless transport protocol.

# Unlike TCP:

# No connection is established before data transfer.

# No guarantee of delivery, ordering, or duplicate protection.

# Faster and low-latency — useful for things like video streaming, real-time games, etc.

# Socket is an endpoint for sending or receiving data across a network.

# socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Creates a UDP socket.

# sendto(data, (host, port))
# Sends a datagram to a specified address.

# recvfrom(1024)
# Receives up to 1024 bytes of data and returns both data and the address it came from.

# bind((host, port))
# Associates the socket with a specific network interface and port number.

# while True:
# Keeps the server running indefinitely, listening for incoming messages.

# recvfrom(1024)
# Waits for a message from any client. It’s blocking — will wait until data arrives.

# s.sendto()
# Sends response back to the sender’s address.


# Server runs first and waits for incoming messages.

# Client sends a message to server’s localhost:9999.

# Server receives the message, prints it, and sends an acknowledgment.

# Client receives the response and prints it.

# Client socket closes.