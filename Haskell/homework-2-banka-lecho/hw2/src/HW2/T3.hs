module HW2.T3
  ( epart
  , mcat
  ) where

fromMaybe :: Monoid a => Maybe a -> a
fromMaybe (Just x) = x
fromMaybe Nothing = mempty

mcat :: Monoid a => [Maybe a] -> a
mcat = foldMap fromMaybe 

getLeftRight :: (Monoid a, Monoid b) => Either a b -> (a,b)
getLeftRight (Left l) = (l, mempty)
getLeftRight (Right r) = (mempty, r)

epart :: (Monoid a, Monoid b) => [Either a b] -> (a, b)
epart = foldMap getLeftRight