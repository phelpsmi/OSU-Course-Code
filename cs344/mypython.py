import string
import random

random.seed()

file1 = open('file1', 'w+')
file2 = open('file2', 'w+')
file3 = open('file3', 'w+')


string1 = ''
string2 = ''
string3 = ''

for i in range(10):
    string1 += random.choice(string.ascii_lowercase)
    string2 += random.choice(string.ascii_lowercase)
    string3 += random.choice(string.ascii_lowercase)
    
print string1
print string2
print string3

file1.write(string1)
file2.write(string2)
file3.write(string3)


one = random.randint(1,42)
two = random.randint(1,42)

print str(one) + " * " + str(two) + " = " + str(one*two)


