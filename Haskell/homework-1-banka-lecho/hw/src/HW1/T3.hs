module HW1.T3
  ( Tree (..)
  , tsize
  , tdepth
  , tmember
  , tinsert
  , tFromList
  ) where

type Meta = Int 

data Tree a = Leaf | Branch Meta (Tree a) a (Tree a) deriving (Show)

mkBranch :: Tree a -> a -> Tree a -> Tree a
mkBranch left val right = case (left, right) of
  (Leaf, Leaf) -> Branch 1 Leaf val Leaf
  (_, Leaf) -> Branch (1 + tsize left) left val Leaf
  (Leaf, _) -> Branch (1 + tsize right) Leaf val right
  (_, _) -> Branch (1 + tsize left + tsize right) left val right

-- | Size of the tree, O(1).
tsize :: Tree a -> Int
tsize Leaf = 0
tsize (Branch size _ _ _) = size

-- | Depth of the tree.
tdepth :: Tree a -> Int
tdepth Leaf = 0
tdepth (Branch _ left _ right) = 1 + max(tdepth left) (tdepth right)

-- | Check if the element is in the tree, O(log n)
tmember :: Ord a => a -> Tree a -> Bool
tmember _ Leaf = False
tmember element (Branch _ left val right) 
  | element > val = tmember element right
  | element == val = True
  | otherwise = tmember element left 

-- | Insert an element into the tree, O(log n)
tinsert :: Ord a => a -> Tree a -> Tree a
tinsert element Leaf = mkBranch Leaf element Leaf
tinsert element tree@(Branch _ left val right)
  | element > val = mkBranch left val (tinsert element right)
  | element == val = tree
  | otherwise = mkBranch (tinsert element left) val left
  

-- | Build a tree from a list, O(n log n)
tFromList :: Ord a => [a] -> Tree a
tFromList vertexes = case vertexes of
  [] -> Leaf
  x:xs -> tinsert x (tFromList xs)
