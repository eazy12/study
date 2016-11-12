import socket
import time

sock = socket.socket()
sock.connect(('localhost', 9080))
print("Введите Готов для начала контрольной работы")
try:
    s = input()
    sock.send(bytes(s,encoding = 'utf-8'))

    while(True):
        data = sock.recv(1024)
        data = data.decode('utf-8')
        if data == "LUL":
            break
        print(data)
        
        
        data = sock.recv(1024)
        data = data.decode('utf-8')
        print(data)
                
        data = sock.recv(1024)
        data = data.decode('utf-8')
        print(data)
                
        data = sock.recv(1024)
        data = data.decode('utf-8')
        print(data)
        
        data = sock.recv(1024)
        data = data.decode('utf-8')
        print(data)
        
        rr = input()
        sock.send(bytes(rr,encoding = 'utf-8'))

    print("Введите программу HelloWorld на python")
    kek = input()
    sock.send(bytes(kek,encoding = 'utf-8'))
    result = sock.recv(1024)
    result = result.decode('utf-8')
    print("************ Результат выполнения программы ************")
    print(result, end = "\n")
    print("************ Результат выполнения программы ************")
    print("Тест закончен")
except KeyboardInterrupt:
    print("Error ctrl+z")
    sock.close()
finally:
    print("End")
    sock.close()
