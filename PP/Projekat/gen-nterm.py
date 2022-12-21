from re import compile

NTERM_REGEX = compile(r'^(\w+)\s*::=')

nterms = []

with open('src/rs/etf/pp1/syntax/syntax.cup') as file:
    for line in file:
        match = NTERM_REGEX.match(line)
        if match:
            nterms.append(match.group(1))

print(f'nonterminal {", ".join(nterms)};')
