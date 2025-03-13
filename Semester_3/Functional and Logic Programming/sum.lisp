; factorial(n) = 1 if n=0
;                  n* factorial(n-1), if n>0 (otherwise)

(defun factorial (n)
  (cond
   ( (= n 0) 1 )
   ( t         (* n (factorial (-n 1) )) )
  )
)

; suma (l1l2...ln) = 0 if n=0
;                      l1 + suma(l2...ln), otherwise
(defun suma(l)
  (cond
   ( (null l) 0 )
   (t         (+ car (l)) (suma (cdr l)))
  )
)

;sumc(l1l2...ln, c) = c, if n=0
;                        summc(l2..ln, c+l1), otherwise

(defun sumc (l c)
   (cond
     ((null l) c)
     (t        (sumc (cdr l)  (+ c (car l)) ))
    )
)

(defun mainsc (l)
  (sumc l 0)
)