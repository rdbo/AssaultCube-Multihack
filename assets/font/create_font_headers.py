import os

for root, dirnames, files in os.walk("."):
	for file in files:
		if file.endswith(".ttf"):
			file_handle = open(file, "rb")
			file_data = file_handle.read()
			file_handle.close()

			file_data_str = ""

			for byte in file_data:
				file_data_str += f"{hex(byte)}, "

			file_data_str = "".join(file_data_str.rsplit(", ", 1)) #Remove last ', '

			font_name = "".join(file.rsplit(".ttf", 1))
			font_name = font_name.replace("-", "_")
			cpp_header = "#pragma once\nconst unsigned char %s[] = { %s };\n" %(font_name, file_data_str)

			header_file = f"{font_name}.h"
			header_handle = open(header_file, "w")
			header_handle.write(cpp_header)
			header_handle.close()