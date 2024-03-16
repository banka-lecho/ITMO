module HW2.T1
(
    Tree(..)
) where


data Tree a = Leaf | Branch !Int (Tree a) a (Tree a) deriving (Show)

tfoldr :: (a -> b -> b) -> b -> Tree a -> b
tfoldr _ n Leaf = n
tfoldr f n (Branch _ left value right) = tfoldr f (f value (tfoldr f n right)) left

treeToList :: Tree a -> [a]    -- output list is sorted
treeToList = tfoldr (:) []
