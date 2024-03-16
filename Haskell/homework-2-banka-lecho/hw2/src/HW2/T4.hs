{-# LANGUAGE InstanceSigs #-}
module HW2.T4
  ( DotString (..)
  , Fun (..)
  , Inclusive (..)
  , ListPlus (..)
  ) where

data ListPlus a = a :+ ListPlus a | Last a
  deriving Show

infixr 5 :+

instance Semigroup (ListPlus a) where
  (<>) :: ListPlus a -> ListPlus a -> ListPlus a
  (Last x) <> y = x :+ y
  (x :+ z) <> y = x :+ (<>) z y

data Inclusive a b = This a | That b | Both a b
  deriving Show

-- You may necessary constraints there
instance (Semigroup a, Semigroup b) => Semigroup (Inclusive a b) where
  (<>) :: Inclusive a b -> Inclusive a b -> Inclusive a b
  (<>) (This x) (This y)     = This (x <> y)
  (<>) (This x) (That y)     = Both x y
  (<>) (This x) (Both z y)   = Both (x <> z) y
  (<>) (That x) (That y)     = That (x <> y)
  (<>) (That x) (This y)     = Both y x
  (<>) (That x) (Both z y)   = Both z (x <> y)
  (<>) (Both x y) (Both z l) = Both (x <> z) (y <> l)
  (<>) (Both x y) (This z)   = Both (x <> z) y
  (<>) (Both x y) (That z)   = Both x (y <> z)
  
newtype DotString = DS String
  deriving Show

instance Semigroup DotString where
  (<>) :: DotString -> DotString -> DotString
  (<>) (DS "") (DS x) = DS x
  (<>) (DS x) (DS "") = DS x
  (<>) (DS x) (DS y)= DS (x ++ "." ++ y)
  
instance Monoid DotString where
  mempty :: DotString
  mempty = DS ""

newtype Fun a = F (a -> a)

instance Semigroup (Fun a) where
  (<>) :: Fun a -> Fun a -> Fun a
  (<>) (F x) (F y) = F (x . y)

instance Monoid (Fun a) where
  mempty :: Fun a
  mempty = F id
