
module HW3.T2
  ( distOption
  , wrapOption
  , distPair
  , wrapPair
  , distQuad
  , wrapQuad
  , distAnnotated
  , wrapAnnotated
  , distExcept
  , wrapExcept
  , distPrioritised
  , wrapPrioritised
  , distStream
  , wrapStream
  , distList
  , wrapList
  , distFun
  , wrapFun
  ) where

import HW3.T1

distOption :: (Option a, Option b) -> Option (a, b)
distOption (Some _, None) = None
distOption (None, Some _) = None
distOption (None, None) = None
distOption (Some x, Some y) = Some (x, y)

wrapOption :: a -> Option a
wrapOption = Some

distPair :: (Pair a, Pair b) -> Pair (a, b)
distPair (P x1 y1, P x2 y2) = P (x1, x2) (y1, y2)

wrapPair :: a -> Pair a
wrapPair x = P x x

distQuad :: (Quad a, Quad b) -> Quad (a, b)
distQuad (Q x1 y1 z1 k1, Q x2 y2 z2 k2) = Q (x1, x2) (y1, y2) (z1, z2) (k1, k2) 

wrapQuad :: a -> Quad a
wrapQuad x = Q x x x x

distAnnotated :: Semigroup e => (Annotated e a, Annotated e b) -> Annotated e (a, b)
distAnnotated (x :# y, z :# k) = (x, z) :# (y <> k)

wrapAnnotated :: Monoid e => a -> Annotated e a
wrapAnnotated x = x :# mempty

distExcept :: (Except e a, Except e b) -> Except e (a, b)
distExcept (Error x, Error _) = Error x
distExcept (Success x, Success y) = Success (x, y)
distExcept (Error x, Success _) = Error x
distExcept (Success _, Error y) = Error y

wrapExcept :: a -> Except e a
wrapExcept = Success


distPrioritised :: (Prioritised a, Prioritised b) -> Prioritised (a, b)
-- если честно, я не знаю, как избавиться от этой копипасты без Prelude
distPrioritised (Low x, Medium y)    = Medium (x, y)
distPrioritised (Medium x, Low y)    = Medium (x, y)
distPrioritised (Medium x, Medium y) = Medium (x, y)
distPrioritised (Low x, High y)      = High (x, y)
distPrioritised (High x, Low y)      = High (x, y)
distPrioritised (High x, High y)     = High (x, y)
distPrioritised (Medium x, High y)   = High (x, y)
distPrioritised (High x, Medium y)   = High (x, y)
distPrioritised (Low x, Low y)       = Low (x, y)

wrapPrioritised :: a -> Prioritised a
wrapPrioritised = Low

distStream :: (Stream a, Stream b) -> Stream (a, b)
distStream (x :> y, z :> k) = (x, z) :> distStream (y, k)

wrapStream :: a -> Stream a
wrapStream x = x :> wrapStream x

toPairList :: a -> List b -> List (a, b)
toPairList _ Nil = Nil
toPairList x (y :. z) = (x, y) :. toPairList x z

mergeLists :: List (a,b) -> List (a, b) -> List (a, b)
mergeLists Nil z = z
mergeLists (x :. y) z = x :. mergeLists y z

distList :: (List a, List b) -> List (a, b)
distList (Nil, _) = Nil
distList (x :. z, y) = mergeLists t d
  where
    t = toPairList x y
    d = distList (z, y)

wrapList :: a -> List a
wrapList x = x :. Nil

distFun :: (Fun i a, Fun i b) -> Fun i (a, b)
distFun (F g, F h) = F (\x -> (g x, h x))

wrapFun :: a -> Fun i a
wrapFun x = F (const x)

