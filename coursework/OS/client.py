import socket
import time

sock = socket.socket()
sock.connect(('localhost', 9090))
print(r"Введите Готов для начала контрольной работы")
try:
    s = input()
    sock.send(bytes(s,encoding = 'utf-8'))

    while(True):
        data = sock.recv(1024)
        data = data.decode('utf-8')
        if data == "LUL":
            break
        print(data)
        s = input()
        sock.send(bytes(s,encoding = 'utf-8'))

    print("Введите программу HelloWorld на python")
    kek = input()
    sock.send(bytes(kek,encoding = 'utf-8'))
    result = sock.recv(1024)
    result= result.decode('utf-8')
    print(result, end = "")
    print("Тест закончен")
except KeyboardInterrupt:
    print("Error ctrl+z")
finally:
    print("End")
    sock.close()
