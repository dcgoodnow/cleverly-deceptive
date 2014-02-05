import subprocess
for i in range(0,20):
	subprocess.call("cp in0 in" + str(i), shell=True)
