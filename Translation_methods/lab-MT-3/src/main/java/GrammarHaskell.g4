grammar GrammarHaskell;

code returns [StringBuilder value]:
     {
        $value = new StringBuilder();
        $value.append("#include <iostream>");
        $value.append("\n");
        $value.append("\n");
     }
     (fd=function{
        $value.append($fd.value);
        $value.append("\n");
        $value.append("\n");
      })+ EOF;

function returns [StringBuilder value]:
    { $value = new StringBuilder(); }
    (header=headerFunc {
        $value = $header.value;
        for (int i = $header.argTypes.size() - 1; i > 0; i--) {
            $value.append($header.argTypes.get(i) + " k" + i + (i == 1 ? ") {\n" : ", "));
        }
    })
    (body=bodyFunc {
        if($body.argsNames == null && $body.argsConiditions == null){
            $value.append($header.argTypes.get(0));
            $value.append($body.body);
        } else if($body.argsNames == null){
            $value.append(") {\n  return " + $body.body + ";\n");
        }else{
            if ($header.argTypes.size() > 1) {
                $value.append("  ");
                for (int i = $header.argTypes.size() - 1; i > 0; i--) {
                    $value.append($header.argTypes.get($header.argTypes.size() - i - 1) + " " + $body.argsNames.get(i - 1) + " = k" + ($header.argTypes.size() - i) + ";\n  ");
                }
                $value.append("if (");
                for (int j = 0; j < $body.argsConiditions.size(); j++) {
                    $value.append($body.argsConiditions.get(j) + (j != $body.argsConiditions.size() - 1 ? " && " : ")"));
                }
                $value.append(" {\n    return " + $body.body + ";\n  }\n");
            } else {
                $value.append($header.argTypes.get(0) + " " + $body.argsNames.get(0) + " = " + $body.body);
            }
        }
    })*
    {$value.append("}");};


headerFunc returns [StringBuilder value, ArrayList<String> argTypes]:
    WORD DOUBLECOLON type {
        $value = new StringBuilder();
        $argTypes = $type.value;
        $value.append($argTypes.get(0) + ' ' + $WORD.text + "(");
    };

bodyFunc returns [String body, ArrayList<String> argsNames, ArrayList<String> argsConiditions]:
    f=WORD x=WORD EQ LET xa=WORD expf=expression IN exps=expression {
        $body = " " + $xa.text + " = " + $expf.text + "; \n  return" + $exps.text + "; \n";
    }
    | WORD ad=args EQ localStatement {
        $body = $localStatement.text;
        $argsNames = $ad.argsNames;
        $argsConiditions = $ad.argsConiditions;
    };

type returns [ArrayList<String> value]:
    TYPE {
        $value = new ArrayList<String>();
        if (!($TYPE.text.equals("Integer") || $TYPE.text.equals("Double") || $TYPE.text.equals("String") || $TYPE.text.equals("Bool"))) {
            $value.add($TYPE.text);
        } else {
            $value.add($TYPE.text.toLowerCase());
        }
    }
    | TYPE '->' tp=type {
        $value = $tp.value;
        if (!($TYPE.text.equals("Integer") || $TYPE.text.equals("Double") || $TYPE.text.equals("String") || $TYPE.text.equals("Bool"))) {
            $value.add($TYPE.text);
        } else {
            $value.add($TYPE.text.toLowerCase());
        }
    };

args returns [ArrayList<String> argsNames, ArrayList<String> argsConiditions]:
    oneArg (COMMA ar=args {
        $argsNames = $ar.argsNames;
        $argsConiditions = $ar.argsConiditions;
    } | {
        $argsNames = new ArrayList<String>();
        $argsConiditions = new ArrayList<String>();
    }) {
        $argsNames.add($oneArg.argName);
        if ($oneArg.argCondition != null)
            $argsConiditions.add($oneArg.argCondition);
    }
    | {
        $argsNames = null;
        $argsConiditions = null;
    };


oneArg returns [String argName, String argCondition] :
    LB oa=oneArg RB {
        $argName = $oa.argName;
        $argCondition = $oa.argCondition;
    }
    | WORD STICK condition {
        $argName = $WORD.text;
        $argCondition = $condition.text;
    }
    | WORD {
        $argName = $WORD.text;
        $argCondition = "true";
    };

data : INTEGER | DOUBLE | BOOL | WORD | WORD LB (expression (COMMA expression)*)? RB | LET WORD EQ expression IN expression;

localStatement : data EQ expression | expression;

condition :
    expression LESS condition |
    expression LESSEQUAL condition |
    expression GREATER condition |
    expression GREATEREQUAL condition |
    expression AND condition |
    expression OR condition |
    expression DEQ condition |
    expression;

expression :
    data PLUS expression |
    data MINUS expression |
    data DIV expression |
    data MUL expression |
    data MOD expression |
    data;

TYPE : 'Integer' | 'Double' | 'String' | 'Bool';
INTEGER : '-'?[0-9]+;
DOUBLE  : INTEGER '.' [0-9]*;
BOOL : 'True' | 'False';
WORD : [a-zA-Z] [a-zA-Z0-9]*;

WS : [ \t\r\n]+ -> skip;

COMMA  : ',';
LB     : '(';
RB     : ')';
COLON  : ':';
DOUBLECOLON : '::';
SEMICOLON : ';';
EQ     : '=';
STICK  : '|';
ARROW  : '->';

PLUS  : '+';
MINUS : '-';
DIV   : '/';
MUL   : '*';
MOD   : '%';
LET   : 'let';
IN    : 'in';

OR : '||';
AND : '&&';
LESS : '<';
LESSEQUAL : '<=';
GREATEREQUAL : '>=';
GREATER : '>';
DEQ : '==';