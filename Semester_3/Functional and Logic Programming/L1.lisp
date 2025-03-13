;;12.
;;a) Write a function to return the dot product of two vectors. https://en.wikipedia.org/wiki/Dot_product
;;b) Write a function to return the maximum value of all the numerical atoms of a list, at any level.
;;c) Write a function to compute the result of an arithmetic expression
;;memorised
;;in preorder on a stack. Examples:
;;(+ 1 3) ==> 4 (1 + 3)
;;(+ * 2 4 3) ==> 11 [((2 * 4) + 3)
;;(+ * 2 4 - 5 * 2 2) ==> 9 ((2 * 4) + (5 - (2 * 2))
;;d) Write a function to return T if a list has an even number of elements on the first level, and NIL on the
;;contrary case, without counting the elements of the list.

;; a) Function to return the dot product of two vectors
;; mathematical (recursive) model:
;; dot-product( (a1 a2 .. an), (b1 b2 .. bn) ) = { 0, if n = 0
;;                                                  a1 * b1 + dot-product( (a2 .. an), (b2 .. bn) ), otherwise } 

(defun dot-product (vec1 vec2)
  (cond
    ((or (null vec1) (null vec2)) 0) ; Base case: end of vectors
    (t (+ (* (car vec1) (car vec2)) (dot-product (cdr vec1) (cdr vec2))))))

;; b) Function to return the maximum value of all the numerical atoms of a list, at any level
;; Mathematical model:
;; max-atom( (a1 a2 .. an) ) = { a1, if n = 1 and a1 is a number
;;                                          mymax(a1, max-atom( (a2 .. an) )), if a1 is a number
;;                                          mymax(max-atom(a1), max-atom( (a2 .. an) )), otherwise }

;; mymax(a1 a2) = { a1, if a1 > a2
;;                 a2, otherwise }


(defun mymax (a b)
  (cond
    ((null a) b) ; If a is nil, return b
    ((null b) a) ; If b is nil, return a
    ( (> a b) a)
    (T b)
  )
)
    
(defun max-atom (lst)
  (cond
    ((null lst) nil) ; Base case: empty list
    ((numberp (car lst)) (mymax (car lst) (or (max-atom (cdr lst)) (car lst)))) ; If first element is a number, return the maximum of it and the rest of the list, treating nil as the current number
    (T (mymax (max-atom (car lst)) (max-atom (cdr lst)))) ; Otherwise, return the maximum of the maximum of the first element and the maximum of the rest of the list
  )
)


;; c) Function to compute the result of an arithmetic expression memorized in preorder on a stack
;; Mathematical model:
;; eval-preorder( (a1 a2 .. an) ) = { a1, if n = 0
;;                                        a1, if a1 is a number
;;                                        a1(eval-preorder( (a2 .. an) ) eval-preorder( (a3 .. an) ) ), if a1 is an operator

;; (defun eval-preorder (stack)
;;   (cond
;;     ((null stack) nil) ; Empty stack
;;     ((numberp (car stack)) (car stack)) ; Single number at the top of the stack
;;     (t ; Process operator and operands
;;      (cond
;;        ((eq (car stack) '+)
;;         (+ (eval-preorder (cdr stack))
;;            (eval-preorder (cddr stack)))) ; Evaluate two operands for +
;;        ((eq (car stack) '-)
;;         (- (eval-preorder (cdr stack))
;;            (eval-preorder (cddr stack)))) ; Evaluate two operands for -
;;        ((eq (car stack) '*)
;;         (* (eval-preorder (cdr stack))
;;            (eval-preorder (cddr stack)))) ; Evaluate two operands for *
;;        ((eq (car stack) '/)
;;         (/ (eval-preorder (cdr stack))
;;            (eval-preorder (cddr stack)))) ; Evaluate two operands for /
;;        (t (error "Unsupported operator: ~A" (car stack)))
;;       )
;;     )
;;   )
;; )

(defun eval-preorder (expr)
  (car (eval-preorder-helper expr)))  ;; Extract the result from the helper function

(defun eval-preorder-helper (expr)
  (cond
    ((null expr) '(0 nil))  ;; Base case: empty list returns (0 nil)
    ((numberp (car expr))  ;; If the first element is a number
     (list (car expr) (cdr expr)))  ;; Return the number and the remaining list
    ((member (car expr) '(+ - * /))  ;; If the first element is an operator
     (let* ((operator (car expr))  ;; Get the operator

            (left-result (eval-preorder-helper (cdr expr)))  ;; Evaluate the left operand
            (left-value (car left-result))  ;; Get the left operand's result
            ;;(rest-after-left (cadr left-result))  ;; Get the remaining list after left operand

            (right-result (eval-preorder-helper (cadr left-result)))  ;; Evaluate the right operand
            (right-value (car right-result))  ;; Get the right operand's result
            (rest-after-right (cadr right-result)))  ;; Remaining list after right operand
       ;; Apply the operator and return the result with the remaining list
       (list (cond ((eq operator '+) (+ left-value right-value))
                   ((eq operator '-) (- left-value right-value))
                   ((eq operator '*) (* left-value right-value))
                   ((eq operator '/) (/ left-value right-value)))
             rest-after-right
        )
      )
    )
  )
)


;; d) Function to return T if a list has an even number of elements on the first level, and NIL otherwise
;; Mathematical model:
;; even-length( (a1 a2 .. an) ) = { T, if n = 0
;;                                   NIL, if n = 1
;;                                   even-length( (a3 a4 .. an) ), otherwise }
(defun even-length (lst)
  (cond
    ((null lst) T) ; Base case: empty list is even
    ((null (cdr lst)) nil) ; Single element: odd
    (T (even-length (cdr (cdr lst)) ))
  )
) ; Skip two elements at a time


;; Example
;;(dot-product '(1 2 3) '(4 5 6)) ; 32
;;(max-atom '(1 2 3 (4 5 6) 7 8 9)) ; 9
;;(eval-preorder '(+ 1 3)) ; 4
;;(eval-preorder '(+ * 2 4 3)) ; 11
;;(even-length '(1 2 3 4 5 6)) ; T
;;(even-length '(1 2 3 4 5)) ; NIL