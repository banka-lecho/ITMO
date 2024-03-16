module HW5.Parser
  ( parse
  ) where

import Data.Void (Void)
import Text.Megaparsec

data HiFun = HiFunDiv
  | HiFunMul
  | HiFunAdd
  | HiFunSub
  deriving (Eq, Ord, Enum, Bounded)
 
 
data HiValue = HiValueNumber Rational
  | HiValueFunction HiFun
  deriving (Eq, Ord)
 
data HiExpr = HiExprValue HiValue
  | HiExprApply HiExpr [HiExpr]
  deriving (Eq, Ord)
 
data HiError = HiErrorInvalidArgument
  | HiErrorInvalidFunction
  | HiErrorArityMismatch
  | HiErrorDivideByZero
  deriving (Eq, Ord)

--------------------------------------------------------------

parse :: String -> Either (ParseErrorBundle String Void) HiExpr
parse = runParser parse' ""

parse' :: Parser HiExpr
parse' = do
  expr <- parse''
  _ <- skipSpace eof
  return expr

-- token нужен для парсера всех штук кроме операций (типа: переменные, числа и тд)
-- operTable нужен для парсинга операций, которые мы определили
parse'' :: Parser HiExpr
parse'' = makeExprParser token' operTable

operTable :: [[Operator Parser HiExpr]]
operatorTable =
  [ [ binL "*" HiFunMul
    , binLNotFollow "/" HiFunDiv "="
    ]
  , [ binL "+" HiFunAdd
    , binL "-" HiFunSub
    ]
  ]
  where
     binary :: (Parser (HiExpr -> HiExpr -> HiExpr) -> Operator Parser HiExpr) -> HiFun -> String -> Operator Parser HiExpr
     binary infx f str = infx $ (\a b -> HiExprApply (HiExprValue $ HiValueFunction f) [a, b]) <$ (lexeme . try) (string name <* notFollowedBy "=")

     binL :: HiFun -> String -> Operator Parser HiExpr
     binL = binary InfixL

type Parser = Parsec Void String

-- переписать 
hiNum :: Parser Rational
hiNum = toRational <$> L.signed space L.scientific

hiBool :: Parser Bool
-- пробует один, потом другой 
hiBool = False <$ string "false" <|> True <$ string "true"

atom :: Parser HiValue
-- слева указывается конструктор HiValue, справа указывается парсер (каждый парсер нужно еще написать)
atom = choice
  [ HiValueBool <$> hiBool
  , HiValueNumber <$> hiNum
  ]