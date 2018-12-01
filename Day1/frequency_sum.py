f = open('input.dat')
s = f.read().split('\n')
print(sum([int(i) for i in s[:-1]]))
