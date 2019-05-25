import re
import csv

def median(data):
    data.sort()
    half = len(data) // 2
    return (data[half] + data[~half])/2

if __name__ == '__main__':
	filenames = ['init', 'remove_even', 'cancel_Bcast', 'cache']
	title = filenames.copy()
	title.insert(0, 'process')
	out = open('integrate.csv', 'a', newline='')
	csv_write = csv.writer(out, dialect='excel')
	csv_write.writerow(title)
	# for i in range(1,21):
	# 	write_line = []
	# 	for idx, filename in enumerate(filenames):
	# 		txt_name = './output/record.' + filename + '.' + str(i) + '.txt'
	# 		# print(txt_name)
	# 		num_array = []
	# 		line_num = 0
	# 		with open(txt_name, 'r') as file:
	# 			for line in file:
	# 				line = line.rstrip('\n')
	# 				line = re.sub('[ ]+', ' ', line)
	# 				process_num = int(line.split(" ")[0])
	# 				num = line.split(" ")[2]
	# 				num_array.append(float(num))
	# 				line_num += 1
	# 		num_median = median(num_array)
	# 		write_line.insert(idx, num_median)
	# 	write_line.insert(0, process_num)
	# 	csv_write.writerow(write_line)


	for i in range(1,21):
		write_line = []
		for idx, filename in enumerate(filenames):
			txt_name = './output/record.' + filename + '.' + str(i) + '.txt'
			total_num = 0
			line_num = 0
			with open(txt_name, 'r') as file:
				for line in file:
					line = line.rstrip('\n')
					line = re.sub('[ ]+', ' ', line)
					process_num = int(line.split(" ")[0])
					num = line.split(" ")[2]
					total_num+=float(num)
					line_num += 1
			num_avg = total_num / line_num
			write_line.insert(idx, num_avg)
		write_line.insert(0, process_num)
		csv_write.writerow(write_line)