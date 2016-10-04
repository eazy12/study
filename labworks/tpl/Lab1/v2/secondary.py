from tkinter import *
from enum import Enum
class LA:
	class condition(Enum):
		start = 1
		contin = 2
		finish = 3
	def __init__(self):
		self.la_condition = self.condition.start
		self.textWidth = 25
		self.entryWidth = 35
		self.root=Tk()
		self.entryString = ''
		self.strr = ""
		self.isEntryFull = False
		self.condition = "start"
		self.where = ""
		self.endStatus = False
		self.obligatory = False
		self.errorStatus = ""
		self.msgSize = 0
		self.i = 0
		self.isItCommentary = False
		self.text1=Text(self.root,height=20,width=self.textWidth,font='Mono 14',wrap=WORD)
		self.entry1=Entry(self.root,width=self.entryWidth,font='Mono 14')
		self.button1=Button(self.root,text="Start",command=self.lex_anal )
		self.label1=Label(self.root,width=30,font='Mono 14',bg="red",fg="blue",text="Start")
		self.text1.grid(row=0,column=0,rowspan=3)
		self.entry1.grid(row=0,column=1,padx=5)
		self.button1.grid(row=0,column=2)
		self.label1.grid(row=0, column=1,sticky="n")
		self.root.rowconfigure(0, weight=1)
		self.root.columnconfigure(0, weight=1)
	def lex_anal(self):
		if(self.endStatus == True):
			self.entry1.delete(0, END)
			print("entry deleted")
			self.endStatus = False
			self.condition = "start"
			self.strr = ""
			self.where = ""
			self.i = 0
			self.entryString = ""
		if( self.strr == ""):
			self.strr = self.text1.get(1.0, END)
			self.strr = self.strr[0:-1]
		while(self.strr[self.i]):
			if( self.errorStatus == "error"):
				break
			elif self.isEntryFull == True:
				print("entryfull cahnged")
				print(self.where)
				self.isEntryFull = False
				break
			elif (self.endStatus == False):
				if (self.condition == "start"):
					self.condition = "continue"
					if (self.strr[self.i]=="0"):
						self.where = "A_digit()"
						self.A_digit()
					elif (self.strr[self.i] in "abcd"):
						self.A_letter()
					elif (self.strr[self.i] == " "):
						print("Space")
						continue
					elif (self.strr[self.i] == "/"):
						self.where = "Commentary2"
						self.i=+1
					else:
						print("Error in begin")
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
					elif self.where =="FIN_digit()":
						self.FIN_digit()
					elif self.where =="A_letter()":
						self.A_letter()
					elif self.where =="B_letter()":
						self.B_letter()
					elif self.where == "Commentary2":
						self.where = ""
						if(self.where==""):
							self.condition = "start"
						elif(self.where[0] not in "BCDFG"):
							self.condition = "start"
						if( (self.i + 1) == len(self.strr)):
							self.endStatus = True
						while(self.strr[self.i]!="/"):
							print("*")
							if( (self.i + 1) == len(self.strr)):
								self.endStatus = True
							self.i+=1
						else:
							self.i+=1
			elif (self.endStatus == True):
				print("End")
				break

	def A_digit(self):
		print("in A_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: A_digit")
			self.errorStatus = "error"
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.where = "A_digit()"
			self.entryString = ""
			self.isEntryFull = True
			return
		self.entryString += tempString
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: A_digit")
			self.errorStatus = "error"
			return
		if (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "B_digit()"
			return
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: A_digit")
			print("Lexical error: A_digit")
			self.errorStatus = "error"

	def B_digit(self):
		print("in B_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: B_digit")
			self.errorStatus = "error"
			return
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "B_digit()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if (self.strr[self.i] == "1" and self.strr[self.i+1] =="1" ):
			print("Lexical error: B_digit There is no self.obligatory part of word")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "LE: B_digit no obligatory part")
			self.errorStatus = "error"
			return
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "C_digit()"
			return
		elif (self.strr[self.i] == "1"):
			self.i+=1
			self.where = "D_digit()"
			return
		else:
			print("Lexical error: B_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: B_digit")
			self.errorStatus = "error"

	def C_digit(self):
		print("in C_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			print("Lexical error: C_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: C_digit")
			self.errorStatus = "error"
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "C_digit()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if( (self.i + 1) == len(self.strr)):
			print("Lexical error: C_digit. Short word")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: C_digit")
			self.endStatus = True
			self.errorStatus = "error"
			return
		elif (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "A_digit()"
			return
		else:
			print("Lexical error: C_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: C_digit")
			self.errorStatus = "error"

	def D_digit(self):
		print("in D_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			print("Lexical error: D_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: D_digit")
			self.errorStatus = "error"
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if (len(self.entryString + tempString) <= self.entryWidth and (self.i + 1) == len(self.strr)):
			self.entryString += tempString
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.endStatus = True
			return
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "D_digit()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.where = "FIN_digit()"
			return
		elif (self.strr[self.i] == "0" and self.strr[self.i+1]==" "):
			self.i+=1
			self.where = "FIN_digit()"
			self.obligatory = True
			return
		elif (self.strr[self.i] == "0" and self.strr[self.i+1]=="0"):
			self.i+=1
			self.where = "E_digit()"
			return
		else:
			print("Lexical error: D_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: D_digit")
			self.errorStatus = "error"

	def E_digit(self):
		print("in E_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			print("Lexical error: E_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: E_digit")
			self.errorStatus = "error"
			return
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "E_digit()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if (self.strr[self.i] == "0"):
			self.i+=1
			self.where = "F_digit()"
			return
		else:
			print("Lexical error: E_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: E_digit")
			self.errorStatus = "error"

	def F_digit(self):
		print("in F_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			print("Lexical error: F_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: F_digit")
			self.errorStatus = "error"
			return
		if (self.i + 1) == len(self.strr) :
			self.endStatus = True
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "F_digit()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if (self.strr[self.i] == "1"):
			self.i+=1
			self.where = "G_digit()"
			return
		else:
			print("Lexical error: F_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: F_digit")
			self.errorStatus = "error"

	def G_digit(self):
		print("in G_digit()")
		if (self.strr[self.i] in "01"):
			type1 = " digit "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			print("Lexical error: G_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: G_digit")
			self.errorStatus = "error"
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if (len(self.entryString + tempString) <= self.entryWidth and (self.i + 1) == len(self.strr)):
			self.entryString += tempString
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.endStatus = True
			return
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "G_digit()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if ( self.strr[self.i]=="0"):
			print("Lexical error: G_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: G_digit")
			self.errorStatus = "error"
			return
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			self.where = "FIN_digit()"
			return
		elif (self.strr[self.i+1] == " " and self.strr[self.i]=="1"):
			self.i+=1
			self.where = "FIN_digit()"
			return
		elif (self.strr[self.i+1] == "0" and self.strr[self.i]=="1"):
			self.i+=1
			self.where = "E_digit()"
			return
		else:
			print("Lexical error: G_digit")
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: G_digit")
			self.errorStatus = "error"

	def A_letter(self):
		print("in A_letter()")
		if (self.strr[self.i] in "abcd"):
			type1 = " letter "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: A_letter")
			self.errorStatus = "error"
			return
		print("1")
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if (len(self.entryString + tempString) <= self.entryWidth and (self.i + 1) == len(self.strr)):
			self.entryString += tempString
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.endStatus = True
			return
		print("2")
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "A_letter()"
			self.isEntryFull = True
			return
		print("3")
		self.entryString += tempString
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			return
		print("4")
		if (self.strr[self.i] in "acd"):
			self.i+=1
			self.where = "A_letter()"
			return
		elif (self.strr[self.i] == "b"):
			self.i+=1
			self.where = "B_letter()"
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: A_letter")
			print("Lexical error: A_letter")
			self.errorStatus = "error"

	def B_letter(self):
		print("in B_letter()")
		if (self.strr[self.i] in "abcd"):
			type1 = " letter "
		elif self.strr[self.i] =='/':
			self.where = "Commentary2"
			self.i+=1
			return
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: A_letter")
			self.errorStatus = "error"
			return
		tempString = self.strr[self.i] + type1 + str(ord(self.strr[self.i])) + ' '
		if (len(self.entryString + tempString) <= self.entryWidth and (self.i + 1) == len(self.strr)):
			self.entryString += tempString
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.endStatus = True
			return
		if( len(self.entryString + tempString) > self.entryWidth):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , self.entryString)
			self.entryString = ""
			self.where = "B_letter()"
			self.isEntryFull = True
			return
		self.entryString += tempString
		if( (self.i + 1) == len(self.strr)):
			self.endStatus = True
			return
		if (self.strr[self.i] in "acd"):
			self.i+=1
			self.where = "A_letter()"
			return
		elif (self.strr[self.i] == "b"):
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: B_digit (2b)")
			print("Lexical error: B_digit")
			self.errorStatus = "error"
		else:
			self.entry1.delete(0, END)
			self.entry1.insert(1 , "Lexical error: B_digit")
			print("Lexical error: B_digit")
			self.errorStatus = "error"
