; Merge tso sorted linear lists without keeping double values
; Ex. (1 2 3 4), (2 3 5 7) => (1 2 3 4 5 7)

;merge_lists(l1l2..ln, k1k2..km) = l1l2..ln, m=0
;                                   k1k2..km, n=0
;                                   l1 U merge_lists(l2..ln, k1..km), l1<k1
;                                   k1 U merge_lists(l1..ln, k2..km), l1>k1
;                                   l1 U merge_lists(l2..ln, k2..km), otherwise


(defun mymerge(l k)
  (cond
      ((NULL l) k)
      ((NULL k) l)
      ((< (car l) (car k)) (cons (car l) mymerge(cdr l) k ))
      ((> (car l) (cark) )) (cons (car k) mymerge l (cdr k))
      (+ (cons (car l) (mymerge(cdr l)(cdr k))))
   )
)

; Remove all occurences of an element from a nonlinear list
; Ex: e=1, (1 2 7 (4 5 (6 1) 1 ) 3 (((1) 2)) ) => (2 7 (4 5 (6) ) 3 ((() 2)) )
; removeEl(l1l2..ln, el) = [], list is empty
;                          removeEl(l2..ln, el), l1 - atom & l1 = el
;                          l1 U removelEl(l2..ln, el), l1-atom & l1 != el
;                          removeEl(l1, el) U removeEl(l2..ln, el), l1=list

(defun removeEl(l el)
   (cond
      ((null l) nil)
      (and (atom (car (l)) (= el car(l))  ) removeEl(cdr(l) el)
      
      (and () () )
      ((atom (car l)) (cons (car l) (removeEl( (cdr l) el)))
      (+ (cons (reomveEl (car l) el)( removeEl(cdr l) el)))
   )
)

; Build a list with the positions of the minimum number from a linear list
; Ex: (1 2 0 a 4 0 n 1 7) => (3 6)

; getMin(l1..ln) = { l1, n = 1
;                    min(l1, getMin(l2..ln)) n>1, l1 number
;                    getMin(l2..ln), otherwise }
; getPos(l1..ln, p, el) = { [], n=0
;                           [p] U getPos(l2..ln, p+1, el), l1 = el
;                    getPos(l2..ln), otherwise
; buildList(l1..ln) = getPos(l1..ln, 1, getMin(l1..ln))

(defun getMin(l)
    (cond
        ((null (cdr l)) (car l))
        ((numberp (car l)) (min (car l) (getMin(cdr l)) ) )
        (T (getMin(cdr l)))
    )
)

(defun getPos(l pos el)
   (cond
       ( (null l) nil )
       ((equal el (car l)) (cons pos (getPos (cdr l) (+ pos 1) el)) )
       (T (getPos(cdr l)))
   )
) 

(defun buildlist(l)
  (getPos l 1 (getMin(l)))
)