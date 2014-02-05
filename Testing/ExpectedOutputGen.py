numTests = 1


def writeQueue(q, outFile):
	if(len(queue) > 0):
		for i in range(len(queue)):
			if(i == 0):
				testFile.write("Front\t[" + str(queue[0]) + "]")
			else:
				testFile.write(" " + str(queue[i]) )

		testFile.write("\trear\n\n")
	else:
		testFile.write("Empty queue\n\n")



for i in range(0, numTests):
	testFile = open("exp" + str(i), 'w')
	testFile.write(
"Testing array implementation\n\
\n\
Commands:\n\
 H  : Help (displays this message)\n\
  +x : Enqueue x\n\
  -  : Dequeue\n\
  C  : Clear the queue\n\
  E  : Empty queue?\n\
  F  : Full queue?\n\
  >x : Put x at front    (  Active : Programming Exercise 2)\n\
  =  : Get x from rear   (  Active : Programming Exercise 2)\n\
  #  : Length            (  Active : Programming Exercise 3)\n\
  Q  : Quit the test program\n\
  \n\
Empty Queue\n\
\n")
	queue = []
	inFile = open("in" + str(i))
	nextChar = inFile.read(1)
	while(nextChar):
		if(nextChar == '+'):
			nextChar = inFile.read(1)
			queue.append(nextChar)
			testFile.write("Command: Enqueue " + str(nextChar) + "\n")
			for i in range(len(queue)):
				if(i == 0):
					testFile.write("Front\t[" + str(queue[0]) + "]")
				else:
					testFile.write(" " + str(queue[i]) )

			testFile.write("\trear\n\n")

		elif(nextChar == 'c' or nextChar == 'C'):
			testFile.write(
"Command: Clear the queue\n\
Empty queue\n\n")
			for i in range(len(queue)):
				queue.pop()
		
		elif(nextChar == '-'):
			testFile.write("Command: ")
			if(len(queue) < 1):
				testFile.write("Queue is empty\nEmpty queue\n\n")
			else:
				testFile.write("Dequeued " + queue.pop() + "\n")
				if(len(queue) < 1):
					testFile.write("Empty Queue\n\n")
				else:
					writeQueue(queue, testFile)


		elif(nextChar == 'E' or nextChar == 'e'):
			testFile.write("Command: ")
			if(len(queue) > 0):
				testFile.write("Queue is NOT empty\n")
				writeQueue(queue, testFile)
			else:
				testFile.write("Queue is empty\n")
				testFile.write("Empty queue\n\n")

		elif(nextChar == 'F' or nextChar == 'f'):
			testFile.write("Command: ")
			testFile.write("Queue is NOT full\n")
			writeQueue(queue, testFile)

		elif(nextChar == '>'):
			nextChar = inFile.read(1)
			queue.insert(0, nextChar)
			testFile.write("Command: Put " + str(nextChar) + " in front\n")
			writeQueue(queue, testFile)

		elif(nextChar == '='):
			last = len(queue) -1
			testFile.write("Command: Got " + str(queue.pop(last)) + " from rear\n")
			writeQueue(queue, testFile)	
		
		elif(nextChar == '#'):
			testFile.write("Command: Length = " + str(len(queue)) + "\n")
			writeQueue(queue, testFile)

		elif(nextChar == 'q' or nextChar == 'Q'):
			testFile.write("Command:\n")
		
				




		nextChar = inFile.read(1)
		



	inFile.close()
	testFile.close()

