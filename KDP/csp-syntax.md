## Concepts and Notations
<command> ::= <simple command>|<structured command>
<simple command> ::= <null command>|<assignment command>
    |<input command>|<output command>
<structured command> ::= <alternative command>
    |<repetitive command>|<parallel command>
<null command> ::= skip
<command list> ::= {<declaration>; | <command>;} <command>

## Parallel Commands
<parallel command> ::= [<process> {||<process>}]
<process> ::= <process label> <command list>
<process label> ::= <empty>|<identifier> ::
    |<identifier>(<label subscript>{,<label subscript>}) ::
<label subscript> ::= <integer constant>|<range>
<integer constant> ::= <numeral>|<bound variable>
<bound variable> ::= <identifier>
<range> ::= <bound variable>:<lower bound>..<upper bound>
<lower bound> ::= <integer constant>
<upper bound> ::= <integer constant>

## Assignment Commands
<assignment command> ::= <target variable> := <expression>
<expression> ::= <simple expression>l<structured expression>
<structured expression> ::= <constructor>(<expression list>)
<constructor> ::= <identifier>|<empty>
<expression list> ::= <empty>|<expression>{,<expression>}
<target variable> ::= <simple variable>|<structured target>
<structured target> ::= <constructor>(<target variable list>)
<target variable list> ::= <empty>|<target variable>
    {,<target variable>}

## Input and Output Commands
<input command> ::= <source>?<target variable>
<output command> ::= <destination>!<expression>
<source> ::= <process name>
<destination> ::= <process name>
<process name> ::= <identifier>|<identifier>(<subscripts>)
<subscripts> ::= <integer expression>{,<integer expression>}

## Alternative and Repetitive Commands
<repetitive command> ::= *<alternative command>
<alternative command> ::= [<guarded command>
  {□<guarded command>} ]
<guarded command> ::= <guard> -> <command list>
    |(<range>{,<range>})<guard> -> <command list>
<guard> ::= <guard list>|<guard list>;<input command>
    |<input command>
<guard list> ::= <guard element>{;<guard element>}
<guard element> ::= <boolean expression>|<declaration>

