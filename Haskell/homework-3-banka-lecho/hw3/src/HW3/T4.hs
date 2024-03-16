module HW3.T4
  ( State (..)
  , Prim (..)
  , Expr (..)
  , mapState
  , wrapState
  , joinState
  , modifyState
  , eval
  ) where

import HW3.T1
import qualified Control.Monad

newtype State s a = S { runS :: s -> Annotated s a }

mapState :: (a -> b) -> State s a -> State s b
mapState f s = S (mapAnnotated f . runS s)

wrapState :: a -> State s a
wrapState x = S (x :#)

joinState :: State s (State s a) -> State s a
joinState st = S (\i -> let (x :# y) = runS st i in runS x y)

modifyState :: (s -> s) -> State s ()
modifyState f = S (\st -> () :# f st)

instance Functor (State s) where
  fmap = mapState

instance Applicative (State s) where
  pure = wrapState
  (<*>) = Control.Monad.ap

instance Monad (State s) where
  (>>=) x f = joinState (fmap f x)

data Prim a =
    Add a a
  | Sub a a
  | Mul a a
  | Div a a
  | Abs a
  | Sgn a
  deriving Show

data Expr = Val Double | Op (Prim Expr)
  deriving Show

instance Num Expr where
  (+) x y  = Op (Add x y)
  (-) x y  = Op (Sub x y)
  (*) x y  = Op (Mul x y)
  abs x    = Op (Abs x)
  signum x = Op (Sgn x)
  fromInteger x = Val (fromInteger x)

instance Fractional Expr where
  (/) x y = Op (Div x y)
  fromRational x = Val (fromRational x)

unaryOperation :: Expr -> (Double -> Double) -> (Double -> Prim Double) -> State [Prim Double] Double
unaryOperation x opExpr opPrim = do
  evalX <- eval x
  modifyState (opPrim evalX :)
  return (opExpr evalX)

binaryOperation :: Expr -> Expr -> (Double -> Double -> Double)  -> (Double -> Double -> Prim Double) -> State [Prim Double] Double
binaryOperation x y opExpr opPrim = do
  evalX <- eval x
  evalY <- eval y
  modifyState (opPrim evalX evalY :)
  return (opExpr evalX evalY)

eval :: Expr -> State [Prim Double] Double
eval (Val x)       = return x
eval (Op(Abs x))   = unaryOperation x abs Abs
eval (Op(Sgn x))   = unaryOperation x signum Sgn
eval (Op(Add x y)) = binaryOperation x y (+) Add
eval (Op(Sub x y)) = binaryOperation x y (-) Sub
eval (Op(Mul x y)) = binaryOperation x y (*) Mul
eval (Op(Div x y)) = binaryOperation x y (/) Div


