; (pick n lst)
;   return the nth item from a list
;   if n > size of list, return '()
(define (pick n lst)
  (if (> n (length lst))
      '()
      (if (= n 1)
          (car lst)
          (pick (- n 1) (cdr lst)))))


; (my-reverse list)
;   return a list that has the same elements as lst, in reverse order
(define (my-reverse lst)
  (define (my-reverse-covariant old-list new-list)
    (if (null? old-list)
        new-list
        (my-reverse-covariant (cdr old-list) (append (list (car old-list)) new-list))))
  (my-reverse-covariant lst '()))


; (deep-reverse lst)
; return a list that has all elements in reverse order, even in sub lists
(define (deep-reverse lst)
  (define (deep-reverse-covariant old-list new-list)
    (if (null? old-list)
        new-list
        (deep-reverse-covariant (cdr old-list) (append (list (if (list? (car old-list))
                                                                 (deep-reverse (car old-list)) ; if element is list, activate recursive sequence
                                                                 (car old-list))) new-list)))) 
  (deep-reverse-covariant lst '()))


; (frontier tree)
; return a list of the leaves of tree in order
(define (frontier tree)
  (if (pair? tree)
      (append (frontier (car tree)) (frontier (cdr tree)))
      (list tree)))
      

      
          
      