module HW1.T2
  ( N (..)
  , nplus
  , nmult
  , nsub
  , nFromNatural
  , nToNum
  , ncmp
  , nEven
  , nOdd
  , ndiv
  , nmod
  ) where

import Numeric.Natural

data N = Z | S N

nplus :: N -> N -> N
nplus x Z = x
nplus Z x = x
nplus x (S y) = S (nplus x y) 

nmult :: N -> N -> N
nmult _ Z = Z
nmult Z _ = Z
nmult (S x) y = nplus y (nmult x y) 

nsub :: N -> N -> Maybe N   
nsub x Z = Just x
nsub Z _ = Nothing
nsub (S x) (S y) = nsub x y

ncmp :: N -> N -> Ordering
ncmp Z _ = LT
ncmp _ Z = GT
ncmp Z Z = EQ
ncmp (S x) (S y) = ncmp x y 

nFromNatural :: Natural -> N
nFromNatural 0 = Z
nFromNatural x = S $ nFromNatural (x - 1)

nToNum :: Num a => N -> a
nToNum Z = 0
nToNum (S x) = nToNum x + 1

nEven, nOdd :: N -> Bool  
nEven Z = True
nEven (S Z) = False
nEven (S(S x)) = nEven x

nOdd = not . nEven

ndiv :: N -> N -> N   
ndiv _ Z = error"we arent zero-friendly"
ndiv x y = case nsub x y of
    Nothing -> Z
    Just Z  -> S Z
    Just c  -> S (ndiv c y)

nmod :: N -> N -> N
nmod _ Z = error"we arent zero-friendly"
nmod x y = case nsub x y of
    Nothing -> x
    Just Z -> Z
    Just res -> nmod res y
