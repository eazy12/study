from tkinter import *
from enum import Enum

class UI:
	def __init__(self,x):
		self.textWidth = 20
		self.entryWidth = 45
		self.root=Tk()
		self.x = x
		self.text1=Text(self.root,height=24,width=self.textWidth,font='Mono 14',wrap=WORD)
		self.text2=Text(self.root,height=8,width=self.textWidth,font='Mono 14',wrap=WORD)
		self.text3=Text(self.root,height=8,width=self.textWidth,font='Mono 14',wrap=WORD)
		self.text4=Text(self.root,height=8,width=self.textWidth,font='Mono 14',wrap=WORD)
		self.entry1=Entry(self.root,width=self.entryWidth,font='Mono 14')
		self.button1=Button(self.root,text="Start",command=self.x.SA )
		self.text1.grid(row=0,column=0,rowspan=3)
		self.text2.grid(row=0,column=1)
		self.text3.grid(row=1,column=1)
		self.text4.grid(row=2,column=1)
		self.entry1.grid(row=1,column=2,padx=5)
		self.button1.grid(row=1,column=3)
		self.root.rowconfigure(0, weight=1)
		self.root.columnconfigure(0, weight=1)
class LA:
	def __init__(self):
		self.saWhere = ""
		self.isLastWord = False
		self.strr = ""
		self.numbers = []
		self.sysSymbols = []
		self.words = []
		self.condition = "start"
		self.where = ""
		self.SAwhere = ""
		self.endStatus = False
		self.obligatory = False
		self.entryString = ""
		self.i = 0
		self.type1 = ""
	def set_ui(self,x):
		self.uiclass = x
	def lex_anal(self):
		self.numbers = []
		self.sysSymbols = []
		self.words = []
		self.uiclass.text2.delete(1.0,END)
		self.uiclass.text3.delete(1.0,END)
		self.uiclass.text4.delete(1.0,END)
		self.uiclass.entry1.delete(0, END)
		self.entryString = ""

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
						if( (self.i + 1) == len(self.strr)):
							self.endStatus = True
							self.isLastWord = True
							return 0,0,True
						self.condition = "start"
						print("Space")
						self.i+=1
						continue
					elif self.strr[self.i] in "[]":
						if self.sysSymbols.count(self.strr[self.i])==0:
							self.sysSymbols.append(self.strr[self.i])
						self.uiclass.text3.insert( END, self.sysSymbols[-1]+" ")
						print("End")
						if( (self.i + 1) == len(self.strr)):
							self.endStatus = True
							self.isLastWord = True
						self.i +=1
						self.condition = "start"
						print(self.strr[self.i-1], self.strr[self.i-1] , self.isLastWord)
						return self.strr[self.i-1], self.strr[self.i-1] , self.isLastWord
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
			elif self.isLastWord == True:
				print("End")
				self.endStatus = False
				self.condition = "start"
				print(self.entryString, self.type1, True)
				return self.entryString, self.type1, True
			elif (self.endStatus == True):
				print("End")
				self.endStatus = False
				self.condition = "start"
				print(self.entryString, self.type1, self.isLastWord)
				return self.entryString, self.type1, self.isLastWord

	def skip(self, instr):
		if(instr == "error"):
			self.uiclass.entry1.insert(0 , "Ошибка")
			self.endStatus = True

	def A_digit(self):
		print("in A_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.skip("error")
			return
		if (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "B_digit()"
		else:
			print("Lexical error: A_digit")
			self.skip("error")

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

	def C_digit(self):
		print("in C_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: C_digit")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			print("Lexical error: C_digit. Short word")
			self.skip("error")
			self.endStatus = True
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "A_digit()"
		else:
			print("Lexical error: C_digit")
			self.skip("error")

	def D_digit(self):
		print("in D_digit()")
		self.obligatory = True
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: D_digit")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.isLastWord = True
			self.endStatus = True
			self.obligatory = False
			if self.numbers.count(self.entryString)==0:
				self.numbers.append(self.entryString)
				self.uiclass.text2.insert( END, self.numbers[-1]+" ")
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "E_digit()"
		else:
			print("Lexical error: D_digit")
			self.skip("error")

	def E_digit(self):
		print("in E_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		elif self.strr[self.i] == ' ' and  (self.i + 1) == len(self.strr):
			self.endStatus = True
			self.isLastWord = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
			self.condition="start"
			return
		elif self.strr[self.i] == ' ':
			self.i+=1
			self.condition="start"
			self.endStatus = True
			self.obligatory = False
			if self.numbers.count(self.entryString)==0:
				self.numbers.append(self.entryString)
				self.uiclass.text2.insert( END, self.numbers[-1]+" ")
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
		if (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "F_digit()"
		else:
			print("Lexical error: E_digit")
			self.skip("error")

	def F_digit(self):
		print("in F_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: F_digit")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if (self.i + 1) == len(self.strr) :
			self.endStatus = True
			self.skip("error")
			return
		if (self.strr[self.i] == "1"):
			self.i+=1
			self.where = "G_digit()"
		else:
			print("Lexical error: F_digit")
			self.skip("error")


	def G_digit(self):
		print("in G_digit()")
		if (self.strr[self.i] in "01"):
			self.type1 = " цифры "
		else:
			print("Lexical error: G_digit")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.isLastWord = True
			self.endStatus = True
			if self.numbers.count(self.entryString)==0:
				self.numbers.append(self.entryString)
				self.uiclass.text2.insert( END, self.numbers[-1]+ " ")
		elif (self.strr[self.i]=="1"):
			self.i+=1
			self.where = "E_digit()"
		else:
			print("Lexical error: G_digit")
			self.skip("error")

	def A_letter(self):
		print("in A_letter()")
		if (self.strr[self.i] in "abcd"):
			self.type1 = " буквы "
		elif self.strr[self.i] == ' ' and  (self.i + 1) == len(self.strr):
			self.endStatus = True
			self.isLastWord = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
			self.condition="start"
			return
		elif self.strr[self.i] == ' ' :
			self.i+=1
			self.endStatus = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
			self.condition="start"
			return
		else:
			print("Lexical error: A_letter")
			self.skip("error")
			return
		self.entryString += self.strr[self.i]
		if( (self.i + 1) == len(self.strr)):
			self.isLastWord = True
			self.endStatus = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
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
		elif self.strr[self.i] == ' ' and  (self.i + 1) == len(self.strr):
			self.endStatus = True
			self.isLastWord = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
			self.condition="start"
			return
		elif self.strr[self.i] == ' ':
			self.endStatus = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
			self.i+=1
			self.condition="start"
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
			self.isLastWord = True
			if self.words.count(self.entryString)==0:
				self.words.append(self.entryString)
				self.uiclass.text4.insert( END, self.words[-1]+" ")
			return
		elif (self.strr[self.i] in "acd"):
			self.i+=1
			self.where = "A_letter()"
			return
		else:
			print("Lexical error: B_letter")
			self.skip("error")
			return

	def SA(self):
		com = False
		for j, value in enumerate(self.uiclass.text1.get(1.0, END)):
			if value == "/" and com == True:
				com = False
				if self.sysSymbols.count(value)==0:
					self.sysSymbols.append(value)
					self.uiclass.text3.insert( END,self.sysSymbols[-1]+" ")
				continue
			elif value == "/" and com == False:
				com = True
				if self.sysSymbols.count(value)==0:
					self.sysSymbols.append(value)
					self.uiclass.text3.insert( END, self.sysSymbols[-1] + " ")
				continue
			elif com == True:
				continue
			elif value == "\n":
				self.strr += " "
				continue
			self.strr += value

		self.localString, self.localType, self.localLastWordStatus = self.lex_anal()
		self.saCond = True
		self.leftNumber = 0
		self.center = False

		while( self.localLastWordStatus != True):
			if self.saCond == True:
				self.saCond = False
				if self.localType != " буквы ":
					self.uiclass.entry1.insert(0 , "ERROR")
					self.saWhere = "error"
				else:
					self.SA_A()
			else:
				if self.saWhere == "error":
					return
				elif self.saWhere == "saA":
					self.SA_A()
				elif self.saWhere == "saB":
					self.SA_B()
		else:
			self.uiclass.entry1.insert(0 , "Все в порядке")


	def SA_A(self):
		print("debug label")
		self.localString, self.localType, self.localLastWordStatus = self.lex_anal()
		if self.localType == "[":
			self.saWhere = "saA"
			if self.center == False:
				self.leftNumber+=1
		elif self.localType == "]":
			if self.center == True:
				self.leftNumber -=1
		elif self.localType == " цифры ":
			if self.center == False:
				self.center = True
				self.saWhere = "saA"
			else:
				if self.leftNumber != 0:
					self.uiclass.entry1.insert(0 , "ERROR")
					self.saWhere = "error"
		else:
			self.uiclass.entry1.insert(0 , "ERROR")
			self.saWhere = "error"


	def SA_B(self):
		self.localString, self.localType, self.localLastWordStatus = self.lex_anal()
		if self.localType == " буквы ":
			self.SAwhere = "SA_B"
		else:
			self.uiclass.entry1.insert(0 , "ERROR")
			self.saWhere = "error"
