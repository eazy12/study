from tkinter import *
from enum import Enum
import random
class LA:
    class condition(Enum):
        start = 1
        contin = 2
        finish = 3
    def __init__(self):
        self.la_condition = self.condition.start
        self.textWidth = 25
        self.endtryWidth = 35
        self.root=Tk()
        self.bufferString = ''
        self.slovo = ''
        self.text1=Text(self.root,height=20,width=self.textWidth,font='Mono 14',wrap=WORD)
        self.entry1=Entry(self.root,width=self.endtryWidth,font='Mono 14')
        self.button1=Button(self.root,text="Start",command=self.lex_anal )
        self.label1=Label(self.root,width=30,font='Mono 14',bg="red",fg="blue",text="Start")
        self.text1.insert(1.0, self.random_msg())
        self.text1.grid(row=0,column=0,rowspan=3)
        self.entry1.grid(row=0,column=1,padx=5)
        self.button1.grid(row=0,column=2)
        self.label1.grid(row=0, column=1,sticky="n")
        self.root.rowconfigure(0, weight=1)
        self.root.columnconfigure(0, weight=1)
    def random_msg(self):
        msg1 = "000" * random.randint(0,5) + "010" + "011" * random.randint(0,5)
        g = random.randint(1,10)
        k = random.randint(1,10)
        msg2=""
        while(g != 0):
            e = random.randint(1,4)
            if e ==1:
                msg2+="a"
            elif e==2:
                msg2+="b"
            elif e==3:
                msg2+="c"
            elif e==4:
                msg2+="d"
            g = g -1
        q = msg2.find("bb")
        while(q != -1 ):
            msg2= msg2[:q] + msg2[(q+1):]
            q = msg2.find("bb")
        if(k>6):
            return msg1 + msg2 + "#" + msg2[e:k]
        else:
            return msg1 + msg2
    def lex_anal(self):
        # if(self.la_condition == self.condition.finish):
        #     self.text1.delete(1.0, END)
        #     strg=self.random_msg()
        #     self.text1.insert(1.0, strg)
        # if self.entry1.get():
        #     self.entry1.delete(0, END)
        # if not self.bufferString:
        #     self.bufferString = self.text1.get(1.0, END)
        #
        # self.b = ''
        # for self.i in enumerate(self.bufferString[:-1]):
        #     self.slovo = ""
        #     self.I = iter(self.bufferString)
        #     if self.i[1] == ' ':
        #         self.type = 'Space'
        #         continue
        #     elif '0' <= self.i[1] <= '1':
        #         self.type = 'Number'
        #         if self.i[1] =='0':
        #             self.A_digit()
        #         elif self.i[1] =='1':
        #             print("error #1")
        #     elif 'a' <= self.i[1] <= 'z':
        #         self.type = "Letter"
        #     elif self.i[1] == '#':
        #         self.type = "Comm"
        #     self.z = self.b + str(self.i[1]) + '-' + str(ord(self.i[1]))+ '-'+ self.type + ' '
        #     if (len(self.z) <= self.endtryWidth ):
        #         self.b+= str(self.i[1]) + '-' + str(ord(self.i[1]))+ '-' + self.type + ' '
        #     else:
        #         self.bufferString = self.bufferString[self.i[0]:]
        #         self.la_condition = self.condition.contin
        #         self.label1['text']="Continue"
        #         break
        # else:
        #     self.la_condition = self.condition.finish
        #     self.label1['text']="Finish"
        #     self.bufferString = ''
        # self.b = self.b[:-1]+ ' '
        # self.entry1.insert(1 ,self.b)
        self.bufferString = self.text1.get(1.0, END)

        iterator = iter(self.bufferString)
        while(1):
            currentSymbol = next(iterator)




    def A_digit(self):
        if(self.i[1]=='0'):
            self.slovo += self.i[1]
            next(self.I)
            print(self.slovo + '+' + self.i[1])
            self.B_digit()
        elif self.i[1] =='1':
            print("Error 2")
    def B_digit(self):
        print("@")
        if(self.i[1]=='0'):
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.C_digit()
        elif(self.i[1]=='1'):
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.D_digit()
        else:
            print("Error")
    def C_digit(self):
        if(self.i[1]=='0'):
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.A_digit()
        else:
            print("Error")
    def D_digit(self):
        if(self.bufferString[i[0]+1]=="0"):
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.E_digit()
        elif self.bufferString[i[0]+1]=="1":
            print("Error")
        else:
            self.FIN_digit()
    def E_digit(self):
        if(self.i[1]=='0'):
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.F_digit()
        elif self.i[1]=='1':
            print("error")
    def F_digit(self):
        if self.i[1] == '1':
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.G_digit()
        elif self.i[1]=='0':
            print("error")
    def G_digit(self):
        if(self.bufferString[i[0]+1]=="0"):
            self.slovo += self.i[1]
            yield self.i[1]
            print(self.slovo + ' ' + self.i[1])
            self.E_digit()
        elif self.bufferString[i[0]+1]=="1":
            print("Error")
        else:
            self.FIN_digit()
    def FIN_digit(self):
        self.entry1.insert(1.0, self.slovo + " Верно")
