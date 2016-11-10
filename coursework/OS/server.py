import socket
import random
import os
import sys
import subprocess

questions = [
    ["Дата создания с++","1950","1960","1970","1980"],
    ["Дата создания java","1950","1960","1970","1980"],
    ["Дата создания python","1950","1960","1970","1980"],
    ["Дата создания javascript","1950","1960","1970","1980"],
    ["Дата создания Lua","1950","1960","1970","1980"]
]
os.system("touch pyt.py")
f = open('pyt.py', 'w')
random.shuffle(questions)

sock = socket.socket()
sock.bind(('', 9090))
sock.listen(1)
conn, addr = sock.accept()
try:
    print('connected:', addr)

    data = conn.recv(1024)
    i=0
    if data.decode('utf-8') == "Готов":
        while(i<5):
            conn.send(bytes(questions[i][0],encoding = 'utf-8'))
            answer = conn.recv(1024)
            print(answer)
            if answer :
                i+=1
        else:
            conn.send(bytes("LUL",encoding = 'utf-8'))
            program = conn.recv(1024)
            program = program.decode('utf-8')
            f.write(program+"\n")
            f.close()
            process = subprocess.check_output("python3 pyt.py", shell=True)
            print("1")
            print(process)
            print("2")
            #conn.send(bytes(process,encoding = 'utf-8'))
            conn.send(process)
    else:
        pass
except KeyboardInterrupt:
    print("Error ctrl+с")
    conn.close()
except:
    conn.close()
finally:
    pass
    #os.system("rm pyt.py")
