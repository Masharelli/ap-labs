import re

def get_length(lst):
	return len(re.findall(r'\d+', str(lst)))