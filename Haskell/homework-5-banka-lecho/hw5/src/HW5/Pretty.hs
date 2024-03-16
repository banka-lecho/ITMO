module HW5.Pretty
  ( prettyValue
  ) where

import Prettyprinter (Doc)
import Prettyprinter.Render.Terminal (AnsiStyle)

import HW5.Base (HiValue)

prettyValue :: HiValue -> Doc AnsiStyle
prettyValue (HiValueBool b) = preety (toBoolString boo)
prettyValue (HiValueNum n) = preety (toNumString n)
prettyValue HiValueNull = pretty "null"


toBoolString :: Bool -> String
toBoolString False = "false"
toBoolString True = "true"

toNumString :: Rational -> String
toNumString n =
    let (a, b) = fromRationalRepetendUnlimited n in
        case b of
            Just _ -> fr (numerator n) (denominator n)
            Nothing ->
                if isInteger a
                    then numerator n
                else formatScientific Fixed Nothing a

fr :: Integer -> Integer -> Doc AnsiStyle
fr a b =
    let (w, r) = quotRem a b in
        let frac = show (abs r) ++ "/" ++ show b in
            if w == 0
                then
                    if r < 0
                        then "-" ++ frac
                    else frac
            else show w ++
                if r < 0
                    then " - " ++ frac
                else " + " ++ frac
