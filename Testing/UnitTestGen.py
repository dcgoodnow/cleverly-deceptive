import subprocess
bashCommand = "./a.exe < in" + str(0) + " > out" + str(0)
subprocess.call(bashCommand, shell=True)

for i in range(0,20):
	bashCommand = "./a.exe < in" + str(i) + " > out" + str(i)
	subprocess.call(bashCommand, shell=True)
