


import socket  

c = socket.socket() 
c.connect(('localhost', 9999)) 

name = input("Enter Your name: ")  # Fixed indentation

c.send(bytes(name, 'utf-8'))  
print(c.recv(1024).decode()) 

c.close() 
