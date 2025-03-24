grammar Grammar;

gram: global* acc* (nontermRule | lexRule)*;
global: VAR;
acc: VARACC;
nontermRule: NONTERM ':=' (alt ('|' alt)*) ';';
alt: (TOKEN CODE? | NONTERM CODE?)* CODE?;
lexRule: TOKEN '=' (STRING_RULE | REGEX_RULE) ';';

CODE: '{' (~[{}]+ CODE?)* '}';
VAR: '$' (~(';'))* ';';
VARACC: '#' (~(';'))* ';';
TOKEN: [A-Z][A-Za-z0-9]*;
NONTERM: [a-z][A-Za-z0-9]*;
STRING_RULE: '\'' (~('\''))+ '\'';
REGEX_RULE: '"' (~('"'))+ '"';
WS: [ \t\r\n]+ -> skip;
