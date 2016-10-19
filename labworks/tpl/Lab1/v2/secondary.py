from tkinter import *
from enum import Enum
class UI:
	def __init__(self,x):
		self.textWidth = 20
		self.entryWidth = 45
		self.root=Tk()
		self.x = x
		self.text1=Text(self.root,height=20,width=self.textWidth,font='Mono 14',wrap=WORD)
		self.entry1=Entry(self.root,width=self.entryWidth,font='Mono 14')
		self.button1=Button(self.root,text="Start",command=self.x.lex_anal )
		self.text1.grid(row=0,column=0,rowspan=3)
		self.entry1.grid(row=0,column=1,padx=5)
		self.button1.grid(row=0,column=2)
		self.root.rowconfigure(0, weight=1)
		self.root.columnconfigure(0, weight=1)
class LA:
	def __init__(self):		
		self.strr = ""
		self.condition = "start"
		self.where = ""
		self.endStatus = False
		self.obligatory = False
		self.entryString = ""
		self.i = 0
		self.type1 = ""
	def set_ui(self,x):
		self.uiclass = x
	def lex_anal(self):
		self.uiclass.entry1.delete(0, END)
		com = False
		for j, value in enumerate(self.uiclass.text1.get(1.0, END)):
			if value == "/" and com == True:
				com = False
				continue
			elif value == "/" and com == False:
				com = True
				continue
			elif com == True:
				continue
			elif value == "\n":
				self.strr += " "
				continue
			self.strr += value
		print(self.strr)
		while(self.i < len(self.strr)):
			if (self.endStatus == False):
				if (self.condition == "start"):
					self.condition = "continue"
					if (self.strr[self.i] in "01"):
						self.where = "A_digit()"
						self.A_digit()
					elif (self.strr[self.i] in "abcd"):
						self.where = "A_letter()"
						self.A_letter()
					elif (self.strr[self.i] == " "):
						self.condition = "start"
						print("Space")
						self.i+=1
						continue
					else:
						print("Error in begin")
						self.entryString += self.strr[self.i]
						self.skip("error")
				else:
					if self.where == "A_digit()":
						self.A_digit()
					elif self.where =="B_digit()":
						self.B_digit()
					elif self.where =="C_digit()":
						self.C_digit()
					elif self.where =="D_digit()":
						self.D_digit()
					elif self.where =="E_digit()":
						self.E_digit()
					elif self.where =="F_digit()":
						self.F_digit()
					elif self.where =="G_digit()":
						self.G_digit()
					elif self.where =="A_letter()":
						self.A_letter()
					elif self.where =="B_letter()":
						self.B_letter()
			elif (self.endStatus == True):
				print("End")
				break

	def skip(self, instr):
		if(instr == "error"):
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString)
			for j in self.strr[self.i:]:
				if self.strr[self.i] == " ":
					self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) ," Ошибка ")
					self.i+=1
					self.entryString =""
					self.condition = "start"
					break
				self.i+=1
				self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.strr[self.i])

	def A_digit(self):
		print("in A_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			self.skip("error")
			self.entryString =""
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.skip("error")
			self.entryString = ""
			return
		if (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "B_digit()"
		else:
			print("Lexical error: A_digit")
			self.skip("error")
			self.entryString = ""

	def B_digit(self):
		print("in B_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.skip("error")
			self.entryString = ""
			return
		if (self.strr[self.i] == "1" and self.strr[self.i+1] =="1" ):
			print("Lexical error: B_digit There is no self.obligatory part of word")
			print(self.entryString)
			self.skip("error")
			self.entryString = ""
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "C_digit()"
		elif (self.strr[self.i] == "1"):
			self.i+=1
			self.where = "D_digit()"
		else:
			print("Lexical error: B_digit")
			self.skip("error")
			self.entryString = ""

	def C_digit(self):
		print("in C_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: C_digit")
			self.skip("error")
			self.entryString = ""
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			print("Lexical error: C_digit. Short word")
			self.skip("error")
			self.endStatus = True
			self.entryString = ""
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "A_digit()"
		else:
			print("Lexical error: C_digit")
			self.skip("error")
			self.entryString = ""

	def D_digit(self):
		print("in D_digit()")
		self.obligatory = True
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: D_digit")
			self.skip("error")
			self.entryString = ""
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.obligatory = False
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + self.type1)
			self.entryString = ""
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "E_digit()"
		else:
			print("Lexical error: D_digit")
			self.skip("error")
			self.entryString = ""

	def E_digit(self):
		print("in E_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		elif self.strr[self.i] == ' ':
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + self.type1)
			self.i+=1
			self.condition="start"
			self.obligatory = False
			self.entryString =""
			return
		else:
			print("Lexical error: E_digit")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.skip("error")
			return
		if self.obligatory == False:
			print("Lexical error: E_digit")
			self.skip("error")
			self.entryString = ""
		if (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "F_digit()"
		else:
			print("Lexical error: E_digit")
			self.skip("error")
			self.entryString = ""

	def F_digit(self):
		print("in F_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: F_digit")
			self.skip("error")
			self.entryString = ""
			return
		self.entryString += self.strr[self.i]
		if (self.i + 1) == len(self.strr) :
			self.endStatus = True
			self.skip("error")
			self.entryString = ""
			return
		if (self.strr[self.i] == "1"):
			self.i+=1
			self.where = "G_digit()"
		else:
			print("Lexical error: F_digit")
			self.skip("error")
			self.entryString = ""


	def G_digit(self):
		print("in G_digit()", self.strr[self.i])
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: G_digit")
			self.skip("error")
			self.entryString = ""
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + self.type1)
			self.entryString = ""
			self.endStatus = True
		elif (self.strr[self.i]=="1"):
			self.i+=1
			self.where = "E_digit()"
		else:
			print("Lexical error: G_digit")
			self.skip("error")
			self.entryString = ""

	def A_letter(self):
		print("in A_letter()")
		if (self.strr[self.i] in "abcd"):
			self.type1 = " буквы "
		elif self.strr[self.i] == ' ':
			self.i+=1
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + " буквы ")
			self.condition="start"
			self.entryString =""
			return
		else:
			print("Lexical error: A_letter")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + self.type1)
			self.entryString = ""
			self.endStatus = True
			return
		elif (self.strr[self.i] in "acd"):
			self.i+=1
			self.where = "A_letter()"
			return
		elif (self.strr[self.i] == "b"):
			self.i+=1
			self.where = "B_letter()"
		else:
			print("Lexical error: A_letter")
			self.skip("error")

	def B_letter(self):
		print("in B_letter()")
		if (self.strr[self.i] in "abcd"):
			self.type1 = " буквы "
		elif self.strr[self.i] == ' ':
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + " буквы ")
			self.i+=1
			self.condition="start"
			self.entryString =""
			return
		else:
			print("Lexical error: B_letter")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if (self.strr[self.i] == "b"):
			print("Lexical error: B_letter")
			self.skip("error")
			return
		if( (self.i + 1) == len(self.strr)):
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + self.type1)
			self.entryString = ""
			self.endStatus = True
			return
		elif self.strr[self.i+1] == ' ':
			self.uiclass.entry1.insert(len(self.uiclass.entry1.get()) , self.entryString + ' ' + self.type1)
			self.entryString = ""
			self.condition = "start"
			self.i+=1
			return
		elif (self.strr[self.i] in "acd"):
			self.i+=1
			self.where = "A_letter()"
			return
