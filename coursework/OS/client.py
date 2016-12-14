# todo:

import socket
import time
from tkinter import *

class CClient:
    def __init__(self):

        self.b=True
        self.root=Tk()
        #self.root1 = Tk()
        #self.root1.withdraw()
        self.root.resizable(width=False, height=False)
        self.root.geometry("500x500")
        #self.root1.geometry("500x500")

        self.labelText = StringVar()
        self.labelText.set("Нажмите Готов")

        self.label0_0=Label(self.root, text="Здраствуйте", font='Helvetica 14 bold ')
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
        self.root1.geometry("500x500")
        self.label1_0=Label(self.root1, text="Итоговый тест", font='Times 14 bold italic')
        self.label1_1=Label(self.root1, text="Лабораторная \n работа", font='Times 14 bold italic')

        self.button1_0=Button(self.root1,text="Пройти",command=self.button1Command)
        self.button1_1=Button(self.root1,text="Пройти",command=self.button2Command)

        self.button1_0.place(x = 350, y = 120)
        self.button1_1.place(x = 350, y = 200)

        self.label1_0.place(x = 40, y = 120)
        self.label1_1.place(x = 40, y = 200)



        #self.root1.deiconify()
        self.root.destroy()
        self.root1.mainloop()


    def button1Command(self):
        self.root1.withdraw()
        self.root2 = Tk()
        v1 = StringVar()
        question1 = StringVar()
        v1.set("1")
        question1.set("How do you do?")

        v2 = StringVar()
        question2 = StringVar()
        v2.set("1")
        question2.set("How do you do?")

        v3 = StringVar()
        question3 = StringVar()
        v3.set("1")
        question3.set("How do you do?")

        v4 = StringVar()
        question4 = StringVar()
        v4.set("1")
        question4.set("How many fingers you see?")

        v5 = StringVar()
        question5 = StringVar()
        v5.set("1")
        question5.set("How do you do?")
        self.root2.geometry("500x500")
        self.button2_0=Button(self.root2, textvariable=v1, command=self.button3Command)
        self.label2_0=Label(self.root2, textvariable=question2, font='Times 14 bold italic')
        self.label2_0.pack(anchor=W)
        Radiobutton(self.root2, text="1", variable=v1, value="1").pack(anchor=W)
        Radiobutton(self.root2, text="2", variable=v1, value="2").pack(anchor=W)
        Radiobutton(self.root2, text="3", variable=v1, value="3").pack(anchor=W)
        Radiobutton(self.root2, text="4", variable=v1, value="4").pack(anchor=W)

        self.label2_1=Label(self.root2, textvariable=question2, font='Times 14 bold italic')
        self.label2_1.pack(anchor=W)
        Radiobutton(self.root2, text="1", variable=v2, value="1").pack(anchor=W)
        Radiobutton(self.root2, text="2", variable=v2, value="2").pack(anchor=W)
        Radiobutton(self.root2, text="3", variable=v2, value="3").pack(anchor=W)
        Radiobutton(self.root2, text="4", variable=v2, value="4").pack(anchor=W)

        self.label2_2=Label(self.root2, textvariable=question3, font='Times 14 bold italic')
        self.label2_2.pack(anchor=W)
        Radiobutton(self.root2, text="1", variable=v3, value="1").pack(anchor=W)
        Radiobutton(self.root2, text="2", variable=v3, value="2").pack(anchor=W)
        Radiobutton(self.root2, text="3", variable=v3, value="3").pack(anchor=W)
        Radiobutton(self.root2, text="4", variable=v3, value="4").pack(anchor=W)

        self.label2_3=Label(self.root2, textvariable=question4, font='Times 14 bold italic')
        self.label2_3.pack(anchor=W)
        Radiobutton(self.root2, text="1", variable=v4, value="1").pack(anchor=W)
        Radiobutton(self.root2, text="2", variable=v4, value="2").pack(anchor=W)
        Radiobutton(self.root2, text="3", variable=v4, value="3").pack(anchor=W)
        Radiobutton(self.root2, text="4", variable=v4, value="4").pack(anchor=W)

        self.label2_4=Label(self.root2, textvariable=question5, font='Times 14 bold italic')
        self.label2_4.pack(anchor=W)
        Radiobutton(self.root2, text="1", variable=v5, value="1").pack(anchor=W)
        Radiobutton(self.root2, text="2", variable=v5, value="2").pack(anchor=W)
        Radiobutton(self.root2, text="3", variable=v5, value="3").pack(anchor=W)
        Radiobutton(self.root2, text="4", variable=v5, value="4").pack(anchor=W)

        self.root2.protocol("WM_DELETE_WINDOW", self.button3Command)

        self.button2_0.pack()
        self.root2.mainloop()
    def button2Command(self):
        self.root1.withdraw()
        self.root2 = Tk()
        self.root2.geometry("500x500")
        self.root2.protocol("WM_DELETE_WINDOW", self.button3Command)
        self.button2_0=Button(self.root2, text="Назад", command=self.button3Command)
        self.button2_0.pack()
        self.root2.mainloop()
    def button3Command(self):
        self.root1.deiconify()
        self.root2.destroy()

ui = CClient()
ui.root.mainloop()
