#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

def main(input):
	start_word = input.readline().strip()

	# ノード作成
	words = dict(((line.strip(), []) for line in input))
	for (k, v) in words.iteritems():
		v[:0] = [item for item in get_nextitem(words, k)]

	#for (k, v) in words.iteritems():
	#	print(k, v)
	#return

	# 探索
	print(start_word)
	win_me(words, [x for x in get_nextitem(words, start_word)], " ")

def get_nextitem(dic, word):
	for k in dic.iterkeys():
		if k[0] == word[-1]:
			yield k

def win_me(dic, choices, indent):
	for choice in choices:
		if choice not in dic:
			continue

		nexts = dic.pop(choice)
		if not win_com(dic, nexts, indent + " "):
			print(indent + choice)
			dic[choice] = nexts
			return True
		dic[choice] = nexts
	return False

def win_com(dic, choices, indent):
	for choice in choices:
		if choice not in dic:
			continue

		nexts = dic.pop(choice)
		if not win_me(dic, nexts, indent + " "):
			dic[choice] = nexts
			return True
		dic[choice] = nexts
	return False

if __name__ == '__main__':
	if len(sys.argv) == 2:
		input = open(sys.argv[1], 'r')
	else:
		input = sys.stdin
	main(input)
