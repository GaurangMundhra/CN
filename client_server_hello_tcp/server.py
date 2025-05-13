import socket #Create a socket.
s = socket.socket()  
print('socket created')  
s.bind(('localhost', 9999)) 
 
s.listen(3) 
 
print("waiting for connection")  
while True: 
    c, addr = s.accept() 
    
    name = c.recv(1024).decode()     
    print("connected with", addr, name) 
    
    c.send(bytes('Hello World', 'utf-8'))     
    c.close() 

# What is Socket Programming?
# It’s a way to allow programs to communicate over a network (either local or internet) using a programming interface called a socket.

# Types of Sockets:

# TCP (SOCK_STREAM): Connection-oriented, reliable, ordered.

# UDP (SOCK_DGRAM): Connectionless, faster, unreliable.

# socket(): Create a socket.

# bind(): Bind socket to IP & Port.

# listen(): Listen for incoming connections.

# accept(): Accept connection.

# connect(): Client requests connection.

# send(): Send data.

# recv(): Receive data.

# close(): Close connection.