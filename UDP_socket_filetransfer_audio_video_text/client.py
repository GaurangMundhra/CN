import socket
import os

BUFFER_SIZE = 70000
SERVER_IP = '127.0.0.1'
PORT = 8000

def send_file(sock, file_path, server_address):
    if not os.path.isfile(file_path):
        print("File does not exist.")
        return

    file_name = os.path.basename(file_path)
    with open(file_path, 'rb') as f:
        data = f.read()

    sock.sendto(file_name.encode(), server_address)
    sock.sendto(data, server_address)

    print(f"'{file_name}' sent successfully.\n")

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = (SERVER_IP, PORT)

    while True:
        print("Enter choice:\n 1. Text File\n 2. Audio File\n 3. Video File\n 4. Exit")
        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("Invalid input. Try again.")
            continue

        sock.sendto(choice.to_bytes(4, byteorder='big'), server_address)

        if choice in [1, 2, 3]:
            file_path = input("Enter file path to send: ")
            send_file(sock, file_path, server_address)
        elif choice == 4:
            print("Exiting client.")
            break
        else:
            print("Invalid choice. Try again.")

    sock.close()

if __name__ == "__main__":
    main()
