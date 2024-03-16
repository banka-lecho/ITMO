module HW5.Evaluator
  ( eval
  ) where

import Control.Monad.Except     (ExceptT, MonadError (throwError),
                                           runExceptT)

import HW5.Base                 (HiAction (..), HiError (..),
                                           HiExpr (..), HiFun (..),
                                           HiMonad (runAction), HiValue (..))

-- The line below is commented to prevent build error
-- in project template because of 'redundant constraint' warning.
-- Uncomment this line and use correct function signature
-- while doing the homework.
--
-- eval :: Monad m => HiExpr -> m (Either HiError HiValue)
eval :: HiExpr -> m (Either HiError HiValue)
eval expr = runExceptT (eval' expr)

eval' :: HiMonad m => HiExpr -> ExceptT HiError m HiValue
eval' expr = val