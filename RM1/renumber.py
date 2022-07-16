from re import match

question_index = None

with open('page.mediawiki') as page:
    for line in page:
        if match(r'^== [^=]+ ==$', line.strip()) is not None:
            question_index = 1
            print(line, end='')
            continue
        question_match = match(r'^=== Pitanje (\d+) ===$', line.strip())
        if question_match is not None:
            if question_index is None:
                raise Exception('Encountered subsection before section')
            print(f'=== Pitanje {question_index} ===')
            question_index += 1
        else:
            print(line, end='')
