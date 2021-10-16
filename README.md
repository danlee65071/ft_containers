# ft_containers Методичка

## Содержание:
* [О чем проект?](#what_project?)
* [Немного о SFINAE](#SFINAE)
* [Итераторы](#Iterators)

## О чем проект? <a name = "what_project?"></a>
Реализовать структуры данных из стандартной библиотеки C++98 STL (vector, map, stack, set). Ниже я постараюсь объяснить, как это все реализовано.

## SFINAE <a name = "SFINAE"></a>
***SFINAE (substitution failure is not an error, неудавшаяся подстановка - не ошибка)*** - правило языка C++, связанное с шаблонами и перегрузкой функций.

***Правило SFINAE:***

Если не получается рассчитать окончательные типы/значения шаблонных параметров функции, компилятор не выбрасывает ошибку, а ищет другую подходящую перегрузку.

***Метапрограммирование*** - вид програмиироания, связанный с созданием программ, которые порождают другие программы как результат своей работы, либо программ, которые меняют себя во время выполнения.

В механизме SFINAE управление функциями происходит при помощи шаблонов.

Ошибки будут в следующих случаях:
* Не нашлось ни одной подходящей перегрузки.
* Нашлось несколько таких перегрузок, и компилятор не может решить, какую взять.
* Перегрузка нашлась, она оказалась шаблонной, и при инстанцировании шаблона случилась ошибка.

## Итераторы  <a name = "Iterators"></a>
***Итератор*** - интерфейс, предоставляющий доступ к элементам коллекции (массива или контейнера) и навигацию по ним.
***Виды итераторов:***
1) InputIterator <- ForwardIterator <- BidirectionalIterator <- RandomAccessIterator   
***InputIterator*** - гарантирует только одного прохождения для контейнеров. Выражения: i == j, i != j, *i, i->n, ++i, i++.
***ForwardIterator*** - гарантирует многопроходность для контейнеров. Выражения: те же выражения, что у InputIterator.
***BidirectionalIteraator*** - гарантирует перемещение в обоих направлениях. Выражения: те же выражения, что у ForwardIterator и --i, i--.
***RandomAccesIterator*** - гарантирует доступ к любому элементу контейнера за O(1). Выражения: те же выражения, что у BidirectionalIterator и i += n, i + n, i -=n, i - j, i[k], i < j, i > j, i >= j, i <= j.
где:

i, j - итераторы,
n, k - целые числа.

  
