# сокеты
import socket
#работа с ОС. Используется для создания файла
import os
# Для выдачи ошибок
import subprocess
# Для задежки
import time
# Работа с бд
import sqlite3
# Сериализация
import pickle

connection2db = sqlite3.connect('database.db')
cursor = connection2db.cursor()
os.system("touch pyt.py")
f = open('pyt.py', 'w')

sock = socket.socket()
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 9082))
sock.listen(1)
conn, addr = sock.accept()

try:
    print('connected:', addr)
    b = False

    while( b!=True):
        login = conn.recv(1024).decode('utf-8')
        password = conn.recv(1024).decode('utf-8')

        cursor.execute('select password, whoIsIt from users where secondName =?', (login,))
        queryResult = cursor.fetchall()

        if queryResult == []:
            conn.send(bytes('Неверный логин',encoding = 'utf-8'))
        elif(password != queryResult[0][0]):
            conn.send(bytes('Неверный пароль',encoding = 'utf-8'))
        else:
            conn.send(bytes('Верный пароль',encoding = 'utf-8'))
            b = True

    workType = conn.recv(1024).decode('utf-8')

    if workType == "test":
        cursor.execute('SELECT * FROM questions WHERE question IN (SELECT question FROM questions ORDER BY RANDOM() LIMIT 5)')
        connection2db.commit()

        aaa = cursor.fetchall()
        print(cursor)
        cursor1 = pickle.dumps(aaa)
        conn.send(cursor1)

        qqq = conn.recv(4096)
        aaaa = pickle.loads(qqq)
        print(aaaa)
        Ocenka =0
        for i in aaaa:
            if i == 1:
                Ocenka+=1
        print(Ocenka)
    elif workType == "labwork":
        pass
    else:
        print("error argument")

    conn.close()
except KeyboardInterrupt:
    print("Error ctrl+с")
    conn.close()
except subprocess.CalledProcessError as err:
    print(err.output)
    conn.send(err.output)
    conn.close()
# except:
#     print("except block")
#     conn.close()
finally:
    conn.close()
