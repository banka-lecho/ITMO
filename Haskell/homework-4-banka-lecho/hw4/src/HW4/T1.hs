module HW4.T1
  ( EvaluationError (..)
  , ExceptState (..)
  , mapExceptState
  , wrapExceptState
  , joinExceptState
  , modifyExceptState
  , throwExceptState
  , eval
  ) where

import HW4.Types
import qualified Control.Monad

data ExceptState e s a = ES { runES :: s -> Except e (Annotated s a) }

mapExceptState :: (a -> b) -> ExceptState e s a -> ExceptState e s b
mapExceptState f es = ES (mapExcept (mapAnnotated f) . runES es)

wrapExceptState :: a -> ExceptState e s a
wrapExceptState x = ES (\st -> wrapExcept (x :# st))

joinExceptState :: ExceptState e s (ExceptState e s a) -> ExceptState e s a
joinExceptState es = ES $ \i ->
  case runES es i of
    Error e          -> Error e
    Success (x :# y) -> runES x y

modifyExceptState :: (s -> s) -> ExceptState e s ()
modifyExceptState f = ES (\st -> Success ( () :# f st))

throwExceptState :: e -> ExceptState e s a
throwExceptState err = ES (\_ -> Error err)

instance Functor (ExceptState e s) where
  fmap = mapExceptState

instance Applicative (ExceptState e s) where
  pure = wrapExceptState
  (<*>) = Control.Monad.ap

instance Monad (ExceptState e s) where
  (>>=) x f = joinExceptState (fmap f x)

data EvaluationError = DivideByZero
  deriving Show

unaryOperation :: Expr -> (Double -> Double) -> (Double -> Prim Double) -> ExceptState EvaluationError [Prim Double] Double
unaryOperation x opExpr opPrim = do
  evalX <- eval x
  modifyExceptState (opPrim evalX :)
  return (opExpr evalX)

binaryOperation :: Expr -> Expr -> (Double -> Double -> Double)  -> (Double -> Double -> Prim Double) -> ExceptState EvaluationError [Prim Double] Double
binaryOperation x y opExpr opPrim = do
  evalX <- eval x
  evalY <- eval y
  modifyExceptState(opPrim evalX evalY :)
  return (opExpr evalX evalY)

eval :: Expr -> ExceptState EvaluationError [Prim Double] Double
eval (Val x)       = return x
eval (Op(Abs x))   = unaryOperation x abs Abs
eval (Op(Sgn x))   = unaryOperation x signum Sgn
eval (Op(Add x y)) = binaryOperation x y (+) Add
eval (Op(Sub x y)) = binaryOperation x y (-) Sub
eval (Op(Mul x y)) = binaryOperation x y (*) Mul
eval (Op (Div x y)) = do
  resX <- eval x
  resY <- eval y
  if resY == 0 then throwExceptState DivideByZero
  else do 
    modifyExceptState (Div resX resY :)
    return (resX / resY)