; (define state-spec '(even ((0 . odd)(1 . even))))
; (define state (make-state state-spec))
; (define state-specs '((even ((0 . odd)(1 . even)))(odd ((0 . even)(1 . odd)))))
; (define dfa-spec '(((even ((0 . odd) (1 . even))) (odd ((0 . even) (1 . odd)))) (0 1) even (even)))
; (define dfa (make-dfa dfa-spec))
; ((dfa 'delta-hat) '(1 0 0 1))

(define (make-state state-spec)
  (let
      ((name (car state-spec))
       (transitions (cadr state-spec)))
    
    (define (get-name)
      name)
    
    (define (next-state-name a-letter)
      (cdr (assoc a-letter transitions)))
    
    (define (dispatch msg)
      (cond
        ((eq? msg 'get-name) get-name)
        ((eq? msg 'next-state-name) next-state-name)))
    dispatch))

(define (make-state-assoc state)
  (cons ((state 'get-name)) state))

(define (make-dfa dfa-spec)
  (let
      ((states (map make-state-assoc (map make-state (car dfa-spec))))
       (letters (cadr dfa-spec))
       (start-state-name (caddr dfa-spec))
       (final-state-names (cadddr dfa-spec))
       (current-state-name (caddr dfa-spec)))
    
    (define (reset)
      (set! current-state-name start-state-name))
    
    (define (get-current-state-name)
      current-state-name)
    
    (define (delta letter)
      (set! current-state-name (((cdr (assoc current-state-name states)) 'next-state-name) letter)))
    
    (define (delta-hat lst)
      (if (null? lst)
          #t
          (begin (delta (car lst)) (delta-hat (cdr lst)))))
    
    (define (final?)
      (define (final-helper lst)
        (if (null? lst)
            #f
            (if (eq? current-state-name (car lst))
                #t
                (final-helper (cdr lst)))))
      (final-helper final-state-names))
    
    (define (dispatch msg)
      (cond
        ((eq? msg 'get-current-state-name) get-current-state-name)
        ((eq? msg 'reset) reset)
        ((eq? msg 'delta) delta)
        ((eq? msg 'delta-hat) delta-hat)
        ((eq? msg 'final?) final?)))
    
    dispatch))



      