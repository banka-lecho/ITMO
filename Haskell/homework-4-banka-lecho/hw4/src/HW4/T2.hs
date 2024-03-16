{-# LANGUAGE BlockArguments             #-}
{-# LANGUAGE DerivingStrategies         #-}
{-# LANGUAGE GeneralizedNewtypeDeriving #-}

module HW4.T2
  ( ParseError (..)
  , Parser (..)
  , pChar
  , pEof
  , parseError
  , parseExpr
  , runP
  ) where

import HW4.Types
    ( Annotated((:#)), Except(..), Expr(..), Prim(Div, Add, Sub, Mul) )
import HW4.T1 (ExceptState (ES, runES))
import GHC.Float.RealFracMethods (int2Double)
import Control.Applicative 
import Control.Monad ( MonadPlus, mfilter ) 
import GHC.Natural (Natural)
import Data.Char

newtype ParseError = ErrorAtPos Natural deriving Show

newtype Parser a = P (ExceptState ParseError (Natural, String) a)
  deriving newtype (Functor, Applicative, Monad)

runP :: Parser a -> String -> Except ParseError a
runP (P parser) d = case runES parser (0, d) of
        (Error e) -> Error e
        (Success (x :# _)) -> Success x

pChar :: Parser Char
pChar = P $ ES $ \(pos, s) ->
  case s of
    []     -> Error (ErrorAtPos pos)
    (c:cs) -> Success (c :# (pos + 1, cs))

parseError :: Parser a
parseError = P (ES \(ind, _) -> Error (ErrorAtPos ind))

instance Alternative Parser where
        empty = parseError
        (<|>) (P a) (P b) = P (ES \(ind, x) ->
            case runES a (ind, x) of
                Success s -> Success s
                Error _ -> runES b (ind, x))

instance MonadPlus Parser   -- No methods.

pEof :: Parser ()
pEof = P (ES (\(ind, x) -> case x of
          [] -> Success (() :# (ind, x))
          _  -> Error (ErrorAtPos ind)))


parseExpr :: String -> Except ParseError Expr
parseExpr = runP (skipWightSpace *> parsePart <* skipWightSpace <* pEof)


pInt :: Parser Int
pInt = do
  int <- some (mfilter isDigit pChar)
  return (parseInt int)

parseInt :: String -> Int
parseInt str = foldl (\acc x -> acc * 10 + x) 0 (map digitToInt str)

parseFrac :: Parser Double
parseFrac = do
  frac <- some (mfilter isDigit pChar)
  return $ let int = int2Double (parseInt frac) in foldr (\_ acc -> acc / 10) int frac

pNegativeNumber :: Parser Double
pNegativeNumber = do
  minus <- optional $ check '-'
  number <- parseNumber
  case minus of
    Just '-' -> return (-1 * number)
    _ -> return number   

parseNumber :: Parser Double
parseNumber = do
  int <- pInt
  dot <- optional $ check '.'
  case dot of
    Just '.' -> do 
      frac <- parseFrac
      return (int2Double int + frac)
    _  -> return (int2Double int)

parsePart :: Parser Expr
parsePart = do
          a <- parsePar 
          parseAddSub a <|> pure a

parseAddSub :: Expr -> Parser Expr
parseAddSub x = do
          pm <- skipWightSpace *> (<|>) (check '+') (check '-') <* skipWightSpace
          y <- parsePar
          c <- operation x y pm
          parseAddSub c <|> pure c 

parseMulDiv :: Expr -> Parser Expr
parseMulDiv x = do
          ud <- skipWightSpace *> (<|>) (check '*') (check '/') <* skipWightSpace
          y <- (parseParenthesis <|> fmap Val pNegativeNumber) <* skipWightSpace
          c <- operation x y ud
          parseMulDiv c <|> pure c 


parsePar :: Parser Expr
parsePar = do
          a <- skipWightSpace *> parseParenthesis <* skipWightSpace
          parseMulDiv a <|> pure a       


operation :: Expr -> Expr -> Char -> Parser Expr
operation x y s = case s of
          '+' -> pure (Op (Add x y))
          '-' -> pure (Op (Sub x y))
          '*' -> pure (Op (Mul x y))
          '/' -> pure (Op (Div x y))
          _  -> parseError


parseParenthesis :: Parser Expr
parseParenthesis = (<|>) (fmap Val pNegativeNumber) (check '(' *> parsePart <* check ')')

check :: Char -> Parser Char
check s = mfilter (s ==) pChar

skipWightSpace :: Parser String
skipWightSpace = many (mfilter isSpace pChar)