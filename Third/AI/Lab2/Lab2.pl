% === Уравнение прямой ===
% Строим уравнение прямой через две точки (X1,Y1) и (X2,Y2):
% A*x + B*y + C = 0
% где:
%   A = Y1 - Y2
%   B = X2 - X1
%   C = X1*Y2 - X2*Y1
line_equation((X1, Y1), (X2, Y2), A, B, C) :-
    A is Y1 - Y2,
    B is X2 - X1,
    C is X1 * Y2 - X2 * Y1.

% === Пересечение прямой и окружности ===
% Решает систему:
%   A*x + B*y + C = 0
%   (x - Xc)^2 + (y - Yc)^2 = R^2
line_circle_intersections((A, B, C), (Xc, Yc, R), Points) :-
    ( B =\= 0 ->
        % выражаем y = (-A*x - C)/B и подставляем в уравнение окружности
        QA is 1 + (A*A)/(B*B),
        QB is 2*((A*C)/(B*B) + A*Yc/B - Xc),
        QC is Xc*Xc + (C/B + Yc)*(C/B + Yc) - R*R,
        D is QB*QB - 4*QA*QC,
        ( D < 0 ->
            Points = []              % нет пересечений
        ; D =:= 0 ->
            X is -QB / (2*QA),
            Y is (-A*X - C) / B,
            Points = [(X, Y)]
        ; D > 0 ->
            SqrtD is sqrt(D),
            X1 is (-QB + SqrtD) / (2*QA),
            Y1 is (-A*X1 - C) / B,
            X2 is (-QB - SqrtD) / (2*QA),
            Y2 is (-A*X2 - C) / B,
            Points = [(X1, Y1), (X2, Y2)]
        )
    ;
        % если прямая вертикальная (B = 0)
        X is -C / A,
        DX is X - Xc,
        D2 is R*R - DX*DX,
        ( D2 < 0 ->
            Points = []
        ; D2 =:= 0 ->
            Y is Yc,
            Points = [(X, Y)]
        ; SqrtD is sqrt(D2),
          Y1 is Yc + SqrtD,
          Y2 is Yc - SqrtD,
          Points = [(X, Y1), (X, Y2)]
        )
    ).

% === Проверка: точка лежит на отрезке ===
% Чтобы убедиться, что пересечение находится именно на стороне треугольника
point_on_segment((X, Y), (X1, Y1), (X2, Y2)) :-
    X >= min(X1, X2), X =< max(X1, X2),
    Y >= min(Y1, Y2), Y =< max(Y1, Y2).

% === Главный предикат ===
% triangle_circle_intersections((A1,A2,A3), (Xc,Yc,R), Intersections)
% Находит все точки пересечения окружности и треугольника
triangle_circle_intersections(
    (A1, A2, A3),   % три вершины треугольника
    Circle,          % (Xc, Yc, R)
    Intersections    % список точек пересечения
) :-
    findall(P,
        ( member((P1, P2), [(A1, A2), (A2, A3), (A3, A1)]),
          line_equation(P1, P2, A, B, C),
          line_circle_intersections((A, B, C), Circle, Points),
          member(P, Points),
          point_on_segment(P, P1, P2)
        ),
        Intersections).
