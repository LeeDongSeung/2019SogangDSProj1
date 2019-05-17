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
		with open(fn, "r") as file:
			content = file.read()
		content = re.sub(r'system *\( *"pause" *\) *;', '', content)
		content = re.sub(r'fscanf_s','fscanf',content)
		content = re.sub(r'fopen_s','fopen',content)
		content = re.sub(r'fprint_s','fprint',content)
		with open(fn, "w") as file:
			file.write(content)
		val=subprocess.call(["gcc",fn])
		fo = open(outputname,'w')
		file_list2 = os.listdir('.')
		file_list2.sort()
		flag = 0;
		for j in file_list2:
				if j == "a.out":
						flag =1;
						break;
		if flag == 0:
				print i+"compile error"
				continue
		val =subprocess.call(["./a.out"],stdout=fo)
		if val == -11:
				print "segmentatin fault"+i
				continue;
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
		subprocess.call(["rm","a.out"])

