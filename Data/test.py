import subprocess
import os
import filecmp
import re
path_dir ='./code'
file_list = os.listdir(path_dir)
file_list.sort()
outputname = "output.txt"
answer = 'answer.txt'
for i in file_list:
		fn = "code/"+i
		print fn
		with open(fn, "r") as file:
			content = file.read()
		content = re.sub(r'system *\( *"pause" *\) *;', '', content)
		content = re.sub(r'fscanf_s','fscanf',content)
		content = re.sub(r'fopen_s','fopen',content)
		content = re.sub(r'fprint_s','fprint',content)
		with open(fn, "w") as file:
			file.write(content)
		subprocess.call(["gcc",fn])
		fo = open(outputname,'w')
		subprocess.call(["./a.out"],stdout=fo)
		with open(outputname,"r") as file:
			content = file.read()
		content = content.replace(' ','')
		content = content.replace('\t','')
		with open(outputname,"w") as file:
			file.write(content)
		fo = open(outputname,'r')
		fa = open('answer.txt','r')
		if filecmp.cmp(outputname,answer,shallow=False):
				print i+"Correct"
		else:
				print i+"Wrong"

