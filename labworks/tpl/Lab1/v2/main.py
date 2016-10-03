strr = "010010"
condition = "start"
where = ""
endstatus = False
obligatory = False
errorStatus = ""
i = 0
stop = len(strr)

def A_digit():
	print("in A_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: A_digit")
		errorStatus = "error"
		return
	print(strr[i] + type1 + str(ord(strr[i])) )
	if( (i+1) == len(strr)):
		endstatus = True
		print("Lexical error: A_digit")
		errorStatus = "error"
		return
	if (strr[i] == "0"):
		i+=1
		where = "B_digit()"
		return
	else:
		print("Lexical error: A_digit")
		errorStatus = "error"

def B_digit():
	print("in B_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: B_digit")
		errorStatus = "error"
		return
	print(strr[i] + type1 + str(ord(strr[i])) )
	if( (i+1) == len(strr)):
		endstatus = True
		return
	if (strr[i] == "1" and strr[i+1] =="1" ):
		print("Lexical error: B_digit There is no obligatory part of word")
		errorStatus = "error"
		return
	elif (strr[i] == "0"):
		i+=1
		where = "C_digit()"
		return
	elif (strr[i] == "1"):
		i+=1
		where = "D_digit()"
		return
	else:
		print("Lexical error: B_digit")
		errorStatus = "error"

def C_digit():
	print("in C_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: C_digit")
		errorStatus = "error"
		return
	print(strr[i] +  type1  + str(ord(strr[i])) )
	if( (i+1) == len(strr)):
		print("Lexical error: C_digit. Short word")
		endstatus = True
		errorStatus = "error"
		return
	elif (strr[i] == "0"):
		i+=1
		where = "A_digit()"
		return
	else:
		print("Lexical error: C_digit")
		errorStatus = "error"

def D_digit():
	print("in D_digit()")
	global i,strr, where, endstatus, errorStatus, condition
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: D_digit")
		errorStatus = "error"
		return
	print(strr[i] + type1  + str(ord(strr[i])) )
	if( (i+1) == len(strr)):
		endstatus = True
		where = "FIN_digit()"
		return
	elif (strr[i] == "0" and strr[i+1]==" "):
		i+=1
		where = "FIN_digit()"
		obligatory = True
		return
	elif (strr[i] == "0" and strr[i+1]=="0"):
		i+=1
		where = "E_digit()"
		return
	else:
		print("Lexical error: D_digit")
		errorStatus = "error"

def E_digit():
	print("in E_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: E_digit")
		errorStatus = "error"
		return
	print(strr[i] +  type1  + str(ord(strr[i])) )
	if( (i+1) == len(strr)):
		endstatus = True
		return
	if (strr[i] == "0"):
		i+=1
		where = "F_digit()"
		return
	else:
		print("Lexical error: E_digit")
		errorStatus = "error"

def F_digit():
	print("in F_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: F_digit")
		errorStatus = "error"
		return
	print(strr[i] +  type1  + str(ord(strr[i])) )
	if (i+1) == len(strr) :
		endstatus = True
		return
	if (strr[i] == "1"):
		i+=1
		where = "G_digit()"
		return
	else:
		print("Lexical error: F_digit")
		errorStatus = "error"

def G_digit():
	print("in G_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] in "01"):
		type1 = " digit "
	else:
		print("Lexical error: G_digit")
		errorStatus = "error"
		return
	print(strr[i] +  type1 + str(ord(strr[i])) )
	if ( strr[i]=="0"):
		print("Lexical error: G_digit")
		errorStatus = "error"
		return
	if( (i+1) == len(strr)):
		endstatus = True
		where = "FIN_digit()"
		return
	if (strr[i+1] == " " and strr[i]=="1"):
		i+=1
		where = "FIN_digit()"
		return
	elif (strr[i+1] == "0" and strr[i]=="1"):
		i+=1
		where = "E_digit()"
		return
	else:
		print("Lexical error: G_digit")
		errorStatus = "error"

def FIN_digit():
	condition = "start"
	print("in FIN_digit()")
	global i,strr, where, endstatus, errorStatus
	if (strr[i] == " "):
		type1 = " space "
	else:
		print("Lexical error: FIN_digit")
		errorStatus = "error"
		return
	print(strr[i] +  type1  + str(ord(strr[i])) )
	if( (i+1) == len(strr)):
		endstatus = True
		return
	i+=1
	return

def A_symbol():
	pass

while(strr[i]):
	if( errorStatus == "error"):
		break
	elif (endstatus == False):
		if (condition == "start"):
			condition = "continue"
			if (strr[i]=="0"):
				where = "A_digit()"
				A_digit()
			elif (strr[i] in "abcd"):
				A_symbol()
			elif (strr[i] == " "):
				print("Space")
				continue
			else:
				print("Error in begin")
		else:
			if where == "A_digit()":
				A_digit()
			elif where =="B_digit()":
				B_digit()
			elif where =="C_digit()":
				C_digit()
			elif where =="D_digit()":
				D_digit()
			elif where =="E_digit()":
				E_digit()
			elif where =="F_digit()":
				F_digit()
			elif where =="G_digit()":
				G_digit()
			elif where =="FIN_digit()":
				FIN_digit()
	elif (endstatus == True):
		print("End")
		break
