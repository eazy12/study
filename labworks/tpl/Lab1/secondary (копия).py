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
        self.root=Tk()
        self.bufferString = ''
        self.text1=Text(self.root,height=20,width=30,font='Mono 14',wrap=WORD)
        self.entry1=Entry(self.root,width=30,font='Mono 14')
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
        msg1 = "000" * random.randint(1,5) + "010" + "011" * random.randint(1,5)
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
        if(self.la_condition == self.condition.finish):
            self.text1.delete(1.0, END)
            strg=self.random_msg()
            self.text1.insert(1.0, strg)
        if self.entry1.get():
            self.entry1.delete(0, END)
        if not self.bufferString:
            self.bufferString = self.text1.get(1.0, END)

        self.b = ''
        self.k = 0

        for i in self.bufferString[:-1]:
            if i == ' ':
                self.type = 'space'
            elif '0' <= i <= '9':
                self.type = 'digit'
            elif 'a' <= i <= 'z':
                self.type = 'Letter'
            elif i == '#':
                self.type = "comm-ry"
            self.z = self.b + str(i) + ' ' + str(ord(i))+ ' '+ self.type
            if (len(self.z) <= 31 ):
                self.k +=1
                self.b+= str(i) + ' ' + str(ord(i))+ ' ' + self.type
            else:
                self.bufferString = self.bufferString[self.k:]
                self.la_condition = self.condition.contin
                self.label1['text']="Continue"
                break
        else:
            self.la_condition = self.condition.finish
            self.label1['text']="Finish"
            self.bufferString = ''
        self.b = self.b[:-1]+ ' '
        self.entry1.insert(1 ,self.b)
