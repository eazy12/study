# работа с сокетами
import socket
# для задержки
import time
# сериализация
import pickle
# массивы
import numpy as np
# GUI
from tkinter import *

class CClient:
    def __init__(self):
        # окно входа
        self.b=True
        self.answers = np.zeros([5])
        self.root=Tk()
        self.errorString = StringVar()
        self.errorString.set(' ')
        self.root.resizable(width=False, height=False)
        self.root.geometry("500x500")

        self.labelText = StringVar()
        self.labelText.set("Нажмите Готов")

        # создаем виджеты
        self.label0_0=Label(self.root, text="Здраствуйте", font='DroidSans 14 bold ')
        self.label0_1=Label(self.root, text="Логин", font='DroidSans 14 bold italic')
        self.label0_2=Label(self.root, text="Пароль", font='DroidSans 14 bold italic')
        self.label0_3=Label(self.root, textvariable = self.errorString, font='DroidSans 14 bold italic', fg="red")

        self.button0_0=Button(self.root,text="Авторизация",command=self.button0Command)

        self.entry0_0 = Entry(self.root, width= 15, font='DroidSans 14 bold italic')
        self.entry0_1 = Entry(self.root, width= 15, font='DroidSans 14 bold italic')

        # размещаем виджеты
        self.label0_0.place(x=130,y=160)
        self.label0_1.place(x=80,y=185)
        self.label0_2.place(x=80,y=210)
        self.label0_3.place(x=90,y=265)
        self.entry0_0.place(x=200,y=185)
        self.entry0_1.place(x=200,y=210)
        self.button0_0.place(x=165, y=240)

        self.label0_3.place_forget()

        # подключение через сокет
        self.sock = socket.socket()
        self.sock.connect(('localhost', 9079))

    def button0Command(self):
        # проверяем логин и пароли
        if( self.entry0_0.get() == "" or self.entry0_1.get()==""):
            self.errorString.set("Пропущено поле")
            self.label0_3.place(x=85,y=270)
            return
        self.sock.send(bytes(self.entry0_0.get(),encoding = 'utf-8'))
        time.sleep(0.1)
        self.sock.send(bytes(self.entry0_1.get(),encoding = 'utf-8'))
        time.sleep(0.1)
        z = self.sock.recv(1024).decode('utf-8')

        if(z=='Неверный логин'):
            self.errorString.set(z)
            self.label0_3.place(x=85,y=270)
            print(z)
            return
        elif(z=='Неверный пароль'):
            self.errorString.set(z)
            self.label0_3.place(x=85,y=270)
            print(z)
            return

        # переход на следующее окно
        self.root1 = Tk()
        self.root1.geometry("500x500")
        self.label1_0=Label(self.root1, text="Итоговый тест", font='DroidSans 14 bold italic')
        self.label1_1=Label(self.root1, text="Лабораторная \n работа", font='DroidSans 14 bold italic')

        self.button1_0=Button(self.root1,text="Пройти",command=self.button1Command)
        self.button1_1=Button(self.root1,text="Пройти",command=self.button2Command)

        self.button1_0.place(x = 350, y = 120)
        self.button1_1.place(x = 350, y = 200)

        self.label1_0.place(x = 40, y = 120)
        self.label1_1.place(x = 40, y = 200)
        self.root1.protocol("WM_DELETE_WINDOW", self.close )
        self.root.destroy()
        self.root1.mainloop()

    def close(self):
        # посылем на сервер сообщение о закрытии
        self.sock.send(bytes("end",encoding = 'utf-8'))
        self.root1.destroy()

    def selected(self, x,y):
        # записываем ответы студента в массив
        if str(self.queryResult[x][5]) == y.get():
            self.answers[x] = True
        else:
            self.answers[x] = False


    def button1Command(self):
        # окно теста
        self.sock.send(bytes("test",encoding = 'utf-8'))
        self.root1.withdraw()
        self.root2 = Tk()

        self.smt = self.sock.recv(4096)
        self.queryResult = pickle.loads(self.smt)

        question1 = StringVar()
        question1.set(self.queryResult[0][0])
        v1 = StringVar()
        v1.set("1")

        question2 = StringVar()
        question2.set(self.queryResult[1][0])
        v2 = StringVar()
        v2.set("2")

        question3 = StringVar()
        question3.set(self.queryResult[2][0])
        v3 = StringVar()
        v3.set("3")

        question4 = StringVar()
        question4.set(self.queryResult[3][0])
        v4 = StringVar()
        v4.set("4")

        question5 = StringVar()
        question5.set(self.queryResult[4][0])
        v5 = StringVar()
        v5.set("5")

        self.root2.geometry("800x550")
        self.button2_0=Button(self.root2,text="Проверить", command=self.button4Command)

        self.label2_0=Label(self.root2,textvariable=question1, font='DroidSans 10 bold italic')
        self.label2_0.pack(anchor=W)
        gen = [ x for x in self.queryResult[0][1:5]]
        for j,i in enumerate(gen):
            b = Radiobutton(self.root2, variable=v1,font='DroidSans 10 italic', text = i, value=j+1, command=lambda: self.selected(0,v1))
            b.deselect()
            b.pack(anchor=W)

        self.label2_1=Label(self.root2,textvariable=question2, font='DroidSans 10 bold italic')
        self.label2_1.pack(anchor=W)
        gen = [ x for x in self.queryResult[1][1:5]]
        for j,i in enumerate(gen):
            b = Radiobutton(self.root2, variable=v2,font='DroidSans 10 italic', text = i, value=j+1,command=lambda: self.selected(1,v2))
            b.deselect()
            b.pack(anchor=W)

        self.label2_2=Label(self.root2,textvariable=question3, font='DroidSans 10 bold italic')
        self.label2_2.pack(anchor=W)
        gen = [ x for x in self.queryResult[2][1:5]]
        for j,i in enumerate(gen):
            b = Radiobutton(self.root2, variable=v3,font='DroidSans 10 italic', text = i, value=j+1,command=lambda: self.selected(2,v3))
            b.deselect()
            b.pack(anchor=W)

        self.label2_3=Label(self.root2,textvariable=question4, font='DroidSans 10 bold italic')
        self.label2_3.pack(anchor=W)
        gen = [ x for x in self.queryResult[3][1:5]]
        for j,i in enumerate(gen):
            b = Radiobutton(self.root2, variable=v4,font='DroidSans 10 italic', text = i, value=j+1,  command=lambda: self.selected(3,v4))
            b.deselect()
            b.pack(anchor=W)

        self.label2_4=Label(self.root2,textvariable=question5, font='DroidSans 10 bold italic',)
        self.label2_4.pack(anchor=W)
        gen = [ x for x in self.queryResult[4][1:5]]
        for j,i in enumerate(gen):
            b = Radiobutton(self.root2, variable=v5,font='DroidSans 10 italic', text = i, value=j+1,  command=lambda: self.selected(4,v5))
            b.deselect()
            b.pack(anchor=W)

        self.root2.protocol("WM_DELETE_WINDOW", self.button3Command)

        self.button2_0.pack()
        self.root2.mainloop()

    def button4Command(self):
        #окно после теста
        self.root3 = Tk()
        self.root3.geometry("500x500")
        quq = pickle.dumps(self.answers)
        self.sock.send(quq)
        r = self.sock.recv(1024).decode('utf-8')
        self.button3_0=Button(self.root3,text="В главное меню", command=self.button5Command)
        self.label3_0=Label(self.root3, text=("Оценка: "+r), font='DroidSans 14 bold ')
        self.button3_0.place(x=150,y = 180)
        self.label3_0.place(x=160,y = 150)
        self.root2.destroy()
        self.root3.mainloop()

    def button5Command(self):
        # выход в главное меню
        self.root1.deiconify()ы
        self.root3.destroy()

    def button2Command(self):
        # окно лабы
        self.sock.send(bytes("labwork",encoding = 'utf-8'))
        self.root1.withdraw()
        self.root2 = Tk()
        self.root2.geometry("500x500")
        self.root2.protocol("WM_DELETE_WINDOW", self.button3Command)
        self.text2 = Text(self.root2, height = 20, width = 55, font='DroidSans 10 italic', pady=10)
        self.text3 = Text(self.root2, height = 7, width = 55, font='DroidSans 10 italic')
        self.button2_0=Button(self.root2,text="Назад", command=self.button3Command)
        self.button3_0=Button(self.root2,text="Проверить", command=self.proverka)
        self.text2.grid(row=0, column=1, pady=(10, 10),padx=(60,0))
        self.text3.grid(row=1, column=1, pady=(0, 10),padx=(60,0))
        self.button2_0.grid(row=2, column=1, pady=(0, 10),padx=(60,0))
        self.button3_0.grid(row=3, column=1, pady=(0, 10),padx=(60,0))
        self.root2.mainloop()
    def proverka(self):
        # кнопка проверки программы. Программа запускает на сервере
        quq = pickle.dumps(self.text2.get("1.0",END))
        self.sock.send(quq)
        time.sleep(0.1)
        qqq = self.sock.recv(4096)
        print("qqq, ",qqq.decode('utf-8'))
        self.text3.delete(1.0, END)
        self.text3.insert(1.0, qqq.decode('utf-8'))

    def button3Command(self):
        # выход из окна лабы
        z = "endd"
        quq = pickle.dumps(z)
        self.sock.send(quq)
        self.root1.deiconify()
        self.root2.destroy()

# создание класса
ui = CClient()
# запуска окна
ui.root.mainloop()
