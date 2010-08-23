#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def main(input):
	# 開始文字
	start_word = input.readline().strip()

	# 開始文字と終端文字のみにする
	words = [line[0] + line.strip()[-1] for line in input]
	# 反転した単語がある場合は、除外
	clean_words = [item for item in words if item[::-1] not in words]

	# 開始辞書
	dic = {}
	for i in range(ord('a'), ord('z') + 1):
		key = chr(i)
		dic[key] = [item for item in clean_words if item[0] == key]

	# 探索
	print start_word
	win_me(dic, start_word[-1], " ")

def print_dic(dic):
	for (k, v) in dic.iteritems():
		print(k, len(v), v)

def win_me(dic, c, indent):
	choices = list(dic[c])
	for choice in choices:
		dic[c].remove(choice)
		if not win_com(dic, choice[-1], indent + " "):
			print(indent + choice)
			dic[c].append(choice)
			return True
		dic[c].append(choice)
	return False

def win_com(dic, c, indent):
	choices = list(dic[c])
	for choice in choices:
		dic[c].remove(choice)
		if not win_me(dic, choice[-1], indent):
			dic[c].append(choice)
			return True
		dic[c].append(choice)
	return False

if __name__ == '__main__':
	if len(sys.argv) == 2:
		input = open(sys.argv[1], 'r')
	else:
		input = sys.stdin
	main(input)
