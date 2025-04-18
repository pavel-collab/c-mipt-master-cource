## Структура данных куча

Среди структур данных существуем множество видов куч. По-сути, отличаются они только реализацией, при этом, все удовлетвряют единому интерфейсу: 
интерфейс очереди с приоритетом. Основная задача этого интерфейса -- сохранять данные таким образом, чтобы можно было извлечь максимальный (или минимальный)
элемент за константное время. Такой интерфейс может пригодиться в различных задачах, например, в оптимизированном алгоритме Дейкстры. Рассмотрим чуть подробнее конкретные реализации интерфейса.

### Двоичная куча

По-сути представляет собой двоичное дерево, где в корне всегда находится максимальный (минимальный элемент). Сами данные удобно хранить в 
динамическом массиве, а консистентность структуры данных определяется методами сдвига элементов (shiftUp и shiftDown).

### Биномиальная куча

В отличие от простой двоичной кучи биномиальная куча состоит из нескольких деревьев. Биномиальная куча может быть различных рангов, начиная от $k = 0$.
Строится биномиальная куча следующим образом: биномиальная куча ранга $k = 0$ это просто одна единственная вершина, биномиальная куча ранга $k > 0$ это
структура данных, состоящая из двух биномиальных куч рангов $T_{k-1}$ так, что корень одной кучи является потомком корня второй кучи.

При этом в каждой биномиальной куче любого ранга поддерживается свойство кучи, то есть любой потомок не больше (не меньше) своего предка.

![Пример биномиальной кучи](/10.05/images/BinHeapExample.png)

### Фибоначева куча

Фиббоначева куча умеет делать все то же самое, что биномиальная куча, но только быстрее с точки зрения ассимптотики.
Точно так же, как в биномиальной куче, фиббоначева куча это список деревьев, каждое из которых удовлетворяет свойству кучи. В отличие от биномиальной кучи
здесь используется другой метод связи предка с потомками: хранится ссылка только на левого потомка, в все остальные потомки связаны
с левым через двусвязнй список.

![Пример фибоначевой кучи](/10.05/images/Fibonacci-heap.png)