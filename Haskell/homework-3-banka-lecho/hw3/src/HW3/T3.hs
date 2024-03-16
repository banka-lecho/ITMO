module HW3.T3
  ( joinOption
  , joinExcept
  , joinAnnotated
  , joinList
  , joinFun
  ) where

import HW3.T1

joinOption :: Option (Option a) -> Option a
joinOption None = None
joinOption (Some None) = None
joinOption (Some (Some x)) = Some x

joinExcept :: Except e (Except e a) -> Except e a
joinExcept (Error x) = Error x
joinExcept (Success (Error x)) = Error x
joinExcept (Success (Success x)) = Success x

joinAnnotated :: Semigroup e => Annotated e (Annotated e a) -> Annotated e a
joinAnnotated ((x :# y) :# z) = x :# (z <> y)

joining :: List a -> List a -> List a 
joining Nil x = x
joining x Nil = x
joining (x :. y) k = x :. joining y k

joinList :: List (List a) -> List a
joinList Nil = Nil
joinList (x :. y) = joining x (joinList y)

innerFunc :: i -> Fun i a -> a
innerFunc x (F f) = f x

joinFun :: Fun i (Fun i a) -> Fun i a
joinFun (F g) = F (\x -> innerFunc x (g x))
