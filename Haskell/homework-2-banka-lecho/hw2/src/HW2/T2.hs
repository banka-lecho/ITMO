module HW2.T2
  ( joinWith
  , splitOn
  ) where

import Data.List.NonEmpty (NonEmpty ((:|)))

splitOn :: Eq a => a -> [a] -> NonEmpty [a]
splitOn separator = foldr func ([] :| [])
  where func str (x :| xs)  
             | str == separator = [] :| (x : xs)
             | otherwise = (str : x) :| xs

joinWith :: a -> NonEmpty [a] -> [a]
joinWith separator (first :| second) = concat (first : maping)
  where maping
         = map (separator :) second
