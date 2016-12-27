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

#подключение к БД
connection2db = sqlite3.connect('database.db')
cursor = connection2db.cursor()
#создание промежуточного файла
os.system("touch pyt.py")
f = open('pyt.py', 'w')

# создание сокета
sock = socket.socket()
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 9079))
sock.listen(3)

# функция авторизации
def autorize():
    global idd # id, нужно для записи оценок
    b = False
    while( b!=True):
        # получаем логин и пароль
        login = conn.recv(1024).decode('utf-8')
        password = conn.recv(1024).decode('utf-8')

        if(login=="" and password==""):
            continue
        # выполняем запрос
        cursor.execute('select password, whoIsIt, id from users where secondName =?', (login,))
        # считываем результат
        queryResult = cursor.fetchall()
        # проверяем результат запроса
        if queryResult == []:
            conn.send(bytes('Неверный логин',encoding = 'utf-8'))
            continue
        elif(password != queryResult[0][0]):
            conn.send(bytes('Неверный пароль',encoding = 'utf-8'))
            continue
        else:
            conn.send(bytes('Верный пароль',encoding = 'utf-8'))
            b = True
            idd = queryResult[0][2]

# функция теста и лабы
def work():
    while(True):
        # считываем тип работы
        workType = conn.recv(1024).decode('utf-8')
        if( workType == ""):
            continue
        if workType == "end":
            workType = ""
            break
        elif workType == "test":
            # если тест
            workType = ""
            # случайные 5 записей ( это наш тест )
            cursor.execute('SELECT * FROM questions WHERE question IN (SELECT question FROM questions ORDER BY RANDOM() LIMIT 5)')
            connection2db.commit()
            # считываем результат
            rez = cursor.fetchall()
            # сериализуем тест
            rez= pickle.dumps(rez)
            # отправляем
            conn.send(rez)
            # получаем результат теста
            testRes = conn.recv(4096)
            testRes = pickle.loads(testRes)
            # считаем оценку
            Ocenka = 0
            for i in testRes:
                if i == 1:
                    Ocenka+=1
            # записываем оценку
            cursor.execute("UPDATE marks SET mark=? WHERE id=? AND workType='test'; ", (Ocenka,idd))
            connection2db.commit()
            # отправляем оценку на клиент
            conn.send(bytes(str(Ocenka),encoding = 'utf-8'))
        elif workType == "labwork":
            # если лабораторная работа
            workType = ""
            while(True):
                # считываем программу
                prog = conn.recv(4096)
                prog = pickle.loads(prog)
                # вариант выхода из лабораторной работы
                if(prog=="endd"):
                    break
                # запись в промежуточный файл
                f = open('pyt.py', 'w')
                f.write(prog)
                f.close()
                # выполнение программы
                proc = subprocess.Popen(
                    "python3 pyt.py",
                    shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE
                )
                # получаем результат
                res = proc.communicate()
                # если ошибка, то посылаем ошибку
                if proc.returncode:
                    conn.send(res[1])
                # если нет ошибки, то посылаем вывод программы
                else:
                    conn.send(res[0])
    # закрываем соединение
    conn.close()

try:
    while(True):
        # подлючение через сокет
        conn, addr = sock.accept()
        print('connected:', addr)
        # ждем авторизацию
        autorize()
        # студент работает
        work()

# исключения
except KeyboardInterrupt:
    print("Error ctrl+с")
    conn.close()
except:
    print("except block")
    conn.close()
finally:
    conn.close()
