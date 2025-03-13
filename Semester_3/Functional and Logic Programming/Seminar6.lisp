;;(1 2 3) => (3 6 9)
(defun triple (x) (x 3 x))
(mapcar #'triple '(1 2 3))

(list (triple 1) (triple 2) (triple 3))
(list 3 6 9)
;;(3 6 9)

;;(1 (a (2 b)) 3 4)

(defun triple_l (x)
    (cond
        ((numberp x) (* 3 x))
        ((atom x) x)
        (t (mapcar #'triple_l x))
    )
)

;; triple_l(x) = { 3*x, if x is a number
;;                x, if x is a non-numerical atom
;;                i=1,n  Ui triple_l(xi), if x-list, x = x1, x2, ..., xn }

;; Product of numerical elems in a nonlinear list
;; Ex: (1 a b 2 (1 5 2) 1 1)
;; prod(l) = { l, if l is a number
;;            1, if l is a non-numeric atom
;;            i=1,n, PIi prod(li), if l=l1l2..ln }
;;             prod(l1) * prod(l2) * ... * prod(ln)

(defun prod(l)

    (cond
        ((numberp l ) l)
        ((atom l) 1)
        (t (apply '* (mapcar #'prod l)))
    )

)

;; Compute the number of nodes from the even levels of an n-ary tree repres as (root (subtree1) (subtree2) ... (subtreen)).
;; Root level is 1.
;; Ex (A (B (D (G) (H)) (C (F(J(L))(K))) => 7
;;      A           -- 1
;;     / \
;;    B   C         -- 2
;;   / \   \
;;  D   E   F       -- 3
;; / \   \  / \
;; G H    I J   K     -- 4
;;          /
;;         L           -- 5


;; count(tree, c) = { 0, if tree is an atom and c is odd
;;                   1, if tree is an atom and c is even
;;                   sum(count(ti, c+1)), if tree is a list of subtrees ti }

(defun count(tree c)
    (cond 
        ((and (atom tree) (= (mod c 2) 1)) 0)
        ((atom tree) 1)
        (t (apply '+ (mapcar #'(lambda (ti) (count ti (+ c 1))) tree)))
    )
)


;; Given a nonlinear list, compute the number of sublists (including the initial list)
;; where the FIRST numeric atom is 5 (at any level).
;; Ex. (A 5 (B C D) 2 1 (G (5 H) 7 D) 11 14) => 3
;;      1               2   3
;; => (5 2 1 5 7 11 14), (5)  

;;transform(x) = { (x), if x is a number
;;                (), if x is a non-numeric atom
;;                append(transform(xi)), if x = x1x2...xn (list) }


(defun transform(x)
    (cond

        ((numberp x) (list x))
        ((atom x) nil)
        (t (apply 'append (mapcar #'transform x)))
    )
)

;;check(l) = { 1, if l is a list and the first element is 5
;;             0, otherwise }
;;sublists(x) = { 0, if x - atom
;;                1, if check(transform(x)) = 1
;;                sum(sublists(xi)), if x = x1x2...xn (list) }


(defun check(l)

    (cond
    )
    (if (and (listp l) (= (car l) 5)) 1 0)
)

(defun sublists(x)
    (cond
        ((atom x) 0)
        ((check (transform x)) 1)
        (t (apply '+ (mapcar #'sublists x)))
    )
)

