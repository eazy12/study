import socket
import random
import os
import sys
import subprocess
import time
b = False
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
sock.bind(('', 9091))
sock.listen(1)
conn, addr = sock.accept()
try:
    print('connected:', addr)

    data = conn.recv(1024)
    i=0
    if data.decode('utf-8') == "Готов":
        while(i<5):
            #conn.send(bytes(questions[i][0],encoding = 'utf-8'))
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
            f.write(program+"\n")
            f.close()
            process = subprocess.check_output("python3 pyt.py", shell=True)
            print(process)
            conn.send(bytes(process, encoding = 'utf-8'))
            conn.send(process)
    else:
        pass
    if b == False:
        conn.close()
        b = True
except KeyboardInterrupt:
    print("Error ctrl+с")
    if b == False:
        conn.close()
        b = True
#except:
    #print("except block")
    #conn.close()
    #os.system("rm pyt.py")
finally:
    if b == False:
        conn.close()
        b = True
