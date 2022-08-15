text = [i for i in input("Enter the main String: ")]
lt = len(text)
pattern = [i for i in input("Enter the Pattern: ")]
lp = len(pattern)
occurences = [999];
temp = [999]
for i in pattern:
    if i not in temp:
        temp.append(i)
        occurences.append(0)
    else:
        temp.append('\0')
        occurences.append(temp.index(i))
pattern.insert(0, '\0')
print(pattern, occurences)

i = 0; j = 0;
while(i < lt):
    if(text[i] == pattern[j + 1]):
        i += 1; j += 1;
        if(j == lp):
            print("Pattern found at index", i - lp, "of the main string")
            break

    elif((text[i] != pattern[j + 1]) and j != 0):
        j = occurences[j]
    elif(text[i] != pattern[j + 1]) and j == 0:
        i += 1

if(j < lp):
    print("Pattern not found...")