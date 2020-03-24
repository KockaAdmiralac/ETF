while (unos := input().strip()) != '': print(str(eval(unos.replace('&&', ' and ').replace('||', ' or '))).lower())
