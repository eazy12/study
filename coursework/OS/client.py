import socket
import time
from tkinter import *

class CClient:
    def __init__(self):

        self.b=True
        self.root=Tk()
        self.root.resizable(width=False, height=False)
        self.root.geometry("500x500")

        self.labelText = StringVar()
        self.labelText.set("Нажмите Готов")

        self.label0_0=Label(self.root, text="Здраствуйте", font='Times 14 bold italic')
        self.label0_1=Label(self.root, text="Логин", font='Times 14 bold italic')
        self.label0_2=Label(self.root, text="Пароль", font='Times 14 bold italic')
        self.label0_3=Label(self.root, text="Ошибка авторизации", font='Times 14 bold italic', fg="red")

        self.button0_0=Button(self.root,text="Авторизация",command=self.button0Command)

        self.entry0_0 = Entry(self.root, width= 15, font='Times 14 bold italic')
        self.entry0_1 = Entry(self.root, width= 15, font='Times 14 bold italic')


        self.label0_0.place(x=130,y=160)
        self.label0_1.place(x=80,y=185)
        self.label0_2.place(x=80,y=210)
        self.label0_3.place(x=90,y=265)
        self.entry0_0.place(x=200,y=185)
        self.entry0_1.place(x=200,y=210)
        self.button0_0.place(x=165, y=240)

        self.label0_3.place_forget()

        sock = socket.socket()
        sock.connect(('localhost', 9081))

    def stuff(self):
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
            print(result)
            print("************ Результат выполнения программы ************")
            print("Тест закончен")
        except KeyboardInterrupt:
            print("Error ctrl+z")
            sock.close()
        finally:
            print("End")
            sock.close()

    def button0Command(self):
    #Авторизация
        self.root1 = Tk()


        self.root.destroy()
        pass


ui = CClient()
ui.root.mainloop()
