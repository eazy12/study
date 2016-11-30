import socket
import random
import os
import subprocess
import time
questions = [
    ["Дата создания с++","1950","1960","1970","1980"],
    ["Дата создания java","1950","1960","1970","1980"],
    ["Дата создания python","1950","1960","1970","1980"],
    ["Дата создания javascript","1950","1960","1970","1980"],
    ["Дата создания Lua","1950","1960","1970","1980"]
]
random.shuffle(questions)
os.system("touch pyt.py")
f = open('pyt.py', 'w')

sock = socket.socket()
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 9081))
sock.listen(1)
conn, addr = sock.accept()

try:
    print('connected:', addr)

    data = conn.recv(1024)
    i=0

    if data.decode('utf-8') == "Готов":
        while(i<1):
            for k in range(0,5):
                conn.send(bytes(questions[i][k],encoding = 'utf-8'))
                time.sleep(0.3)
            answer = conn.recv(1024)
            answer = answer.decode('utf-8')
            print(answer)
            i=i+1
        else:
            conn.send(bytes("LUL",encoding = 'utf-8'))
            program = conn.recv(1024)
            program = program.decode('utf-8')
            f.write(program)
            f.close()
            process = subprocess.check_output("python3 pyt.py", stderr = subprocess.STDOUT, shell=True)
            process = process[:-1]
            print(process)
            #conn.send(bytes(process, encoding = 'utf-8'))
            conn.send(process)
    else:
        pass
    conn.close()
except KeyboardInterrupt:
    print("Error ctrl+с")
    conn.close()
except subprocess.CalledProcessError as err:
    print(err.output)
    conn.send(err.output)
    conn.close()
except:
    print("except block")
    conn.close()
finally:
    conn.close()
