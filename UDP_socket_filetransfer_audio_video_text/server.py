import socket

BUFFER_SIZE = 70000
PORT = 8000

def receive_file(sock, client_addr):
    file_name, _ = sock.recvfrom(1024)
    file_name = file_name.decode()

    print(f"Receiving '{file_name}'...")

    data, _ = sock.recvfrom(BUFFER_SIZE)

    # Add prefix to file name
    new_file_name = f"received_{file_name}"

    with open(new_file_name, 'wb') as f:
        f.write(data)

    print(f"'{new_file_name}' received successfully.\n")


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('0.0.0.0', PORT))

    print("UDP Server is running and waiting for file...")

    while True:
        choice_data, client_addr = sock.recvfrom(1024)
        choice = int.from_bytes(choice_data, byteorder='big')

        if choice in [1, 2, 3]:
            receive_file(sock, client_addr)
        elif choice == 4:
            print("Shutting down server.")
            break

    sock.close()

if __name__ == "__main__":
    main()


# Concept	Use in Code
# UDP Socket	Fast, connectionless communication (SOCK_DGRAM)
# sendto() / recvfrom()	For sending/receiving data with client-server addresses
# File Handling (binary)	For transferring any type of file
# Choice-based Control	Client chooses file type; server handles accordingly
# File Prefix on Server	Added via string manipulation in filename